#pragma once

#include "UiVisualHelper.h"

namespace Nav
{

	class UiColorView : public UiVisualHelper<UiColorView, Ui::IColorView>
	{
	public:
		AveWrapVisual( UiColorView );

		~UiColorView()
		{
		}

		static PCAChar					GetExportName() { return "UiColorView"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:

	private:
		UiColorView*					SetSolidColor( const WrapData<U8_4>& vColor ) { GetControlTyped().SetSolidColor( vColor ); return this; }
		WrapData<U8_4>					GetSolidColor() const { return GetControlTyped().GetSolidColor(); }

		UiColorView*					SetBackColor1( const WrapData<U8_4>& vColor ) { GetControlTyped().SetBackColor1( vColor ); return this; }
		WrapData<U8_4>					GetBackColor1() const { return GetControlTyped().GetBackColor1(); }

		UiColorView*					SetBackColor2( const WrapData<U8_4>& vColor ) { GetControlTyped().SetBackColor2( vColor ); return this; }
		WrapData<U8_4>					GetBackColor2() const { return GetControlTyped().GetBackColor2(); }

		UiColorView*					SetBackBlockSize( const WrapData<Ui::DpiSize>& nSize ) { GetControlTyped().SetBackBlockSize( nSize ); return this; }
		WrapData<Ui::DpiSize>			GetBackBlockSize() const { return GetControlTyped().GetBackBlockSize(); }

	};
}
