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
		AutoAddMethod( GetText );
		AutoAddMethod( SetValue );
		AutoAddMethod( GetValue );
		AutoAddMethod( GetNextValue );
		AutoAddMethod( SetTriple );
		AutoAddMethod( GetTriple );
		AutoAddMethod( SetCheckBoxStyle );
		AutoAddMethod( GetCheckBoxStyle );

		AutoAddMethod( OnCheck );
		AutoAddMethod( OnChecking );
	}

	U1 UiCheckBox::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::ICheckBox::OnCheck>() += MakeThisFunc( __OnCheck );
		GetControlTyped().GetEvent<Ui::ICheckBox::OnChecking>() += MakeThisFunc( __OnChecking );

		return true;
	}

	void UiCheckBox::__OnCheck( Ui::ICheckBox & sender )
	{
		m_OnCheck( this );
	}

	void UiCheckBox::__OnChecking( Ui::ICheckBox & sender, U1 & bCanCheck )
	{
		if ( m_OnChecking )
		{
			m_OnChecking.WaitAsyncCall( this, [this]( const U1& r )
			{
				if ( r )
					GetControlTyped().SetValue( GetControlTyped().GetNextValue() );
			} );
			bCanCheck = false;
		}
		else
			bCanCheck = true;
	}

}
