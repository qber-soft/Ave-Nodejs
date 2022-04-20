#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiButtonCustomDrawResult
	{
	public:
		U32								m_Behavior;
		WrapData<U8_4>					m_NewTextColor;
		WrapData<S32_R>					m_NewRect;
		U32								m_NewFormat;
	};

	NavDefineDataByMember_( UiButtonCustomDrawResult, Behavior, NewTextColor, NewRect, NewFormat );

	class UiButtonCustomDraw
	{
	public:
		UiPainter*						m_Painter;
		Ui::IButton::CustomDrawPart		m_Part;
		Ui::CustomDrawStage				m_Stage;
		WrapData<S32_R>					m_RectButton;
		WrapData<S32_R>					m_Rect;
		WString							m_Text;
		U32								m_TextFlag;
		WrapData<UiPainterState>		m_State;
	};

	NavDefineDataByMember_( UiButtonCustomDraw, Painter, Part, Stage, RectButton, Rect, Text, TextFlag, State );

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
		using CustomDraw_t = JsFuncSafe<WrapData<UiButtonCustomDrawResult>( UiButton* sender, const WrapData<UiButtonCustomDraw>& cdp )>;

		Callback_t						m_OnClick;
		Callback_t						m_OnDrop;
		CustomDraw_t					m_OnCustomDraw;

		void							__OnClick( Ui::IButton& sender );
		void							__OnDrop( Ui::IButton& sender );
		void							__OnCustomDraw( Ui::IButton& sender, const Ui::IButton::CustomDrawParam& cdp, U32& cdr );

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

		UiButton*						OnClick( Callback_t&& fn );
		UiButton*						OnDrop( Callback_t&& fn );
		UiButton*						OnCustomDraw( const CallbackInfo& ci, CustomDraw_t&& fn );
	};
}
