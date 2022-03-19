#pragma once

#include "UiVisualHelper.h"

namespace Nav
{

	class UiLabel : public UiVisualHelper<UiLabel, Ui::ILabel>
	{
	public:
		AveWrapVisual( UiLabel );

		~UiLabel()
		{
		}

		static PCAChar					GetExportName() { return "UiLabel"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:

	private:
		UiLabel*						SetText( PCWChar szText ) { GetControlTyped().SetText( szText ? szText : AveWide( "" ) ); return this; }
		WString							GetText() const { return GetControlTyped().GetText(); }

		UiLabel*						SetAlignHorz( Ui::AlignType nAlign ) { GetControlTyped().SetAlignHorz( nAlign ); return this; }
		Ui::AlignType					GetAlignHorz() const { return GetControlTyped().GetAlignHorz(); }

		UiLabel*						SetAlignVert( Ui::AlignType nAlign ) { GetControlTyped().SetAlignVert( nAlign ); return this; }
		Ui::AlignType					GetAlignVert() const { return GetControlTyped().GetAlignVert(); }

		UiLabel*						SetBackColor( const WrapData<U8_4>& vColor ) { GetControlTyped().SetBackColor( vColor ); return this; }
		WrapData<U8_4>					GetBackColor() const { return GetControlTyped().GetBackColor(); }

		UiLabel*						SetWrappable( U1 b ) { GetControlTyped().SetWrappable( b ); return this; }
		U1								GetWrappable() const { return GetControlTyped().GetWrappable(); }

	};
}
