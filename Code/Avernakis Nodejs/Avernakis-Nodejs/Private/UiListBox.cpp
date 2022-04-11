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
		AutoAddMethod( Find );
		AutoAddMethod( Swap );
		AutoAddMethod( Set );
		AutoAddMethod( Get );
		AutoAddMethod( GetCount );
		AutoAddMethod( GetSelection );
		AutoAddMethod( IsSelected );
		AutoAddMethod( GetNextSelection );

		AutoAddMethod( Ensure );
		AutoAddMethod( GetTopIndex );
		AutoAddMethod( ItemIsVisible );
		AutoAddMethod( ItemGetRect );
		AutoAddMethod( ItemHitTest );

		AutoAddMethod( SetCount );

		AutoAddMethod( SetVirtual );

		AutoAddMethod( SetSelectionMode );
		AutoAddMethod( GetSelectionMode );

		AutoAddMethod( OnSelectionChange );
		AutoAddMethod( OnSelectionEnd );
		AutoAddMethod( OnDoubleClick );
		AutoAddMethod( OnRightClick );
	}

	U1 UiListBox::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::IListBox::OnSelectionChange>() += MakeThisFunc( __OnSelectionChange );
		GetControlTyped().GetEvent<Ui::IListBox::OnSelectionEnd>() += MakeThisFunc( __OnSelectionEnd );
		GetControlTyped().GetEvent<Ui::IListBox::OnDoubleClick>() += MakeThisFunc( __OnDoubleClick );
		GetControlTyped().GetEvent<Ui::IListBox::OnRightClick>() += MakeThisFunc( __OnRightClick );

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

}
