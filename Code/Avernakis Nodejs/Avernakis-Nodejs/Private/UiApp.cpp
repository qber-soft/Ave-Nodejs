#include "StdAfx.h"
#include "UiApp.h"
#include "UiWindow.h"
#include "App.h"

#define ThisMethod($x) &UiApp::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, ThisMethod( $x ) )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiApp> c_obj;
	}

	UiApp::UiApp( const Napi::CallbackInfo & cb ) : WrapObject( cb )
	{
		__CtorCi( cb );
	}

	UiApp::~UiApp()
	{
		App::GetSingleton().DestroyUiApp();
	}

	void UiApp::DefineObject()
	{
		AutoAddMethod( ResAddPackageIndex );
		AutoAddMethod( ResAddPackage );
		AutoAddMethod( ResSetIconSizeList );

		AutoAddMethod( LangSetDefaultString );

		AutoAddMethod( LangSetType );
		AutoAddMethod( LangSetFileRoot );
		AutoAddMethod( LangSetDefaultString );
		AutoAddMethod( LangRefresh );
		AutoAddMethod( LangGet );
		//AutoAddMethod( LangCreateMenu );
		AutoAddMethod( LangExport, WrapObjectUi );
		AutoAddMethod( LangSetCurrent );
		AutoAddMethod( LangGetCurrent );
		AutoAddMethod( LangGetString );
		AutoAddMethod( LangGetStringTable );

		AutoAddMethod( OnExit );
	}

	U1 UiApp::Ctor( const CallbackInfo& ci )
	{
		napi_create_threadsafe_function( ci.GetEnv(), nullptr, Napi::Object(), Napi::String::New( ci.GetEnv(), "" ), 0, 1, this, __JsFuncFinalize, this, __JsFuncCall, &m_JsFunc );
		if ( !m_JsFunc )
			return false;

		if ( !App::GetSingleton().CreateUiApp( this ) )
			return false;

		if ( !m_InitFinishEvent.Create( true ) )
			return false;

		if ( !m_UiExecuteLock.Create() )
			return false;

		if ( !m_UiExecuteFinish.Create() )
			return false;

		if ( !m_JsExecuteLock.Create() )
			return false;

		if ( !m_JsExecuteFinish.Create() )
			return false;

		if ( !m_Blocker.Create() )
			return false;

		m_Thread = AveKak.Create<Sys::IThread>( Sys::IThread::CreationParam( [this] { __UiThread(); }, "Ave Ui" ) );
		if ( !m_Thread )
			return false;

		return true;
	}

	U1 UiApp::ResAddPackageIndex( PCWChar szFile, PCWChar szRoot )
	{
		auto res = AveKak.Create<Io::IFilePackage>();
		if ( !res )
			return false;
		auto sFile = App::GetSingleton().GetFileSystem().FileGetFullPath( szFile );
		auto sRoot = App::GetSingleton().GetFileSystem().FileGetFullPath( szRoot );
		if ( !res->OpenPackage( sFile.c_str(), sRoot.c_str() ) )
			return false;
		App::GetSingleton().m_InitDpiware->AddResourcePackage( std::move( res ) );
		return true;
	}

	U1 UiApp::ResAddPackage( PCWChar szFile )
	{
		auto res = AveKak.Create<Io::IFilePackage>();
		if ( !res )
			return false;
		auto sFile = App::GetSingleton().GetFileSystem().FileGetFullPath( szFile );
		if ( !res->OpenPackage( sFile.c_str() ) )
			return false;
		App::GetSingleton().m_InitDpiware->AddResourcePackage( std::move( res ) );
		return true;
	}

	UiApp * UiApp::ResSetIconSizeList( const List<U32>& v )
	{
		App::GetSingleton().m_IconSizeList = v;
		return this;
	}

	UiApp * UiApp::LangSetType( AppLangType nType )
	{
		App::GetSingleton().m_LangType = nType;
		return this;
	}

	UiApp * UiApp::LangSetFileRoot( PCWChar szFolder, PCWChar szExt )
	{
		auto sFolder = App::GetSingleton().GetFileSystem().FileGetFullPath( szFolder );
		App::GetSingleton().m_InitStringIni->SetFolder( sFolder.c_str(), szExt );
		return this;
	}

	UiApp * UiApp::LangSetDefaultString( CultureId cid, Napi::Value v )
	{
		auto obj = v.As<Napi::Object>();
		auto arr = obj.GetPropertyNames();
		const auto nCount = arr.Length();
		List<WChar> vData;
		List<S32_2> vPos;
		for ( U32 i = 0; i < nCount; ++i )
		{
			auto key = arr.Get( i );
			auto val = obj.Get( key );
			if ( key && val )
			{
				auto pkey = key.ToString().Utf16Value();
				auto pval = val.ToString().Utf16Value();
				auto nkey = 1 + pkey.length();
				auto nval = 1 + pval.length();
				S32_2 pos;
				pos.x = (S32) vData.Size();
				pos.y = pos.x + (S32) nkey;
				vPos.Add( pos );
				vData.Resize( pos.y + nval );
				AveCopyMemory( &vData[pos.x], pkey.c_str(), sizeof( WChar ) * nkey );
				AveCopyMemory( &vData[pos.y], pval.c_str(), sizeof( WChar ) * nval );
			}
		}
		if ( !vPos.IsEmpty() )
		{
			m_DefaultStringData = std::move( vData );
			List<PCWChar[2]> vPointer( vPos.Size() );
			for ( auto& i : vPos.RangeIndexAll() )
			{
				vPointer[i.Index][0] = &m_DefaultStringData[i->x];
				vPointer[i.Index][1] = &m_DefaultStringData[i->y];
			}
			m_DefaultString = std::move( vPointer );
			App::GetSingleton().m_InitStringIni->SetDefault( m_DefaultString.Data(), m_DefaultString.Size(), cid );
			LangSetCurrent( cid );
			App::GetSingleton().m_LangSetText = true;
		}
		return this;
	}

	UiApp * UiApp::LangRefresh()
	{
		App::GetSingleton().IniRefreshLanguage();
		return this;
	}

	List<WrapData<AppLanguageItem>> UiApp::LangGet() const
	{
		List<WrapData<AppLanguageItem>> v;
		auto& lang = App::GetSingleton().IniGetUiLang();
		for ( auto& i : lang )
		{
			auto& info = AveStr.GetCultureInfo( i.m_Cid );
			v.Add( { { i.m_File, i.m_Cid, info.m_NameEnglish, info.m_NameNative } } );
		}
		return std::move( v );
	}

	void * UiApp::LangCreateMenu( UiWindow * window, U1 bIncludeExportMenuItem ) const
	{
		return nullptr;
	}

	void UiApp::LangExport( UiWindow * window ) const
	{
		App::GetSingleton().IniShowSaveLanguage( &window->PublicGetNativeWindow() );
	}

	UiApp * UiApp::LangSetCurrent( CultureId cid )
	{
		App::GetSingleton().IniApplyLanguage( cid );
		return this;
	}

	CultureId UiApp::LangGetCurrent() const
	{
		return App::GetSingleton().IniGetString().GetCultureId();
	}

	WString UiApp::LangGetString( Napi::Value key )
	{
		if ( AppLangType::Text == App::GetSingleton().m_LangType && key.IsString() )
			return App::GetSingleton().IniGetString().GetString( (PCWChar) key.ToString().Utf16Value().c_str() );
		return {};
	}

	Napi::Value UiApp::LangGetStringTable( const CallbackInfo& ci )
	{
		auto obj = Napi::Object::New( ci.GetEnv() );
		if ( AppLangType::Text == App::GetSingleton().m_LangType )
		{
			auto& str = App::GetSingleton().IniGetString();
			auto vkey = str.GetKey();
			for ( auto& i : vkey )
				obj.Set( AveStr.Utf16ToUtf8( i ), Napi::String::New( ci.GetEnv(), (const char16_t*) str.GetString( i ) ) );
		}
		return obj;
	}

	void UiApp::OnAppWakeup( Ave::IApplication & pApplication, const void * pContext )
	{
		__UiExecuteQueued( true );
	}

	S32 UiApp::OnAppRunStart( Ave::IApplication & pApplication )
	{
		if ( m_UiExecuteBlock > 0 )
		{
			m_UiExecuteCanceled = true;
			return -1;
		}
		return 0;
	}

	void UiApp::OnAppRunEnd( Ave::IApplication & pApplication, S32 nExitCode )
	{
	}

	void UiApp::__UiThread()
	{
		m_Object = AveKak.CreateAppScope();
		if ( !m_Object )
			return;

		AveKak.GetApp().GetEvent<IApplication::OnWakeup>() += MakeThisFunc( OnAppWakeup );
		AveKak.GetApp().GetEvent<IApplication::OnRunStart>() += MakeThisFunc( OnAppRunStart );
		//AveKak.GetApp().GetEvent<IApplication::OnRunEnd>() += MakeThisFunc( OnAppRunEnd );

		m_InitFinishEvent->Set();

		auto n = AveKak.GetApp().Run();

		m_OnExit( n );

		napi_release_threadsafe_function( m_JsFunc, napi_threadsafe_function_release_mode::napi_tsfn_release );
		m_JsFunc = nullptr;
	}

	void UiApp::__JsFuncFinalize( napi_env env, void * finalize_data, void * finalize_hint )
	{
	}

	void UiApp::__JsFuncCall( napi_env env, napi_value js_callback, void* context, void* data )
	{
		auto pApp = (UiApp*) context;
		pApp->__JsExecuteQueued( true );
		{
			Sys::RwLockScoped __Lock( *pApp->m_JsExecuteLock );
			--pApp->m_JsExecuteDepth;
		}
	}

	U1 UiApp::__UiExecuteQueued( U1 bAll )
	{
		List<Work> vExecuteBuffer;
		U1 bCanceled = false;
		for ( ;; )
		{
			CSize nCount = 0;
			CSize nExecuted = 0;

			{
				Sys::RwLockScoped __Lock( *m_UiExecuteLock );
				nCount = m_UiExecuteFunc.Size();
				if ( nCount > vExecuteBuffer.Size() )
					vExecuteBuffer.Resize( nCount );
				for ( CSize i = 0; i < nCount; ++i )
					m_UiExecuteFunc.Dequeue( vExecuteBuffer[i] );
			}

			if ( 0 == nCount )
				break;

			for ( CSize i = 0; i < nCount; ++i )
			{
				auto& w = vExecuteBuffer[i];
				if ( bAll )
					w.m_Canceled = false;
				else if ( !w.m_Wakeup )
					continue;
				if ( w.m_Canceled )
				{
					Sys::RwLockScoped __Lock( *m_UiExecuteLock );
					m_UiExecuteFunc.Enqueue( w );
					continue;
				}
				if ( w.m_Promise )
					w.m_Promise->Call();
				else
					w.m_Work();
				if ( m_UiExecuteCanceled )
				{
					w.m_Canceled = true;
					bCanceled = true;
					m_UiExecuteCanceled = false;
					{
						Sys::RwLockScoped __Lock( *m_UiExecuteLock );
						m_UiExecuteFunc.Enqueue( w );
					}
					continue;
				}
				++nExecuted;
				if ( w.m_Promise )
					__ExecuteInJsThread( w.m_Promise );
				m_Blocker.Signal( w.m_Blocker );
				m_UiExecuteFinish->Set();
			}

			if ( !bAll )
			{
				Sys::RwLockScoped __Lock( *m_UiExecuteLock );
				auto f = std::move( m_UiExecuteFunc );
				for ( CSize i = 0; i < nCount; ++i )
				{
					auto& w = vExecuteBuffer[i];
					if ( !w.m_Wakeup )
						m_UiExecuteFunc.Enqueue( w );
				}
				while ( !f.IsEmpty() )
					m_UiExecuteFunc.Enqueue( f.Dequeue() );
				break;
			}

			if ( 0 == nExecuted )
				break;
		}

		return !bCanceled;
	}

	void UiApp::__JsExecuteQueued( U1 bAll )
	{
		List<Work> vExecuteBuffer;
		for ( ;; )
		{
			CSize nCount = 0;

			{
				Sys::RwLockScoped __Lock( *m_JsExecuteLock );
				nCount = m_JsExecuteFunc.Size();
				if ( nCount > vExecuteBuffer.Size() )
					vExecuteBuffer.Resize( nCount );
				for ( CSize i = 0; i < nCount; ++i )
					m_JsExecuteFunc.Dequeue( vExecuteBuffer[i] );
			}

			if ( 0 == nCount )
				break;

			for ( CSize i = 0; i < nCount; ++i )
			{
				auto& w = vExecuteBuffer[i];
				if ( !bAll && !w.m_Wakeup )
					continue;
				if ( w.m_Promise )
					w.m_Promise->Resolve();
				else
					w.m_Work();
				m_Blocker.Signal( w.m_Blocker );
				m_JsExecuteFinish->Set();
			}

			if ( !bAll )
			{
				Sys::RwLockScoped __Lock( *m_JsExecuteLock );
				auto f = std::move( m_JsExecuteFunc );
				for ( CSize i = 0; i < nCount; ++i )
				{
					auto& w = vExecuteBuffer[i];
					if ( !w.m_Wakeup )
						m_JsExecuteFunc.Enqueue( w );
				}
				while ( !f.IsEmpty() )
					m_JsExecuteFunc.Enqueue( f.Dequeue() );
				break;
			}
		}
	}

	void UiApp::__ExecuteInJsThread( IPromiseCall * p )
	{
		Sys::RwLockScoped __Lock( *m_JsExecuteLock );
		const auto nJsExecute = m_JsExecute;

		m_JsExecuteFunc.Enqueue( { {}, -1, p, nJsExecute > 0 } );

		if ( 0 == m_JsExecute && 0 == m_JsExecuteDepth )
		{
			++m_JsExecuteDepth;
			napi_call_threadsafe_function( m_JsFunc, nullptr, napi_threadsafe_function_call_mode::napi_tsfn_blocking );
		}
		else
		{
			m_UiExecuteBreak = true;
			m_UiExecuteFinish->Set();
		}
	}

	// Execute f in UI Thread, this method should be called by JS thread
	void UiApp::ExecuteInUiThread( Func<void()>&& f )
	{
		m_InitFinishEvent->Wait();

		const auto nBlocker = m_Blocker.Acquire();
		const auto nUiExecute = m_UiExecuteBlock;

		{
			Sys::RwLockScoped __Lock( *m_UiExecuteLock );
			m_UiExecuteFunc.Enqueue( { std::move( f ), nBlocker, nullptr, m_UiExecuteBlock > 0 } );
		}

		if ( 0 == nUiExecute )
			AveKak.GetApp().Wakeup( nullptr );
		else
		{
			m_JsExecuteBreak = true;
			m_JsExecuteFinish->Set();
		}

		{
			Sys::RwLockScoped __Lock( *m_JsExecuteLock );
			++m_JsExecute;
		}

		for ( ;; )
		{
			m_UiExecuteFinish->Wait();
			U1 bUiBreak = true;
			if ( m_UiExecuteBreak.compare_exchange_strong( bUiBreak, false ) )
				__JsExecuteQueued( false );
			if ( m_Blocker.Release( nBlocker ) )
				break;
		}

		S32 nJsExecute;
		{
			Sys::RwLockScoped __Lock( *m_JsExecuteLock );
			nJsExecute = --m_JsExecute;
		}
	}

	void UiApp::ExecuteInUiThread( IPromiseCall * p )
	{
		m_InitFinishEvent->Wait();

		{
			Sys::RwLockScoped __Lock( *m_UiExecuteLock );
			m_UiExecuteFunc.Enqueue( { {}, -1, p } );
		}

		AveKak.GetApp().Wakeup( nullptr );
	}

	// Execute f in JS Thread, this method should be called by UI thread
	void UiApp::ExecuteInJsThread( Func<void()> && f, U1 bWait, U1 bUiThread )
	{
		S32 nBlocker = -1;

		if ( bWait )
		{
			if ( bUiThread )
				++m_UiExecuteBlock;
			nBlocker = m_Blocker.Acquire();
		}

		S32 nJsExecute;
		{
			Sys::RwLockScoped __Lock( *m_JsExecuteLock );
			nJsExecute = m_JsExecute;

			m_JsExecuteFunc.Enqueue( { std::move( f ), nBlocker, nullptr, bWait && nJsExecute > 0 } );

			if ( 0 == nJsExecute && 0 == m_JsExecuteDepth )
			{
				++m_JsExecuteDepth;
				napi_call_threadsafe_function( m_JsFunc, nullptr, napi_threadsafe_function_call_mode::napi_tsfn_blocking );
			}
			else
			{
				m_UiExecuteBreak = true;
				m_UiExecuteFinish->Set();
			}
		}

		if ( bWait )
		{
			for ( ;; )
			{
				while ( !m_JsExecuteFinish->Wait( 100 ) )
				{
					Sys::RwLockScoped __Lock( *m_JsExecuteLock );
					if ( 0 == nJsExecute && 0 == m_JsExecuteDepth )
					{
						++m_JsExecuteDepth;
						napi_call_threadsafe_function( m_JsFunc, nullptr, napi_threadsafe_function_call_mode::napi_tsfn_blocking );
					}
					else
					{
						m_UiExecuteBreak = true;
						m_UiExecuteFinish->Set();
					}
				}

				U1 bJsBreak = true;
				if ( bUiThread && m_JsExecuteBreak.compare_exchange_strong( bJsBreak, false ) && !__UiExecuteQueued( false ) )
				{
					// Schedule another wakeup, a new app message loop can't be started in an unfinished message processing
					AveKak.GetApp().Wakeup( nullptr );
					break;
				}
				if ( m_Blocker.Release( nBlocker ) )
					break;
			}

			if ( bUiThread )
				--m_UiExecuteBlock;
		}
	}

}
