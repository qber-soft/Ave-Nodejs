#include "StdAfx.h"
#include "UiTrackBar.h"

#define ThisMethod($x) &UiTrackBar::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiTrackBar::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiTrackBar> c_obj;
	}

	void UiTrackBar::DefineControl()
	{
		AutoAddMethod( SetOrientation );
		AutoAddMethod( GetOrientation );
		AutoAddMethod( GetOrientationActually );
		AutoAddMethod( SetMinimum );
		AutoAddMethod( GetMinimum );
		AutoAddMethod( SetMaximum );
		AutoAddMethod( GetMaximum );
		AutoAddMethod( SetValue );
		AutoAddMethod( SetValueForce );
		AutoAddMethod( GetValue );
		AutoAddMethod( SetPage );
		AutoAddMethod( GetPage );
		AutoAddMethod( OnThumbChange );
		AutoAddMethod( OnThumbRelease );
		AutoAddMethod( OnPageChange );
	}

	U1 UiTrackBar::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::ITrackBar::OnThumbChange  /**/>() += MakeThisFunc( __OnThumbChange  /**/ );
		GetControlTyped().GetEvent<Ui::ITrackBar::OnThumbRelease /**/>() += MakeThisFunc( __OnThumbRelease /**/ );
		GetControlTyped().GetEvent<Ui::ITrackBar::OnPageChange   /**/>() += MakeThisFunc( __OnPageChange   /**/ );

		return true;
	}

	void UiTrackBar::__OnThumbChange( Ui::ITrackBar & sender )
	{
		m_OnThumbChange( this );
	}

	void UiTrackBar::__OnThumbRelease( Ui::ITrackBar & sender )
	{
		m_OnThumbRelease( this );
	}

	void UiTrackBar::__OnPageChange( Ui::ITrackBar & sender )
	{
		m_OnPageChange( this );
	}

}
