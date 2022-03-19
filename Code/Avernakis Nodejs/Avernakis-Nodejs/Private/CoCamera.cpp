#include "StdAfx.h"
#include "CoCamera.h"

#define ThisMethod($x) &CoCamera::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, ThisMethod( $x ) )

namespace Nav
{

	namespace
	{
		ObjectRegister<CoCamera> c_obj;
	}

	void CoCamera::DefineObject()
	{
		AutoAddMethod( CopyFrom );

		AutoAddMethod( SetProjectionType );
		AutoAddMethod( GetProjectionType );

		AutoAddMethod( SetPosition );
		AutoAddMethod( GetPosition );

		AutoAddMethod( SetRotation );
		AutoAddMethod( GetRotation );



		AutoAddMethod( SetZNear );
		AutoAddMethod( GetZNear );

		AutoAddMethod( SetZFar );
		AutoAddMethod( GetZFar );

		AutoAddMethod( SetDirection );
		AutoAddMethod( GetDirection );

		AutoAddMethod( SetTarget );

		AutoAddMethod( Roll );
		AutoAddMethod( Yaw );
		AutoAddMethod( Pitch );
		AutoAddMethod( RotateAngle );



		AutoAddMethod( SetFovY );
		AutoAddMethod( GetFovY );

		AutoAddMethod( SetAspect );
		AutoAddMethod( GetAspect );

		AutoAddMethod( GetFrustum );



		AutoAddMethod( SetOrthoRange );
		AutoAddMethod( GetOrthoRange );

		AutoAddMethod( GetOrthoBox );



		AutoAddMethod( SetCustomProjection );



		AutoAddMethod( GetViewUp );
		AutoAddMethod( GetViewRight );
		AutoAddMethod( GetView );
		AutoAddMethod( GetView33 );
		AutoAddMethod( GetView33_4 );
		AutoAddMethod( GetViewT );
		AutoAddMethod( GetViewT33 );
		AutoAddMethod( GetViewT33_4 );
		AutoAddMethod( GetProjection );
		AutoAddMethod( GetProjectionT );
		AutoAddMethod( GetViewProjection );
		AutoAddMethod( GetViewProjectionT );
	}

	U1 CoCamera::Ctor()
	{
		if ( !m_CameraData.Create() )
			return false;

		m_Camera = m_CameraData;

		return true;
	}

}
