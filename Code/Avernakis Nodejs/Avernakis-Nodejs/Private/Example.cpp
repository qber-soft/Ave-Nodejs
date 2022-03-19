#include "StdAfx.h"
#include "Example.h"

#include "WrapData.h"

#define ThisMethod($x) &Example::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, ThisMethod( $x ) )

namespace Nav
{

	namespace
	{
		ObjectRegister<Example> c_obj;
	}

	void Example::DefineObject()
	{
		AutoAddMethod(GetX);
		AutoAddMethod(TestThrowJsException);
	}

	U1 Example::Ctor()
	{
		return true;
	}

	S32 Example::GetX() const
	{
		return 5;
	}

	void Example::TestThrowJsException(const CallbackInfo& ci)
	{
		ci.ThrowJsException("throw exception from cpp");
	}
}
