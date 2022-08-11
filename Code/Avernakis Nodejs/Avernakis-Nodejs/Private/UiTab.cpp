#include "StdAfx.h"
#include "UiTab.h"

#define ThisMethod($x) &UiTab::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiTab::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiTab> c_obj;
	}

	void UiTab::DefineControl()
	{
		AutoAddMethod( TabInsert );
		AutoAddMethod( TabGetAll, WrapObjectGeneric );
		AutoAddMethod( TabGet, WrapObjectGeneric );
		AutoAddMethod( TabSet );
		AutoAddMethod( TabRemove );
		AutoAddMethod( TabClear );
		AutoAddMethod( TabSelect );
		AutoAddMethod( TabGetSelection, WrapObjectGeneric );
		AutoAddMethod( TabSetSelected );
		AutoAddMethod( TabGetSelected, WrapObjectGeneric );
		AutoAddMethod( TabGetSelectionCount, WrapObjectGeneric );
		AutoAddMethod( TabGetAllSelection, WrapObjectGeneric );
		AutoAddMethod( TabSetMultipleSelection );
		AutoAddMethod( TabGetMultipleSelection, WrapObjectGeneric );
		AutoAddMethod( TabGetRect, WrapObjectGeneric );
		AutoAddMethod( TabGetHeaderRect, WrapObjectGeneric );
		AutoAddMethod( TabSetDirection );
		AutoAddMethod( TabGetDirection, WrapObjectGeneric );
		AutoAddMethod( TabSetVertical );
		AutoAddMethod( TabGetVertical, WrapObjectGeneric );
		AutoAddMethod( TabSetOverflow );
		AutoAddMethod( TabGetOverflow, WrapObjectGeneric );
		AutoAddMethod( TabSetSort );
		AutoAddMethod( TabGetSort, WrapObjectGeneric );
		AutoAddMethod( TabSetHeaderSize );
		AutoAddMethod( TabGetHeaderSize, WrapObjectGeneric );
		AutoAddMethod( TabSetMaxHeaderSize );
		AutoAddMethod( TabGetMaxHeaderSize, WrapObjectGeneric );
		AutoAddMethod( TabSetUngroupedPosition );
		AutoAddMethod( TabGetUngroupedPosition, WrapObjectGeneric );
		AutoAddMethod( TabSetUngroupedName );
		AutoAddMethod( TabGetUngroupedName, WrapObjectGeneric );
		AutoAddMethod( TabSetReorderable );
		AutoAddMethod( TabGetReorderable, WrapObjectGeneric );
		AutoAddMethod( TabSetRegroup );
		AutoAddMethod( TabGetRegroup, WrapObjectGeneric );
		AutoAddMethod( GroupInsert );
		AutoAddMethod( GroupGetAll, WrapObjectGeneric );
		AutoAddMethod( GroupGet, WrapObjectGeneric );
		AutoAddMethod( GroupSet );
		AutoAddMethod( GroupRemove );
		AutoAddMethod( GroupClear );
		AutoAddMethod( GroupExpand );
		AutoAddMethod( GroupIsExpanded, WrapObjectGeneric );
		AutoAddMethod( GroupSetGlyphVisible );
		AutoAddMethod( GroupGetGlyphVisible, WrapObjectGeneric );
		AutoAddMethod( ButtonClear );
		AutoAddMethod( ButtonSetIcon );
		AutoAddMethod( ButtonGetIcon, WrapObjectGeneric );
		AutoAddMethod( ButtonSetDisplay );
		AutoAddMethod( ButtonGetDisplay, WrapObjectGeneric );
		AutoAddMethod( ButtonSetName );
		AutoAddMethod( ButtonGetName, WrapObjectGeneric );
		AutoAddMethod( HeaderSetNearSize );
		AutoAddMethod( HeaderGetNearSize, WrapObjectGeneric );
		AutoAddMethod( HeaderSetNearContent );
		AutoAddMethod( HeaderGetNearContent, WrapObjectGeneric );
		AutoAddMethod( HeaderSetFarSize );
		AutoAddMethod( HeaderGetFarSize, WrapObjectGeneric );
		AutoAddMethod( HeaderSetFarContent );
		AutoAddMethod( HeaderGetFarContent, WrapObjectGeneric );
		AutoAddMethod( SetSimpleTab );
		AutoAddMethod( GetSimpleTab, WrapObjectGeneric );
		AutoAddMethod( SetSimpleColor );
		AutoAddMethod( GetSimpleColor, WrapObjectGeneric );
		AutoAddMethod( ContentSet );
		AutoAddMethod( ContentGet, WrapObjectGeneric );
		AutoAddMethod( ContentGetRect, WrapObjectGeneric );
		AutoAddMethod( ContentSetMargin );
		AutoAddMethod( ContentGetMargin, WrapObjectGeneric );
		AutoAddMethod( StopReordering );
		AutoAddMethod( SetTabKeyTip );
		AutoAddMethod( GetTabKeyTip, WrapObjectGeneric );
		AutoAddMethod( OnSelectionChange, WrapObjectGeneric );
		AutoAddMethod( OnDoubleClick, WrapObjectGeneric );
		AutoAddMethod( OnRightClick, WrapObjectGeneric );
		AutoAddMethod( OnMiddleClick, WrapObjectGeneric );
		AutoAddMethod( OnDrag, WrapObjectGeneric );
		AutoAddMethod( OnButtonClick, WrapObjectGeneric );
	}

	U1 UiTab::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().SetIconManager( p->PublicCloneIconManager() );

		return true;
	}

	void UiTab::__OnSelectionChange( Ui::ITab & sender )
	{
		m_OnSelectionChange( this );
	}

	void UiTab::__OnDoubleClick( Ui::ITab & sender, U32 nId, Ui::TabObjectType nType )
	{
		m_OnDoubleClick( this, nId, nType );
	}

	void UiTab::__OnRightClick( Ui::ITab & sender, U32 nId, Ui::TabObjectType nType )
	{
		m_OnRightClick( this, nId, nType );
	}

	void UiTab::__OnMiddleClick( Ui::ITab & sender, U32 nId, Ui::TabObjectType nType )
	{
		m_OnMiddleClick( this, nId, nType );
	}

	void UiTab::__OnDrag( Ui::ITab & sender, U32 nId, Ui::TabObjectType nType, const S32_2 & vDragStartPosition )
	{
		m_OnDrag( this, nId, nType, vDragStartPosition );
	}

	void UiTab::__OnButtonClick( Ui::ITab & sender, U32 nId, Ui::TabObjectType nType, U32 nButtonIndex )
	{
		m_OnButtonClick( this, nId, nType, nButtonIndex );
	}

	U1 UiTab::TabInsert( const WrapData<UiTabItem>& pTab )
	{
		Ui::TabItem ti{};
		WrapDataTransit<Ui::TabItem>::Transit( ti, pTab );
		return GetControlTyped().TabInsert( ti );
	}

	WrapData<UiTabItem> UiTab::TabGet( U32 nId ) const
	{
		Ui::TabItem ti{ Ui::TabItem::Flag_Order | Ui::TabItem::Flag_Icon | Ui::TabItem::Flag_Text | Ui::TabItem::Flag_Stack | Ui::TabItem::Flag_Group | Ui::TabItem::Flag_Misc | Ui::TabItem::Flag_Button | Ui::TabItem::Flag_Color };
		WChar szText[1024];
		WChar szStackGroup[1024];
		WChar szStackText[1024];
		ti.m_Id = nId;
		ti.m_Text = szText;
		ti.m_StackGroup = szStackGroup;
		ti.m_StackText = szStackText;
		if ( !GetControlTyped().TabGet( ti ) )
			return {};
		WrapData<UiTabItem> r{};
		WrapDataTransit<Ui::TabItem>::Transit( r, ti );
		return r;
	}

	U1 UiTab::TabSet( const WrapData<UiTabItem>& pTab )
	{
		Ui::TabItem ti{};
		WrapDataTransit<Ui::TabItem>::Transit( ti, pTab );
		return GetControlTyped().TabSet( ti );
	}

	U1 UiTab::GroupInsert( const WrapData<UiTabGroup>& pGroup )
	{
		Ui::TabGroup tg{};
		WrapDataTransit<Ui::TabGroup>::Transit( tg, pGroup );
		return GetControlTyped().GroupInsert( tg );
	}

	WrapData<UiTabGroup> UiTab::GroupGet( U32 nId ) const
	{
		Ui::TabGroup tg{ Ui::TabGroup::Flag_OrderNormal | Ui::TabGroup::Flag_OrderPinned | Ui::TabItem::Flag_Icon | Ui::TabItem::Flag_Text | Ui::TabItem::Flag_Misc | Ui::TabItem::Flag_Button | Ui::TabItem::Flag_Color };
		WChar szText[1024];
		tg.m_Id = nId;
		tg.m_Text = szText;
		if ( !GetControlTyped().GroupGet( tg ) )
			return {};
		WrapData<UiTabGroup> r{};
		WrapDataTransit<Ui::TabGroup>::Transit( r, tg );
		return r;
	}

	U1 UiTab::GroupSet( const WrapData<UiTabGroup>& pGroup )
	{
		Ui::TabGroup tg{};
		WrapDataTransit<Ui::TabGroup>::Transit( tg, pGroup );
		return GetControlTyped().GroupSet( tg );
	}

	UiTab* UiTab::OnSelectionChange /**/( OnSelectionChange_t /**/ && fn ) { SetEventCallback<Ui::ITab::OnSelectionChange /**/>( m_OnSelectionChange /**/, std::move( fn ), MakeThisFunc( __OnSelectionChange /**/ ) ); return this; }
	UiTab* UiTab::OnDoubleClick     /**/( OnTabClick_t        /**/ && fn ) { SetEventCallback<Ui::ITab::OnDoubleClick     /**/>( m_OnDoubleClick     /**/, std::move( fn ), MakeThisFunc( __OnDoubleClick     /**/ ) ); return this; }
	UiTab* UiTab::OnRightClick      /**/( OnTabClick_t        /**/ && fn ) { SetEventCallback<Ui::ITab::OnRightClick      /**/>( m_OnRightClick      /**/, std::move( fn ), MakeThisFunc( __OnRightClick      /**/ ) ); return this; }
	UiTab* UiTab::OnMiddleClick     /**/( OnTabClick_t        /**/ && fn ) { SetEventCallback<Ui::ITab::OnMiddleClick     /**/>( m_OnMiddleClick     /**/, std::move( fn ), MakeThisFunc( __OnMiddleClick     /**/ ) ); return this; }
	UiTab* UiTab::OnDrag            /**/( OnDrag_t            /**/ && fn ) { SetEventCallback<Ui::ITab::OnDrag            /**/>( m_OnDrag            /**/, std::move( fn ), MakeThisFunc( __OnDrag            /**/ ) ); return this; }
	UiTab* UiTab::OnButtonClick     /**/( OnButtonClick_t     /**/ && fn ) { SetEventCallback<Ui::ITab::OnButtonClick     /**/>( m_OnButtonClick     /**/, std::move( fn ), MakeThisFunc( __OnButtonClick     /**/ ) ); return this; }
}
