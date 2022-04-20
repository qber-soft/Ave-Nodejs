#include "StdAfx.h"
#include "UiRibbonBackstage.h"
#include "UiRibbonGroup.h"

#define ThisMethod($x) &UiRibbonBackstage::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiRibbonBackstage::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiRibbonBackstage> c_obj;
	}

	void UiRibbonBackstage::DefineControl()
	{
		AutoAddMethod( SetCount );
		AutoAddMethod( GetCount, WrapObjectGeneric );
		AutoAddMethod( Add );
		AutoAddMethod( Select );
		AutoAddMethod( GetSelection, WrapObjectGeneric );
		AutoAddMethod( GetHighlight, WrapObjectGeneric );
		AutoAddMethod( SetText );
		AutoAddMethod( GetText, WrapObjectGeneric );
		AutoAddMethod( SetIcon );
		AutoAddMethod( GetIcon, WrapObjectGeneric );
		AutoAddMethod( SetContent );
		AutoAddMethod( GetContent, WrapObjectGeneric );
		AutoAddMethod( SetItemEnable );
		AutoAddMethod( GetItemEnable, WrapObjectGeneric );
		AutoAddMethod( GetItemRect, WrapObjectGeneric );
		AutoAddMethod( SetBannerWidth );
		AutoAddMethod( GetBannerWidth, WrapObjectGeneric );
		AutoAddMethod( SetTextVisible );
		AutoAddMethod( GetTextVisible, WrapObjectGeneric );
		AutoAddMethod( ClearHighlight );
		AutoAddMethod( OnSelect, WrapObjectGeneric );
		AutoAddMethod( OnHighlight, WrapObjectGeneric );
	}

	U1 UiRibbonBackstage::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().SetTrackingWindowActivity( &p->PublicGetWindow() );
		GetControlTyped().SetIconManager( p->PublicCloneIconManager() );

		return true;
	}

	void UiRibbonBackstage::__OnSelect( Ui::IRibbonBackstage & sender, U32 nIndex )
	{
		m_OnSelect( this, nIndex );
	}

	void UiRibbonBackstage::__OnHighlight( Ui::IRibbonBackstage & sender, S32 nIndex )
	{
		m_OnHighlight( this, nIndex );
	}

	UiRibbonBackstage* UiRibbonBackstage::OnSelect    /**/( Callback_t&& fn ) { m_OnSelect    /**/ = SetEventCallback<Ui::IRibbonBackstage::OnSelect    /**/>( std::move( fn ), MakeThisFunc( __OnSelect    /**/ ) ); return this; }
	UiRibbonBackstage* UiRibbonBackstage::OnHighlight /**/( Callback_t&& fn ) { m_OnHighlight /**/ = SetEventCallback<Ui::IRibbonBackstage::OnHighlight /**/>( std::move( fn ), MakeThisFunc( __OnHighlight /**/ ) ); return this; }

}
