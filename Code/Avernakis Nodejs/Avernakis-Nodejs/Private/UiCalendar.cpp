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
		AutoAddMethod( GetRange );

		AutoAddMethod( SetRangeLevel );
		AutoAddMethod( GetRangeLevel );

		AutoAddMethod( SetDate );
		AutoAddMethod( GetDate );

		AutoAddMethod( SetDateMark );
		AutoAddMethod( GetDateMark );

		AutoAddMethod( SetCultureId );
		AutoAddMethod( GetCultureId );

		AutoAddMethod( SetFormat );
		AutoAddMethod( GetFormat );

		AutoAddMethod( OnChange );
	}

	U1 UiCalendar::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::ICalendar::OnChange>() += MakeThisFunc( __OnChange );

		return true;
	}

	void UiCalendar::__OnChange( Ui::ICalendar & sender )
	{
		m_OnChange( this );
	}

	UiCalendar * UiCalendar::SetFormat( const WrapData<UiDateTimeFormat>& pFormat )
	{
		if ( 7 != pFormat.m_DayNameFull.Size() || 7 != pFormat.m_DayNameAbbreviated.Size() || 12 != pFormat.m_MonthNameFull.Size() || 12 != pFormat.m_MonthNameAbbreviated.Size() )
			return this;
		
		m_Format = pFormat;

		CultureInfoDateTime cidt{};
		m_Format.ToCultureInfo( cidt );
		GetControlTyped().SetFormat( cidt );

		return this;
	}

	WrapData<UiDateTimeFormat> UiCalendar::GetFormat() const
	{
		WrapData<UiDateTimeFormat> r{};
		r.FromCultureInfo( GetControlTyped().GetFormat() );
		return r;
	}

}
