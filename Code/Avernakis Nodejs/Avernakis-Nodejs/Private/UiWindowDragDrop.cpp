#include "StdAfx.h"
#include "UiWindowDragDrop.h"
#include "UiCommon.h"
#include "IoStream.h"

#define ThisMethod($x) &UiWindowDragDrop::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiCommonUiWait::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiWindowDragDrop> c_obj;
	}

	void UiWindowDragDrop::DefineObject()
	{
	}
}
