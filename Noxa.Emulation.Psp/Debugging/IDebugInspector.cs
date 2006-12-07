// ----------------------------------------------------------------------------
// PSP Player Emulation Suite
// Copyright (C) 2006 Ben Vanik (noxa)
// Licensed under the LGPL - see License.txt in the project root for details
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;

namespace Noxa.Emulation.Psp.Debugging
{
	public interface IDebugInspector
	{
		void Update( int newAddress );

		CallstackFrame[] Callstack
		{
			get;
		}

		void PushCall( int address, string name );
		void PopCall();
	}
}
