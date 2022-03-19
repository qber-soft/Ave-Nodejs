#include "StdAfx.h"
#include "UiPicture.h"

#define ThisMethod($x) &UiPicture::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiPicture::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiPicture> c_obj;
	}

	void UiPicture::DefineControl()
	{
		AutoAddMethod( SetStretchMode );
		AutoAddMethod( GetStretchMode );
		AutoAddMethod( SetPicture );
	}

	U1 UiPicture::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}
}
