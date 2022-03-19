#include "StdAfx.h"
#include "UiProgressBar.h"

#define ThisMethod($x) &UiProgressBar::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiProgressBar::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiProgressBar> c_obj;
	}

	void UiProgressBar::DefineControl()
	{
		AutoAddMethod( SetState );
		AutoAddMethod( GetState );
		AutoAddMethod( SetMaximum );
		AutoAddMethod( GetMaximum );
		AutoAddMethod( SetValue );
		AutoAddMethod( GetValue );
		AutoAddMethod( SetStep );
		AutoAddMethod( GetStep );
		AutoAddMethod( Step );
		AutoAddMethod( SetAnimation );
		AutoAddMethod( GetAnimation );
	}

	U1 UiProgressBar::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

}
