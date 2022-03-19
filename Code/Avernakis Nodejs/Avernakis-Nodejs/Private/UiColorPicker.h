#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiColorPicker : public UiControlHelper<UiColorPicker, Ui::IColorPicker>
	{
	public:
		AveWrapControl( UiColorPicker );

		~UiColorPicker()
		{
		}

		static PCAChar					GetExportName() { return "UiColorPicker"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnChange_t = JsFuncSafe<void( UiColorPicker* sender )>;

		OnChange_t						m_OnChange;

		void							__OnChange( Ui::IColorPicker& sender );

	private:
		UiColorPicker*					SetPickerType( Ui::ColorPickerType nType ) { GetControlTyped().SetPickerType( nType ); return this; }
		Ui::ColorPickerType				GetPickerType() const { return GetControlTyped().GetPickerType(); }

		UiColorPicker*					SetCubePrimary( Ui::ColorPickerCubePrimary nPrimary ) { GetControlTyped().SetCubePrimary( nPrimary ); return this; }
		Ui::ColorPickerCubePrimary		GetCubePrimary() const { return GetControlTyped().GetCubePrimary(); }

		UiColorPicker*					SetColor( const WrapData<U8_3>& vColor ) { GetControlTyped().SetColor( vColor ); return this; }
		WrapData<U8_3>					GetColor() const { return GetControlTyped().GetColor(); }

		UiColorPicker*					OnChange( OnChange_t&& fn ) { m_OnChange = std::move( fn ); return this; }
	};
}
