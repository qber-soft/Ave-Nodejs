#include "StdAfx.h"
#include "UiWindowSysTray.h"
#include "UiCommon.h"

#define ThisMethod($x) &UiWindowSysTray::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiWindowSysTray::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiWindowSysTray> c_obj;
	}

	void UiWindowSysTray::DefineObject()
	{
		AutoAddMethod( GetWindow );
		AutoAddMethod( SetVisible );
		AutoAddMethod( GetVisible );
		AutoAddMethod( SetText );
		AutoAddMethod( GetText );
		AutoAddMethod( OnClick );
		AutoAddMethod( OnRightClick );
	}

}
