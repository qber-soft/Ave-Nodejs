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
		AutoAddMethod( TabGetAll );
		AutoAddMethod( TabGet );
		AutoAddMethod( TabSet );
		AutoAddMethod( TabRemove );
		AutoAddMethod( TabClear );
		AutoAddMethod( TabSelect );
		AutoAddMethod( TabGetSelection );
		AutoAddMethod( TabSetSelected );
		AutoAddMethod( TabGetSelected );
		AutoAddMethod( TabGetSelectionCount );
		AutoAddMethod( TabGetAllSelection );
		AutoAddMethod( TabSetMultipleSelection );
		AutoAddMethod( TabGetMultipleSelection );
		AutoAddMethod( TabGetRect );
		AutoAddMethod( TabGetHeaderRect );
		AutoAddMethod( TabSetDirection );
		AutoAddMethod( TabGetDirection );
		AutoAddMethod( TabSetVertical );
		AutoAddMethod( TabGetVertical );
		AutoAddMethod( TabSetOverflow );
		AutoAddMethod( TabGetOverflow );
		AutoAddMethod( TabSetSort );
		AutoAddMethod( TabGetSort );
		AutoAddMethod( TabSetHeaderSize );
		AutoAddMethod( TabGetHeaderSize );
		AutoAddMethod( TabSetMaxHeaderSize );
		AutoAddMethod( TabGetMaxHeaderSize );
		AutoAddMethod( TabSetUngroupedPosition );
		AutoAddMethod( TabGetUngroupedPosition );
		AutoAddMethod( TabSetUngroupedName );
		AutoAddMethod( TabGetUngroupedName );
		AutoAddMethod( TabSetReorderable );
		AutoAddMethod( TabGetReorderable );
		AutoAddMethod( TabSetRegroup );
		AutoAddMethod( TabGetRegroup );
		AutoAddMethod( GroupInsert );
		AutoAddMethod( GroupGetAll );
		AutoAddMethod( GroupGet );
		AutoAddMethod( GroupSet );
		AutoAddMethod( GroupRemove );
		AutoAddMethod( GroupClear );
		AutoAddMethod( GroupExpand );
		AutoAddMethod( GroupIsExpanded );
		AutoAddMethod( GroupSetGlyphVisible );
		AutoAddMethod( GroupGetGlyphVisible );
		AutoAddMethod( ButtonClear );
		AutoAddMethod( ButtonSetIcon );
		AutoAddMethod( ButtonGetIcon );
		AutoAddMethod( ButtonSetDisplay );
		AutoAddMethod( ButtonGetDisplay );
		AutoAddMethod( ButtonSetName );
		AutoAddMethod( ButtonGetName );
		AutoAddMethod( HeaderSetNearSize );
		AutoAddMethod( HeaderGetNearSize );
		AutoAddMethod( HeaderSetNearContent );
		AutoAddMethod( HeaderGetNearContent );
		AutoAddMethod( HeaderSetFarSize );
		AutoAddMethod( HeaderGetFarSize );
		AutoAddMethod( HeaderSetFarContent );
		AutoAddMethod( HeaderGetFarContent );
		AutoAddMethod( SetSimpleTab );
		AutoAddMethod( GetSimpleTab );
		AutoAddMethod( SetSimpleColor );
		AutoAddMethod( GetSimpleColor );
		AutoAddMethod( ContentSet );
		AutoAddMethod( ContentGet );
		AutoAddMethod( ContentGetRect );
		AutoAddMethod( ContentSetMargin );
		AutoAddMethod( ContentGetMargin );
		AutoAddMethod( StopReordering );
		AutoAddMethod( SetTabKeyTip );
		AutoAddMethod( GetTabKeyTip );
		AutoAddMethod( OnSelectionChange );
		AutoAddMethod( OnDoubleClick );
		AutoAddMethod( OnRightClick );
		AutoAddMethod( OnMiddleClick );
		AutoAddMethod( OnDrag );
		AutoAddMethod( OnButtonClick );
	}

	U1 UiTab::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().SetIconManager( p->PublicCloneIconManager() );

		GetControlTyped().GetEvent<Ui::ITab::OnSelectionChange /**/>() += MakeThisFunc( __OnSelectionChange /**/ );
		GetControlTyped().GetEvent<Ui::ITab::OnDoubleClick     /**/>() += MakeThisFunc( __OnDoubleClick     /**/ );
		GetControlTyped().GetEvent<Ui::ITab::OnRightClick      /**/>() += MakeThisFunc( __OnRightClick      /**/ );
		GetControlTyped().GetEvent<Ui::ITab::OnMiddleClick     /**/>() += MakeThisFunc( __OnMiddleClick     /**/ );
		GetControlTyped().GetEvent<Ui::ITab::OnDrag            /**/>() += MakeThisFunc( __OnDrag            /**/ );
		GetControlTyped().GetEvent<Ui::ITab::OnButtonClick     /**/>() += MakeThisFunc( __OnButtonClick     /**/ );

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

}
