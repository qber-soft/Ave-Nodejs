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
		AutoAddMethod( GetText, WrapObjectGeneric );

		AutoAddMethod( ValueSetRange );
		AutoAddMethod( ValueGetRange, WrapObjectGeneric );

		AutoAddMethod( ValueSetDefault );
		AutoAddMethod( ValueGetDefault, WrapObjectGeneric );

		AutoAddMethod( ValueSet );
		AutoAddMethod( ValueGet, WrapObjectGeneric );

		AutoAddMethod( StepSetUnlimited );
		AutoAddMethod( StepGetUnlimited, WrapObjectGeneric );

		AutoAddMethod( ValueSetCycle );
		AutoAddMethod( ValueGetCycle, WrapObjectGeneric );

		AutoAddMethod( StepSetLarge );
		AutoAddMethod( StepGetLarge, WrapObjectGeneric );

		AutoAddMethod( StepSetSmall );
		AutoAddMethod( StepGetSmall, WrapObjectGeneric );

		AutoAddMethod( ValueSetSplit );
		AutoAddMethod( ValueGetSplit, WrapObjectGeneric );

		AutoAddMethod( ValueSetTick );
		AutoAddMethod( ValueGetTick, WrapObjectGeneric );

		AutoAddMethod( RingSetColor );
		AutoAddMethod( RingGetColor, WrapObjectGeneric );

		AutoAddMethod( RingSetDefaultColor );
		AutoAddMethod( RingGetDefaultColor, WrapObjectGeneric );

		AutoAddMethod( RingSetTickColor );
		AutoAddMethod( RingGetTickColor, WrapObjectGeneric );

		AutoAddMethod( RingSetVisual );
		AutoAddMethod( RingGetVisual, WrapObjectGeneric );

		AutoAddMethod( OnChange, WrapObjectGeneric );
		AutoAddMethod( OnRotateBegin, WrapObjectGeneric );
		AutoAddMethod( OnRotateEnd, WrapObjectGeneric );
	}

	U1 UiKnob::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

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

	UiKnob* UiKnob::OnChange      /**/( OnGeneric_t   /**/ && fn ) { SetEventCallback<Ui::IKnob::OnChange      /**/>( m_OnChange      /**/, std::move( fn ), MakeThisFunc( __OnChange      /**/ ) ); return this; }
	UiKnob* UiKnob::OnRotateBegin /**/( OnGeneric_t   /**/ && fn ) { SetEventCallback<Ui::IKnob::OnRotateBegin /**/>( m_OnRotateBegin /**/, std::move( fn ), MakeThisFunc( __OnRotateBegin /**/ ) ); return this; }
	UiKnob* UiKnob::OnRotateEnd   /**/( OnRotateEnd_t /**/ && fn ) { SetEventCallback<Ui::IKnob::OnRotateEnd   /**/>( m_OnRotateEnd   /**/, std::move( fn ), MakeThisFunc( __OnRotateEnd   /**/ ) ); return this; }

}
