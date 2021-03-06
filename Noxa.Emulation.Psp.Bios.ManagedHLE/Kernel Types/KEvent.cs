// ----------------------------------------------------------------------------
// PSP Player Emulation Suite
// Copyright (C) 2006 Ben Vanik (noxa)
// Licensed under the LGPL - see License.txt in the project root for details
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace Noxa.Emulation.Psp.Bios.ManagedHLE
{
	enum KEventAttributes
	{
		/// <summary>
		/// Allow multiple threads to wait on the event.
		/// </summary>
		KEventWaitMultiple = 0x200,
	}

	enum KWaitType
	{
		/// <summary>
		/// Wait for all bits to be set.
		/// </summary>
		And = 0x00,
		/// <summary>
		/// Wait for one or more bits to be set.
		/// </summary>
		Or = 0x01,
		/// <summary>
		/// Clear the entire bitmask when it matches.
		/// </summary>
		ClearAll = 0x10,
		/// <summary>
		/// Clear the just the matched pattern when it matches.
		/// </summary>
		ClearPattern = 0x20,
	}

	class KEvent : KHandle
	{
		public Kernel Kernel;
		
		public string Name;
		public KEventAttributes Attributes;
		public uint InitialValue;
		public uint Value;

		public FastLinkedList<KThread> WaitingThreads;

		public KEvent( Kernel kernel, string name, KEventAttributes attributes, uint initialValue )
		{
			Kernel = kernel;
			Name = name;
			Attributes = attributes;
			InitialValue = initialValue;
			Value = initialValue;

			WaitingThreads = new FastLinkedList<KThread>();
		}

		public bool Matches( uint userValue, KWaitType waitType )
		{
			if( ( ( int )waitType & 0x1 ) == ( int )KWaitType.And )
			{
				// &
				return ( Value & userValue ) == userValue;
			}
			else
			{
				// |
				Debug.Assert( ( waitType & KWaitType.Or ) == KWaitType.Or );
				return (Value & userValue) > 0;
			}
		}

		public bool Clear(uint userValue, KWaitType waitType)
		{
			if ((waitType & KWaitType.ClearAll) != 0)
			{
				this.Value = 0;
				return true;
			}
			else if ((waitType & KWaitType.ClearPattern) != 0)
			{
				this.Value = this.Value & ~userValue;
				return true;
			}

			return false;
		}

		public bool Signal()
		{
			bool needsSwitch = false;

			LinkedListEntry<KThread> e = WaitingThreads.HeadEntry;
			while( e != null )
			{
				LinkedListEntry<KThread> next = e.Next;

				KThread thread = e.Value;
				Debug.Assert( thread != null );
				Debug.Assert( thread.WaitingOn == KThreadWait.Event );
				Debug.Assert( thread.WaitHandle == this );

				bool matches = this.Matches( thread.WaitArgument, thread.WaitEventMode );
				if( matches == true )
				{
					// Finish wait
					if( thread.WaitAddress != 0x0 )
					{
						unsafe
						{
							uint* poutBits = ( uint* )Kernel.MemorySystem.Translate( thread.WaitAddress );
							*poutBits = this.Value;
						}
					}

					this.Clear(thread.WaitArgument, thread.WaitEventMode);

					WaitingThreads.Remove( e );

					// Wake thread
					thread.Wake( 0 );

					needsSwitch = true;
				}

				e = next;
			}

			return needsSwitch;
		}
	}
}
