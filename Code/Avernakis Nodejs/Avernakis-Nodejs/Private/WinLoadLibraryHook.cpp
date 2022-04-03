// Details at: https://docs.microsoft.com/en-us/cpp/build/reference/understanding-the-helper-function

#ifdef _MSC_VER

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <delayimp.h>

namespace
{
	FARPROC WINAPI PreLoadLibraryHook( unsigned int dliNotify, PDelayLoadInfo pdli )
	{
		if ( dliNotePreLoadLibrary == dliNotify && 0 == _stricmp( pdli->szDll, "node.exe" ) )
			return (FARPROC) GetModuleHandleW( nullptr );
		else
			return nullptr;
	}
}

extern "C" const PfnDliHook __pfnDliNotifyHook2 = PreLoadLibraryHook;

#endif
