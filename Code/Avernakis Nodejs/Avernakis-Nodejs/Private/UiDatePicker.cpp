#include "StdAfx.h"
#include "UiDatePicker.h"

#define ThisMethod($x) &UiDatePicker::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiDatePicker::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiDatePicker> c_obj;
	}

	void UiDatePicker::DefineControl()
	{
		AutoAddMethod( SetRange );
		AutoAddMethod( GetRange, WrapObjectGeneric );

		AutoAddMethod( SetDate );
		AutoAddMethod( GetDate, WrapObjectGeneric );

		AutoAddMethod( SetDateMark );
		AutoAddMethod( GetDateMark, WrapObjectGeneric );

		AutoAddMethod( SetCultureId );
		AutoAddMethod( GetCultureId, WrapObjectGeneric );

		AutoAddMethod( SetFormat );
		AutoAddMethod( GetFormat, WrapObjectGeneric );

		AutoAddMethod( SetBorder );
		AutoAddMethod( GetBorder, WrapObjectGeneric );

		AutoAddMethod( Drop );

		AutoAddMethod( OnChange, WrapObjectGeneric );
	}

	U1 UiDatePicker::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiDatePicker::__OnChange( Ui::IDatePicker & sender )
	{
		m_OnChange( this );
	}

	UiDatePicker * UiDatePicker::SetFormat( const WrapData<DateTimeFormat>& pFormat )
	{
		if ( 7 != pFormat.m_DayNameFull.Size() || 7 != pFormat.m_DayNameAbbreviated.Size() || 12 != pFormat.m_MonthNameFull.Size() || 12 != pFormat.m_MonthNameAbbreviated.Size() )
			return this;

		m_Format = pFormat;

		CultureInfoDateTime cidt{};
		m_Format.ToCultureInfo( cidt );
		GetControlTyped().SetFormat( cidt );

		return this;
	}

	WrapData<DateTimeFormat> UiDatePicker::GetFormat() const
	{
		WrapData<DateTimeFormat> r{};
		r.FromCultureInfo( GetControlTyped().GetFormat() );
		return r;
	}

	UiDatePicker * UiDatePicker::OnChange( OnChange_t && fn )
	{
		m_OnChange = SetEventCallback<Ui::IDatePicker::OnDateChange>( std::move( fn ), MakeThisFunc( __OnChange ) );
		return this;
	}

}
