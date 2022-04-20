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
		AutoAddMethod( GetText, WrapObjectGeneric );
		AutoAddMethod( SetValue );
		AutoAddMethod( GetValue, WrapObjectGeneric );
		AutoAddMethod( SetGroup );
		AutoAddMethod( GetGroup, WrapObjectGeneric );

		AutoAddMethod( OnCheck, WrapObjectGeneric );
		AutoAddMethod( OnChecking, WrapObjectGeneric );
	}

	U1 UiRadioBox::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

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

	UiRadioBox* UiRadioBox::OnCheck( OnCheck_t&& fn ) { m_OnCheck = SetEventCallback<Ui::IRadioBox::OnCheck>( std::move( fn ), MakeThisFunc( __OnCheck ) ); return this; }
	UiRadioBox* UiRadioBox::OnChecking( OnChecking_t&& fn ) { m_OnChecking = SetEventCallback<Ui::IRadioBox::OnChecking>( std::move( fn ), MakeThisFunc( __OnChecking ) ); return this; }
}
