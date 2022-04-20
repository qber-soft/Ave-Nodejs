#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiRadioBox : public UiControlHelper<UiRadioBox, Ui::IRadioBox>
	{
	public:
		AveWrapControl( UiRadioBox );

		~UiRadioBox()
		{
		}

		static PCAChar					GetExportName() { return "UiRadioBox"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnCheck_t    /**/ = JsFuncSafe<void( UiRadioBox* sender )>;
		using OnChecking_t /**/ = JsFuncSafe<U1( UiRadioBox* sender, U1 bCanChangeValue )>;

		OnCheck_t						m_OnCheck;
		OnChecking_t					m_OnChecking;

		void							__OnCheck( Ui::IRadioBox& sender );
		void							__OnChecking( Ui::IRadioBox& sender, U1& bCanChangeValue );

	private:
		UiRadioBox*						SetText( PCWChar szText ) { GetControlTyped().SetText( szText ); return this; }
		WString							GetText() const { return GetControlTyped().GetText(); }

		UiRadioBox*						SetValue( U1 nValue ) { GetControlTyped().SetValue( nValue ); return this; }
		U1								GetValue() const { return GetControlTyped().GetValue(); }

		UiRadioBox*						SetGroup( U32 nGroup ) { GetControlTyped().SetGroup( nGroup ); return this; }
		U32								GetGroup() const { return GetControlTyped().GetGroup(); }

		UiRadioBox*						OnCheck( OnCheck_t&& fn );
		UiRadioBox*						OnChecking( OnChecking_t&& fn );
	};
}
