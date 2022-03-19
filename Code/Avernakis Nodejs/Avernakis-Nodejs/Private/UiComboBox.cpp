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
		AutoAddMethod( Find );
		AutoAddMethod( Set );
		AutoAddMethod( Get );
		AutoAddMethod( GetCount );
		AutoAddMethod( GetSelection );

		AutoAddMethod( SetCount );

		AutoAddMethod( SetMode );
		AutoAddMethod( GetMode );

		AutoAddMethod( SetDropHeight );
		AutoAddMethod( GetDropHeight );

		AutoAddMethod( SetFindExact );
		AutoAddMethod( GetFindExact );

		AutoAddMethod( SetFindCaseInsensitive );
		AutoAddMethod( GetFindCaseInsensitive );

		AutoAddMethod( SetBorder );
		AutoAddMethod( GetBorder );

		AutoAddMethod( OnSelectionChange );
	}

	U1 UiComboBox::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::IComboBox::OnSelectionChange>() += MakeThisFunc( __OnSelectionChange );

		return true;
	}

	void UiComboBox::__OnSelectionChange( Ui::IComboBox & sender )
	{
		m_OnSelectionChange( this );
	}

}
