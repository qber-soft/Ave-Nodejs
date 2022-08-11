#include "StdAfx.h"
#include "UiListBox.h"

#define ThisMethod($x) &UiListBox::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiListBox::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiListBox> c_obj;
	}

	void UiListBox::DefineControl()
	{
		AutoAddMethod( Append );
		AutoAddMethod( Insert );
		AutoAddMethod( Remove );
		AutoAddMethod( Clear );
		AutoAddMethod( Select );
		AutoAddMethod( SetSelect );
		AutoAddMethod( SetSelectRange );
		AutoAddMethod( Sort );
		AutoAddMethod( Find, WrapObjectGeneric );
		AutoAddMethod( Swap );
		AutoAddMethod( Set );
		AutoAddMethod( Get, WrapObjectGeneric );
		AutoAddMethod( GetCount, WrapObjectGeneric );
		AutoAddMethod( GetSelection, WrapObjectGeneric );
		AutoAddMethod( IsSelected, WrapObjectGeneric );
		AutoAddMethod( GetNextSelection, WrapObjectGeneric );

		AutoAddMethod( Ensure );
		AutoAddMethod( SetTopIndex );
		AutoAddMethod( GetTopIndex, WrapObjectGeneric );
		AutoAddMethod( ItemIsVisible, WrapObjectGeneric );
		AutoAddMethod( ItemGetRect, WrapObjectGeneric );
		AutoAddMethod( ItemHitTest, WrapObjectGeneric );

		AutoAddMethod( SetCount );

		AutoAddMethod( SetVirtual );

		AutoAddMethod( SetSelectionMode );
		AutoAddMethod( GetSelectionMode, WrapObjectGeneric );

		AutoAddMethod( OnSelectionChange, WrapObjectGeneric );
		AutoAddMethod( OnSelectionEnd, WrapObjectGeneric );
		AutoAddMethod( OnDoubleClick, WrapObjectGeneric );
		AutoAddMethod( OnRightClick, WrapObjectGeneric );
	}

	U1 UiListBox::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiListBox::__OnSelectionChange( Ui::IListBox & sender )
	{
		m_OnSelectionChange( this );
	}

	void UiListBox::__OnSelectionEnd( Ui::IListBox & sender )
	{
		m_OnSelectionEnd( this );
	}

	void UiListBox::__OnDoubleClick( Ui::IListBox & sender, S32 nIndex )
	{
		m_OnDoubleClick( this, nIndex );
	}

	void UiListBox::__OnRightClick( Ui::IListBox & sender, S32 nIndex )
	{
		m_OnRightClick( this, nIndex );
	}

	void UiListBox::__OnVirtual( Ui::IListBox & sender, Ui::ListBoxItemVirtual & iv )
	{
		UiListBoxItemVirtual_t r;
		m_Virtual.BlockCall( this, iv.m_Item, r );
		iv.m_Misc = r.m_Misc;
		iv.m_StringData = r.m_String;
	}

	UiListBox * UiListBox::SetVirtual( Virtual_t && fn )
	{
		m_Virtual = std::move( fn );
		if ( m_Virtual )
			GetControlTyped().SetVirtual( MakeThisFunc( __OnVirtual ) );
		else
			GetControlTyped().SetVirtual( {} );
		return this;
	}

	UiListBox* UiListBox::OnSelectionChange /**/( OnSelectionChange_t /**/ && fn ) { SetEventCallback<Ui::IListBox::OnSelectionChange /**/>( m_OnSelectionChange /**/, std::move( fn ), MakeThisFunc( __OnSelectionChange /**/ ) ); return this; }
	UiListBox* UiListBox::OnSelectionEnd    /**/( OnSelectionChange_t /**/ && fn ) { SetEventCallback<Ui::IListBox::OnSelectionEnd    /**/>( m_OnSelectionEnd    /**/, std::move( fn ), MakeThisFunc( __OnSelectionEnd    /**/ ) ); return this; }
	UiListBox* UiListBox::OnDoubleClick     /**/( OnClick_t           /**/ && fn ) { SetEventCallback<Ui::IListBox::OnDoubleClick     /**/>( m_OnDoubleClick     /**/, std::move( fn ), MakeThisFunc( __OnDoubleClick     /**/ ) ); return this; }
	UiListBox* UiListBox::OnRightClick      /**/( OnClick_t           /**/ && fn ) { SetEventCallback<Ui::IListBox::OnRightClick      /**/>( m_OnRightClick      /**/, std::move( fn ), MakeThisFunc( __OnRightClick      /**/ ) ); return this; }

}
