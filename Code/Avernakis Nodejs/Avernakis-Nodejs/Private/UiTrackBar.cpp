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
		AutoAddMethod( GetOrientation, WrapObjectGeneric );
		AutoAddMethod( GetOrientationActually, WrapObjectGeneric );
		AutoAddMethod( SetMinimum );
		AutoAddMethod( GetMinimum, WrapObjectGeneric );
		AutoAddMethod( SetMaximum );
		AutoAddMethod( GetMaximum, WrapObjectGeneric );
		AutoAddMethod( SetValue );
		AutoAddMethod( SetValueForce );
		AutoAddMethod( GetValue, WrapObjectGeneric );
		AutoAddMethod( SetPage );
		AutoAddMethod( GetPage, WrapObjectGeneric );
		AutoAddMethod( OnThumbChange, WrapObjectGeneric );
		AutoAddMethod( OnThumbRelease, WrapObjectGeneric );
		AutoAddMethod( OnPageChange, WrapObjectGeneric );
	}

	U1 UiTrackBar::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

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

	UiTrackBar* UiTrackBar::OnThumbChange  /**/( Callback_t&& fn ) { m_OnThumbChange  /**/ = SetEventCallback<Ui::ITrackBar::OnThumbChange  /**/>( std::move( fn ), MakeThisFunc( __OnThumbChange  /**/ ) ); return this; }
	UiTrackBar* UiTrackBar::OnThumbRelease /**/( Callback_t&& fn ) { m_OnThumbRelease /**/ = SetEventCallback<Ui::ITrackBar::OnThumbRelease /**/>( std::move( fn ), MakeThisFunc( __OnThumbRelease /**/ ) ); return this; }
	UiTrackBar* UiTrackBar::OnPageChange   /**/( Callback_t&& fn ) { m_OnPageChange   /**/ = SetEventCallback<Ui::ITrackBar::OnPageChange   /**/>( std::move( fn ), MakeThisFunc( __OnPageChange   /**/ ) ); return this; }
}
