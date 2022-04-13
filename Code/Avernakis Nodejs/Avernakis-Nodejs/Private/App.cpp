#include "StdAfx.h"
#include "App.h"
#include "UiApp.h"

namespace Nav
{

	__App::__App()
	{
	}

	__App::~__App()
	{
	}

	U1 __App::OnInitializeModule()
	{
		Ave::Mod::AveSystem::GetSingleton();
		Ave::Mod::AveIo::GetSingleton();
		Ave::Mod::AveText::GetSingleton();
		Ave::Mod::AveGui::GetSingleton();
		Ave::Mod::AveGuiImage::GetSingleton();
		Ave::Mod::AveByo3::GetSingleton();

		return true;
	}

	U1 __App::OnInitializeDpiware( IInitializeDpiware & p ) const
	{
		m_InitDpiware = &p;
		return true;
	}

	U1 __App::OnInitializeStringIni( IInitializeDefaultStringIni & init )
	{
		static PCWChar c_Default[][2]{ { AveWide( "" ), AveWide( "" ) } };
		m_InitStringIni = &init;
		init.SetDefault( c_Default, CultureId::en_us );
		return true;
	}

	U1 __App::OnInitialize()
	{
		AveStr.GetCultureLevel2();

#if AvePlatform == AvePlatformWinDesktop
		AveKak.StaticRegister<Ave::Byo2::IDeviceD2D1>();
		AveKak.StaticRegister<Ave::Byo3::IDeviceD3D11>();
#elif AvePlatform == AvePlatformMac
		AveKak.StaticRegister<Ave::Byo2::IDeviceCg>();
#endif
		return true;
	}

	U1 __App::CreateUiApp( UiApp* app )
	{
		if ( m_App )
			return false;
		m_App = app;
		return true;
	}

	void __App::DestroyUiApp()
	{
		m_App = nullptr;
	}

	void __App::SetDpiwareSizeList( Ui::IIconManager & im )
	{
		im.SetSizeList( m_IconSizeList );
	}

	void __App::ExecuteInUiThread( Func<void()> && f )
	{
		if ( m_App )
			m_App->ExecuteInUiThread( std::move( f ) );
	}

	void __App::ExecuteInUiThread( IPromiseCall * p )
	{
		if ( m_App )
			m_App->ExecuteInUiThread( p );
	}

	void __App::ExecuteInJsThread( Func<void()> && f, U1 bWait, U1 bUiThread )
	{
		if ( m_App )
			m_App->ExecuteInJsThread( std::move( f ), bWait, bUiThread );
	}

}
