#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiProgressBar : public UiControlHelper<UiProgressBar, Ui::IProgressBar>
	{
	public:
		AveWrapControl( UiProgressBar );

		~UiProgressBar()
		{
		}

		static PCAChar					GetExportName() { return "UiProgressBar"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:

	private:

	private:
		UiProgressBar*					SetState( Ui::ProgressBarState n ) { GetControlTyped().SetState( n ); return this; }
		Ui::ProgressBarState 			GetState() { return GetControlTyped().GetState(); }

		UiProgressBar*					SetMaximum( U64 nValue ) { GetControlTyped().SetMaximum( nValue ); return this; }
		U64								GetMaximum() const { return GetControlTyped().GetMaximum(); }

		UiProgressBar*					SetValue( U64 nValue ) { GetControlTyped().SetValue( nValue ); return this; }
		U64								GetValue() const { return GetControlTyped().GetValue(); }

		UiProgressBar*					SetStep( U64 nValue ) { GetControlTyped().SetStep( nValue ); return this; }
		U64								GetStep() const { return GetControlTyped().GetStep(); }
		UiProgressBar*					Step() { GetControlTyped().Step(); return this; }

		UiProgressBar*					SetAnimation( U1 b ) { GetControlTyped().SetAnimation( b ); return this; }
		U1								GetAnimation() const { return GetControlTyped().GetAnimation(); }
	};
}
