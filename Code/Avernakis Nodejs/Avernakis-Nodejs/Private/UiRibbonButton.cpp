#include "StdAfx.h"
#include "UiRibbonButton.h"

#define ThisMethod($x) &UiRibbonButton::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiRibbonButton::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiRibbonButton> c_obj;
	}

	void UiRibbonButton::DefineControl()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText, WrapObjectGeneric );
		AutoAddMethod( SetSmall );
		AutoAddMethod( GetSmall, WrapObjectGeneric );
		AutoAddMethod( SetCheck );
		AutoAddMethod( GetCheck, WrapObjectGeneric );
		AutoAddMethod( SetButtonType );
		AutoAddMethod( GetButtonType, WrapObjectGeneric );
		AutoAddMethod( SetDrop );
		AutoAddMethod( GetDrop, WrapObjectGeneric );
		AutoAddMethod( SetBigVisual );
		AutoAddMethod( GetBigVisual, WrapObjectGeneric );
		AutoAddMethod( SetSmallVisual );
		AutoAddMethod( GetSmallVisual, WrapObjectGeneric );
		AutoAddMethod( OnClick, WrapObjectGeneric );
		AutoAddMethod( OnDrop, WrapObjectGeneric );
	}

	U1 UiRibbonButton::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiRibbonButton::__OnClick( Ui::IRibbonButton & sender )
	{
		m_OnClick( this );
	}

	void UiRibbonButton::__OnDrop( Ui::IRibbonButton & sender )
	{
		m_OnDrop( this );
	}

	UiRibbonButton* UiRibbonButton::OnClick /**/( Callback_t&& fn ) { SetEventCallback<Ui::IRibbonButton::OnClick /**/>( m_OnClick /**/, std::move( fn ), MakeThisFunc( __OnClick /**/ ) ); return this; }
	UiRibbonButton* UiRibbonButton::OnDrop  /**/( Callback_t&& fn ) { SetEventCallback<Ui::IRibbonButton::OnDrop  /**/>( m_OnDrop  /**/, std::move( fn ), MakeThisFunc( __OnDrop  /**/ ) ); return this; }
}
