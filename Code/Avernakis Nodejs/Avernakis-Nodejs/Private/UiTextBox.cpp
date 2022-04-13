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
		AutoAddMethod( GetText );

		AutoAddMethod( SetCue );
		AutoAddMethod( GetCue );

		AutoAddMethod( SetLimit );
		AutoAddMethod( GetLimit );

		AutoAddMethod( SetLimitMode );
		AutoAddMethod( GetLimitMode );

		AutoAddMethod( SetNumeric );
		AutoAddMethod( GetNumeric );

		AutoAddMethod( SetRange );
		AutoAddMethod( GetRange );

		AutoAddMethod( SetStep );
		AutoAddMethod( GetStep );

		AutoAddMethod( SetDefault );
		AutoAddMethod( GetDefault );

		AutoAddMethod( SetValue );
		AutoAddMethod( GetValue );

		AutoAddMethod( SetInvalid );
		AutoAddMethod( GetInvalid );

		AutoAddMethod( SetValid );
		AutoAddMethod( GetValid );

		AutoAddMethod( SetReadOnly );
		AutoAddMethod( GetReadOnly );

		AutoAddMethod( SetPassword );
		AutoAddMethod( GetPassword );

		AutoAddMethod( SetIme );
		AutoAddMethod( GetIme );

		AutoAddMethod( SetRememberCaret );
		AutoAddMethod( GetRememberCaret );

		AutoAddMethod( SetHideSelection );
		AutoAddMethod( GetHideSelection );

		AutoAddMethod( SetBorder );
		AutoAddMethod( GetBorder );

		AutoAddMethod( SetForceCue );
		AutoAddMethod( GetForceCue );

		AutoAddMethod( SetKeyInputMode );
		AutoAddMethod( GetKeyInputMode );

		AutoAddMethod( SetKey );
		AutoAddMethod( GetKey );

		AutoAddMethod( SelectionSet );
		AutoAddMethod( SelectionGet );
		AutoAddMethod( SelectionGetText );
		AutoAddMethod( SelectionReplace );

		AutoAddMethod( GetCaretPos );

		AutoAddMethod( OnChange );
		AutoAddMethod( OnSpinStart );
		AutoAddMethod( OnSpinEnd );
		AutoAddMethod( OnSpin );
	}

	U1 UiTextBox::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::ITextBox::OnChange>() += MakeThisFunc( __OnChange );
		GetControlTyped().GetEvent<Ui::ITextBox::OnSpinStart>() += MakeThisFunc( __OnSpinStart );
		GetControlTyped().GetEvent<Ui::ITextBox::OnSpinEnd>() += MakeThisFunc( __OnSpinEnd );
		GetControlTyped().GetEvent<Ui::ITextBox::OnSpin>() += MakeThisFunc( __OnSpin );

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

}
