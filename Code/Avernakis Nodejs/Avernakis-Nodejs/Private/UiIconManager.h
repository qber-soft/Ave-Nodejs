#pragma once

#include "WrapObject.h"

namespace Nav
{

	class UiIconManager : public WrapObject<UiIconManager, void()>
	{
	public:
		AveWrapObject( UiIconManager );

		static PCAChar					GetExportName() { return "4e086bc5e70948aba354fa3283174a5b"; }
		static void						DefineObject() {}

		U1								Ctor() { return true; }
		Napi::Value						GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Ui::IIconManager*				m_IconManager;

	private:

	public:
		AveInline UiIconManager*		SetIconManager( Ui::IIconManager* p ) { m_IconManager = p; return this; }
		AveInline Ui::IIconManager*		GetIconManager() { return m_IconManager; }
	};

}
