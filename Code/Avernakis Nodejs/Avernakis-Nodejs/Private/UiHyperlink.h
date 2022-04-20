#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiHyperlink : public UiControlHelper<UiHyperlink, Ui::IHyperlink>
	{
	public:
		AveWrapControl( UiHyperlink );

		~UiHyperlink()
		{
		}

		static PCAChar					GetExportName() { return "UiHyperlink"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using Callback_t = JsFuncSafe<void( UiHyperlink* sender, U32 nId )>;

		Callback_t						m_OnClick;

		void							__OnClick( Ui::IHyperlink& sender, U32 nId );

	private:
		UiHyperlink*					SetText( PCWChar szText ) { GetControlTyped().SetText( szText ? szText : AveWide( "" ) ); return this; }
		WString							GetText() const { return GetControlTyped().GetText(); }
		U1								GetTextValid() const { return GetControlTyped().GetTextValid(); }

		UiHyperlink*					SetAlignHorz( Ui::AlignType nAlign ) { GetControlTyped().SetAlignHorz( nAlign ); return this; }
		Ui::AlignType					GetAlignHorz() const { return GetControlTyped().GetAlignHorz(); }

		UiHyperlink*					SetAlignVert( Ui::AlignType nAlign ) { GetControlTyped().SetAlignVert( nAlign ); return this; }
		Ui::AlignType					GetAlignVert() const { return GetControlTyped().GetAlignVert(); }

		UiHyperlink*					SetBackColor( const WrapData<U8_4>& vColor ) { GetControlTyped().SetBackColor( vColor ); return this; }
		WrapData<U8_4>					GetBackColor() const { return GetControlTyped().GetBackColor(); }

		UiHyperlink*					SetWrappable( U1 b ) { GetControlTyped().SetWrappable( b ); return this; }
		U1								GetWrappable() const { return GetControlTyped().GetWrappable(); }

		UiHyperlink*					SetUnderline( Ui::HyperlinkUnderline nUnderline ) { GetControlTyped().SetUnderline( nUnderline ); return this; }
		Ui::HyperlinkUnderline			GetUnderline() const { return GetControlTyped().GetUnderline(); }

		UiHyperlink*					OnClick( Callback_t&& fn );
	};
}
