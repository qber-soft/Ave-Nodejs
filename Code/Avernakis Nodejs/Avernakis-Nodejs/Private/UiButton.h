#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiButton : public UiControlHelper<UiButton, Ui::IButton>
	{
	public:
		AveWrapControl( UiButton );

		~UiButton()
		{
		}

		static PCAChar					GetExportName() { return "UiButton"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using Callback_t = JsFuncSafe<void( UiButton* sender )>;

		Callback_t						m_OnClick;
		Callback_t						m_OnDrop;

		void							__OnClick( Ui::IButton& sender );
		void							__OnDrop( Ui::IButton& sender );

	private:
		UiButton*						SetText( PCWChar szText ) { GetControlTyped().SetText( szText ? szText : AveWide( "" ) ); return this; }
		WString							GetText() const { return GetControlTyped().GetText(); }
		UiButton*						SetButtonType( Ui::ButtonType nType ) { GetControlTyped().SetButtonType( nType ); return this; }
		Ui::ButtonType					GetButtonType() const { return GetControlTyped().GetButtonType(); }
		UiButton*						SetButtonStyle( Ui::ButtonStyle nStyle ) { GetControlTyped().SetButtonStyle( nStyle ); return this; }
		Ui::ButtonStyle					GetButtonStyle() const { return GetControlTyped().GetButtonStyle(); }
		WrapPointer<UiControl>			SetDrop( WrapPointer<UiControl> c ) { return __ChangeContent( GetControlTyped().SetDrop( std::move( c->TakeOwnership() ) ) ); }
		WrapPointer<UiControl>			GetDrop() const { return __ReturnContent( GetControlTyped().GetDrop() ); }
		UiButton*						SetAlignHorz( Ui::AlignType nAlign ) { GetControlTyped().SetAlignHorz( nAlign ); return this; }
		Ui::AlignType					GetAlignHorz() const { return GetControlTyped().GetAlignHorz(); }
		UiButton*						SetVisualTextLayout( Ui::VisualTextLayout nLayout ) { GetControlTyped().SetVisualTextLayout( nLayout ); return this; }
		Ui::VisualTextLayout			GetVisualTextLayout() const { return GetControlTyped().GetVisualTextLayout(); }
		WrapPointer<UiVisual>			SetVisual( WrapPointer<UiVisual> v ) { return __ChangeContent( GetControlTyped().SetVisual( v->TakeVisual() ) ); }
		WrapPointer<UiVisual>			GetVisual() const { return __ReturnContent( GetControlTyped().GetVisual() ); }

		UiButton*						OnClick( Callback_t&& fn ) { m_OnClick = std::move( fn ); return this; }
		UiButton*						OnDrop( Callback_t&& fn ) { m_OnDrop = std::move( fn ); return this; }
	};
}
