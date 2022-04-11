#include "StdAfx.h"

#include "WrapObject.h"
#include "App.h"

namespace
{
	Napi::Object AveGetSDKVersion( const Napi::CallbackInfo& ci )
	{
		auto obj = Napi::Object::New( ci.Env() );
		auto& ver = Ave::AveGetSdkVersion();
		obj.Set( "Major", ver.m_Version[0] );
		obj.Set( "Minor", ver.m_Version[1] );
		obj.Set( "Patch", ver.m_Version[2] );
		obj.Set( "Private", ver.m_Version[3] );
		return obj;
	}
}

Napi::Object ExportAll( Napi::Env env, Napi::Object exports )
{
	// These did nothing but forcing the symbols to be included when compiling
	Nav::App::GetSingleton().Initialize( false );

	exports.Set( "AveGetSDKVersion", Napi::Function::New( env, AveGetSDKVersion ) );

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
