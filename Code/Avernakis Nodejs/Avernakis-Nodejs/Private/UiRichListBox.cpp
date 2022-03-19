#include "StdAfx.h"
#include "UiRichListBox.h"
#include "UiHeader.h"

#define ThisMethod($x) &UiRichListBox::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiRichListBox::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiRichListBox> c_obj;
	}

	void UiRichListBox::DefineControl()
	{
		AutoAddMethod( ItemInsert );
		AutoAddMethod( ItemRemove );
		AutoAddMethod( ItemClear );
		AutoAddMethod( ItemSelect );
		AutoAddMethod( ItemSetSelect );
		AutoAddMethod( ItemSetSelectRange );
		AutoAddMethod( ItemSort );
		AutoAddMethod( ItemFind );
		AutoAddMethod( ItemSet );
		AutoAddMethod( ItemGet );
		AutoAddMethod( ItemGetCount );
		AutoAddMethod( ItemGetCountPerPage );
		AutoAddMethod( ItemGetSelectionCount );
		AutoAddMethod( ItemGetSelection );
		AutoAddMethod( ItemIsSelected );
		AutoAddMethod( ItemGetNextSelection );
		AutoAddMethod( ItemEnsure );
		AutoAddMethod( ItemGetTopIndex );
		AutoAddMethod( ItemIsVisible );
		AutoAddMethod( ItemGetRect );
		AutoAddMethod( ItemHitTest );
		AutoAddMethod( ItemSetCount );
		AutoAddMethod( ItemSetHighlight );
		AutoAddMethod( ItemSetMinimumHeight );
		AutoAddMethod( ItemGetMinimumHeight );

		AutoAddMethod( SetVirtual );

		AutoAddMethod( GetHeader );
		AutoAddMethod( SetHeaderAutoWidth );
		AutoAddMethod( GetHeaderAutoWidth );

		AutoAddMethod( SetScrollPosition );
		AutoAddMethod( GetScrollPosition );

		AutoAddMethod( SetSelectionMode );
		AutoAddMethod( GetSelectionMode );

		AutoAddMethod( SetViewMode );
		AutoAddMethod( GetViewMode );

		AutoAddMethod( SetTileSize );
		AutoAddMethod( GetTileSize );
		AutoAddMethod( SetTileColumnPriority );
		AutoAddMethod( GetTileColumnPriority );

		AutoAddMethod( SetItemSpace );
		AutoAddMethod( GetItemSpace );

		AutoAddMethod( SetTreeStyle );
		AutoAddMethod( GetTreeStyle );

		AutoAddMethod( SetItemCheck );
		AutoAddMethod( GetItemCheck );

		AutoAddMethod( SetIconSize );
		AutoAddMethod( GetIconSize );

		AutoAddMethod( SetIconNameColumn );
		AutoAddMethod( GetIconNameColumn );

		AutoAddMethod( SetListItemWidth );
		AutoAddMethod( GetListItemWidth );

		AutoAddMethod( GetListRect );

		AutoAddMethod( OnSelectionChange /**/ );
		AutoAddMethod( OnSelectionEnd    /**/ );
		AutoAddMethod( OnDoubleClick     /**/ );
		AutoAddMethod( OnRightClick      /**/ );
		AutoAddMethod( OnDragBegin       /**/ );
		AutoAddMethod( OnGlyphClick      /**/ );
		AutoAddMethod( OnItemCheck       /**/ );
	}

	U1 UiRichListBox::Ctor( const CallbackInfo& ci, UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		m_Header = ci.NewJsObject<UiHeader>( true );
		if ( !m_Header )
			return false;
		m_Header->SetSharedControl( &GetControlTyped().GetHeader() );

		GetControlTyped().SetIconManager( Ui::RichListBoxViewMode::Detail, p->PublicCloneIconManager() );
		GetControlTyped().SetIconManager( Ui::RichListBoxViewMode::Tile, p->PublicCloneIconManager() );
		GetControlTyped().SetIconManager( Ui::RichListBoxViewMode::Icon, p->PublicCloneIconManager() );
		GetControlTyped().SetIconManager( Ui::RichListBoxViewMode::List, p->PublicCloneIconManager() );

		GetControlTyped().GetEvent<Ui::IRichListBox::OnSelectionChange /**/>() += MakeThisFunc( __OnSelectionChange /**/ );
		GetControlTyped().GetEvent<Ui::IRichListBox::OnSelectionEnd    /**/>() += MakeThisFunc( __OnSelectionEnd    /**/ );
		GetControlTyped().GetEvent<Ui::IRichListBox::OnDoubleClick     /**/>() += MakeThisFunc( __OnDoubleClick     /**/ );
		GetControlTyped().GetEvent<Ui::IRichListBox::OnRightClick      /**/>() += MakeThisFunc( __OnRightClick      /**/ );
		GetControlTyped().GetEvent<Ui::IRichListBox::OnDragBegin       /**/>() += MakeThisFunc( __OnDragBegin       /**/ );
		GetControlTyped().GetEvent<Ui::IRichListBox::OnGlyphClick      /**/>() += MakeThisFunc( __OnGlyphClick      /**/ );
		GetControlTyped().GetEvent<Ui::IRichListBox::OnItemCheck       /**/>() += MakeThisFunc( __OnItemCheck       /**/ );

		return true;
	}

	void UiRichListBox::__OnSelectionChange( Ui::IRichListBox & sender )
	{
		m_OnSelectionChange( this );
	}

	void UiRichListBox::__OnSelectionEnd( Ui::IRichListBox & sender )
	{
		m_OnSelectionEnd( this );
	}

	void UiRichListBox::__OnDoubleClick( Ui::IRichListBox & sender, S32 nIndex )
	{
		m_OnDoubleClick( this, nIndex );
	}

	void UiRichListBox::__OnRightClick( Ui::IRichListBox & sender, S32 nIndex )
	{
		m_OnRightClick( this, nIndex );
	}

	void UiRichListBox::__OnDragBegin( Ui::IRichListBox & sender )
	{
		m_OnDragBegin( this );
	}

	void UiRichListBox::__OnGlyphClick( Ui::IRichListBox & sender, S32 nIndex )
	{
		m_OnGlyphClick( this, nIndex );
	}

	void UiRichListBox::__OnItemCheck( Ui::IRichListBox & sender, S32 nIndex )
	{
		m_OnItemCheck( this, nIndex );
	}

	void UiRichListBox::__OnVirtual( Ui::IRichListBox & sender, Ui::RichListBoxItemVirtual & iv )
	{
		m_Virtual.BlockAsyncCall( this, iv.m_Item, iv.m_SubItem, [&iv]( const UiRichListBoxItemVirtual_t& r ) {
			iv.m_Icon = r.m_Icon;
			iv.m_Indent = r.m_Indent;
			iv.m_Misc = r.m_Misc;
			iv.m_StringData = r.m_String;
		} );
	}

	S32 UiRichListBox::ItemInsert( const UiRichListBoxItem_t & pItem, U1 bReserveSelection )
	{
		Ui::RichListBoxItem item{};
		item.m_Flag = pItem.m_Flag;
		item.m_Index = pItem.m_Index;
		item.m_IndexSub = pItem.m_IndexSub;
		item.m_Icon = pItem.m_Icon;
		item.m_Text = (PWChar) pItem.m_Text.c_str();
		item.m_Indent = pItem.m_Indent;
		item.m_GroupId = pItem.m_GroupId;
		item.m_Misc = pItem.m_Misc;
		item.m_Context = (void*) (USize) pItem.m_Context;
		return GetControlTyped().ItemInsert( item, bReserveSelection );
	}

	U1 UiRichListBox::ItemSet( const UiRichListBoxItem_t & pItem )
	{
		Ui::RichListBoxItem item{};
		item.m_Flag = pItem.m_Flag;
		item.m_Index = pItem.m_Index;
		item.m_IndexSub = pItem.m_IndexSub;
		item.m_Icon = pItem.m_Icon;
		item.m_Text = (PWChar) pItem.m_Text.c_str();
		item.m_Indent = pItem.m_Indent;
		item.m_GroupId = pItem.m_GroupId;
		item.m_Misc = pItem.m_Misc;
		item.m_Context = (void*) (USize) pItem.m_Context;
		return GetControlTyped().ItemSet( item );
	}

	UiRichListBoxItem_t UiRichListBox::ItemGet( U32 nFlag, S32 nIndex, S32 nSubIndex )
	{
		Ui::RichListBoxItem item{ nFlag, nIndex, nSubIndex };
		WChar szText[1024]{};
		item.m_Text = szText;
		item.m_TextCharLength = CountOf( szText );
		
		UiRichListBoxItem_t r{};
		r.m_Flag = nFlag;
		r.m_Index = nIndex;
		r.m_IndexSub = nSubIndex;
		if ( GetControlTyped().ItemGet( item ) )
		{
			r.m_Icon = item.m_Icon;
			r.m_Text = szText;
			r.m_Indent = item.m_Indent;
			r.m_GroupId = item.m_GroupId;
			r.m_Misc = item.m_Misc;
			r.m_Context = (U32) (USize) item.m_Context;
		}
		return r;
	}

	UiRichListBoxHitTestResult_t UiRichListBox::ItemHitTest( const WrapData<S32_2>& pt, U1 bMustOnContent, U1 bIncludePlaceholder ) const
	{
		UiRichListBoxHitTestResult_t r{};
		if ( bMustOnContent )
			r.m_Index = GetControlTyped().ItemHitTest( pt, r.m_SubIndex, bIncludePlaceholder, &r.m_Place, &r.m_PlaceAb );
		else
			r.m_Index = GetControlTyped().ItemHitTest( pt, false, bIncludePlaceholder, &r.m_Place, &r.m_PlaceAb );
		return r;
	}

	UiRichListBox * UiRichListBox::SetVirtual( Virtual_t && fn )
	{
		m_Virtual = std::move( fn );
		if ( m_Virtual )
			GetControlTyped().SetVirtual( MakeThisFunc( __OnVirtual ) );
		else
			GetControlTyped().SetVirtual( {} );
		return this;
	}

}
