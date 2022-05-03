#include "StdAfx.h"
#include "UiLabel.h"

#define ThisMethod($x) &UiLabel::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiLabel::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiLabel> c_obj;
	}

	void UiLabel::DefineControl()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText, WrapObjectGeneric );
		AutoAddMethod( SetAlignHorz );
		AutoAddMethod( GetAlignHorz, WrapObjectGeneric );
		AutoAddMethod( SetAlignVert );
		AutoAddMethod( GetAlignVert, WrapObjectGeneric );
		AutoAddMethod( SetBackColor );
		AutoAddMethod( GetBackColor, WrapObjectGeneric );
		AutoAddMethod( SetWrappable );
		AutoAddMethod( GetWrappable, WrapObjectGeneric );
	}

	U1 UiLabel::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}
}
