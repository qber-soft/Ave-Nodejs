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
		AutoAddMethod( GetCount );
		AutoAddMethod( Add );
		AutoAddMethod( Select );
		AutoAddMethod( GetSelection );
		AutoAddMethod( GetHighlight );
		AutoAddMethod( SetText );
		AutoAddMethod( GetText );
		AutoAddMethod( SetIcon );
		AutoAddMethod( GetIcon );
		AutoAddMethod( SetContent );
		AutoAddMethod( GetContent );
		AutoAddMethod( SetItemEnable );
		AutoAddMethod( GetItemEnable );
		AutoAddMethod( GetItemRect );
		AutoAddMethod( SetBannerWidth );
		AutoAddMethod( GetBannerWidth );
		AutoAddMethod( SetTextVisible );
		AutoAddMethod( GetTextVisible );
		AutoAddMethod( ClearHighlight );
		AutoAddMethod( OnSelect );
		AutoAddMethod( OnHighlight );
	}

	U1 UiRibbonBackstage::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().SetTrackingWindowActivity( &p->PublicGetWindow() );
		GetControlTyped().SetIconManager( p->PublicCloneIconManager() );

		GetControlTyped().GetEvent<Ui::IRibbonBackstage::OnSelect>() += MakeThisFunc( __OnSelect );
		GetControlTyped().GetEvent<Ui::IRibbonBackstage::OnHighlight>() += MakeThisFunc( __OnHighlight );

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

}
