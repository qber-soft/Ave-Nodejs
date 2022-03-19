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
		AutoAddMethod( GetOrientation );
		AutoAddMethod( GetOrientationActually );
		AutoAddMethod( SetShrink );
		AutoAddMethod( GetShrink );
		AutoAddMethod( SetArrowVisible );
		AutoAddMethod( GetArrowVisible );
		AutoAddMethod( SetDynamicPage );
		AutoAddMethod( GetDynamicPage );
		AutoAddMethod( SetMinimumExtend );
		AutoAddMethod( GetMinimumExtend );
		AutoAddMethod( SetMaximumExtend );
		AutoAddMethod( GetMaximumExtend );
		AutoAddMethod( SetMinimum );
		AutoAddMethod( GetMinimum );
		AutoAddMethod( GetMinimumVirtual );
		AutoAddMethod( SetMaximum );
		AutoAddMethod( GetMaximum );
		AutoAddMethod( GetMaximumVirtual );
		AutoAddMethod( SetValue );
		AutoAddMethod( SetValueForce );
		AutoAddMethod( GetValue );
		AutoAddMethod( GetValueFinal );
		AutoAddMethod( GetValuePercent );
		AutoAddMethod( GetValuePercentFinal );
		AutoAddMethod( SetPage );
		AutoAddMethod( GetPage );
		AutoAddMethod( SetStep );
		AutoAddMethod( GetStep );
		AutoAddMethod( Scroll );

		AutoAddMethod( OnScroll );
		AutoAddMethod( OnScrolling );
		AutoAddMethod( OnPageChange );

	}

	U1 UiScrollBar::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::IScrollBar::OnScroll>() += MakeThisFunc( __OnScroll );
		GetControlTyped().GetEvent<Ui::IScrollBar::OnScrolling>() += MakeThisFunc( __OnScrolling );
		GetControlTyped().GetEvent<Ui::IScrollBar::OnPageChange>() += MakeThisFunc( __OnPageChange );

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

}
