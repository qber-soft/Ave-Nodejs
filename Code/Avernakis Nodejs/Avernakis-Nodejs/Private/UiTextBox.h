#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiTextBox : public UiControlHelper<UiTextBox, Ui::ITextBox>
	{
	public:
		AveWrapControl( UiTextBox );

		~UiTextBox()
		{
		}

		static PCAChar					GetExportName() { return "UiTextBox"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnChange_t  /**/ = JsFuncSafe<void( UiTextBox* sender, Ui::TextBoxChangeReason nReason )>;
		using OnGeneric_t /**/ = JsFuncSafe<void( UiTextBox* sender )>;
		using OnSpinEnd_t /**/ = JsFuncSafe<void( UiTextBox* sender, U1 bCanceled )>;

		OnChange_t						m_OnChange;
		OnGeneric_t						m_OnSpinStart;
		OnSpinEnd_t						m_OnSpinEnd;
		OnGeneric_t						m_OnSpin;

		void							__OnChange( Ui::ITextBox& sender, Ui::TextBoxChangeReason nReason );
		void							__OnSpinStart( Ui::ITextBox& sender );
		void							__OnSpinEnd( Ui::ITextBox& sender, U1 bCanceled );
		void							__OnSpin( Ui::ITextBox& sender );

	private:
		UiTextBox*						SetText( PCWChar szText ) { GetControlTyped().SetText( szText ? szText : AveWide( "" ) ); return this; }
		WString							GetText() const { return GetControlTyped().GetText(); }

		UiTextBox*						SetCue( PCWChar szText ) { GetControlTyped().SetCue( szText ? szText : AveWide( "" ) ); return this; }
		WString							GetCue() const { return GetControlTyped().GetCue(); }

		UiTextBox*						SetLimit( S32 nLimit ) { GetControlTyped().SetLimit( nLimit ); return this; }
		S32								GetLimit() const { return GetControlTyped().GetLimit(); }

		UiTextBox*						SetLimitMode( Ui::TextBoxLimitMode nMode ) { GetControlTyped().SetLimitMode( nMode ); return this; }
		Ui::TextBoxLimitMode			GetLimitMode() const { return GetControlTyped().GetLimitMode(); }

		UiTextBox*						SetNumeric( S32 nFracCount ) { GetControlTyped().SetNumeric( nFracCount ); return this; }
		S32								GetNumeric() const { return GetControlTyped().GetNumeric(); }

		UiTextBox*						SetRange( R64 fMin, R64 fMax ) { GetControlTyped().SetRange( fMin, fMax ); return this; }
		WrapData<R64_2>					GetRange() const { return GetControlTyped().GetRange(); }

		UiTextBox*						SetStep( R64 fStep ) { GetControlTyped().SetStep( fStep ); return this; }
		R64								GetStep() const { return GetControlTyped().GetStep(); }

		UiTextBox*						SetDefault( R64 fDefault ) { GetControlTyped().SetDefault( fDefault ); return this; }
		R64								GetDefault() const { return GetControlTyped().GetDefault(); }

		UiTextBox*						SetValue( R64 fValue ) { GetControlTyped().SetValue( fValue ); return this; }
		R64								GetValue() const { return GetControlTyped().GetValue(); }

		UiTextBox*						SetInvalid( PCWChar szText ) { GetControlTyped().SetInvalid( szText ); return this; }
		WString							GetInvalid() const { return GetControlTyped().GetInvalid(); }

		UiTextBox*						SetValid( PCWChar szText ) { GetControlTyped().SetValid( szText ? szText : AveWide( "" ) ); return this; }
		WString							GetValid() const { return GetControlTyped().GetValid(); }

		UiTextBox*						SetReadOnly( U1 b ) { GetControlTyped().SetReadOnly( b ); return this; }
		U1								GetReadOnly() const { return GetControlTyped().GetReadOnly(); }

		UiTextBox*						SetPassword( PCWChar szChar ) { GetControlTyped().SetPassword( szChar && (szChar[0] < 0xd800 || szChar[0] > 0xdfff) ? szChar[0] : 0 ); return this; }
		WString							GetPassword() const { WString s; if ( GetControlTyped().GetPassword() ) s += GetControlTyped().GetPassword(); return std::move( s ); }

		UiTextBox*						SetIme( U1 b ) { GetControlTyped().SetIme( b ); return this; }
		U1								GetIme() const { return GetControlTyped().GetIme(); }

		UiTextBox*						SetRememberCaret( U1 b ) { GetControlTyped().SetRememberCaret( b ); return this; }
		U1								GetRememberCaret() const { return GetControlTyped().GetRememberCaret(); }

		UiTextBox*						SetHideSelection( U1 b ) { GetControlTyped().SetHideSelection( b ); return this; }
		U1								GetHideSelection() const { return GetControlTyped().GetHideSelection(); }

		UiTextBox*						SetBorder( U1 b ) { GetControlTyped().SetBorder( b ); return this; }
		U1								GetBorder() const { return GetControlTyped().GetBorder(); }

		UiTextBox*						SetForceCue( U1 b ) { GetControlTyped().SetForceCue( b ); return this; }
		U1								GetForceCue() const { return GetControlTyped().GetForceCue(); }

		UiTextBox*						SetKeyInputMode( U32 nKeyInputMode ) { GetControlTyped().SetKeyInputMode( nKeyInputMode ); return this; }
		U32								GetKeyInputMode() const { return GetControlTyped().GetKeyInputMode(); }

		UiTextBox*						SetKey( const WrapData<Ui::Hotkey>& hk ) { GetControlTyped().SetKey( hk ); return this; }
		WrapData<Ui::Hotkey>			GetKey() const { return GetControlTyped().GetKey(); }

		UiTextBox*						SelectionSet( S32 nStart, S32 nEnd ) { GetControlTyped().SelectionSet( nStart, nEnd ); return this; }
		WrapData<S32_2>					SelectionGet() const { return GetControlTyped().SelectionGet(); }
		WString							SelectionGetText() const { return GetControlTyped().SelectionGetText(); }
		UiTextBox*						SelectionReplace( PCWChar szText ) { GetControlTyped().SelectionReplace( szText ? szText : AveWide( "" ) ); return this; }

		WrapData<S32_2>					GetCaretPos() const { return GetControlTyped().GetCaretPos(); }

		UiTextBox*						OnChange    /**/( OnChange_t  /**/ && fn );
		UiTextBox*						OnSpinStart /**/( OnGeneric_t /**/ && fn );
		UiTextBox*						OnSpinEnd   /**/( OnSpinEnd_t /**/ && fn );
		UiTextBox*						OnSpin      /**/( OnGeneric_t /**/ && fn );
	};
}
