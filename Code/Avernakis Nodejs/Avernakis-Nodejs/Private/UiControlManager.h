#pragma once

#include "WrapObject.h"

namespace Nav
{

	class UiControl;

	class UiControlManager : public WrapObject<UiControlManager, void(), WrapObjectGeneric>
	{
	public:
		AveWrapObject( UiControlManager );

		static PCAChar						GetExportName() { return "6484fc9e777e4aac82b28561f5be5f1d"; }
		static void							DefineObject();

		U1									Ctor() { return true; }
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Ui::IControlManager*				m_ControlManager;

	private:
		U1									AddControl( WrapPointer<UiControl> c, Napi::Value key );
		void								RemoveControl( WrapPointer<UiControl> c );

	public:
		AveInline UiControlManager*	SetControlManager( Ui::IControlManager* p ) { m_ControlManager = p; return this; }
	};

}
