#include "StdAfx.h"
#include "UiHeader.h"

#define ThisMethod($x) &UiHeader::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiHeader::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiHeader> c_obj;
	}

	void UiHeader::DefineControl()
	{
		AutoAddMethod( Add );
		AutoAddMethod( Insert );
		AutoAddMethod( GetCount, WrapObjectGeneric );
		AutoAddMethod( Get, WrapObjectGeneric );
		AutoAddMethod( GetRect, WrapObjectGeneric );
		AutoAddMethod( Set );
		AutoAddMethod( Remove );
		AutoAddMethod( RemoveAll );

		AutoAddMethod( ItemSetDownDrop );
		AutoAddMethod( ItemGetDownDrop, WrapObjectGeneric );
		AutoAddMethod( ItemSetFilter );
		AutoAddMethod( ItemGetFilter, WrapObjectGeneric );
		AutoAddMethod( ItemSetCheckValue );
		AutoAddMethod( ItemGetCheckValue, WrapObjectGeneric );

		AutoAddMethod( SetOrder );
		AutoAddMethod( GetOrder, WrapObjectGeneric );

		AutoAddMethod( SetSort );

		AutoAddMethod( GetSortIndex, WrapObjectGeneric );
		AutoAddMethod( GetSortOrder, WrapObjectGeneric );

		AutoAddMethod( SetDrag );
		AutoAddMethod( GetDrag, WrapObjectGeneric );

		AutoAddMethod( SetButton );
		AutoAddMethod( GetButton, WrapObjectGeneric );

		AutoAddMethod( SetCheckMode );
		AutoAddMethod( GetCheckMode, WrapObjectGeneric );

		AutoAddMethod( SetCheckValue );
		AutoAddMethod( GetCheckValue, WrapObjectGeneric );

		AutoAddMethod( OnClick       /**/, WrapObjectGeneric );
		AutoAddMethod( OnAdjustWidth /**/, WrapObjectGeneric );
		AutoAddMethod( OnOrder       /**/, WrapObjectGeneric );
		AutoAddMethod( OnDropDown    /**/, WrapObjectGeneric );
		AutoAddMethod( OnCheckItem   /**/, WrapObjectGeneric );
		AutoAddMethod( OnCheckHeader /**/, WrapObjectGeneric );
	}

	U1 UiHeader::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiHeader::__OnClick( Ui::IHeader & sender, U32 nIndex )
	{
		m_OnClick( this, nIndex );
	}

	void UiHeader::__OnAdjustWidth( Ui::IHeader & sender, U32 nIndex, U1 bAdjusting )
	{
		m_OnAdjustWidth( this, nIndex, bAdjusting );
	}

	void UiHeader::__OnOrder( Ui::IHeader & sender, U32 nNewIndex, U32 nOldIndex )
	{
		m_OnOrder( this, nNewIndex, nOldIndex );
	}

	void UiHeader::__OnDropDown( Ui::IHeader & sender, U32 nIndex )
	{
		m_OnDropDown( this, nIndex );
	}

	void UiHeader::__OnCheckItem( Ui::IHeader & sender, U32 nIndex )
	{
		m_OnCheckItem( this, nIndex );
	}

	void UiHeader::__OnCheckHeader( Ui::IHeader & sender )
	{
		m_OnCheckHeader( this );
	}

	UiHeader * UiHeader::Add( const UiHeaderItem_t & pItem )
	{
		Ui::HeaderItem item{};
		item.m_Flag = pItem.m_Flag;
		item.m_Format = pItem.m_Format;
		item.m_Width = pItem.m_Width;
		item.m_MinWidth = pItem.m_MinWidth;
		item.m_Text = pItem.m_Text.c_str();
		item.m_Context = (void*) (USize) pItem.m_Context;
		GetControlTyped().Add( item );
		return this;
	}

	U1 UiHeader::Insert( U32 nInsertBefore, const UiHeaderItem_t & pItem )
	{
		Ui::HeaderItem item{};
		item.m_Flag = pItem.m_Flag;
		item.m_Format = pItem.m_Format;
		item.m_Width = pItem.m_Width;
		item.m_MinWidth = pItem.m_MinWidth;
		item.m_Text = pItem.m_Text.c_str();
		item.m_Context = (void*) (USize) pItem.m_Context;
		return GetControlTyped().Insert( nInsertBefore, item );
	}

	UiHeaderItem_t UiHeader::Get( U32 nIndex )
	{
		UiHeaderItem_t r{};
		if ( auto p = GetControlTyped().Get( nIndex ) )
		{
			r.m_Format = p->m_Format;
			r.m_Width = p->m_Width;
			r.m_MinWidth = p->m_MinWidth;
			r.m_Text = p->m_Text;
			r.m_Context = (U32) (USize) p->m_Context;
		}
		return r;
	}

	U1 UiHeader::Set( U32 nIndex, const UiHeaderItem_t & pItem )
	{
		Ui::HeaderItem item{};
		item.m_Flag = pItem.m_Flag;
		item.m_Format = pItem.m_Format;
		item.m_Width = pItem.m_Width;
		item.m_MinWidth = pItem.m_MinWidth;
		item.m_Text = pItem.m_Text.c_str();
		item.m_Context = (void*) (USize) pItem.m_Context;
		return GetControlTyped().Set( nIndex, item );
	}

	UiHeader * UiHeader::OnClick       /**/( OnCallback1_t   /**/ && fn ) { m_OnClick       /**/ = SetEventCallback<Ui::IHeader::OnClick       /**/>( std::move( fn ), MakeThisFunc( __OnClick       /**/ ) ); return this; }
	UiHeader * UiHeader::OnAdjustWidth /**/( OnAdjustWidth_t /**/ && fn ) { m_OnAdjustWidth /**/ = SetEventCallback<Ui::IHeader::OnAdjustWidth /**/>( std::move( fn ), MakeThisFunc( __OnAdjustWidth /**/ ) ); return this; }
	UiHeader * UiHeader::OnOrder       /**/( OnOrder_t       /**/ && fn ) { m_OnOrder       /**/ = SetEventCallback<Ui::IHeader::OnOrder       /**/>( std::move( fn ), MakeThisFunc( __OnOrder       /**/ ) ); return this; }
	UiHeader * UiHeader::OnDropDown    /**/( OnCallback1_t   /**/ && fn ) { m_OnDropDown    /**/ = SetEventCallback<Ui::IHeader::OnDropDown    /**/>( std::move( fn ), MakeThisFunc( __OnDropDown    /**/ ) ); return this; }
	UiHeader * UiHeader::OnCheckItem   /**/( OnCallback1_t   /**/ && fn ) { m_OnCheckItem   /**/ = SetEventCallback<Ui::IHeader::OnCheckItem   /**/>( std::move( fn ), MakeThisFunc( __OnCheckItem   /**/ ) ); return this; }
	UiHeader * UiHeader::OnCheckHeader /**/( OnCallback0_t   /**/ && fn ) { m_OnCheckHeader /**/ = SetEventCallback<Ui::IHeader::OnCheckHeader /**/>( std::move( fn ), MakeThisFunc( __OnCheckHeader /**/ ) ); return this; }

}
