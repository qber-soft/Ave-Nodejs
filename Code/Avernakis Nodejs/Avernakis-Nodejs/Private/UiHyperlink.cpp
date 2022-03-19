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
		AutoAddMethod( GetText );
		AutoAddMethod( GetTextValid );
		AutoAddMethod( SetAlignHorz );
		AutoAddMethod( GetAlignHorz );
		AutoAddMethod( SetAlignVert );
		AutoAddMethod( GetAlignVert );
		AutoAddMethod( SetBackColor );
		AutoAddMethod( GetBackColor );
		AutoAddMethod( SetWrappable );
		AutoAddMethod( GetWrappable );
		AutoAddMethod( SetUnderline );
		AutoAddMethod( GetUnderline );

		AutoAddMethod( OnClick );
	}

	U1 UiHyperlink::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::IHyperlink::OnClick>() += MakeThisFunc( __OnClick );

		return true;
	}

	void UiHyperlink::__OnClick( Ui::IHyperlink & sender, U32 nId )
	{
		m_OnClick( this, nId );
	}

}
