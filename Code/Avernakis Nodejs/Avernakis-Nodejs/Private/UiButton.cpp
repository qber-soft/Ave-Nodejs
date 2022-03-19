#include "StdAfx.h"
#include "UiButton.h"

#define ThisMethod($x) &UiButton::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiButton::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiButton> c_obj;
	}

	void UiButton::DefineControl()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText );
		AutoAddMethod( SetButtonType );
		AutoAddMethod( GetButtonType );
		AutoAddMethod( SetButtonStyle );
		AutoAddMethod( GetButtonStyle );
		AutoAddMethod( SetDrop );
		AutoAddMethod( GetDrop );
		AutoAddMethod( SetAlignHorz );
		AutoAddMethod( GetAlignHorz );
		AutoAddMethod( SetVisualTextLayout );
		AutoAddMethod( GetVisualTextLayout );
		AutoAddMethod( SetVisual );
		AutoAddMethod( GetVisual );

		AutoAddMethod( OnClick );
		AutoAddMethod( OnDrop );
	}

	U1 UiButton::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::IButton::OnClick>() += MakeThisFunc( __OnClick );
		GetControlTyped().GetEvent<Ui::IButton::OnDrop>() += MakeThisFunc( __OnDrop );

		return true;
	}

	void UiButton::__OnClick( Ui::IButton & sender )
	{
		m_OnClick( this );
	}

	void UiButton::__OnDrop( Ui::IButton & sender )
	{
		m_OnDrop( this );
	}

}
