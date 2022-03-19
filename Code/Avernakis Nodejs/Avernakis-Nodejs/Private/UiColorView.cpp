#include "StdAfx.h"
#include "UiColorView.h"

#define ThisMethod($x) &UiColorView::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiColorView::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiColorView> c_obj;
	}

	void UiColorView::DefineControl()
	{
		AutoAddMethod( SetSolidColor );
		AutoAddMethod( GetSolidColor );
		AutoAddMethod( SetBackColor1 );
		AutoAddMethod( GetBackColor1 );
		AutoAddMethod( SetBackColor2 );
		AutoAddMethod( GetBackColor2 );
		AutoAddMethod( SetBackBlockSize );
		AutoAddMethod( GetBackBlockSize );
	}

	U1 UiColorView::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}
}
