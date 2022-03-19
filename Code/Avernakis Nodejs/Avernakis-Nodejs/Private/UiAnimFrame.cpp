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
		AutoAddMethod( GetStretchMode );
		
		AutoAddMethod( SetFrameInfo );
		AutoAddMethod( GetFrameInfo );
		
		//AutoAddMethod( SetPicture );

		AutoAddMethod( Play );
		AutoAddMethod( Stop );
		
		AutoAddMethod( SetPlayPosition );
		AutoAddMethod( GetPlayPosition );
		
		AutoAddMethod( IsPlaying );
	}

	U1 UiAnimFrame::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}
}
