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
		AutoAddMethod( ItemFind, WrapObjectGeneric );
		AutoAddMethod( ItemSet );
		AutoAddMethod( ItemGet, WrapObjectGeneric );
		AutoAddMethod( ItemGetCount, WrapObjectGeneric );
		AutoAddMethod( ItemGetCountPerPage, WrapObjectGeneric );
		AutoAddMethod( ItemGetSelectionCount, WrapObjectGeneric );
		AutoAddMethod( ItemGetSelection, WrapObjectGeneric );
		AutoAddMethod( ItemIsSelected, WrapObjectGeneric );
		AutoAddMethod( ItemGetNextSelection, WrapObjectGeneric );
		AutoAddMethod( ItemEnsure );
		AutoAddMethod( ItemGetTopIndex, WrapObjectGeneric );
		AutoAddMethod( ItemIsVisible, WrapObjectGeneric );
		AutoAddMethod( ItemGetRect, WrapObjectGeneric );
		AutoAddMethod( ItemHitTest, WrapObjectGeneric );
		AutoAddMethod( ItemSetCount );
		AutoAddMethod( ItemSetHighlight );
		AutoAddMethod( ItemSetMinimumHeight );
		AutoAddMethod( ItemGetMinimumHeight );

		AutoAddMethod( SetVirtual );

		AutoAddMethod( GetHeader, WrapObjectGeneric );
		AutoAddMethod( SetHeaderAutoWidth );
		AutoAddMethod( GetHeaderAutoWidth, WrapObjectGeneric );

		AutoAddMethod( SetScrollPosition );
		AutoAddMethod( GetScrollPosition, WrapObjectGeneric );
		AutoAddMethod( GetScrollSize, WrapObjectGeneric );
		AutoAddMethod( GetScrollMax, WrapObjectGeneric );

		AutoAddMethod( SetSelectionMode );
		AutoAddMethod( GetSelectionMode, WrapObjectGeneric );

		AutoAddMethod( SetViewMode );
		AutoAddMethod( GetViewMode, WrapObjectGeneric );

		AutoAddMethod( SetTileSize );
		AutoAddMethod( GetTileSize, WrapObjectGeneric );
		AutoAddMethod( SetTileColumnPriority );
		AutoAddMethod( GetTileColumnPriority, WrapObjectGeneric );

		AutoAddMethod( SetItemSpace );
		AutoAddMethod( GetItemSpace, WrapObjectGeneric );

		AutoAddMethod( SetTreeStyle );
		AutoAddMethod( GetTreeStyle, WrapObjectGeneric );

		AutoAddMethod( SetItemCheck );
		AutoAddMethod( GetItemCheck, WrapObjectGeneric );

		AutoAddMethod( SetIconSize );
		AutoAddMethod( GetIconSize, WrapObjectGeneric );

		AutoAddMethod( SetIconNameColumn );
		AutoAddMethod( GetIconNameColumn, WrapObjectGeneric );

		AutoAddMethod( SetListItemWidth );
		AutoAddMethod( GetListItemWidth, WrapObjectGeneric );

		AutoAddMethod( GetListRect, WrapObjectGeneric );

		AutoAddMethod( OnSelectionChange /**/, WrapObjectGeneric );
		AutoAddMethod( OnSelectionEnd    /**/, WrapObjectGeneric );
		AutoAddMethod( OnDoubleClick     /**/, WrapObjectGeneric );
		AutoAddMethod( OnRightClick      /**/, WrapObjectGeneric );
		AutoAddMethod( OnDragBegin       /**/, WrapObjectGeneric );
		AutoAddMethod( OnGlyphClick      /**/, WrapObjectGeneric );
		AutoAddMethod( OnItemCheck       /**/, WrapObjectGeneric );
	}

	U1 UiRichListBox::Ctor( const CallbackInfo& ci, UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		m_Header = ci.NewJsObjectWithOwnership<UiHeader>();
		if ( !m_Header )
			return false;
		m_Header->SetSharedControl( &GetControlTyped().GetHeader() );

		GetControlTyped().SetIconManager( Ui::RichListBoxViewMode::Detail, p->PublicCloneIconManager() );
		GetControlTyped().SetIconManager( Ui::RichListBoxViewMode::Tile, p->PublicCloneIconManager() );
		GetControlTyped().SetIconManager( Ui::RichListBoxViewMode::Icon, p->PublicCloneIconManager() );
		GetControlTyped().SetIconManager( Ui::RichListBoxViewMode::List, p->PublicCloneIconManager() );

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
		//if ( !App::GetSingleton().BlockCallTest() )
		//{
		//	auto r = m_Virtual.DirectCall( this, iv.m_Item, iv.m_SubItem );
		//	iv.m_Icon = r.m_Icon;
		//	iv.m_Indent = r.m_Indent;
		//	iv.m_Misc = r.m_Misc;
		//	iv.m_StringData = r.m_String;
		//	return;
		//}
		UiRichListBoxItemVirtual_t r;
		m_Virtual.BlockCall( this, iv.m_Item, iv.m_SubItem, r );
		iv.m_Icon = r.m_Icon;
		iv.m_Indent = r.m_Indent;
		iv.m_Misc = r.m_Misc;
		iv.m_StringData = r.m_String;
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

	WrapData<S32_2> UiRichListBox::GetScrollMax() const
	{
		S32_2 v{};
		if ( GetControlTyped().GetScrollH().GetVisible() )
			v.x = GetControlTyped().GetScrollH().GetMaximum();
		if ( GetControlTyped().GetScrollV().GetVisible() )
			v.y = GetControlTyped().GetScrollV().GetMaximum();
		return v;
	}

	UiRichListBox* UiRichListBox::OnSelectionChange /**/( OnCallback0_t&& fn ) { m_OnSelectionChange /**/ = SetEventCallback<Ui::IRichListBox::OnSelectionChange /**/>( std::move( fn ), MakeThisFunc( __OnSelectionChange /**/ ) ); return this; }
	UiRichListBox* UiRichListBox::OnSelectionEnd    /**/( OnCallback0_t&& fn ) { m_OnSelectionEnd    /**/ = SetEventCallback<Ui::IRichListBox::OnSelectionEnd    /**/>( std::move( fn ), MakeThisFunc( __OnSelectionEnd    /**/ ) ); return this; }
	UiRichListBox* UiRichListBox::OnDoubleClick     /**/( OnCallback1_t&& fn ) { m_OnDoubleClick     /**/ = SetEventCallback<Ui::IRichListBox::OnDoubleClick     /**/>( std::move( fn ), MakeThisFunc( __OnDoubleClick     /**/ ) ); return this; }
	UiRichListBox* UiRichListBox::OnRightClick      /**/( OnCallback1_t&& fn ) { m_OnRightClick      /**/ = SetEventCallback<Ui::IRichListBox::OnRightClick      /**/>( std::move( fn ), MakeThisFunc( __OnRightClick      /**/ ) ); return this; }
	UiRichListBox* UiRichListBox::OnDragBegin       /**/( OnCallback0_t&& fn ) { m_OnDragBegin       /**/ = SetEventCallback<Ui::IRichListBox::OnDragBegin       /**/>( std::move( fn ), MakeThisFunc( __OnDragBegin       /**/ ) ); return this; }
	UiRichListBox* UiRichListBox::OnGlyphClick      /**/( OnCallback1_t&& fn ) { m_OnGlyphClick      /**/ = SetEventCallback<Ui::IRichListBox::OnGlyphClick      /**/>( std::move( fn ), MakeThisFunc( __OnGlyphClick      /**/ ) ); return this; }
	UiRichListBox* UiRichListBox::OnItemCheck       /**/( OnCallback1_t&& fn ) { m_OnItemCheck       /**/ = SetEventCallback<Ui::IRichListBox::OnItemCheck       /**/>( std::move( fn ), MakeThisFunc( __OnItemCheck       /**/ ) ); return this; }
}
