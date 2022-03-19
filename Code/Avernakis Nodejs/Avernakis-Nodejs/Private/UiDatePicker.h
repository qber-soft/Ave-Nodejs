#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiDatePicker : public UiControlHelper<UiDatePicker, Ui::IDatePicker>
	{
	public:
		AveWrapControl( UiDatePicker );

		~UiDatePicker()
		{
		}

		static PCAChar					GetExportName() { return "UiDatePicker"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnChange_t = JsFuncSafe<void( UiDatePicker* sender )>;

		UiDateTimeFormat				m_Format;

		OnChange_t						m_OnChange;

		void							__OnChange( Ui::IDatePicker& sender );

	private:
		UiDatePicker*					SetRange( const WrapData<TimePoint>& tpEarliest, const WrapData<TimePoint>& tpLatest ) { GetControlTyped().SetRange( tpEarliest, tpLatest ); return this; }
		List<WrapData<TimePoint>>		GetRange() const { List<WrapData<TimePoint>> v( 2 ); GetControlTyped().GetRange( v[0], v[1] ); return std::move( v ); }

		UiDatePicker*					SetDate( const WrapData<TimePoint>& tpDate ) { GetControlTyped().SetDate( tpDate ); return this; }
		WrapData<TimePoint>				GetDate() const { return GetControlTyped().GetDate(); }

		UiDatePicker*					SetDateMark( const WrapData<TimePoint>& tpDate ) { GetControlTyped().SetDateMark( tpDate ); return this; }
		WrapData<TimePoint>				GetDateMark() const { return GetControlTyped().GetDateMark(); }

		UiDatePicker*					SetCultureId( CultureId nCid ) { GetControlTyped().SetCultureId( nCid ); return this; }
		CultureId						GetCultureId() const { return GetControlTyped().GetCultureId(); }

		UiDatePicker*					SetFormat( const WrapData<UiDateTimeFormat>& pFormat );
		WrapData<UiDateTimeFormat>		GetFormat() const;

		UiDatePicker*					SetBorder( U1 b ) { GetControlTyped().SetBorder( b ); return this; }
		U1								GetBorder() const { return GetControlTyped().GetBorder(); }

		UiDatePicker*					Drop() { GetControlTyped().Drop(); return this; }

		UiDatePicker*					OnChange( OnChange_t&& fn ) { m_OnChange = std::move( fn ); return this; }
	};
}
