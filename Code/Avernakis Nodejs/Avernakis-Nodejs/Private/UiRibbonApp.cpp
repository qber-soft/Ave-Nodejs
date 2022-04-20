#include "StdAfx.h"
#include "UiRibbonApp.h"

#define ThisMethod($x) &UiRibbonApp::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiRibbonApp::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiRibbonApp> c_obj;
	}

	void UiRibbonApp::DefineControl()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText, WrapObjectGeneric );

		AutoAddMethod( OnClick, WrapObjectGeneric );
	}

	U1 UiRibbonApp::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiRibbonApp::__OnClick( Ui::IRibbonApp & sender )
	{
		m_OnClick( this );
	}

	UiRibbonApp* UiRibbonApp::OnClick( Callback_t&& fn ) { m_OnClick = SetEventCallback<Ui::IRibbonApp::OnClick>( std::move( fn ), MakeThisFunc( __OnClick ) ); return this; }

}
