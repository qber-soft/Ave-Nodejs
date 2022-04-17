#include "StdAfx.h"
#include "UiMenu.h"

#define ThisMethod($x) &UiMenu::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiMenu::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiMenu> c_obj;
	}

	void UiMenu::DefineControl()
	{
		AutoAddMethod( InsertItem );
		AutoAddMethod( InsertSubMenu, WrapObjectMix );
		AutoAddMethod( RemoveById );
		AutoAddMethod( RemoveByIndex );
		AutoAddMethod( SetById );
		AutoAddMethod( SetByIndex );
		AutoAddMethod( GetById );
		AutoAddMethod( GetByIndex );
		AutoAddMethod( GetSubMenuById, WrapObjectMix );
		AutoAddMethod( GetSubMenuByIndex, WrapObjectMix );
		AutoAddMethod( Clear );
		AutoAddMethod( GetCount );
		AutoAddMethod( SetItemHeight );
		AutoAddMethod( GetItemHeight );
		AutoAddMethod( SetCheckById );
		AutoAddMethod( GetCheckById );
		AutoAddMethod( SetRadioId );
		AutoAddMethod( GetRadioId );
		AutoAddMethod( SetGroupRadioId );
		AutoAddMethod( GetGroupRadioId );
		AutoAddMethod( SetContentById );
		AutoAddMethod( SetContentByIndex );
		AutoAddMethod( GetContentById );
		AutoAddMethod( GetContentByIndex );

		AutoAddMethod( OnClick       /**/ );
		AutoAddMethod( OnRightClick  /**/ );
		AutoAddMethod( OnMiddleClick /**/ );
		AutoAddMethod( OnShow        /**/ );
		AutoAddMethod( OnHide        /**/ );
	}

	U1 UiMenu::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		m_Window = p;

		GetControlTyped().SetIconManager( p->PublicCloneIconManager() );

		GetControlTyped().GetEvent<Ui::IMenu::OnClick       /**/>() += MakeThisFunc( __OnClick       /**/ );
		GetControlTyped().GetEvent<Ui::IMenu::OnRightClick  /**/>() += MakeThisFunc( __OnRightClick  /**/ );
		GetControlTyped().GetEvent<Ui::IMenu::OnMiddleClick /**/>() += MakeThisFunc( __OnMiddleClick /**/ );
		GetControlTyped().GetEvent<Ui::IMenu::OnShow        /**/>() += MakeThisFunc( __OnShow        /**/ );
		GetControlTyped().GetEvent<Ui::IMenu::OnHide        /**/>() += MakeThisFunc( __OnHide        /**/ );

		return true;
	}

	void UiMenu::__OnClick( Ui::IMenu & sender, U32 nId )
	{
		m_OnClick( this, nId );
	}

	void UiMenu::__OnRightClick( Ui::IMenu & sender, U32 nId )
	{
		m_OnRightClick( this, nId );
	}

	void UiMenu::__OnMiddleClick( Ui::IMenu & sender, U32 nId )
	{
		m_OnMiddleClick( this, nId );
	}

	void UiMenu::__OnShow( Ui::IMenu & sender )
	{
		m_OnShow( this );
	}

	void UiMenu::__OnHide( Ui::IMenu & sender )
	{
		m_OnHide( this );
	}

	S32 UiMenu::InsertItem( const WrapData<UiMenuItem>& pItem )
	{
		Ui::MenuItem mi{};
		WrapDataTransit<Ui::MenuItem>::Transit( mi, pItem );
		return GetControlTyped().InsertItem( mi );
	}

	UiMenu * UiMenu::InsertSubMenu( const MixCallContext & cc, const WrapData<UiMenuItem>& pItem )
	{
		if ( MixCallStage::InUi == cc.GetStage() )
		{
			Ui::MenuItem mi{};
			WrapDataTransit<Ui::MenuItem>::Transit( mi, pItem );
			if ( auto pMenu = GetControlTyped().InsertSubMenu( mi ) )
			{
				pMenu->SetIconManager( m_Window->PublicCloneIconManager() );
				cc.SetUserContext( pMenu );
			}
		}
		else if ( MixCallStage::PostUi == cc.GetStage() )
		{
			if ( !cc.GetUserContext() )
				return nullptr;
			if ( auto r = cc.NewJsObject<UiMenu>() )
			{
				r->SetSharedControl( (Ui::IControl*) cc.GetUserContext() );
				return r;
			}
		}
		return nullptr;
	}

	U1 UiMenu::SetById( const WrapData<UiMenuItem>& pItem )
	{
		Ui::MenuItem mi{};
		WrapDataTransit<Ui::MenuItem>::Transit( mi, pItem );
		return GetControlTyped().SetById( mi );
	}

	U1 UiMenu::SetByIndex( const WrapData<UiMenuItem>& pItem )
	{
		Ui::MenuItem mi{};
		WrapDataTransit<Ui::MenuItem>::Transit( mi, pItem );
		return GetControlTyped().SetByIndex( mi );
	}

	WrapData<UiMenuItem> UiMenu::GetById( U32 nId ) const
	{
		Ui::MenuItem mi{ Ui::MenuItem::Flag_State | Ui::MenuItem::Flag_Type | Ui::MenuItem::Flag_Text | Ui::MenuItem::Flag_TextSub | Ui::MenuItem::Flag_Key | Ui::MenuItem::Flag_Icon | Ui::MenuItem::Flag_Size };
		WChar szText[1024];
		WChar szSubText[1024];
		mi.m_Id = nId;
		mi.m_Text = szText;
		mi.m_TextSub = szSubText;
		mi.m_TextCharLength = CountOf( szText );
		mi.m_TextSubCharLength = CountOf( szSubText );
		if ( !GetControlTyped().GetById( mi ) )
			return {};
		WrapData<UiMenuItem> r;
		r.FromMenuItem( mi );
		return r;
	}

	WrapData<UiMenuItem> UiMenu::GetByIndex( U32 nIndex ) const
	{
		Ui::MenuItem mi{ Ui::MenuItem::Flag_State | Ui::MenuItem::Flag_Type | Ui::MenuItem::Flag_Text | Ui::MenuItem::Flag_TextSub | Ui::MenuItem::Flag_Key | Ui::MenuItem::Flag_Icon | Ui::MenuItem::Flag_Size };
		WChar szText[1024];
		WChar szSubText[1024];
		mi.m_Index = nIndex;
		mi.m_Text = szText;
		mi.m_TextSub = szSubText;
		mi.m_TextCharLength = CountOf( szText );
		mi.m_TextSubCharLength = CountOf( szSubText );
		if ( !GetControlTyped().GetById( mi ) )
			return {};
		WrapData<UiMenuItem> r;
		r.FromMenuItem( mi );
		return r;
	}

	UiMenu * UiMenu::GetSubMenuById( const MixCallContext & cc, U32 nId ) const
	{
		if ( MixCallStage::InUi == cc.GetStage() )
		{
			cc.SetUserContext( GetControlTyped().GetSubMenuById( nId ) );
		}
		else if ( MixCallStage::PostUi == cc.GetStage() )
		{
			if ( !cc.GetUserContext() )
				return nullptr;
			if ( auto r = cc.NewJsObject<UiMenu>() )
			{
				r->SetSharedControl( (Ui::IControl*) cc.GetUserContext() );
				return r;
			}
		}
		return nullptr;
	}

	UiMenu * UiMenu::GetSubMenuByIndex( const MixCallContext & cc, S32 nIndex ) const
	{
		if ( MixCallStage::InUi == cc.GetStage() )
		{
			cc.SetUserContext( GetControlTyped().GetSubMenuByIndex( nIndex ) );
		}
		else if ( MixCallStage::PostUi == cc.GetStage() )
		{
			if ( !cc.GetUserContext() )
				return nullptr;
			if ( auto r = cc.NewJsObject<UiMenu>() )
			{
				r->SetSharedControl( (Ui::IControl*) cc.GetUserContext() );
				return r;
			}
		}
		return nullptr;
	}

}
