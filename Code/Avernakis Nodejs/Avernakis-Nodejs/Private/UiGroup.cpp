#include "StdAfx.h"
#include "UiGroup.h"

#define ThisMethod($x) &UiGroup::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiGroup::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiGroup> c_obj;
	}

	void UiGroup::DefineControl()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText, WrapObjectGeneric );

		AutoAddMethod( SetHeader );
		AutoAddMethod( GetHeader, WrapObjectGeneric );

		AutoAddMethod( SetContent );
		AutoAddMethod( GetContent, WrapObjectGeneric );

		AutoAddMethod( GetContentSize, WrapObjectGeneric );
	}

	U1 UiGroup::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

}
