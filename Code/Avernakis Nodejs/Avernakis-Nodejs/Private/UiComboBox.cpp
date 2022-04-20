#include "StdAfx.h"
#include "UiComboBox.h"

#define ThisMethod($x) &UiComboBox::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiComboBox::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiComboBox> c_obj;
	}

	void UiComboBox::DefineControl()
	{
		AutoAddMethod( Append );
		AutoAddMethod( Insert );
		AutoAddMethod( Remove );
		AutoAddMethod( Clear );
		AutoAddMethod( Select );
		AutoAddMethod( Sort );
		AutoAddMethod( Find, WrapObjectGeneric );
		AutoAddMethod( Set );
		AutoAddMethod( Get, WrapObjectGeneric );
		AutoAddMethod( GetCount, WrapObjectGeneric );
		AutoAddMethod( GetSelection, WrapObjectGeneric );

		AutoAddMethod( SetCount );

		AutoAddMethod( SetMode );
		AutoAddMethod( GetMode, WrapObjectGeneric );

		AutoAddMethod( SetDropHeight );
		AutoAddMethod( GetDropHeight, WrapObjectGeneric );

		AutoAddMethod( SetFindExact );
		AutoAddMethod( GetFindExact, WrapObjectGeneric );

		AutoAddMethod( SetFindCaseInsensitive );
		AutoAddMethod( GetFindCaseInsensitive, WrapObjectGeneric );

		AutoAddMethod( SetBorder );
		AutoAddMethod( GetBorder, WrapObjectGeneric );

		AutoAddMethod( OnSelectionChange, WrapObjectGeneric );
	}

	U1 UiComboBox::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiComboBox::__OnSelectionChange( Ui::IComboBox & sender )
	{
		m_OnSelectionChange( this );
	}

	UiComboBox * UiComboBox::OnSelectionChange( OnSelectionChange_t && fn )
	{
		m_OnSelectionChange = SetEventCallback<Ui::IComboBox::OnSelectionChange>( std::move( fn ), MakeThisFunc( __OnSelectionChange ) );
		return this;
	}

}
