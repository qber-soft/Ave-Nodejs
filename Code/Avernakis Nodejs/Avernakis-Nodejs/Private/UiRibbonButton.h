#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiRibbonButton : public UiControlHelper<UiRibbonButton, Ui::IRibbonButton>
	{
	public:
		AveWrapControl( UiRibbonButton );

		~UiRibbonButton()
		{
		}

		static PCAChar					GetExportName() { return "UiRibbonButton"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using Callback_t = JsFuncSafe<void( UiRibbonButton* sender )>;

		Callback_t						m_OnClick;
		Callback_t						m_OnDrop;

		void							__OnClick( Ui::IRibbonButton& sender );
		void							__OnDrop( Ui::IRibbonButton& sender );

	private:
		UiRibbonButton*					SetText( PCWChar szText ) { GetControlTyped().SetText( szText ? szText : AveWide( "" ) ); return this; }
		WString							GetText() const { return GetControlTyped().GetText(); }

		UiRibbonButton*					SetSmall( U1 b ) { GetControlTyped().SetSmall( b ); return this; }
		U1								GetSmall() const { return GetControlTyped().GetSmall(); }

		UiRibbonButton*					SetCheck( U1 b ) { GetControlTyped().SetCheck( b ); return this; }
		U1								GetCheck() const { return GetControlTyped().GetCheck(); }

		UiRibbonButton*					SetButtonType( Ui::ButtonType nType ) { GetControlTyped().SetButtonType( nType ); return this; }
		Ui::ButtonType					GetButtonType() const { return GetControlTyped().GetButtonType(); }

		WrapPointer<UiControl>			SetDrop( WrapPointer<UiControl> c ) { return __ChangeContent( GetControlTyped().SetDrop( std::move( c->TakeOwnership() ) ) ); }
		WrapPointer<UiControl>			GetDrop() const { return __ReturnContent( GetControlTyped().GetDrop() ); }
		
		WrapPointer<UiVisual>			SetBigVisual( WrapPointer<UiVisual> v ) { return __ChangeContent( GetControlTyped().SetBigVisual( v->TakeVisual() ) ); }
		WrapPointer<UiVisual>			GetBigVisual() const { return __ReturnContent( GetControlTyped().GetBigVisual() ); }

		WrapPointer<UiVisual>			SetSmallVisual( WrapPointer<UiVisual> v ) { return __ChangeContent( GetControlTyped().SetSmallVisual( v->TakeVisual() ) ); }
		WrapPointer<UiVisual>			GetSmallVisual() const { return __ReturnContent( GetControlTyped().GetSmallVisual() ); }

		UiRibbonButton*					OnClick /**/( Callback_t&& fn );
		UiRibbonButton*					OnDrop  /**/( Callback_t&& fn );
	};
}
