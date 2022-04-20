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
		AutoAddMethod( GetText, WrapObjectGeneric );
		AutoAddMethod( SetDetailButton );
		AutoAddMethod( GetDetailButton, WrapObjectGeneric );
		AutoAddMethod( SetVisual );
		AutoAddMethod( GetVisual, WrapObjectGeneric );
		AutoAddMethod( ControlAdd );
		AutoAddMethod( ControlInsert );
		AutoAddMethod( ControlGetByIndex, WrapObjectGeneric );
		AutoAddMethod( ControlGetById, WrapObjectGeneric );
		AutoAddMethod( ControlRemoveByIndex );
		AutoAddMethod( ControlRemoveById );
		AutoAddMethod( ControlRemove );
		AutoAddMethod( ControlRemoveAll );
		AutoAddMethod( OnDetailClick, WrapObjectGeneric );
	}

	U1 UiRibbonGroup::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiRibbonGroup::__OnDetailClick( Ui::IRibbonGroup & sender )
	{
		m_OnClick( this );
	}

	UiRibbonGroup* UiRibbonGroup::OnDetailClick( Callback_t&& fn ) { m_OnClick = SetEventCallback<Ui::IRibbonGroup::OnDetailClick>( std::move( fn ), MakeThisFunc( __OnDetailClick ) ); return this; }

}
