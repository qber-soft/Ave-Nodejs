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
		AutoAddMethod( GetPickerType );

		AutoAddMethod( SetCubePrimary );
		AutoAddMethod( GetCubePrimary );

		AutoAddMethod( SetColor );
		AutoAddMethod( GetColor );

		AutoAddMethod( OnChange );
	}

	U1 UiColorPicker::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::IColorPicker::OnChange>() += MakeThisFunc( __OnChange );

		return true;
	}

	void UiColorPicker::__OnChange( Ui::IColorPicker & sender )
	{
		m_OnChange( this );
	}

}
