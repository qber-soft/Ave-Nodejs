#include "StdAfx.h"
#include "UiWindowTaskbar.h"
#include "UiCommon.h"

#define ThisMethod($x) &UiWindowTaskbar::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiWindowTaskbar::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiWindowTaskbar> c_obj;
	}

	void UiWindowTaskbar::DefineObject()
	{
		AutoAddMethod( GetWindow );
		AutoAddMethod( SetState );
		AutoAddMethod( GetState );
		AutoAddMethod( SetMaximum );
		AutoAddMethod( GetMaximum );
		AutoAddMethod( SetValue );
		AutoAddMethod( GetValue );
		AutoAddMethod( SetStep );
		AutoAddMethod( GetStep );
		AutoAddMethod( Step );
		AutoAddMethod( SetForceBigIconSize100 );
		AutoAddMethod( GetForceBigIconSize100 );
	}

}
