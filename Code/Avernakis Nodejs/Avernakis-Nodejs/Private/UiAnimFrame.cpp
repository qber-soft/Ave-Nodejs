#include "StdAfx.h"
#include "UiAnimFrame.h"

#define ThisMethod($x) &UiAnimFrame::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiAnimFrame::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiAnimFrame> c_obj;
	}

	void UiAnimFrame::DefineControl()
	{
		AutoAddMethod( SetStretchMode );
		AutoAddMethod( GetStretchMode, WrapObjectGeneric );
		
		AutoAddMethod( SetFrameInfo );
		AutoAddMethod( GetFrameInfo, WrapObjectGeneric );
		
		//AutoAddMethod( SetPicture );

		AutoAddMethod( Play, WrapObjectGeneric );
		AutoAddMethod( Stop, WrapObjectGeneric );
		
		AutoAddMethod( SetPlayPosition );
		AutoAddMethod( GetPlayPosition, WrapObjectGeneric );
		
		AutoAddMethod( IsPlaying, WrapObjectGeneric );
	}

	U1 UiAnimFrame::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}
}
