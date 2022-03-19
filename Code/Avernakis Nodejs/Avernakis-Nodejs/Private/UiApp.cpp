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
		__Ctor( cb );
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

	U1 UiApp::Ctor()
	{
		if ( !App::GetSingleton().CreateUiApp( this ) )
			return false;

		if ( !m_InitFinishEvent.Create( true ) )
			return false;

		if ( !m_ExecuteFinishEvent.Create( true ) )
			return false;

		if ( !m_ExecuteLock.Create() )
			return false;

		m_Thread = AveKak.Create<Sys::IThread>( Sys::IThread::CreationParam( [this] { __UiThread(); }, "Ave Ui" ) );
		if ( !m_Thread )
			return false;

		return true;
	}

	void UiApp::__UiThread()
	{
		m_Object = AveKak.CreateAppScope();
		if ( !m_Object )
			return;

		AveKak.GetApp().GetEvent<IApplication::OnWakeup>() += MakeThisFunc( OnAppWakeup );

		m_InitFinishEvent->Set();

		auto n = AveKak.GetApp().Run();

		m_OnExit( n, true );

		__Detail::__EventManger::GetSingleton().ReleaseFuncSafe();
	}

	void UiApp::__ExecuteQueued()
	{
		for ( ;; )
		{
			CSize nCount = 0;

			{
				Sys::RwLockScoped __Lock( *m_ExecuteLock );
				nCount = m_Execute.Size();
				if ( nCount > m_ExecuteBuffer.Size() )
					m_ExecuteBuffer.Resize( nCount );
				for ( CSize i = 0; i < nCount; ++i )
					m_Execute.Dequeue( m_ExecuteBuffer[i] );
			}

			if ( 0 == nCount )
				break;

			for ( CSize i = 0; i < nCount; ++i )
				m_ExecuteBuffer[i]();
		}
	}

	void UiApp::OnAppWakeup( Ave::IApplication & pApplication, const void * pContext )
	{
		__ExecuteQueued();

		m_ExecuteFinishEvent->Set();
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

	void UiApp::ExecuteInUiThread( Func<void()>&& f, U1 bWait )
	{
		m_InitFinishEvent->Wait();

		if ( m_BlockCall )
		{
			f();
		}
		else
		{
			m_ExecuteFinishEvent->Reset();
			{
				Sys::RwLockScoped __Lock( *m_ExecuteLock );
				m_Execute.Enqueue( std::move( f ) );
			}
			AveKak.GetApp().Wakeup( nullptr );
			if ( bWait )
				m_ExecuteFinishEvent->Wait();
		}
	}

	void UiApp::BlockCallEnter()
	{
		if ( 0 == m_BlockCall.fetch_add( 1 ) )
		{
			// The UI thread will start waiting for the nodejs thread from this point, and the nodejs is started waiting for the UI thread here
			// It's safe to execute all queued UI thread executes here
			__ExecuteQueued();
			m_ExecuteFinishEvent->Set();
		}
	}

	void UiApp::BlockCallLeave()
	{
		--m_BlockCall;
	}

}
