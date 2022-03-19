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
		AutoAddMethod( GetText );
		AutoAddMethod( SetSmall );
		AutoAddMethod( GetSmall );
		AutoAddMethod( SetCheck );
		AutoAddMethod( GetCheck );
		AutoAddMethod( SetButtonType );
		AutoAddMethod( GetButtonType );
		AutoAddMethod( SetDrop );
		AutoAddMethod( GetDrop );
		AutoAddMethod( SetBigVisual );
		AutoAddMethod( GetBigVisual );
		AutoAddMethod( SetSmallVisual );
		AutoAddMethod( GetSmallVisual );
		AutoAddMethod( OnClick );
		AutoAddMethod( OnDrop );
	}

	U1 UiRibbonButton::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::IRibbonButton::OnClick>() += MakeThisFunc( __OnClick );
		GetControlTyped().GetEvent<Ui::IRibbonButton::OnDrop>() += MakeThisFunc( __OnDrop );

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

}
