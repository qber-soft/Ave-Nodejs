#include "StdAfx.h"
#include "UiPager.h"

#define ThisMethod($x) &UiPager::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiPager::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiPager> c_obj;
	}

	void UiPager::DefineControl()
	{
		AutoAddMethod( SetContent );
		AutoAddMethod( GetContent, WrapObjectGeneric );

		AutoAddMethod( SetContentSize );
		AutoAddMethod( GetContentSize, WrapObjectGeneric );
		AutoAddMethod( GetRealContentSize, WrapObjectGeneric );

		AutoAddMethod( SetContentHorizontalAlign );
		AutoAddMethod( GetContentHorizontalAlign, WrapObjectGeneric );

		AutoAddMethod( SetContentVerticalAlign );
		AutoAddMethod( GetContentVerticalAlign, WrapObjectGeneric );

		AutoAddMethod( SetAdjustment );
		AutoAddMethod( GetAdjustment, WrapObjectGeneric );

		AutoAddMethod( SetAutoHideScroll );
		AutoAddMethod( GetAutoHideScroll, WrapObjectGeneric );

		AutoAddMethod( SetPointerScroll );
		AutoAddMethod( GetPointerScroll, WrapObjectGeneric );

		AutoAddMethod( SetScrollPosition );
		AutoAddMethod( GetScrollPosition, WrapObjectGeneric );
		AutoAddMethod( GetScrollSize, WrapObjectGeneric );
		AutoAddMethod( GetScrollMax, WrapObjectGeneric );
	}

	U1 UiPager::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	WrapData<S32_2> UiPager::GetScrollMax() const
	{
		S32_2 v{};
		if ( GetControlTyped().GetScrollH().GetEnable() )
			v.x = GetControlTyped().GetScrollH().GetMaximum();
		if ( GetControlTyped().GetScrollV().GetEnable() )
			v.y = GetControlTyped().GetScrollV().GetMaximum();
		return v;
	}

}
