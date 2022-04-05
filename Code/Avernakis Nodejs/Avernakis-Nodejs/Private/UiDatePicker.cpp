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
		AutoAddMethod( GetRange );

		AutoAddMethod( SetDate );
		AutoAddMethod( GetDate );

		AutoAddMethod( SetDateMark );
		AutoAddMethod( GetDateMark );

		AutoAddMethod( SetCultureId );
		AutoAddMethod( GetCultureId );

		AutoAddMethod( SetFormat );
		AutoAddMethod( GetFormat );

		AutoAddMethod( SetBorder );
		AutoAddMethod( GetBorder );

		AutoAddMethod( Drop );

		AutoAddMethod( OnChange );
	}

	U1 UiDatePicker::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetEvent<Ui::IDatePicker::OnDateChange>() += MakeThisFunc( __OnChange );

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

}
