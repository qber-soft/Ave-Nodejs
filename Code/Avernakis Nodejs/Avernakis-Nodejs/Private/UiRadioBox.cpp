#include "StdAfx.h"
#include "UiRadioBox.h"

#define ThisMethod($x) &UiRadioBox::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiRadioBox::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiRadioBox> c_obj;
	}

	void UiRadioBox::DefineControl()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText );
		AutoAddMethod( SetValue );
		AutoAddMethod( GetValue );
		AutoAddMethod( SetGroup );
		AutoAddMethod( GetGroup );

		AutoAddMethod( OnCheck );
		AutoAddMethod( OnChecking );
	}

	U1 UiRadioBox::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::IRadioBox::OnCheck>() += MakeThisFunc( __OnCheck );
		GetControlTyped().GetEvent<Ui::IRadioBox::OnChecking>() += MakeThisFunc( __OnChecking );

		return true;
	}

	void UiRadioBox::__OnCheck( Ui::IRadioBox & sender )
	{
		m_OnCheck( this );
	}

	void UiRadioBox::__OnChecking( Ui::IRadioBox & sender, U1 & bCanChangeValue )
	{
		m_OnChecking.BlockCall( this, bCanChangeValue, bCanChangeValue );
	}

}
