#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiContainer3DMesh
	{
	public:
		WrapArray<R32_3>				m_Position;
		WrapArray<R32_2>				m_Texcoord;
		WrapArray<U16>					m_Index;
	};

	NavDefineDataByMember_( UiContainer3DMesh, Position, Texcoord, Index );

	class UiContainer3DData
	{
	public:
		WrapData<UiContainer3DMesh>		m_Geometry;
		WrapData<UiContainer3DMesh>		m_Render;
	};

	NavDefineDataByMember_( UiContainer3DData, Geometry, Render );

	class UiContainer3DObject : public WrapObject<UiContainer3DObject, void(), WrapObjectUi>
	{
	public:
		AveWrapObject( UiContainer3DObject );

		static PCAChar					GetExportName() { return "bc204abc602441e9ba0ea2a19d5255c7"; }
		static void						DefineObject();

		U1								Ctor() { return true; }
		Napi::Value						GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Ui::Container3DObject			m_Object;

	private:
		U1								SetData( const WrapData<UiContainer3DData>& pObject );

	public:
		AveInline void					SetObject( Ui::Container3DObject&& p ) { m_Object = std::move( p ); }
		AveInline Ui::Container3DObject	TakeObject() { return std::move( m_Object ); }
	};

	class UiContainer3DControl : public WrapObject<UiContainer3DControl, void(), WrapObjectUi>
	{
	public:
		AveWrapObject( UiContainer3DControl );

		static PCAChar					GetExportName() { return "95af71ee31a3425290041e22338f7043"; }
		static void						DefineObject();

		U1								Ctor() { return true; }
		Napi::Value						GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Ui::IContainer3DControl*		m_Control;
		UiContainer3DObject*			m_Object{ nullptr };

	private:
		WrapPointer<UiControl>			GetControl() { return { (UiControl*) m_Control->GetControl()->GetUserContext() }; }

		UiContainer3DControl*			SetSize( const WrapData<Ui::DpiSize_2>& v ) { m_Control->SetSize( v ); return this; }
		WrapData<Ui::DpiSize_2>			GetSize() const { return m_Control->GetSize(); }

		UiContainer3DObject*			SetCustomObject( UiContainer3DObject* pObject ) { auto t = m_Object; m_Object = pObject; m_Control->SetCustomObject( std::move( pObject->TakeObject() ) ); return t; }
		UiContainer3DObject*			GetCustomObject() const { return m_Object; }


		UiContainer3DControl*			SetPosition( const WrapData<R32_3>& v ) { m_Control->SetPosition( v ); return this; }
		UiContainer3DControl*			SetRotation( const WrapData<R32_Q>& q ) { m_Control->SetRotation( q ); return this; }
		UiContainer3DControl*			SetScaling( const WrapData<R32_3>& v ) { m_Control->SetScaling( v ); return this; }

		UiContainer3DControl*			Translate( const WrapData<R32_3>& v ) { m_Control->Translate( v ); return this; }
		UiContainer3DControl*			Rotate( const WrapData<R32_Q>& q ) { m_Control->Rotate( q ); return this; }
		UiContainer3DControl*			Scale( const WrapData<R32_3>& v ) { m_Control->Scale( v ); return this; }
		UiContainer3DControl*			Transform( const WrapData<R32_4x4>& m ) { m_Control->Transform( m ); return this; }

		WrapData<R32_3>					GetPosition() const { return m_Control->GetPosition(); }
		WrapData<R32_Q>					GetRotation() const { return m_Control->GetRotation(); }
		WrapData<R32_3>					GetScaling() const { return m_Control->GetScaling(); }
		WrapData<R32_4x4>				GetTransform() const { return m_Control->GetTransform(); }
		WrapData<R32_4x4>				GetTransformT() const { return m_Control->GetTransformT(); }

	public:
		AveInline void					SetControl( Ui::IContainer3DControl* p ) { m_Control = p; }
	};

	class CoCamera;

	class UiContainer3D : public UiControlHelper<UiContainer3D, Ui::IContainer3D>
	{
	public:
		AveWrapControl( UiContainer3D );

		~UiContainer3D()
		{
		}

		static PCAChar					GetExportName() { return "UiContainer3D"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:

	private:
		U1								ControlAdd( WrapPointer<UiControl> c ) { return !!GetControlTyped().ControlAdd( std::move( c->TakeOwnership() ) ); }
		WrapPointer<UiControl>			ControlRemove( WrapPointer<UiControl> c ) { return __ChangeContent( GetControlTyped().ControlRemove( &c->GetControl() ) ); }
		UiContainer3D*					ControlRemoveAll() { GetControlTyped().ControlRemoveAll(); return this; }

		UiContainer3DControl*			GetContainerControl( const MixCallContext& cc, WrapPointer<UiControl> c );

		WrapPointer<UiControl>			SetContent2D( WrapPointer<UiControl> c ) { return __ChangeContent( GetControlTyped().SetContent2D( std::move( c->TakeOwnership() ) ) ); }
		WrapPointer<UiControl>			GetContent2D() const { return { (UiControl*) GetControlTyped().GetContent2D()->GetUserContext() }; }

		UiContainer3D*					SetDepthFormat( Img::PixFormat nFormat ) { GetControlTyped().SetDepthFormat( nFormat ); return this; }
		Img::PixFormat					GetDepthFormat() const { return GetControlTyped().GetDepthFormat(); }

		CoCamera*						GetCamera( const CallbackInfo& cc );

		UiContainer3DObject*			CreateCustom3DObject( const CallbackInfo& cc );
	};
}
