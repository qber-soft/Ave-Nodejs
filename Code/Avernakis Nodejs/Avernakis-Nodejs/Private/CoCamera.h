#pragma once

#include "Common.h"

namespace Nav
{

	class CoCamera : public WrapObject<CoCamera, void()>
	{
	public:
		AveWrapObject( CoCamera );

		static PCAChar						GetExportName() { return "CoCamera"; }
		static void							DefineObject();

		U1									Ctor();
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Camera								m_CameraData;
		ICamera*							m_Camera{};

	private:

	private:
		void								CopyFrom( CoCamera* pCamera ) { m_Camera->CopyFrom( *pCamera->m_Camera ); }

		void								SetProjectionType( ProjectionType nType ) { m_Camera->SetProjectionType( nType ); }
		ProjectionType						GetProjectionType() const { return m_Camera->GetProjectionType(); }

		void								SetPosition( const WrapData<R32_3>& v ) { m_Camera->SetPosition( v ); }
		WrapData<R32_3>						GetPosition() const { return m_Camera->GetPosition(); }

		void								SetRotation( const WrapData<R32_Q>& q ) { m_Camera->SetRotation( q ); }
		WrapData<R32_Q>						GetRotation() const { return m_Camera->GetRotation(); }



		void								SetZNear( R32 fNear ) { m_Camera->SetZNear( fNear ); }
		R32									GetZNear() const { return m_Camera->GetZNear(); }

		void								SetZFar( R32 fFar ) { m_Camera->SetZFar( fFar ); }
		R32									GetZFar() const { return m_Camera->GetZFar(); }

		void								SetDirection( const WrapData<R32_3>& v ) { m_Camera->SetDirection( v ); }
		WrapData<R32_3>						GetDirection() const { return m_Camera->GetDirection(); }

		void								SetTarget( const WrapData<R32_3>& v ) { m_Camera->SetTarget( v ); }

		void								Roll( R32 f ) { m_Camera->Roll( f ); }
		void								Yaw( R32 f ) { m_Camera->Yaw( f ); }
		void								Pitch( R32 f ) { m_Camera->Pitch( f ); }
		void								RotateAngle( const WrapData<R32_3>& v, R32 f ) { m_Camera->RotateAngle( v, f ); }



		void								SetFovY( R32 fFov ) { m_Camera->SetFovY( fFov ); }
		R32									GetFovY() const { return m_Camera->GetFovY(); }

		void								SetAspect( R32 fAspect ) { m_Camera->SetAspect( fAspect ); }
		R32									GetAspect() const { return m_Camera->GetAspect(); }

		WrapData<R32_F>						GetFrustum() const { return m_Camera->GetFrustum(); }



		void								SetOrthoRange( const WrapData<R32_4>& vLRBT ) { m_Camera->SetOrthoRange( vLRBT ); }
		WrapData<R32_4>						GetOrthoRange() const { return m_Camera->GetOrthoRange(); }

		WrapData<R32_B>						GetOrthoBox() const { return m_Camera->GetOrthoBox(); }



		void								SetCustomProjection( const WrapData<R32_4x4>& mProj ) { m_Camera->SetCustomProjection( mProj ); }



		WrapData<R32_3>						GetViewUp() const { return m_Camera->GetViewUp(); }
		WrapData<R32_3>						GetViewRight() const { return m_Camera->GetViewRight(); }
		WrapData<R32_4x4>					GetView() const { return m_Camera->GetView(); }
		WrapData<R32_3x4>					GetView33() const { return m_Camera->GetView33(); }
		WrapData<R32_4x4>					GetView33_4() const { return m_Camera->GetView33_4(); }
		WrapData<R32_4x4>					GetViewT() const { return m_Camera->GetViewT(); }
		WrapData<R32_3x4>					GetViewT33() const { return m_Camera->GetViewT33(); }
		WrapData<R32_4x4>					GetViewT33_4() const { return m_Camera->GetViewT33_4(); }
		WrapData<R32_4x4>					GetProjection() const { return m_Camera->GetProjection(); }
		WrapData<R32_4x4>					GetProjectionT() const { return m_Camera->GetProjectionT(); }
		WrapData<R32_4x4>					GetViewProjection() const { return m_Camera->GetViewProjection(); }
		WrapData<R32_4x4>					GetViewProjectionT() const { return m_Camera->GetViewProjectionT(); }

	public:
		AveInline void						SetCamera( ICamera* p ) { m_Camera = p; }
	};
}
