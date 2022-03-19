#include "StdAfx.h"
#include "UiRibbonTab.h"
#include "UiRibbonGroup.h"

#define ThisMethod($x) &UiRibbonTab::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiRibbonTab::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiRibbonTab> c_obj;
	}

	void UiRibbonTab::DefineControl()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText );
		AutoAddMethod( GroupGetCount );
		AutoAddMethod( GroupAdd );
		AutoAddMethod( GroupInsert );
		AutoAddMethod( GroupGetByIndex );
		AutoAddMethod( GroupGetById );
		AutoAddMethod( GroupRemoveByIndex );
		AutoAddMethod( GroupRemoveById );
		AutoAddMethod( GroupRemove );
		AutoAddMethod( GroupRemoveAll );
	}

	U1 UiRibbonTab::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	U1 UiRibbonTab::GroupAdd( UiRibbonGroup * pChild )
	{
		return nullptr != GetControlTyped().GroupAdd( Ui::RibbonGroup( (Ui::IRibbonGroup*) pChild->TakeOwnership().Detach() ) );
	}

	U1 UiRibbonTab::GroupInsert( U32 nInsertBefore, UiRibbonGroup * pChild )
	{
		return nullptr != GetControlTyped().GroupInsert( nInsertBefore, Ui::RibbonGroup( (Ui::IRibbonGroup*) pChild->TakeOwnership().Detach() ) );
	}

	UiRibbonGroup * UiRibbonTab::GroupRemove( UiRibbonGroup * pChild )
	{
		return (UiRibbonGroup*) (UiControl*) __ChangeContent( (Ui::Control&&) GetControlTyped().GroupRemove( (Ui::IRibbonGroup*) &pChild->GetControl() ) );
	}

}
