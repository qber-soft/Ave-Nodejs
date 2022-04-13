#include "StdAfx.h"
#include "UiCommonUiWait.h"

#define ThisMethod($x) &UiCommonUiWait::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiCommonUiWait::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiCommonUiWait> c_obj;
	}

	void UiCommonUiWait::DefineObject()
	{
		//AutoAddMethod( GetThreadIndex );
		//AutoAddMethod( SyncBarrier );
		AutoAddMethod( IsCanceled );
		AutoAddMethod( IsPaused );
		AutoAddMethod( Pause );
		AutoAddMethod( SetMaximum );
		AutoAddMethod( SetPosition );
		AutoAddMethod( AddPosition );
		AutoAddMethod( SetState );
		AutoAddMethod( Fail );
		AutoAddMethod( UpdateUi );
	}

}
