#include "StdAfx.h"
#include "UiContainer3D.h"

#include "CoCamera.h"

#define ThisMethod($x) &UiContainer3D::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiContainer3D::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiContainer3DObject> c_co;
		ObjectRegister<UiContainer3DControl> c_cc;
		ObjectRegister<UiContainer3D> c_obj;
	}

	void UiContainer3DObject::DefineObject()
	{
		AddMethod( "SetData", &UiContainer3DObject::SetData );
	}

	U1 UiContainer3DObject::SetData( const WrapData<UiContainer3DData>& pObject )
	{
		if ( !pObject.m_Geometry.m_Position || !pObject.m_Geometry.m_Texcoord || !pObject.m_Geometry.m_Index )
			return false;
		if ( pObject.m_Geometry.m_Position.m_Length != pObject.m_Geometry.m_Texcoord.m_Length )
			return false;
		if ( 0 != (pObject.m_Geometry.m_Index.m_Length % 3) || pObject.m_Geometry.m_Index.m_Length < 3 )
			return false;

		List<Ui::Container3DVertexGeometry, 16> gv( pObject.m_Geometry.m_Position.m_Length );
		List<Ui::Container3DVertexRender, 16> rv;
		for ( USize i = 0; i < pObject.m_Geometry.m_Position.m_Length; ++i )
		{
			gv[i].m_Position = pObject.m_Geometry.m_Position[i];
			gv[i].m_Texcoord = pObject.m_Geometry.m_Texcoord[i];
		}

		Ui::Container3DObjectData data{};
		data.m_GeometryVertex = gv.Data();
		data.m_GeometryVertexCount = (U32) gv.Size();
		data.m_GeometryIndex = pObject.m_Geometry.m_Index;
		data.m_GeometryIndexCount = (U32) pObject.m_Geometry.m_Index.m_Length;

		if ( pObject.m_Render.m_Position && pObject.m_Render.m_Texcoord && pObject.m_Render.m_Index )
		{
			if ( pObject.m_Render.m_Position.m_Length != pObject.m_Render.m_Texcoord.m_Length )
				return false;
			if ( 0 != (pObject.m_Render.m_Index.m_Length % 3) || pObject.m_Render.m_Index.m_Length < 3 )
				return false;

			rv.Resize( pObject.m_Render.m_Position.m_Length );

			// Position
			XR32_4 vMin = XMath::XMLoadFloat3( &NT<R32_3>::Max );
			XR32_4 vMax = XMath::XMLoadFloat3( &NT<R32_3>::Min );
			XR32_4 v;
			for ( USize i = 0; i < pObject.m_Render.m_Position.m_Length; ++i )
			{
				v = XMath::XMLoadFloat3( &pObject.m_Render.m_Position[i] );
				vMin = XMath::XMVectorMin( vMin, v );
				vMax = XMath::XMVectorMax( vMax, v );
			}

			vMax = XMath::XMVectorMultiply( XMath::XMVectorSubtract( vMax, vMin ), XMath::XMVectorReplicate( 0.5f ) );
			XMath::XMStoreFloat3( &data.m_PositionBounding[0], vMax );
			vMin = XMath::XMVectorAdd( vMin, vMax );
			XMath::XMStoreFloat3( &data.m_PositionBounding[1], vMin );

			vMin = XMath::XMVectorNegate( vMin );
			vMax = XMath::XMVectorSelect( XMath::XMVectorReciprocal( vMax ), XMath::g_XMZero, XMath::XMVectorEqual( vMax, XMath::g_XMZero ) );

			for ( USize i = 0; i < pObject.m_Render.m_Position.m_Length; ++i )
			{
				v = XMath::XMLoadFloat3( &pObject.m_Render.m_Position[i] );
				v = XMath::XMVectorMultiply( XMath::XMVectorAdd( v, vMin ), vMax );
				XMath::XMStoreShortN4( &rv[i].m_Position, v );
			}

			// Texcoord
			for ( USize i = 0; i < pObject.m_Render.m_Position.m_Length; ++i )
			{
				v = XMath::XMLoadFloat2( &pObject.m_Render.m_Texcoord[i] );
				XMath::XMStoreShortN2( &rv[i].m_Texcoord, v );
			}

			data.m_RenderVertex = rv.Data();
			data.m_RenderVertexCount = (U32) rv.Size();
			data.m_RenderIndex = pObject.m_Render.m_Index;
			data.m_RenderIndexCount = (U32) pObject.m_Render.m_Index.m_Length;
		}
		
		return m_Object->SetData( data );
	}

	void UiContainer3DControl::DefineObject()
	{
#	define __AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, &UiContainer3DControl::$x )
		__AutoAddMethod( GetControl, WrapObjectGeneric );
		__AutoAddMethod( SetSize );
		__AutoAddMethod( GetSize, WrapObjectGeneric );
		__AutoAddMethod( SetCustomObject );
		__AutoAddMethod( GetCustomObject, WrapObjectGeneric );

		__AutoAddMethod( SetPosition );
		__AutoAddMethod( SetRotation );
		__AutoAddMethod( SetScaling );

		__AutoAddMethod( Translate );
		__AutoAddMethod( Rotate );
		__AutoAddMethod( Scale );
		__AutoAddMethod( Transform );

		__AutoAddMethod( GetPosition, WrapObjectGeneric );
		__AutoAddMethod( GetRotation, WrapObjectGeneric );
		__AutoAddMethod( GetScaling, WrapObjectGeneric );
		__AutoAddMethod( GetTransform, WrapObjectGeneric );
		__AutoAddMethod( GetTransformT, WrapObjectGeneric );
#	undef __AutoAddMethod
	}

	void UiContainer3D::DefineControl()
	{
		AutoAddMethod( ControlAdd );
		AutoAddMethod( ControlRemove );
		AutoAddMethod( ControlRemoveAll );
		AutoAddMethod( GetContainerControl, WrapObjectMix );
		AutoAddMethod( SetContent2D );
		AutoAddMethod( GetContent2D, WrapObjectGeneric );
		AutoAddMethod( SetDepthFormat );
		AutoAddMethod( GetDepthFormat, WrapObjectGeneric );
		AutoAddMethod( GetCamera, WrapObjectGeneric );
		AutoAddMethod( CreateCustom3DObject, WrapObjectGeneric );
	}

	U1 UiContainer3D::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	UiContainer3DControl * UiContainer3D::GetContainerControl( const MixCallContext & cc, WrapPointer<UiControl> c )
	{
		if ( MixCallStage::InUi == cc.GetStage() )
		{
			cc.SetUserContext( GetControlTyped().GetContainerControl( &c->GetControl() ) );
		}
		else if ( MixCallStage::PostUi == cc.GetStage() )
		{
			auto gc = (Ui::IContainer3DControl*) cc.GetUserContext();
			if ( !gc )
				return nullptr;
			if ( auto uigc = cc.NewJsObject<UiContainer3DControl>() )
			{
				uigc->SetControl( gc );
				return uigc;
			}
		}
		return nullptr;
	}

	CoCamera * UiContainer3D::GetCamera( const CallbackInfo & cc )
	{
		if ( auto obj = cc.NewJsObject<CoCamera>() )
		{
			obj->SetCamera( &GetControlTyped().GetCamera() );
			return obj;
		}
		return nullptr;
	}

	UiContainer3DObject * UiContainer3D::CreateCustom3DObject( const CallbackInfo & cc )
	{
		if ( auto obj = cc.NewJsObject<UiContainer3DObject>() )
		{
			obj->SetObject( GetControlTyped().CreateCustom3DObject() );
			return obj;
		}
		return nullptr;
	}

}
