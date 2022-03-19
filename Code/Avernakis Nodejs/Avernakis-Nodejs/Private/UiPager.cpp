#include "StdAfx.h"
#include "UiPager.h"

#define ThisMethod($x) &UiPager::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiPager::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiPager> c_obj;
	}

	void UiPager::DefineControl()
	{
		AutoAddMethod( SetContent );
		AutoAddMethod( GetContent );

		AutoAddMethod( SetContentSize );
		AutoAddMethod( GetContentSize );
		AutoAddMethod( GetRealContentSize );

		AutoAddMethod( SetAdjustment );
		AutoAddMethod( GetAdjustment );

		AutoAddMethod( SetAutoHideScroll );
		AutoAddMethod( GetAutoHideScroll );

		AutoAddMethod( SetPointerScroll );
		AutoAddMethod( GetPointerScroll );
	}

	U1 UiPager::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

}
