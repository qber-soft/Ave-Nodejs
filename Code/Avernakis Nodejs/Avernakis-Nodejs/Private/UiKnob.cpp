#include "StdAfx.h"
#include "UiKnob.h"

#define ThisMethod($x) &UiKnob::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiKnob::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiKnob> c_obj;
	}

	void UiKnob::DefineControl()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText );

		AutoAddMethod( ValueSetRange );
		AutoAddMethod( ValueGetRange );

		AutoAddMethod( ValueSetDefault );
		AutoAddMethod( ValueGetDefault );

		AutoAddMethod( ValueSet );
		AutoAddMethod( ValueGet );

		AutoAddMethod( StepSetUnlimited );
		AutoAddMethod( StepGetUnlimited );

		AutoAddMethod( ValueSetCycle );
		AutoAddMethod( ValueGetCycle );

		AutoAddMethod( StepSetLarge );
		AutoAddMethod( StepGetLarge );

		AutoAddMethod( StepSetSmall );
		AutoAddMethod( StepGetSmall );

		AutoAddMethod( ValueSetSplit );
		AutoAddMethod( ValueGetSplit );

		AutoAddMethod( ValueSetTick );
		AutoAddMethod( ValueGetTick );

		AutoAddMethod( RingSetColor );
		AutoAddMethod( RingGetColor );

		AutoAddMethod( RingSetDefaultColor );
		AutoAddMethod( RingGetDefaultColor );

		AutoAddMethod( RingSetTickColor );
		AutoAddMethod( RingGetTickColor );

		AutoAddMethod( RingSetVisual );
		AutoAddMethod( RingGetVisual );

		AutoAddMethod( OnChange );
		AutoAddMethod( OnRotateBegin );
		AutoAddMethod( OnRotateEnd );
	}

	U1 UiKnob::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::IKnob::OnChange>() += MakeThisFunc( __OnChange );
		GetControlTyped().GetEvent<Ui::IKnob::OnRotateBegin>() += MakeThisFunc( __OnRotateBegin );
		GetControlTyped().GetEvent<Ui::IKnob::OnRotateEnd>() += MakeThisFunc( __OnRotateEnd );

		return true;
	}

	void UiKnob::__OnChange( Ui::IKnob & sender )
	{
		m_OnChange( this );
	}

	void UiKnob::__OnRotateBegin( Ui::IKnob & sender )
	{
		m_OnRotateBegin( this );
	}

	void UiKnob::__OnRotateEnd( Ui::IKnob & sender, U1 bCanceled )
	{
		m_OnRotateEnd( this, bCanceled );
	}

}
