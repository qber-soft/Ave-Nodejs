#include "StdAfx.h"
#include "UiCalendar.h"

#define ThisMethod($x) &UiCalendar::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiCalendar::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiCalendar> c_obj;
	}

	void UiCalendar::DefineControl()
	{
		AutoAddMethod( SetRange );
		AutoAddMethod( GetRange, WrapObjectGeneric );

		AutoAddMethod( SetRangeLevel );
		AutoAddMethod( GetRangeLevel, WrapObjectGeneric );

		AutoAddMethod( SetDate );
		AutoAddMethod( GetDate, WrapObjectGeneric );

		AutoAddMethod( SetDateMark );
		AutoAddMethod( GetDateMark, WrapObjectGeneric );

		AutoAddMethod( SetCultureId );
		AutoAddMethod( GetCultureId, WrapObjectGeneric );

		AutoAddMethod( SetFormat );
		AutoAddMethod( GetFormat, WrapObjectGeneric );

		AutoAddMethod( OnChange, WrapObjectGeneric );
	}

	U1 UiCalendar::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	void UiCalendar::__OnChange( Ui::ICalendar & sender )
	{
		m_OnChange( this );
	}

	UiCalendar * UiCalendar::SetFormat( const WrapData<DateTimeFormat>& pFormat )
	{
		if ( 7 != pFormat.m_DayNameFull.Size() || 7 != pFormat.m_DayNameAbbreviated.Size() || 12 != pFormat.m_MonthNameFull.Size() || 12 != pFormat.m_MonthNameAbbreviated.Size() )
			return this;

		m_Format = pFormat;

		CultureInfoDateTime cidt{};
		m_Format.ToCultureInfo( cidt );
		GetControlTyped().SetFormat( cidt );

		return this;
	}

	WrapData<DateTimeFormat> UiCalendar::GetFormat() const
	{
		WrapData<DateTimeFormat> r{};
		r.FromCultureInfo( GetControlTyped().GetFormat() );
		return r;
	}

	UiCalendar * UiCalendar::OnChange( OnChange_t && fn )
	{
		SetEventCallback<Ui::ICalendar::OnChange>( m_OnChange, std::move( fn ), MakeThisFunc( __OnChange ) );
		return this;
	}

}
