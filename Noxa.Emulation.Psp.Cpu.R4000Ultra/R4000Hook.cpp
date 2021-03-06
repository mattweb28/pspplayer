// ----------------------------------------------------------------------------
// PSP Player Emulation Suite
// Copyright (C) 2006 Ben Vanik (noxa)
// Licensed under the LGPL - see License.txt in the project root for details
// ----------------------------------------------------------------------------

#include "StdAfx.h"
#include "R4000Hook.h"
#include "R4000Cpu.h"

using namespace System::Diagnostics;
using namespace System::Reflection;
using namespace System::Text;
using namespace Noxa::Emulation::Psp;
using namespace Noxa::Emulation::Psp::Cpu;
using namespace Noxa::Emulation::Psp::Debugging;

extern R4000Ctx* _cpuCtx;

#ifdef DEBUGGING
// In R4000Controller
void SetBreakpoint( Breakpoint^ breakpoint );
void UnsetBreakpoint( Breakpoint^ breakpoint );
#endif

R4000Hook::R4000Hook( R4000Cpu^ cpu )
{
	this->Cpu = cpu;

	this->Breakpoints = gcnew List<Breakpoint^>();
	this->SteppingBreakpoints = gcnew List<Breakpoint^>();
}

// -- Breakpoints --

void R4000Hook::RefreshBreakpointTable()
{
	//// We assume we have free reign over everything now (no codegen, etc)
	//Monitor::Enter( this->Breakpoints );
	//try
	//{
	//	this->BreakpointLookup->Clear();
	//	for each( KeyValuePair<int, Breakpoint^>^ pair in this->Breakpoints )
	//	{
	//		uint address;
	//		switch( pair->Value->Type )
	//		{
	//		case BreakpointType::CodeExecute:
	//			address = pair->Value->Address;
	//			break;
	//		case BreakpointType::BiosFunction:
	//			if( pair->Value->CachedFunction == nullptr )
	//			{
	//				pair->Value->CachedFunction = this->Cpu->Emulator->Bios->FindFunction( pair->Value->Function );
	//				if( pair->Value->CachedFunction == nullptr )
	//				{
	//					Log::WriteLine( Verbosity::Critical, Feature::Debug, "function {0} not registered - cannot set breakpoint yet", pair->Value->Function );
	//					continue;
	//				}
	//			}
	//			if( pair->Value->CachedFunction->StubAddress == 0x0 )
	//			{
	//				Log::WriteLine( Verbosity::Critical, Feature::Debug, "stub address for {0} not found (unused?) - cannot set breakpoint yet", pair->Value->Function );
	//				continue;
	//			}
	//			else
	//				address = pair->Value->CachedFunction->StubAddress;
	//			break;
	//		case BreakpointType::MemoryAccess:
	//			address = pair->Value->Address;
	//			break;
	//		}
	//		this->Breakpoints->Add( address, pair->Key );
	//	}
	//}
	//finally
	//{
	//	Monitor::Exit( this->Breakpoints );
	//}
}

void R4000Hook::AddBreakpoint( Breakpoint^ breakpoint )
{
	Debug::Assert( breakpoint != nullptr );
	for each( Breakpoint^ bp in this->Breakpoints )
	{
		if( bp->ID == breakpoint->ID )
		{
			Debug::Assert( false, "Adding duplicate breakpoint ID" );
			return;
		}
	}

	this->Breakpoints->Add( breakpoint );
	this->RefreshBreakpointTable();
	if( breakpoint->Enabled == true )
		SetBreakpoint( breakpoint );
}

Breakpoint^ R4000Hook::FindBreakpoint( int id )
{
	for each( Breakpoint^ bp in this->Breakpoints )
	{
		if( bp->ID == id )
			return bp;
	}
	return nullptr;
}

bool R4000Hook::UpdateBreakpoint( Breakpoint^ newBreakpoint )
{
	Debug::Assert( newBreakpoint != nullptr );
	Breakpoint^ old = nullptr;
	for each( Breakpoint^ bp in this->Breakpoints )
	{
		if( bp->ID == newBreakpoint->ID )
		{
			old = bp;
			break;
		}
	}
	Debug::Assert( old != nullptr, "Could not find original breakpoint" );
	if( old == nullptr )
		return false;

	// Mode and Enabled are the only ones we care about that can change
	// We don't even bother with mode - that is used by the handler - we just copy

	old->Mode = newBreakpoint->Mode;
	if( old->Enabled != newBreakpoint->Enabled )
	{
		old->Enabled = newBreakpoint->Enabled;
		this->RefreshBreakpointTable();
		if( old->Enabled == true )
			SetBreakpoint( old );
		else
			UnsetBreakpoint( old );
	}

	return true;
}

void R4000Hook::RemoveBreakpoint( int id )
{
	Breakpoint^ breakpoint;
	for each( Breakpoint^ bp in this->Breakpoints )
	{
		if( bp->ID == id )
		{
			breakpoint = bp;
			break;
		}
	}
	Debug::Assert( breakpoint != nullptr, "Could not find breakpoint" );
	if( breakpoint == nullptr )
		return;

	this->Breakpoints->Remove( breakpoint );
	this->RefreshBreakpointTable();
	if( breakpoint->Enabled == true )
		UnsetBreakpoint( breakpoint );
}

// -- CPU --

CoreState^ R4000Hook::GetCoreState( int core )
{
	Debug::Assert( core == 0 );

	if( core == 0 )
	{
		R4000Core^ core = this->Cpu->_core0;

		CoreState^ state = gcnew CoreState();

		state->ProgramCounter = *core->PC;
		state->GeneralRegisters = core->GeneralRegisters;
		state->Hi = ( uint )*core->HI;
		state->Lo = ( uint )*core->LO;
		state->LL = ( *core->LL == 1 ) ? true : false;

		state->Cp0ControlRegisters = core->Cp0->Control;
		state->Cp0Registers = core->Cp0->Registers;
		state->Cp0ConditionBit = core->Cp0->ConditionBit;

		state->FpuControlRegister = core->Cp1->Control;
		state->FpuConditionBit = core->Cp1->ConditionBit;
		state->FpuRegisters = core->Cp1->Registers;

		state->VfpuRegisters = gcnew array<float>( 128 );
		for( int n = 0; n < 128; n++ )
			state->VfpuRegisters[ n ] = _cpuCtx->Cp2Registers[ n ];
		//state->VfpuControlRegister

		return state;
	}
	else
	{
		return nullptr;
	}
}

void R4000Hook::SetCoreState( int core, CoreState^ state )
{
}

CoreState^ R4000Hook::GetThreadCoreState( int core, int internalThreadId )
{
	Debug::Assert( core == 0 );

	if( core == 0 )
	{
		R4000Core^ core = this->Cpu->_core0;

		CoreState^ state = gcnew CoreState();

		/*state->ProgramCounter = *core->PC;
		state->GeneralRegisters = core->GeneralRegisters;
		state->Hi = ( uint )*core->HI;
		state->Lo = ( uint )*core->LO;
		state->LL = ( *core->LL == 1 ) ? true : false;

		state->Cp0ControlRegisters = core->Cp0->Control;
		state->Cp0Registers = core->Cp0->Registers;
		state->Cp0ConditionBit = core->Cp0->ConditionBit;

		state->FpuControlRegister = core->Cp1->Control;
		state->FpuConditionBit = core->Cp1->ConditionBit;
		state->FpuRegisters = core->Cp1->Registers;

		state->VfpuRegisters = gcnew array<float>( 128 );
		for( int n = 0; n < 128; n++ )
			state->VfpuRegisters[ n ] = _cpuCtx->Cp2Registers[ n ];*/
		//state->VfpuControlRegister

		return state;
	}
	else
	{
		return nullptr;
	}
}

generic<typename T>
T R4000Hook::GetRegister( RegisterSet set, int ordinal )
{
	switch( set )
	{
	case RegisterSet::Gpr:
		Debug::Assert( ( T::typeid == uint::typeid ) || ( T::typeid == int::typeid ) );
		if( ordinal == 32 )
			return ( T )( uint )_cpuCtx->LO;
		else if( ordinal == 33 )
			return ( T )( uint )_cpuCtx->HI;
		else
			return ( T )( uint )_cpuCtx->Registers[ ordinal ];
	case RegisterSet::Fpu:
		Debug::Assert( T::typeid == float::typeid );
		return ( T )_cpuCtx->Cp1Registers[ ordinal ];
	case RegisterSet::Vfpu:
		Debug::Assert( T::typeid == float::typeid );
		return ( T )_cpuCtx->Cp2Registers[ ordinal ];
	}
	return ( T )0;
}

generic<typename T>
void R4000Hook::SetRegister( RegisterSet set, int ordinal, T value )
{
	switch( set )
	{
	case RegisterSet::Gpr:
		Debug::Assert( ( T::typeid == uint::typeid ) || ( T::typeid == int::typeid ) );
		if( ordinal == 32 )
			_cpuCtx->LO = ( uint )value;
		else if( ordinal == 33 )
			_cpuCtx->HI = ( uint )value;
		else
			_cpuCtx->Registers[ ordinal ] = ( uint )value;
		break;
	case RegisterSet::Fpu:
		Debug::Assert( T::typeid == float::typeid );
		_cpuCtx->Cp1Registers[ ordinal ] = ( float )value;
		break;
	case RegisterSet::Vfpu:
		Debug::Assert( T::typeid == float::typeid );
		_cpuCtx->Cp2Registers[ ordinal ] = ( float )value;
		break;
	}
}

int pspDebugGetStackTrace(unsigned int *results, int max);

array<Frame^>^ R4000Hook::GetCallstack()
{
	R4000Core^ core = this->Cpu->_core0;

	uint* addresses = ( uint* )malloc( sizeof( uint ) * 512 );
	int count = pspDebugGetStackTrace( addresses, 512 );
	array<Frame^>^ frames = gcnew array<Frame^>( count + 1 );

	// Add current PC
	frames[ 0 ] = gcnew Frame( FrameType::UserCode, *core->PC );

	// Add all others
	for( int n = 0; n < count; n++ )
	{
		FrameType type = FrameType::UserCode;
		uint address = addresses[ n ];
		if( address == CALL_RETURN_DUMMY )
			type = FrameType::CallMarshal;
		else if( address == BIOS_SAFETY_DUMMY )
			type = FrameType::BiosBarrier;
		frames[ n + 1 ] = gcnew Frame( type, address );
	}

	free( addresses );
	return frames;
}

// -- Memory --

array<byte>^ R4000Hook::GetMemory( uint startAddress, int length )
{
	return nullptr;
}

void R4000Hook::SetMemory( uint startAddress, array<byte>^ buffer, int offset, int length )
{
}

IntPtr R4000Hook::GetMemoryPointer( uint address )
{
	return IntPtr( this->Cpu->_memory->NativeSystem->Translate( address ) );
}

array<uint>^ R4000Hook::SearchMemory( uint64 value, int width )
{
	return nullptr;
}

uint R4000Hook::Checksum( uint startAddress, int length )
{
	return 0;
}

array<uint>^ R4000Hook::GetMethodBody( Method^ method )
{
	Debug::Assert( method != nullptr );
	array<uint>^ body = gcnew array<uint>( method->Length / 4 );
	byte* p = this->Cpu->_memory->NativeSystem->Translate( method->Address );
	for( int n = 0; n < ( int )method->Length / 4; n++ )
	{
		body[ n ] =
			( ( uint )p[ 0 ] ) |
			( ( uint )p[ 1 ] << 8 ) |
			( ( uint )p[ 2 ] << 16 ) |
			( ( uint )p[ 3 ] << 24 );
		p += 4;
	}
	return body;
}
