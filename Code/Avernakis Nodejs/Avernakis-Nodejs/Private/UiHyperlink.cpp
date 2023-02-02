#include "StdAfx.h"
#include "UiHyperlink.h"

#define ThisMethod($x) &UiHyperlink::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiHyperlink::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiHyperlink> c_obj;
	}

	void UiHyperlink::DefineControl()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText, WrapObjectGeneric );
		AutoAddMethod( GetTextDisplay, WrapObjectGeneric );
		AutoAddMethod( GetTextValid, WrapObjectGeneric );
		AutoAddMethod( SetAlignHorz );
		AutoAddMethod( GetAlignHorz, WrapObjectGeneric );
		AutoAddMethod( SetAlignVert );
		AutoAddMethod( GetAlignVert, WrapObjectGeneric );
		AutoAddMethod( SetBackColor );
		AutoAddMethod( GetBackColor, WrapObjectGeneric );
		AutoAddMethod( SetWrappable );
		AutoAddMethod( GetWrappable, WrapObjectGeneric );
		AutoAddMethod( SetUnderline );
		AutoAddMethod( GetUnderline, WrapObjectGeneric );

		AutoAddMethod( OnClick, WrapObjectGeneric );
	}

	U1 UiHyperlink::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiHyperlink::__OnClick( Ui::IHyperlink & sender, U32 nId )
	{
		m_OnClick( this, nId );
	}

	UiHyperlink * UiHyperlink::OnClick( Callback_t && fn )
	{
		SetEventCallback<Ui::IHyperlink::OnClick>( m_OnClick, std::move( fn ), MakeThisFunc( __OnClick ) );
		return this;
	}

}
