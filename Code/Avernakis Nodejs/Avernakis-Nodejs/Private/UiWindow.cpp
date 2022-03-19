#include "StdAfx.h"
#include "UiWindow.h"
#include "App.h"

#include "UiControlManager.h"
#include "UiCommonUi.h"
#include "UiPlatform.h"
#include "UiIconManager.h"
#include "UiIcon.h"
#include "UiWindowSysTray.h"
#include "UiWindowTaskbar.h"

#include "UiThemeImage.h"
#include "UiWindowFrame.h"

#define ThisMethod($x) &UiWindow::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, ThisMethod( $x ) )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiWindow> c_obj;
	}

	void UiWindow::DefineObject()
	{
		__DefineObject<UiWindow>();

		AutoAddMethod( CreateWindow, WrapObjectGeneric );
		AutoAddMethod( CloseWindow );

		AutoAddMethod( GetDeviceType );

		AutoAddMethod( Activate );
		AutoAddMethod( IsActive );

		AutoAddMethod( SetTitle );
		AutoAddMethod( GetTitle );

		AutoAddMethod( SetPosition );
		AutoAddMethod( SetSize );

		AutoAddMethod( SetClientPosition );
		AutoAddMethod( GetClientPosition );

		AutoAddMethod( SetClientSize );
		AutoAddMethod( GetClientSize );

		AutoAddMethod( SetMinimumSize );
		AutoAddMethod( GetMinimumSize );

		AutoAddMethod( SetSizeState );
		AutoAddMethod( GetSizeState );
		AutoAddMethod( IsMinimizable );
		AutoAddMethod( IsSizeable );

		AutoAddMethod( SetTopMost );
		AutoAddMethod( GetTopMost );

		AutoAddMethod( SetIme );
		AutoAddMethod( GetIme );

		AutoAddMethod( SetBackground );
		AutoAddMethod( GetBackground );

		AutoAddMethod( SetRtl );
		AutoAddMethod( GetRtl );

		AutoAddMethod( SetScale );
		AutoAddMethod( GetScale );

		AutoAddMethod( SetKeyTipEnable );
		AutoAddMethod( GetKeyTipEnable );

		AutoAddMethod( SetDirectKeyTip );
		AutoAddMethod( GetDirectKeyTip );

		AutoAddMethod( SetContent );
		AutoAddMethod( GetContent );

		AutoAddMethod( SetIcon );
		AutoAddMethod( GetIcon );

		AutoAddMethod( SetAppId );

		AutoAddMethod( SetDeviceNotification );
		AutoAddMethod( GetDeviceNotification );

		AutoAddMethod( GetTheme );
		AutoAddMethod( GetFrame, WrapObjectGeneric );

		AddMethod<WrapObjectGeneric>( "GetControlManager", ThisMethod( __GetControlManager ) );
		AddMethod<WrapObjectGeneric>( "GetIconManager", ThisMethod( __GetIconManager ) );
		AddMethod<WrapObjectGeneric>( "GetCommonUi", ThisMethod( __GetCommonUi ) );
		AutoAddMethod( GetSysTray, WrapObjectGeneric );
		AutoAddMethod( GetTaskbar, WrapObjectGeneric );
		AutoAddMethod( GetPlatform, WrapObjectGeneric );

		AutoAddMethod( GetTime );

		AddMethod<WrapObjectGeneric>( "CacheIcon", ThisMethod( __CacheIcon ) );
		AddMethod<WrapObjectGeneric>( "CreateManagedIcon", ThisMethod( __CreateManagedIcon ) );

		AddMethod<>( "HotkeyRegister", ThisMethod( __HotkeyRegister ) );
		AddMethod<>( "HotkeyDeregister", ThisMethod( __HotkeyDeregister ) );
		AddMethod<>( "HotkeySetEnable", ThisMethod( __HotkeySetEnable ) );
		AddMethod<>( "HotkeyGetEnable", ThisMethod( __HotkeyGetEnable ) );
		AddMethod<>( "HotkeyClear", ThisMethod( __HotkeyClear ) );

		AutoAddMethod( OnCreateContent );
		AutoAddMethod( OnClosing );
		AutoAddMethod( OnClose );

		AddMethod<>( "OnWindowOk", ThisMethod( __OnWindowOk ) );
		AddMethod<>( "OnWindowCancel", ThisMethod( __OnWindowCancel ) );
		AddMethod<>( "OnWindowHotkey", ThisMethod( __OnWindowHotkey ) );

		AutoAddMethod( OnScaleChange );
		AutoAddMethod( OnLanguageChange );

		AutoAddMethod( OnDeviceChange );
	}

	U1 UiWindow::Ctor( const CallbackInfo& ci, const UiWindowCreation_t & cp )
	{
		m_Param = cp;

		if ( UiWindowDevice::Default2D == m_Param.m_Device )
		{
#		if AvePlatform == AvePlatformWinDesktop
			m_Param.m_Device = UiWindowDevice::D2D1;
#		elif AvePlatform == AvePlatformMac
			m_Param.m_Device = UiWindowDevice::CG;
#		else
#			error Not implemented.
#		endif
		}
		else if ( UiWindowDevice::Default3D == m_Param.m_Device )
		{
#		if AvePlatform == AvePlatformWinDesktop
			m_Param.m_Device = UiWindowDevice::D3D11;
#		elif AvePlatform == AvePlatformMac
			m_Param.m_Device = UiWindowDevice::Metal;
#		else
#			error Not implemented.
#		endif
		}

		if ( m_Param.m_Theme )
		{
			m_Theme = m_Param.m_Theme;
		}
		else
		{
			auto p = ci.NewJsObject<UiThemeImage>( true );
			if ( !p->Ctor() )
				return false;
			m_Theme.m_Pointer = p;
		}
		if ( !m_Theme )
			return false;

		m_Frame = ci.NewJsObject<UiWindowFrame>( true );
		if ( !m_Frame )
			return false;

		m_IconManager = ci.NewJsObject<UiIconManager>( true );
		if ( !m_IconManager )
			return false;

		m_ControlManager = ci.NewJsObject<UiControlManager>( true );
		if ( !m_ControlManager )
			return false;

		m_CommonUi = ci.NewJsObject<UiCommonUi>( true );
		if ( !m_CommonUi )
			return false;

		m_Platform = ci.NewJsObject<UiPlatform>( true );
		if ( !m_Platform->Ctor() )
			return false;
		if ( !m_Platform )
			return false;

		m_SysTray = ci.NewJsObject<UiWindowSysTray>( true );
		if ( !m_SysTray )
			return false;

		m_Taskbar = ci.NewJsObject<UiWindowTaskbar>( true );
		if ( !m_Taskbar )
			return false;

		return true;
	}

	U1 UiWindow::OnCreate( Ui::IWindow::CreationParam & cp )
	{
		auto theme = m_Theme->CloneTheme();
		if ( !theme )
			return false;
		theme->GetResourceManager().ProviderAdd( App::GetSingleton().GetDpiResourceProvider() );

		cp.m_Window.m_Title = m_Param.m_Title.c_str();
		cp.m_Window.m_Layout = m_Param.m_Layout;
		cp.m_Window.m_Flag = m_Param.m_Flag;
		cp.m_Window.m_Flag &= ~Ui::IWindowNative::CreationParam::Flag_ParentHandle;
		cp.m_Window.m_Flag |= Ui::IWindowNative::CreationParam::Flag_Render;
		cp.m_Window.m_Flag |= Ui::IWindowNative::CreationParam::Flag_CustomFrame;
		if ( m_Param.m_ParentWindow && m_Param.m_ParentWindow->IsWindowCreated() )
			cp.m_Window.m_Parent = &m_Param.m_ParentWindow->GetNativeWindow();
		cp.m_Theme = std::move( theme );
		switch ( m_Param.m_Device )
		{
#	if AvePlatform == AvePlatformWinDesktop
		case UiWindowDevice::GDI: cp.m_Device.m_DeviceType = Ui::WindowDeviceType::Byo2; cp.m_Device.m_DeviceId = AveGuidOf( Byo2::IDeviceGdi ); break;
		case UiWindowDevice::D2D1: cp.m_Device.m_DeviceType = Ui::WindowDeviceType::Byo2; cp.m_Device.m_DeviceId = AveGuidOf( Byo2::IDeviceD2D1 ); break;
		case UiWindowDevice::D3D11: cp.m_Device.m_DeviceType = Ui::WindowDeviceType::Byo3; cp.m_Device.m_DeviceId = AveGuidOf( Byo3::IDeviceD3D11 ); break;
		case UiWindowDevice::D3D12: cp.m_Device.m_DeviceType = Ui::WindowDeviceType::Byo3; cp.m_Device.m_DeviceId = AveGuidOf( Byo3::IDeviceD3D12 ); break;
#	elif AvePlatform == AvePlatformMac
		case UiWindowDevice::CG: cp.m_Device.m_DeviceType = Ui::WindowDeviceType::Byo2; cp.m_Device.m_DeviceId = AveGuidOf( Byo2::IDeviceCg ); break;
		case UiWindowDevice::Metal: cp.m_Device.m_DeviceType = Ui::WindowDeviceType::Byo3; cp.m_Device.m_DeviceId = AveGuidOf( Byo3::IDeviceMetal ); break;
#	endif

		default:
			return false;
	}
		if ( AveGuidNull == cp.m_Device.m_DeviceId )
			return false;

		cp.m_Device.m_Debug = Ui::WindowDeviceDebug::Auto;
		cp.m_Device.m_Multithreaded = true;
		cp.m_Device.m_TouchSupport = false;
		cp.m_Device.m_Msaa = 0;
		cp.m_Device.m_SyncInterval = 1;

		return true;
	}

	U1 UiWindow::OnCreateWindowContent()
	{
		App::GetSingleton().OnIniApplyLanguage += MakeThisFunc( __ApplyLanguage );
		App::GetSingleton().SetDpiwareSizeList( GetIconManager() );
		SetStringProvider( App::GetSingleton().IniGetProvider() );
		SetDpiId( AppHelper::DpiId::SystemDefault );
		GetWindow().SetBackground( 0 != (Ui::IWindowNative::CreationParam::Flag_Layered & m_Param.m_Flag) );
		GetCommonUiOrigin().SetIconManager( CloneIconManager() );
		if ( AppLangType::Text == App::GetSingleton().GetLangType() )
			GetControlManager().SetStringProvider( &App::GetSingleton().IniGetString() );

		GetWindow().SetFrame( GetUiFactory().Create<Ui::IWindowFrame>() );
		m_Frame->SetSharedControl( GetWindow().GetFrame() );
		m_Frame->InitCallback();

		Ui::CommonUiConfig cuicfg{};
		cuicfg.m_Message.m_DefaultTitle = AveWide( "AveApp" );
		cuicfg.m_Message.m_DefaultIconInfo = 0;
		cuicfg.m_Message.m_DefaultIconWarning = 0;
		cuicfg.m_Message.m_DefaultIconError = 0;
		cuicfg.m_Message.m_DefaultOffence = false;
		cuicfg.m_Message.m_BackColor = { 0, 0, 0, 200 };
		cuicfg.m_Wait.m_DefaultTitle = AveWide( "Please Wait..." );
		cuicfg.m_Wait.m_UiUpdateInterval = 200;
		cuicfg.m_Wait.m_BackColor = { 0, 0, 0, 200 };
		cuicfg.m_Input.m_DefaultTitle = AveWide( "AveApp" );
		cuicfg.m_Color.m_DefaultTitle = AveWide( "AveApp" );

		GetCommonUiOrigin().SetConfig( cuicfg );

		m_IconManager->SetIconManager( &GetIconManager() );
		m_ControlManager->SetControlManager( &GetControlManager() );
		m_CommonUi->SetCommonUi( &GetWindow(), &GetCommonUi() );

		Ui::IWindowSysTray* pSysTray;
		if ( GetNativeWindow().QueryInterface( &pSysTray ) )
		{
			pSysTray->GetEvent<Ui::IWindowSysTray::OnClick>() += MakeThisFunc( OnSysTrayClick );
			pSysTray->GetEvent<Ui::IWindowSysTray::OnRightClick>() += MakeThisFunc( OnSysTrayRightClick );
			m_SysTray->SetSysTray( this, pSysTray );
		}
		else
			m_SysTray = nullptr;

		Ui::IWindowTaskbar* pTaskbar;
		if ( GetNativeWindow().QueryInterface( &pTaskbar ) )
			m_Taskbar->SetTaskbar( this, pTaskbar );
		else
			m_Taskbar = nullptr;

		return true;
	}

	void UiWindow::OnWindowDestroy()
	{
		App::GetSingleton().OnIniApplyLanguage -= MakeThisFunc( __ApplyLanguage );

		// When this method is called, the window will be destroyed definitely while there is no time to wait the callback to be executed on another (node js engine) thread.
		// It should simulate an OnClose event on OnWindowClose method instead.
	}

	U1 UiWindow::OnWindowClose()
	{
		auto result = m_OnClosingResult;
		m_OnClosingResult = 0;

		if ( 0 == result )
		{
			if ( m_OnClosing )
			{
				m_OnClosing.WaitAsyncCall( this, [this]( const U1& r )
				{
					if ( r )
					{
						m_OnClosingResult = 1;
						GetWindow().Close();
					}
				} );
				return false;
			}
			else
				result = 1;
		}

		if ( 1 == result && m_OnClose )
		{
			m_OnClose.WaitAsyncCall( this, [this]
			{
				m_OnClosingResult = 2;
				GetWindow().Close();
			} );
			return false;
		}

		return true;
	}

	void UiWindow::OnWindowCancel()
	{
		m_OnWindowCancel( this );
	}

	void UiWindow::OnWindowOk()
	{
		m_OnWindowOk( this );
	}

	U1 UiWindow::OnWindowHotkey( U32 nId, Ui::Key nKey, U32 nModifier )
	{
		m_OnWindowHotkey( this, nId, nKey, nModifier );
		return true;
	}

	void UiWindow::OnDpiChange()
	{
		m_OnScaleChange( this );
	}

	void UiWindow::OnSysTrayClick( Ui::IWindowSysTray & sender, const S32_2 & vPos )
	{
		m_OnSysTrayClick( this );
	}

	void UiWindow::OnSysTrayRightClick( Ui::IWindowSysTray & sender, const S32_2 & vPos )
	{
		m_OnSysTrayRightClick( this );
	}

	void UiWindow::__OnDeviceChange( Ui::IWindowDeviceNotification & sender )
	{
		m_OnDeviceChange( this );
	}

	void UiWindow::__ApplyLanguage()
	{
		if ( !App::GetSingleton().IsLangSet() )
			return;

		GetControlManager().ApplyLanguage();

		if ( AppLangType::Text == App::GetSingleton().GetLangType() )
		{
			SetDpiMenuText( "CoUiScaleSys"_ls, "CoUiScaleHw"_ls );
			SetCommonUiDefaultConfig( App::GetSingleton().IniGetString() );
			GetNativeWindow().SetTitle( "AppTitle"_ls );

			Byo2::FontDesc fd{};
			fd.m_Res.m_Name = "__FontStd"_ls;
			fd.m_Size = 9;
			if ( fd.m_Res.m_Name && *fd.m_Res.m_Name )
				GetWindow().GetTheme().SetFont( fd );
			GetWindow().UpdateLayout( true );
		}

		m_OnLanguageChange( this );
	}

	U1 UiWindow::CreateWindow( const CallbackInfo& ci )
	{
		//App::GetSingleton().GetSysInfo().DebugWaitDebugger( 10000 );

		U1 b = false;
		App::GetSingleton().ExecuteInUiThread( [&]
		{
			if ( Window::CreateWindow() )
			{
				GetWindow().SetUserContext( static_cast<UiControl*>(this) );
				b = true;
			}
		} );

		if ( m_OnCreateContent && !m_OnCreateContent( this ) )
			return false;

		m_Keep.SetEmptyFunc( ci.GetEnv() );

		__ApplyLanguage();

		return b;
	}

	UiWindow * UiWindow::SetDeviceNotification( U1 b )
	{
		if ( m_DeviceNotificationEnable == b )
			return this;
		Ui::IWindowDeviceNotification* p;
		if ( GetNativeWindow().QueryInterface( &p ) )
		{
			if ( b )
				p->GetEvent<Ui::IWindowDeviceNotification::OnDeviceChange>() += MakeThisFunc( __OnDeviceChange );
			else
				p->GetEvent<Ui::IWindowDeviceNotification::OnDeviceChange>() -= MakeThisFunc( __OnDeviceChange );
			m_DeviceNotificationEnable = b;
		}
		return this;
	}

	UiIcon * UiWindow::__CreateManagedIcon( const CallbackInfo & ci, const WrapData<Ui::IconSource>& is )
	{
		if ( auto p = ci.NewJsObject<UiIcon>() )
			return p->SetIcon( CreateManagedIcon( is ) );
		return nullptr;
	}

}
