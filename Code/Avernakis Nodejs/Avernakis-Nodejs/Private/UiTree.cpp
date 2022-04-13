#include "StdAfx.h"
#include "UiTree.h"

#define ThisMethod($x) &UiTree::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiTree::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiTree> c_obj;
	}

	void UiTree::DefineControl()
	{
		AutoAddMethod( ItemInsert );
		AutoAddMethod( ItemRemove );
		AutoAddMethod( ItemClear );
		AutoAddMethod( ItemSelect );
		AutoAddMethod( ItemSetSelected );
		AutoAddMethod( ItemSort );
		AutoAddMethod( ItemSet );
		AutoAddMethod( ItemGet );
		AutoAddMethod( ItemGetNext );
		AutoAddMethod( ItemGetCountPerPage );
		AutoAddMethod( ItemGetSelectionCount );
		AutoAddMethod( ItemGetSelection );
		AutoAddMethod( ItemGetSelected );
		AutoAddMethod( ItemGetSelectionAll );
		AutoAddMethod( ItemEnsure );
		AutoAddMethod( ItemGetTop );
		AutoAddMethod( ItemGetTopIndex );
		AutoAddMethod( ItemSetTopIndex );
		AutoAddMethod( ItemIsVisible );
		AutoAddMethod( ItemGetRect );
		AutoAddMethod( ItemHitTest );
		AutoAddMethod( ItemExpand );
		AutoAddMethod( ItemIsExpanded );
		AutoAddMethod( ItemEdit );
		AutoAddMethod( ItemIsEdit );
		AutoAddMethod( ItemEditFinish );
		AutoAddMethod( ItemSetHighlight );
		AutoAddMethod( SetAutoEdit );
		AutoAddMethod( GetAutoEdit );
		AutoAddMethod( SetAutoScrollOnHover );
		AutoAddMethod( GetAutoScrollOnHover );
		AutoAddMethod( SetNodeLine );
		AutoAddMethod( GetNodeLine );
		AutoAddMethod( SetNodeLineHighlight );
		AutoAddMethod( GetNodeLineHighlight );
		AutoAddMethod( SetSingleClickExpand );
		AutoAddMethod( GetSingleClickExpand );
		AutoAddMethod( SetSelectionMode );
		AutoAddMethod( GetSelectionMode );
		AutoAddMethod( SetIndentWidth );
		AutoAddMethod( GetIndentWidth );
		AutoAddMethod( SetScrollPosition );
		AutoAddMethod( GetScrollPosition );
		AutoAddMethod( GetScrollSize );
		AutoAddMethod( GetScrollMax );
		AutoAddMethod( OnSelectionChange );
		AutoAddMethod( OnDoubleClick );
		AutoAddMethod( OnRightClick );
		AutoAddMethod( OnEditBegin );
		AutoAddMethod( OnEditEnd );
		AutoAddMethod( OnEditFinish );
		AutoAddMethod( OnDragBegin );
	}

	U1 UiTree::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().SetIconManager( p->PublicCloneIconManager() );

		GetControlTyped().GetEvent<Ui::ITree::OnSelectionChange /**/>() += MakeThisFunc( __OnSelectionChange /**/ );
		GetControlTyped().GetEvent<Ui::ITree::OnDoubleClick     /**/>() += MakeThisFunc( __OnDoubleClick     /**/ );
		GetControlTyped().GetEvent<Ui::ITree::OnRightClick      /**/>() += MakeThisFunc( __OnRightClick      /**/ );
		GetControlTyped().GetEvent<Ui::ITree::OnEditBegin       /**/>() += MakeThisFunc( __OnEditBegin       /**/ );
		GetControlTyped().GetEvent<Ui::ITree::OnEditEnd         /**/>() += MakeThisFunc( __OnEditEnd         /**/ );
		GetControlTyped().GetEvent<Ui::ITree::OnEditFinish      /**/>() += MakeThisFunc( __OnEditFinish      /**/ );
		GetControlTyped().GetEvent<Ui::ITree::OnDragBegin       /**/>() += MakeThisFunc( __OnDragBegin       /**/ );

		return true;
	}

	UiTreeItemHandle UiTree::ItemInsert( const WrapData<UiTreeInsert>& pInsert )
	{
		Ui::TreeInsert ti{};
		ti.m_Parent = Hj2c( pInsert.m_Parent );
		ti.m_After = Hj2c( pInsert.m_After );
		ti.m_Item.m_Flag = pInsert.m_Item.m_Flag;
		ti.m_Item.m_Icon = pInsert.m_Item.m_Icon;
		ti.m_Item.m_Text = (PWChar) pInsert.m_Item.m_Text.c_str();
		ti.m_Item.m_Blank = pInsert.m_Item.m_Blank;
		if ( GetControlTyped().ItemInsert( ti ) )
			return Hc2j( ti.m_Item.m_Item );
		return 0;
	}

	U1 UiTree::ItemSet( const WrapData<UiTreeItem>& pItem )
	{
		Ui::TreeItem ti{};
		ti.m_Flag = pItem.m_Flag;
		ti.m_Icon = pItem.m_Icon;
		ti.m_Text = (PWChar) pItem.m_Text.c_str();
		ti.m_Item = Hj2c( pItem.m_Item );
		ti.m_Blank = pItem.m_Blank;
		return GetControlTyped().ItemSet( ti );
	}

	WrapData<UiTreeItem> UiTree::ItemGet( UiTreeItemHandle pItem )
	{
		Ui::TreeItem ti{ Ui::TreeItem::Flag_Text | Ui::TreeItem::Flag_Icon | Ui::TreeItem::Flag_Blank };
		WChar szText[2048];
		ti.m_Item = Hj2c( pItem );
		ti.m_Text = szText;
		ti.m_TextCharLength = CountOf( szText );
		WrapData<UiTreeItem> r{};
		if ( GetControlTyped().ItemGet( ti ) )
		{
			r.m_Flag = ti.m_Flag;
			r.m_Icon = ti.m_Icon;
			r.m_Text = ti.m_Text;
			r.m_Item = pItem;
			r.m_Blank = ti.m_Blank;
		}
		return r;
	}

	List<UiTreeItemHandle> UiTree::ItemGetSelectionAll() const
	{
		auto v = GetControlTyped().ItemGetSelectionAll();
		List<UiTreeItemHandle> vr( v.Size() );
		for ( auto& i : v.RangeIndexAll() )
			vr[i.Index] = Hc2j( *i );
		return std::move( vr );
	}

	WrapData<UiTreeHitTestResult> UiTree::ItemHitTest( const WrapData<S32_2>& pt )
	{
		WrapData<UiTreeHitTestResult> r{};
		r.m_Item = Hc2j( GetControlTyped().ItemHitTest( pt, &r.m_Part, &r.m_Place, &r.m_PlaceAb ) );
		return r;
	}

	WrapData<S32_2> UiTree::GetScrollMax() const
	{
		S32_2 v{};
		if ( GetControlTyped().GetScrollH().GetVisible() )
			v.x = GetControlTyped().GetScrollH().GetMaximum();
		if ( GetControlTyped().GetScrollV().GetVisible() )
			v.y = GetControlTyped().GetScrollV().GetMaximum();
		return v;
	}

	void UiTree::__OnSelectionChange( Ui::ITree & sender )
	{
		m_OnSelectionChange( this );
	}

	void UiTree::__OnDoubleClick( Ui::ITree & sender, Ui::TreeItemHandle pItem, U1 & bCanToggle )
	{
		m_OnDoubleClick( this, Hc2j( pItem ) );
	}

	void UiTree::__OnRightClick( Ui::ITree & sender, Ui::TreeItemHandle pItem )
	{
		m_OnRightClick( this, Hc2j( pItem ) );
	}

	void UiTree::__OnEditBegin( Ui::ITree & sender, Ui::TreeItemHandle pItem, WString & sEdit, U1 & bCanEdit )
	{
		UiTreeEdit te{ sEdit, bCanEdit };
		WrapData<UiTreeEdit> r;
		m_OnEditBegin.BlockCall( this, Hc2j( pItem ), te, r );
		sEdit = r.m_Text;
		bCanEdit = r.m_CanEdit;
	}

	void UiTree::__OnEditEnd( Ui::ITree & sender, Ui::TreeItemHandle pItem, WString & sEdit, U1 & bCanEdit )
	{
		UiTreeEdit te{ sEdit, bCanEdit };
		WrapData<UiTreeEdit> r;
		m_OnEditEnd.BlockCall( this, Hc2j( pItem ), te, r );
		sEdit = r.m_Text;
		bCanEdit = r.m_CanEdit;
	}

	void UiTree::__OnEditFinish( Ui::ITree & sender, Ui::TreeItemHandle pItem, const WString & sEdit, U1 bCanceled )
	{
		UiTreeEditFinish te{ sEdit, bCanceled };
		m_OnEditFinish( this, Hc2j( pItem ), te );
	}

	void UiTree::__OnDragBegin( Ui::ITree & sender, U1 & bCanDrag )
	{
		m_OnDragBegin.BlockCall( this, bCanDrag );
	}

}
