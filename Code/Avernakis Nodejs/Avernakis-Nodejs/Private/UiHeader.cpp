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
		AutoAddMethod( GetCount );
		AutoAddMethod( Get );
		AutoAddMethod( GetRect );
		AutoAddMethod( Set );
		AutoAddMethod( Remove );
		AutoAddMethod( RemoveAll );

		AutoAddMethod( ItemSetDownDrop );
		AutoAddMethod( ItemGetDownDrop );
		AutoAddMethod( ItemSetFilter );
		AutoAddMethod( ItemGetFilter );
		AutoAddMethod( ItemSetCheckValue );
		AutoAddMethod( ItemGetCheckValue );

		AutoAddMethod( SetOrder );
		AutoAddMethod( GetOrder );

		AutoAddMethod( SetSort );

		AutoAddMethod( GetSortIndex );
		AutoAddMethod( GetSortOrder );

		AutoAddMethod( SetDrag );
		AutoAddMethod( GetDrag );

		AutoAddMethod( SetButton );
		AutoAddMethod( GetButton );

		AutoAddMethod( SetCheckMode );
		AutoAddMethod( GetCheckMode );

		AutoAddMethod( SetCheckValue );
		AutoAddMethod( GetCheckValue );

		AutoAddMethod( OnClick       /**/ );
		AutoAddMethod( OnAdjustWidth /**/ );
		AutoAddMethod( OnOrder       /**/ );
		AutoAddMethod( OnDropDown    /**/ );
		AutoAddMethod( OnCheckItem   /**/ );
		AutoAddMethod( OnCheckHeader /**/ );
	}

	U1 UiHeader::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::IHeader::OnClick       /**/>() += MakeThisFunc( __OnClick       /**/ );
		GetControlTyped().GetEvent<Ui::IHeader::OnAdjustWidth /**/>() += MakeThisFunc( __OnAdjustWidth /**/ );
		GetControlTyped().GetEvent<Ui::IHeader::OnOrder       /**/>() += MakeThisFunc( __OnOrder       /**/ );
		GetControlTyped().GetEvent<Ui::IHeader::OnDropDown    /**/>() += MakeThisFunc( __OnDropDown    /**/ );
		GetControlTyped().GetEvent<Ui::IHeader::OnCheckItem   /**/>() += MakeThisFunc( __OnCheckItem   /**/ );
		GetControlTyped().GetEvent<Ui::IHeader::OnCheckHeader /**/>() += MakeThisFunc( __OnCheckHeader /**/ );

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

}
