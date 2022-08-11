#include "StdAfx.h"
#include "UiColorPicker.h"

#define ThisMethod($x) &UiColorPicker::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiColorPicker::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiColorPicker> c_obj;
	}

	void UiColorPicker::DefineControl()
	{
		AutoAddMethod( SetPickerType );
		AutoAddMethod( GetPickerType, WrapObjectGeneric );

		AutoAddMethod( SetCubePrimary );
		AutoAddMethod( GetCubePrimary, WrapObjectGeneric );

		AutoAddMethod( SetColor );
		AutoAddMethod( GetColor, WrapObjectGeneric );

		AutoAddMethod( OnChange, WrapObjectGeneric );
	}

	U1 UiColorPicker::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiColorPicker::__OnChange( Ui::IColorPicker & sender )
	{
		m_OnChange( this );
	}

	UiColorPicker * UiColorPicker::OnChange( OnChange_t && fn )
	{
		SetEventCallback<Ui::IColorPicker::OnChange>( m_OnChange, std::move( fn ), MakeThisFunc( __OnChange ) );
		return this;
	}

}
