#include "StdAfx.h"
#include "UiRibbonGroup.h"

#define ThisMethod($x) &UiRibbonGroup::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiRibbonGroup::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiRibbonGroup> c_obj;
	}

	void UiRibbonGroup::DefineControl()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText );
		AutoAddMethod( SetDetailButton );
		AutoAddMethod( GetDetailButton );
		AutoAddMethod( SetVisual );
		AutoAddMethod( GetVisual );
		AutoAddMethod( ControlAdd );
		AutoAddMethod( ControlInsert );
		AutoAddMethod( ControlGetByIndex );
		AutoAddMethod( ControlGetById );
		AutoAddMethod( ControlRemoveByIndex );
		AutoAddMethod( ControlRemoveById );
		AutoAddMethod( ControlRemove );
		AutoAddMethod( ControlRemoveAll );
		AutoAddMethod( OnDetailClick );
	}

	U1 UiRibbonGroup::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::IRibbonGroup::OnDetailClick>() += MakeThisFunc( __OnDetailClick );

		return true;
	}

	void UiRibbonGroup::__OnDetailClick( Ui::IRibbonGroup & sender )
	{
		m_OnClick( this );
	}

}
