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
		AutoAddMethod( GetState, WrapObjectGeneric );
		AutoAddMethod( SetMaximum );
		AutoAddMethod( GetMaximum, WrapObjectGeneric );
		AutoAddMethod( SetValue );
		AutoAddMethod( GetValue, WrapObjectGeneric );
		AutoAddMethod( SetStep );
		AutoAddMethod( GetStep, WrapObjectGeneric );
		AutoAddMethod( Step );
		AutoAddMethod( SetAnimation );
		AutoAddMethod( GetAnimation, WrapObjectGeneric );
	}

	U1 UiProgressBar::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

}
