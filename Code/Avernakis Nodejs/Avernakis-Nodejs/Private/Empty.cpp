#include "StdAfx.h"
#include "Empty.h"

#define ThisMethod($x) &Empty::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, ThisMethod( $x ) )

namespace Nav
{

	namespace
	{
		ObjectRegister<Empty> c_obj;
	}

	void Empty::DefineObject()
	{
	}

	U1 Empty::Ctor()
	{
		return true;
	}

}
