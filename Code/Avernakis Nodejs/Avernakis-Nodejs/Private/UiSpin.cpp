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
		AutoAddMethod( OnClick );
		AutoAddMethod( OnSpinStart );
		AutoAddMethod( OnSpinEnd );
		AutoAddMethod( OnSpin );
	}

	U1 UiSpin::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::ISpin::OnClick     /**/>() += MakeThisFunc( __OnClick     /**/ );
		GetControlTyped().GetEvent<Ui::ISpin::OnSpinStart /**/>() += MakeThisFunc( __OnSpinStart /**/ );
		GetControlTyped().GetEvent<Ui::ISpin::OnSpinEnd   /**/>() += MakeThisFunc( __OnSpinEnd   /**/ );
		GetControlTyped().GetEvent<Ui::ISpin::OnSpin      /**/>() += MakeThisFunc( __OnSpin      /**/ );

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

}
