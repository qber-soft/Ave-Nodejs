#include "StdAfx.h"
#include "UiGrid.h"

#define ThisMethod($x) &UiGrid::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiGrid::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiGridControl> c_gc;
		ObjectRegister<UiGrid> c_obj;
	}

	void UiGridControl::DefineObject()
	{
#	define __AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, &UiGridControl::$x )
		__AutoAddMethod( GetControl );

		__AutoAddMethod( SetDock );
		__AutoAddMethod( GetDock, WrapObjectGeneric );
		__AutoAddMethod( SetAnchor );
		__AutoAddMethod( GetAnchor, WrapObjectGeneric );
		__AutoAddMethod( SetMargin );
		__AutoAddMethod( GetMargin, WrapObjectGeneric );
		__AutoAddMethod( SetGrid );
		__AutoAddMethod( GetGrid, WrapObjectGeneric );
		__AutoAddMethod( SetPos );
		__AutoAddMethod( SetSize );
		__AutoAddMethod( SetPosZ );
		__AutoAddMethod( GetPosZ, WrapObjectGeneric );
		__AutoAddMethod( BringToFront );
		__AutoAddMethod( BringToBack );
#	undef __AutoAddMethod
	}

	void UiGrid::DefineControl()
	{
		AutoAddMethod( SetBackground );
		AutoAddMethod( GetBackground, WrapObjectGeneric );

		AutoAddMethod( SetBackColor );
		AutoAddMethod( GetBackColor, WrapObjectGeneric );

		AutoAddMethod( SetSplitterX );
		AutoAddMethod( GetSplitterX, WrapObjectGeneric );
		AutoAddMethod( SetSplitterY );
		AutoAddMethod( GetSplitterY, WrapObjectGeneric );

		AutoAddMethod( RowClear );
		AutoAddMethod( RowGetCount, WrapObjectGeneric );
		AutoAddMethod( RowGetOffset, WrapObjectGeneric );
		AutoAddMethod( RowGetSize, WrapObjectGeneric );
		AutoAddMethod( RowGetDef, WrapObjectGeneric );
		AutoAddMethod( RowAdd );
		AutoAddMethod( RowInsert );
		AutoAddMethod( RowRemove );
		AutoAddMethod( RowSet );
		AutoAddMethod( RowSetDef );

		AutoAddMethod( ColClear );
		AutoAddMethod( ColGetCount, WrapObjectGeneric );
		AutoAddMethod( ColGetOffset, WrapObjectGeneric );
		AutoAddMethod( ColGetSize, WrapObjectGeneric );
		AutoAddMethod( ColGetDef, WrapObjectGeneric );
		AutoAddMethod( ColAdd );
		AutoAddMethod( ColInsert );
		AutoAddMethod( ColRemove );
		AutoAddMethod( ColSet );
		AutoAddMethod( ColSetDef );

		AutoAddMethod( ControlAdd );
		AutoAddMethod( ControlGet, WrapObjectMix );
		AutoAddMethod( ControlRemove );
		AutoAddMethod( ControlRemoveAll );
	}

	U1 UiGrid::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;
		return true;
	}

	UiGridControl* UiGrid::__GridGetControl( const MixCallContext& cc, UiControl * p )
	{
		if ( MixCallStage::InUi == cc.GetStage() )
		{
			cc.SetUserContext( GetControlTyped().GridGetControl( &p->GetControl() ) );
		}
		else if ( MixCallStage::PostUi == cc.GetStage() )
		{
			auto gc = (Ui::IGridControl*) cc.GetUserContext();
			if ( !gc )
				return nullptr;
			if ( auto uigc = cc.NewJsObject<UiGridControl>() )
			{
				uigc->SetControl( gc );
				return uigc;
			}
		}
		return nullptr;
	}

}
