#include "StdAfx.h"
#include "UiPlaceholder.h"

#define ThisMethod($x) &UiPlaceholder::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiPlaceholder::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiPlaceholder> c_obj;
	}

	void UiPlaceholder::DefineControl()
	{
	}

	U1 UiPlaceholder::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

}
