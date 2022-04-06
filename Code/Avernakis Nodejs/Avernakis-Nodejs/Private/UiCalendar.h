#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiCalendar : public UiControlHelper<UiCalendar, Ui::ICalendar>
	{
	public:
		AveWrapControl( UiCalendar );

		~UiCalendar()
		{
		}

		static PCAChar					GetExportName() { return "UiCalendar"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnChange_t = JsFuncSafe<void( UiCalendar* sender )>;

		DateTimeFormat					m_Format;

		OnChange_t						m_OnChange;

		void							__OnChange( Ui::ICalendar& sender );

	private:
		UiCalendar*						SetRange( const WrapData<TimePoint>& tpEarliest, const WrapData<TimePoint>& tpLatest ) { GetControlTyped().SetRange( tpEarliest, tpLatest ); return this; }
		List<WrapData<TimePoint>>		GetRange() const { List<WrapData<TimePoint>> v( 2 ); GetControlTyped().GetRange( v[0], v[1] ); return std::move( v ); }

		UiCalendar*						SetRangeLevel( Ui::CalendarRangeLevel nLevel ) { GetControlTyped().SetRangeLevel( nLevel ); return this; }
		Ui::CalendarRangeLevel			GetRangeLevel() const { return GetControlTyped().GetRangeLevel(); }

		UiCalendar*						SetDate( const WrapData<TimePoint>& tpDate ) { GetControlTyped().SetDate( tpDate ); return this; }
		WrapData<TimePoint>				GetDate() const { return GetControlTyped().GetDate(); }

		UiCalendar*						SetDateMark( const WrapData<TimePoint>& tpDate ) { GetControlTyped().SetDateMark( tpDate ); return this; }
		WrapData<TimePoint>				GetDateMark() const { return GetControlTyped().GetDateMark(); }

		UiCalendar*						SetCultureId( CultureId nCid ) { GetControlTyped().SetCultureId( nCid ); return this; }
		CultureId						GetCultureId() const { return GetControlTyped().GetCultureId(); }

		UiCalendar*						SetFormat( const WrapData<DateTimeFormat>& pFormat );
		WrapData<DateTimeFormat>		GetFormat() const;

		UiCalendar*						OnChange( OnChange_t&& fn ) { m_OnChange = std::move( fn ); return this; }
	};
}
