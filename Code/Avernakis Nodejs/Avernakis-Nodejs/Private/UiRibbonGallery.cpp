#include "StdAfx.h"
#include "UiRibbonGallery.h"

#define ThisMethod($x) &UiRibbonGallery::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiRibbonGallery::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiRibbonGallery> c_obj;
	}

	void WrapDataTransit<Ui::RibbonGalleryItem>::Transit( Ui::RibbonGalleryItem& d, const UiRibbonGalleryItem& s )
	{
		d.m_Flag    /**/ = s.m_Flag    /**/;
		d.m_Index   /**/ = s.m_Index   /**/;
		d.m_Icon    /**/ = s.m_Icon    /**/;
		d.m_Group   /**/ = s.m_Group   /**/;
		d.m_Text    /**/ = (PWChar) s.m_Text    /**/.c_str();
		d.m_Tooltip /**/ = (PWChar) s.m_Tooltip /**/.c_str();
	}

	void WrapDataTransit<Ui::RibbonGalleryMenu>::Transit( Ui::RibbonGalleryMenu& d, const UiRibbonGalleryMenu& s )
	{
		d.m_Flag    /**/ = s.m_Flag    /**/;
		d.m_Index   /**/ = s.m_Index   /**/;
		d.m_Id      /**/ = s.m_Id      /**/;
		d.m_Icon    /**/ = s.m_Icon    /**/;
		d.m_State   /**/ = s.m_State   /**/;
		d.m_Text    /**/ = (PWChar) s.m_Text    /**/.c_str();
	}

	void UiRibbonGallery::DefineControl()
	{
		AutoAddMethod( ItemInsert );
		AutoAddMethod( ItemRemove );
		AutoAddMethod( ItemClear );
		AutoAddMethod( ItemSelect );
		AutoAddMethod( ItemSet );
		AutoAddMethod( ItemGet, WrapObjectGeneric );
		AutoAddMethod( ItemGetCount, WrapObjectGeneric );
		AutoAddMethod( ItemGetSelection, WrapObjectGeneric );
		AutoAddMethod( GroupInsert );
		AutoAddMethod( GroupRemove );
		AutoAddMethod( GroupClear );
		AutoAddMethod( GroupSet );
		AutoAddMethod( GroupGet, WrapObjectGeneric );
		AutoAddMethod( GroupGetCount, WrapObjectGeneric );
		AutoAddMethod( MenuInsert );
		AutoAddMethod( MenuRemove );
		AutoAddMethod( MenuClear );
		AutoAddMethod( MenuSet );
		AutoAddMethod( MenuGet, WrapObjectGeneric );
		AutoAddMethod( MenuSetEnable );
		AutoAddMethod( MenuGetEnable, WrapObjectGeneric );
		AutoAddMethod( MenuGetCount, WrapObjectGeneric );
		AutoAddMethod( ViewSetMode );
		AutoAddMethod( ViewGetMode, WrapObjectGeneric );
		AutoAddMethod( ViewSetItemWidth );
		AutoAddMethod( ViewGetItemWidth, WrapObjectGeneric );
		AutoAddMethod( ViewSetDefaultItemCountPerLine );
		AutoAddMethod( ViewGetDefaultItemCountPerLine, WrapObjectGeneric );
		AutoAddMethod( ViewSetItemCountPerLineRange );
		AutoAddMethod( ViewGetItemCountPerLineRange, WrapObjectGeneric );
		AutoAddMethod( ViewSetWidthWeight );
		AutoAddMethod( ViewGetWidthWeight, WrapObjectGeneric );
		AutoAddMethod( OnSelect, WrapObjectGeneric );
		AutoAddMethod( OnPreview, WrapObjectGeneric );
		AutoAddMethod( OnDrop, WrapObjectGeneric );
		AutoAddMethod( OnMenuClick, WrapObjectGeneric );
	}

	U1 UiRibbonGallery::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().SetIconManager( p->PublicCloneIconManager() );

		return true;
	}

	S32 UiRibbonGallery::ItemInsert( const WrapData<UiRibbonGalleryItem>& pItem )
	{
		Ui::RibbonGalleryItem gi{};
		WrapDataTransit<Ui::RibbonGalleryItem>::Transit( gi, pItem );
		return GetControlTyped().ItemInsert( gi );
	}

	U1 UiRibbonGallery::ItemSet( const WrapData<UiRibbonGalleryItem>& pItem )
	{
		Ui::RibbonGalleryItem gi{};
		WrapDataTransit<Ui::RibbonGalleryItem>::Transit( gi, pItem );
		return GetControlTyped().ItemSet( gi );
	}

	WrapData<UiRibbonGalleryItem> UiRibbonGallery::ItemGet( S32 nIndex ) const
	{
		Ui::RibbonGalleryItem gi{ Ui::RibbonGalleryItem::Flag_Icon | Ui::RibbonGalleryItem::Flag_Text | Ui::RibbonGalleryItem::Flag_Group | Ui::RibbonGalleryItem::Flag_Tooltip };
		WChar szText[1024];
		WChar szTooltip[1024];
		gi.m_Index = nIndex;
		gi.m_Text = szText;
		gi.m_TextCharLength = CountOf( szText );
		gi.m_Tooltip = szTooltip;
		gi.m_TooltipCharLength = CountOf( szTooltip );
		WrapData<UiRibbonGalleryItem> r{};
		if ( GetControlTyped().ItemGet( gi ) )
			WrapDataTransit<Ui::RibbonGalleryItem>::Transit( r, gi );
		return r;
	}

	S32 UiRibbonGallery::MenuInsert( const WrapData<UiRibbonGalleryMenu>& pItem )
	{
		Ui::RibbonGalleryMenu mi{};
		WrapDataTransit<Ui::RibbonGalleryMenu>::Transit( mi, pItem );
		return GetControlTyped().MenuInsert( mi );
	}

	U1 UiRibbonGallery::MenuSet( const WrapData<UiRibbonGalleryMenu>& pItem )
	{
		Ui::RibbonGalleryMenu mi{};
		WrapDataTransit<Ui::RibbonGalleryMenu>::Transit( mi, pItem );
		return GetControlTyped().MenuSet( mi );
	}

	WrapData<UiRibbonGalleryMenu> UiRibbonGallery::MenuGet( S32 nIndex ) const
	{
		Ui::RibbonGalleryMenu gm{ Ui::RibbonGalleryMenu::Flag_Icon | Ui::RibbonGalleryMenu::Flag_Id | Ui::RibbonGalleryMenu::Flag_Text | Ui::RibbonGalleryMenu::Flag_State };
		WChar szText[1024];
		gm.m_Index = nIndex;
		gm.m_Text = szText;
		gm.m_TextCharLength = CountOf( szText );
		WrapData<UiRibbonGalleryMenu> r{};
		if ( GetControlTyped().MenuGet( gm ) )
			WrapDataTransit<Ui::RibbonGalleryMenu>::Transit( r, gm );
		return r;
	}

	void UiRibbonGallery::__OnSelect( Ui::IRibbonGallery & sender )
	{
		m_OnSelect( this );
	}

	void UiRibbonGallery::__OnPreview( Ui::IRibbonGallery & sender, S32 nIndex )
	{
		m_OnPreview( this, nIndex );
	}

	void UiRibbonGallery::__OnDrop( Ui::IRibbonGallery & sender )
	{
		m_OnDrop( this );
	}

	void UiRibbonGallery::__OnMenuClick( Ui::IRibbonGallery & sender, U32 nId )
	{
		m_OnMenuClick( this, nId );
	}

	UiRibbonGallery* UiRibbonGallery::OnSelect    /**/( Callback_t    /**/ && fn ) { SetEventCallback<Ui::IRibbonGallery::OnSelect    /**/>( m_OnSelect    /**/, std::move( fn ), MakeThisFunc( __OnSelect    /**/ ) ); return this; }
	UiRibbonGallery* UiRibbonGallery::OnPreview   /**/( OnPreview_t   /**/ && fn ) { SetEventCallback<Ui::IRibbonGallery::OnPreview   /**/>( m_OnPreview   /**/, std::move( fn ), MakeThisFunc( __OnPreview   /**/ ) ); return this; }
	UiRibbonGallery* UiRibbonGallery::OnDrop      /**/( Callback_t    /**/ && fn ) { SetEventCallback<Ui::IRibbonGallery::OnDrop      /**/>( m_OnDrop      /**/, std::move( fn ), MakeThisFunc( __OnDrop      /**/ ) ); return this; }
	UiRibbonGallery* UiRibbonGallery::OnMenuClick /**/( OnMenuClick_t /**/ && fn ) { SetEventCallback<Ui::IRibbonGallery::OnMenuClick /**/>( m_OnMenuClick /**/, std::move( fn ), MakeThisFunc( __OnMenuClick /**/ ) ); return this; }
}
