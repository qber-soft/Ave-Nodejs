#include "StdAfx.h"
#include "UiScrollBar.h"

#define ThisMethod($x) &UiScrollBar::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiScrollBar::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiScrollBar> c_obj;
	}

	void UiScrollBar::DefineControl()
	{
		AutoAddMethod( SetOrientation );
		AutoAddMethod( GetOrientation, WrapObjectGeneric );
		AutoAddMethod( GetOrientationActually, WrapObjectGeneric );
		AutoAddMethod( SetShrink );
		AutoAddMethod( GetShrink, WrapObjectGeneric );
		AutoAddMethod( SetArrowVisible );
		AutoAddMethod( GetArrowVisible, WrapObjectGeneric );
		AutoAddMethod( SetDynamicPage );
		AutoAddMethod( GetDynamicPage, WrapObjectGeneric );
		AutoAddMethod( SetMinimumExtend );
		AutoAddMethod( GetMinimumExtend, WrapObjectGeneric );
		AutoAddMethod( SetMaximumExtend );
		AutoAddMethod( GetMaximumExtend, WrapObjectGeneric );
		AutoAddMethod( SetMinimum );
		AutoAddMethod( GetMinimum, WrapObjectGeneric );
		AutoAddMethod( GetMinimumVirtual, WrapObjectGeneric );
		AutoAddMethod( SetMaximum );
		AutoAddMethod( GetMaximum, WrapObjectGeneric );
		AutoAddMethod( GetMaximumVirtual, WrapObjectGeneric );
		AutoAddMethod( SetValue );
		AutoAddMethod( SetValueForce );
		AutoAddMethod( GetValue, WrapObjectGeneric );
		AutoAddMethod( GetValueFinal, WrapObjectGeneric );
		AutoAddMethod( GetValuePercent, WrapObjectGeneric );
		AutoAddMethod( GetValuePercentFinal, WrapObjectGeneric );
		AutoAddMethod( SetPage );
		AutoAddMethod( GetPage, WrapObjectGeneric );
		AutoAddMethod( SetStep );
		AutoAddMethod( GetStep, WrapObjectGeneric );
		AutoAddMethod( Scroll );

		AutoAddMethod( OnScroll, WrapObjectGeneric );
		AutoAddMethod( OnScrolling, WrapObjectGeneric );
		AutoAddMethod( OnPageChange, WrapObjectGeneric );

	}

	U1 UiScrollBar::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiScrollBar::__OnScroll( Ui::IScrollBar & sender, U1 bThumb )
	{
		m_OnScroll( this, bThumb );
	}

	void UiScrollBar::__OnScrolling( Ui::IScrollBar & sender )
	{
		m_OnScrolling( this );
	}

	void UiScrollBar::__OnPageChange( Ui::IScrollBar & sender, R32 fPagePercent )
	{
		m_OnPageChange( this, fPagePercent );
	}

	UiScrollBar* UiScrollBar::OnScroll     /**/( OnScroll_t     /**/ && fn ) { m_OnScroll     /**/ = SetEventCallback<Ui::IScrollBar::OnScroll     /**/>( std::move( fn ), MakeThisFunc( __OnScroll     /**/ ) ); return this; }
	UiScrollBar* UiScrollBar::OnScrolling  /**/( OnScrolling_t  /**/ && fn ) { m_OnScrolling  /**/ = SetEventCallback<Ui::IScrollBar::OnScrolling  /**/>( std::move( fn ), MakeThisFunc( __OnScrolling  /**/ ) ); return this; }
	UiScrollBar* UiScrollBar::OnPageChange /**/( OnPageChange_t /**/ && fn ) { m_OnPageChange /**/ = SetEventCallback<Ui::IScrollBar::OnPageChange /**/>( std::move( fn ), MakeThisFunc( __OnPageChange /**/ ) ); return this; }
}
