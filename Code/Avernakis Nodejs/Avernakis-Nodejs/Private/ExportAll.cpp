#include "StdAfx.h"

#include "WrapObject.h"
#include "App.h"

Napi::Object ExportAll( Napi::Env env, Napi::Object exports )
{
	// These did nothing but forcing the symbols to be included when compiling
	Nav::App::GetSingleton().Initialize( false );

	Nav::ObjectFactory::GetSingleton().ExportJsObject( env, exports );

	return exports;
}

#if AvePlatform == AvePlatformWinDesktop
Ave::S32 AveStdCall DllMain( void* hInstance, Ave::U32 nReason, void* )
{
	switch ( nReason )
	{
	case 1: // DLL_PROCESS_ATTACH
		break;

	case 2: // DLL_THREAD_ATTACH
		break;

	case 3: // DLL_THREAD_DETACH
		break;

	case 0: // DLL_PROCESS_DETACH
		break;
	}
	return 1;
}
#endif

NODE_API_MODULE( Ave, ExportAll )
