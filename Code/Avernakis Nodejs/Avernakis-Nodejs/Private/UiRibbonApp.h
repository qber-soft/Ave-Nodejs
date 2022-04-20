#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiRibbonApp : public UiControlHelper<UiRibbonApp, Ui::IRibbonApp>
	{
	public:
		AveWrapControl( UiRibbonApp );

		~UiRibbonApp()
		{
		}

		static PCAChar					GetExportName() { return "UiRibbonApp"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using Callback_t = JsFuncSafe<void( UiRibbonApp* sender )>;

		Callback_t						m_OnClick;

		void							__OnClick( Ui::IRibbonApp& sender );

	private:
		UiRibbonApp*					SetText( PCWChar szText ) { GetControlTyped().SetText( szText ); return this; }
		WString							GetText() const { return GetControlTyped().GetText(); }

		UiRibbonApp*					OnClick( Callback_t&& fn );
	};
}
