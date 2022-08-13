#include "StdAfx.h"
#include "UiSpin.h"

#define ThisMethod($x) &UiSpin::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiSpin::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiSpin> c_obj;
	}

	void UiSpin::DefineControl()
	{
		AutoAddMethod( OnClick, WrapObjectGeneric );
		AutoAddMethod( OnSpinStart, WrapObjectGeneric );
		AutoAddMethod( OnSpinEnd, WrapObjectGeneric );
		AutoAddMethod( OnSpin, WrapObjectGeneric );
	}

	U1 UiSpin::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiSpin::__OnClick( Ui::ISpin & sender, S32 nDelta )
	{
		m_OnClick( this, nDelta );
	}

	void UiSpin::__OnSpinStart( Ui::ISpin & sender )
	{
		m_OnSpinStart( this );
	}

	void UiSpin::__OnSpinEnd( Ui::ISpin & sender, U1 bCanceled )
	{
		m_OnSpinEnd( this, bCanceled );
	}

	void UiSpin::__OnSpin( Ui::ISpin & sender, S32 nDelta )
	{
		m_OnSpin( this, nDelta );
	}

	UiSpin* UiSpin::OnClick     /**/( OnClick_t     /**/ && fn ) { SetEventCallback<Ui::ISpin::OnClick     /**/>( m_OnClick     /**/, std::move( fn ), MakeThisFunc( __OnClick     /**/ ) ); return this; }
	UiSpin* UiSpin::OnSpinStart /**/( OnSpinStart_t /**/ && fn ) { SetEventCallback<Ui::ISpin::OnSpinStart /**/>( m_OnSpinStart /**/, std::move( fn ), MakeThisFunc( __OnSpinStart /**/ ) ); return this; }
	UiSpin* UiSpin::OnSpinEnd   /**/( OnSpinEnd_t   /**/ && fn ) { SetEventCallback<Ui::ISpin::OnSpinEnd   /**/>( m_OnSpinEnd   /**/, std::move( fn ), MakeThisFunc( __OnSpinEnd   /**/ ) ); return this; }
	UiSpin* UiSpin::OnSpin      /**/( OnSpin_t      /**/ && fn ) { SetEventCallback<Ui::ISpin::OnSpin      /**/>( m_OnSpin      /**/, std::move( fn ), MakeThisFunc( __OnSpin      /**/ ) ); return this; }
}
