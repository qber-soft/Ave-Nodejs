#include "StdAfx.h"
#include "UiRibbon.h"
#include "UiRibbonApp.h"
#include "UiRibbonTab.h"
#include "UiToolBar.h"

#define ThisMethod($x) &UiRibbon::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiRibbon::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiRibbon> c_obj;
	}

	void UiRibbon::DefineControl()
	{
		AutoAddMethod( GetApp );
		AutoAddMethod( GetToolBar );
		AutoAddMethod( SetBackground );
		AutoAddMethod( GetBackground );
		AutoAddMethod( SetMinimized );
		AutoAddMethod( GetMinimized );
		AutoAddMethod( SetCanMinimize );
		AutoAddMethod( GetCanMinimize );
		AutoAddMethod( TabGetCount );
		AutoAddMethod( TabAdd );
		AutoAddMethod( TabInsert );
		AutoAddMethod( TabGetByIndex );
		AutoAddMethod( TabGetById );
		AutoAddMethod( TabRemoveByIndex );
		AutoAddMethod( TabRemoveById );
		AutoAddMethod( TabRemove );
		AutoAddMethod( TabRemoveAll );
		AutoAddMethod( TabSelect );
		AutoAddMethod( TabGetRect );
		AutoAddMethod( TabGetContentRect );
		AutoAddMethod( TabGetIndex );
		AutoAddMethod( SetContent );
		AutoAddMethod( GetContent );
		AutoAddMethod( SetAppMenu );
		AutoAddMethod( GetAppMenu );
		AutoAddMethod( SetBackstage );
		AutoAddMethod( GetBackstage );
		AutoAddMethod( SetBackstageVisible );
		AutoAddMethod( GetBackstageVisible );
	}

	U1 UiRibbon::Ctor( const CallbackInfo& ci, UiWindow * p, Napi::Value v )
	{
		m_App = ci.NewJsObjectWithOwnership<UiRibbonApp>();
		if ( !m_App )
			return false;

		m_ToolBar = ci.NewJsObjectWithOwnership<UiToolBar>();
		if ( !m_ToolBar )
			return false;

		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().SetTrackingWindow( &p->PublicGetWindow() );
		GetControlTyped().SetTrackingWindowActivity( true );
		GetControlTyped().SetTrackingWindowMoving( true );

		m_App->SetSharedControl( &GetControlTyped().GetApp() );
		m_ToolBar->SetSharedControl( &GetControlTyped().GetToolBar() );

		return true;
	}

	U1 UiRibbon::TabAdd( UiRibbonTab * pChild )
	{
		return nullptr != GetControlTyped().TabAdd( Ui::RibbonTab( (Ui::IRibbonTab*) pChild->TakeOwnership().Detach() ) );
	}

	U1 UiRibbon::TabInsert( U32 nInsertBefore, UiRibbonTab * pChild )
	{
		return nullptr != GetControlTyped().TabInsert( nInsertBefore, Ui::RibbonTab( (Ui::IRibbonTab*) pChild->TakeOwnership().Detach() ) );
	}

	UiRibbonTab * UiRibbon::TabRemove( UiRibbonTab * pChild )
	{
		return (UiRibbonTab*) (UiControl*) __ChangeContent( (Ui::Control&&) GetControlTyped().TabRemove( (Ui::IRibbonTab*) &pChild->GetControl() ) );
	}

	S32 UiRibbon::TabGetIndex( UiRibbonTab * p )
	{
		return GetControlTyped().TabGetIndex( (Ui::IRibbonTab*) &p->GetControl() );
	}

}
