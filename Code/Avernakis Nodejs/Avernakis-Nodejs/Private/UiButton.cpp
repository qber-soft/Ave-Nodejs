#include "StdAfx.h"
#include "UiButton.h"
#include "UiPainter.h"

#define ThisMethod($x) &UiButton::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiButton::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiButton> c_obj;
	}

	void UiButton::DefineControl()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText, WrapObjectGeneric );
		AutoAddMethod( SetButtonType );
		AutoAddMethod( GetButtonType, WrapObjectGeneric );
		AutoAddMethod( SetButtonStyle );
		AutoAddMethod( GetButtonStyle, WrapObjectGeneric );
		AutoAddMethod( SetDrop );
		AutoAddMethod( GetDrop, WrapObjectGeneric );
		AutoAddMethod( SetAlignHorz );
		AutoAddMethod( GetAlignHorz, WrapObjectGeneric );
		AutoAddMethod( SetVisualTextLayout );
		AutoAddMethod( GetVisualTextLayout, WrapObjectGeneric );
		AutoAddMethod( SetVisual );
		AutoAddMethod( GetVisual, WrapObjectGeneric );

		AutoAddMethod( OnClick, WrapObjectGeneric );
		AutoAddMethod( OnDrop, WrapObjectGeneric );
		AutoAddMethod( OnCustomDraw, WrapObjectGeneric );
	}

	U1 UiButton::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiButton::__OnClick( Ui::IButton & sender )
	{
		m_OnClick( this );
	}

	void UiButton::__OnDrop( Ui::IButton & sender )
	{
		m_OnDrop( this );
	}

	void UiButton::__OnCustomDraw( Ui::IButton & sender, const Ui::IButton::CustomDrawParam & cdp, U32 & cdr )
	{
		if ( auto p = GetPainter( cdp.m_Painter ) )
		{
			UiButtonCustomDraw cd{};
			cd.m_Painter = p;
			cd.m_Part = cdp.m_Part;
			cd.m_Stage = cdp.m_Stage;
			cd.m_RectButton = cdp.m_RectButton;
			cd.m_Rect = cdp.m_Rect;
			cd.m_Text = cdp.m_Text ? cdp.m_Text : AveWide( "" );
			cd.m_TextFlag = cdp.m_TextFlag;
			if ( cdp.m_StateDynamic )
				cd.m_State.Set( *cdp.m_StateDynamic );

			WrapData<UiButtonCustomDrawResult> result{};
			m_OnCustomDraw.BlockCall( this, cd, result );
			cdr = result.m_Behavior;
			cdp.m_ColorText = result.m_NewTextColor;
			cdp.m_Rect = result.m_NewRect;
			cdp.m_TextFlag = result.m_NewFormat;
		}
	}

	UiButton * UiButton::OnClick( Callback_t && fn )
	{
		m_OnClick = SetEventCallback<Ui::IButton::OnClick>( std::move( fn ), MakeThisFunc( __OnClick ) );
		return this;
	}

	UiButton * UiButton::OnDrop( Callback_t && fn )
	{
		m_OnDrop = SetEventCallback<Ui::IButton::OnClick>( std::move( fn ), MakeThisFunc( __OnDrop ) );
		return this;
	}

	UiButton * UiButton::OnCustomDraw( const CallbackInfo& ci, CustomDraw_t && fn )
	{
		if ( m_OnCustomDraw = SetEventCallback<Ui::IButton::OnCustomDraw>( std::move( fn ), MakeThisFunc( __OnCustomDraw ) ) )
			AcquirePainter( ci );
		else
			ReleasePainter();
		return this;
	}

}
