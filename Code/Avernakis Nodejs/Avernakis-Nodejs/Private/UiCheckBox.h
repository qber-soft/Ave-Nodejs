#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiCheckBox : public UiControlHelper<UiCheckBox, Ui::ICheckBox>
	{
	public:
		AveWrapControl( UiCheckBox );

		~UiCheckBox()
		{
		}

		static PCAChar					GetExportName() { return "UiCheckBox"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnCheck_t = JsFuncSafe<void( UiCheckBox* sender )>;
		using OnChecking_t = JsFuncSafe<U1( UiCheckBox* sender )>;

		OnCheck_t						m_OnCheck;
		OnChecking_t					m_OnChecking;

		void							__OnCheck( Ui::ICheckBox& sender );
		void							__OnChecking( Ui::ICheckBox& sender, U1& bCanCheck );

	private:
		UiCheckBox*						SetText( PCWChar szText ) { GetControlTyped().SetText( szText ? szText : AveWide( "" ) ); return this; }
		WString							GetText() const { return GetControlTyped().GetText(); }
		
		UiCheckBox*						SetValue( Ui::CheckValue nValue ) { GetControlTyped().SetValue( nValue ); return this; }
		Ui::CheckValue					GetValue() const { return GetControlTyped().GetValue(); }
		Ui::CheckValue					GetNextValue() const { return GetControlTyped().GetNextValue(); }

		UiCheckBox*						SetTriple( U1 b ) { GetControlTyped().SetTriple( b ); return this; }
		U1								GetTriple() const { return GetControlTyped().GetTriple(); }

		UiCheckBox*						SetCheckBoxStyle( Ui::CheckBoxStyle nStyle ) { GetControlTyped().SetCheckBoxStyle( nStyle ); return this; }
		Ui::CheckBoxStyle				GetCheckBoxStyle() const { return GetControlTyped().GetCheckBoxStyle(); }

		UiCheckBox*						OnCheck( OnCheck_t&& fn ) { m_OnCheck = std::move( fn ); return this; }
		UiCheckBox*						OnChecking( OnChecking_t&& fn ) { m_OnChecking = std::move( fn ); return this; }
	};
}
