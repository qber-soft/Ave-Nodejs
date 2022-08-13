#include "StdAfx.h"
#include "UiCheckBox.h"

#define ThisMethod($x) &UiCheckBox::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiCheckBox::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiCheckBox> c_obj;
	}

	void UiCheckBox::DefineControl()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText, WrapObjectGeneric );
		AutoAddMethod( SetValue );
		AutoAddMethod( GetValue, WrapObjectGeneric );
		AutoAddMethod( GetNextValue, WrapObjectGeneric );
		AutoAddMethod( SetTriple );
		AutoAddMethod( GetTriple, WrapObjectGeneric );
		AutoAddMethod( SetCheckBoxStyle );
		AutoAddMethod( GetCheckBoxStyle, WrapObjectGeneric );
		AutoAddMethod( SetVisualTextLayout );
		AutoAddMethod( GetVisualTextLayout, WrapObjectGeneric );
		AutoAddMethod( SetVisual );
		AutoAddMethod( GetVisual, WrapObjectGeneric );

		AutoAddMethod( OnCheck, WrapObjectGeneric );
		AutoAddMethod( OnChecking, WrapObjectGeneric );
	}

	U1 UiCheckBox::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiCheckBox::__OnCheck( Ui::ICheckBox & sender )
	{
		m_OnCheck( this );
	}

	void UiCheckBox::__OnChecking( Ui::ICheckBox & sender, U1 & bCanCheck )
	{
		m_OnChecking.BlockCall( this, bCanCheck );
	}

	UiCheckBox * UiCheckBox::OnCheck( OnCheck_t && fn )
	{
		SetEventCallback<Ui::ICheckBox::OnCheck>( m_OnCheck, std::move( fn ), MakeThisFunc( __OnCheck ) );
		return this;
	}

	UiCheckBox * UiCheckBox::OnChecking( OnChecking_t && fn )
	{
		SetEventCallback<Ui::ICheckBox::OnChecking>( m_OnChecking, std::move( fn ), MakeThisFunc( __OnChecking ) );
		return this;
	}

}
