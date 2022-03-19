#include "StdAfx.h"
#include "Test.h"

#include "WrapData.h"

#define ThisMethod($x) &Test::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, ThisMethod( $x ) )

namespace Nav
{

	namespace
	{
		ObjectRegister<Test> c_obj;
	}

	void Test::DefineObject()
	{
		AutoAddMethod( SetX );
		AutoAddMethod( GetX );

		AutoAddMethod( SetY );
		AutoAddMethod( GetY );

		AutoAddMethod( TestString );

		AutoAddMethod( ShowTestWindow );

		AutoAddMethod( ThrowJsException );
	}

	U1 Test::Ctor( S32 x, S32 y )
	{
		m_Pos = { x, y };
		return true;
	}

	void Test::SetX( S32 x )
	{
		m_Pos.x = x;
	}

	void Test::SetY( S32 y )
	{
		m_Pos.y = y;
	}

	S32 Test::GetX() const
	{
		return m_Pos.x;
	}

	S32 Test::GetY() const
	{
		return m_Pos.y;
	}

	WString Test::TestString( PCWChar szMessage ) const
	{
		return WString( szMessage ) + AveWide( "我好啊" );
	}

	WString Test::ShowTestWindow()
	{
		auto app = AveKak.CreateAppScope();
		{
			auto theme = AveKak.Create<Ave::Ui::IThemeImage>();
			if ( !theme )
				return AveWide( "Failed to create theme." );

			auto dark = AveKak.Create<Ave::Ui::IThemeImagePredefinedStyle_HyperOnyx>();
			dark->SetStyle( *theme, 0, {} );

			Ave::Ui::IWindow::CreationParam cpWindow{};
			cpWindow.m_Theme = theme;
			cpWindow.m_Device.m_DeviceType = Ave::Ui::WindowDeviceType::Byo2;
			cpWindow.m_Device.m_DeviceId = AveGuidOf( Ave::Byo2::IDeviceD2D1 );
			cpWindow.m_Window.m_Title = AveWide( "Test Window" );
			cpWindow.m_Window.m_Flag = Ave::Ui::IWindowNative::CreationParam::Flag_Default;
			cpWindow.m_Window.m_Flag |= Ave::Ui::IWindowNative::CreationParam::Flag_CustomFrame;
			cpWindow.m_Window.m_Flag |= Ave::Ui::IWindowNative::CreationParam::Flag_Layered;

			auto window = AveKak.Create<Ave::Ui::IWindow>( cpWindow );
			if ( !window )
				return AveWide( "Failed to initialize window." );

			if ( !window->Create() )
				return AveWide( "Failed to create window." );

			window->SetFrame( window->GetTheme().GetFactory().Create<Ave::Ui::IWindowFrame>() );

			window->SetVisible( true );
			window->GetNativeWindow().Activate();

			AveKak.GetApp().Run();

			return AveWide( "Window closed." );
		}
	}

	void Test::ThrowJsException( const CallbackInfo & ci, S32 x )
	{
		ci.ThrowJsException( "Throw exception, x is %0%."_strfp % x );
	}

}
