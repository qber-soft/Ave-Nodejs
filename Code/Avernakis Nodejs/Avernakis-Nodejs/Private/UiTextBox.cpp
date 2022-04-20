#include "StdAfx.h"
#include "UiTextBox.h"

#define ThisMethod($x) &UiTextBox::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiTextBox::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiTextBox> c_obj;
	}

	void UiTextBox::DefineControl()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText, WrapObjectGeneric );

		AutoAddMethod( SetCue );
		AutoAddMethod( GetCue, WrapObjectGeneric );

		AutoAddMethod( SetLimit );
		AutoAddMethod( GetLimit, WrapObjectGeneric );

		AutoAddMethod( SetLimitMode );
		AutoAddMethod( GetLimitMode, WrapObjectGeneric );

		AutoAddMethod( SetNumeric );
		AutoAddMethod( GetNumeric, WrapObjectGeneric );

		AutoAddMethod( SetRange );
		AutoAddMethod( GetRange, WrapObjectGeneric );

		AutoAddMethod( SetStep );
		AutoAddMethod( GetStep, WrapObjectGeneric );

		AutoAddMethod( SetDefault );
		AutoAddMethod( GetDefault, WrapObjectGeneric );

		AutoAddMethod( SetValue );
		AutoAddMethod( GetValue, WrapObjectGeneric );

		AutoAddMethod( SetInvalid );
		AutoAddMethod( GetInvalid, WrapObjectGeneric );

		AutoAddMethod( SetValid );
		AutoAddMethod( GetValid, WrapObjectGeneric );

		AutoAddMethod( SetReadOnly );
		AutoAddMethod( GetReadOnly, WrapObjectGeneric );

		AutoAddMethod( SetPassword );
		AutoAddMethod( GetPassword, WrapObjectGeneric );

		AutoAddMethod( SetIme );
		AutoAddMethod( GetIme, WrapObjectGeneric );

		AutoAddMethod( SetRememberCaret );
		AutoAddMethod( GetRememberCaret, WrapObjectGeneric );

		AutoAddMethod( SetHideSelection );
		AutoAddMethod( GetHideSelection, WrapObjectGeneric );

		AutoAddMethod( SetBorder );
		AutoAddMethod( GetBorder, WrapObjectGeneric );

		AutoAddMethod( SetForceCue );
		AutoAddMethod( GetForceCue, WrapObjectGeneric );

		AutoAddMethod( SetKeyInputMode );
		AutoAddMethod( GetKeyInputMode, WrapObjectGeneric );

		AutoAddMethod( SetKey );
		AutoAddMethod( GetKey, WrapObjectGeneric );

		AutoAddMethod( SelectionSet );
		AutoAddMethod( SelectionGet, WrapObjectGeneric );
		AutoAddMethod( SelectionGetText, WrapObjectGeneric );
		AutoAddMethod( SelectionReplace );

		AutoAddMethod( GetCaretPos, WrapObjectGeneric );

		AutoAddMethod( OnChange, WrapObjectGeneric );
		AutoAddMethod( OnSpinStart, WrapObjectGeneric );
		AutoAddMethod( OnSpinEnd, WrapObjectGeneric );
		AutoAddMethod( OnSpin, WrapObjectGeneric );
	}

	U1 UiTextBox::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiTextBox::__OnChange( Ui::ITextBox & sender, Ui::TextBoxChangeReason nReason )
	{
		m_OnChange( this, nReason );
	}

	void UiTextBox::__OnSpinStart( Ui::ITextBox & sender )
	{
		m_OnSpinStart( this );
	}

	void UiTextBox::__OnSpinEnd( Ui::ITextBox & sender, U1 bCanceled )
	{
		m_OnSpinEnd( this, bCanceled );
	}

	void UiTextBox::__OnSpin( Ui::ITextBox & sender )
	{
		m_OnSpin( this );
	}

	UiTextBox* UiTextBox::OnChange    /**/( OnChange_t  /**/ && fn ) { m_OnChange    /**/ = SetEventCallback<Ui::ITextBox::OnChange    /**/>( std::move( fn ), MakeThisFunc( __OnChange    /**/ ) ); return this; }
	UiTextBox* UiTextBox::OnSpinStart /**/( OnGeneric_t /**/ && fn ) { m_OnSpinStart /**/ = SetEventCallback<Ui::ITextBox::OnSpinStart /**/>( std::move( fn ), MakeThisFunc( __OnSpinStart /**/ ) ); return this; }
	UiTextBox* UiTextBox::OnSpinEnd   /**/( OnSpinEnd_t /**/ && fn ) { m_OnSpinEnd   /**/ = SetEventCallback<Ui::ITextBox::OnSpinEnd   /**/>( std::move( fn ), MakeThisFunc( __OnSpinEnd   /**/ ) ); return this; }
	UiTextBox* UiTextBox::OnSpin      /**/( OnGeneric_t /**/ && fn ) { m_OnSpin      /**/ = SetEventCallback<Ui::ITextBox::OnSpin      /**/>( std::move( fn ), MakeThisFunc( __OnSpin      /**/ ) ); return this; }
}
