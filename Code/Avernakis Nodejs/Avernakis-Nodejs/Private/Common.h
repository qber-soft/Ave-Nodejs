#pragma once

#include "WrapObject.h"
#include "WrapData.h"

namespace Nav
{

	// Define vectors, all permutations of $*_# where
	//  $ ∈ (U, S)
	//  * ∈ (8, 16, 32, 64)
	//  # ∈ (2, 3, 4)
	// and R*_# where
	//  * ∈ (32, 64)
	//  # ∈ (2, 3, 4)

#define ___DefineData($type) \
	NavDefineDataByMember( $type##_2, x, y ) \
	NavDefineDataByMember( $type##_3, x, y, z ) \
	NavDefineDataByMember( $type##_4, x, y, z, w )

#	define __DefineData($bit) ___DefineData( U##$bit ); ___DefineData( S##$bit )
	__DefineData( 8 );
	__DefineData( 16 );
	__DefineData( 32 );
	__DefineData( 64 );
#	undef __DefineData

#	define __DefineData($bit) ___DefineData( R##$bit )
	__DefineData( 32 );
	__DefineData( 64 );
#	undef __DefineData

#undef ___DefineData


	NavDefineDataByMember( S32_R, x, y, w, h );
	NavDefineDataByMember( R32_R, x, y, w, h );
	NavDefineDataByMember( R32_Q, x, y, z, w );

	NavDefineDataByMember( R32_4x4, _11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44 );

	template<>
	class WrapDataDefine<R32_3x2> : WrapDataBase<R32_3x4>
	{
	public:
		static void DefineData()
		{
			AddField( "_11", &R32_3x4::d, 0 );
			AddField( "_12", &R32_3x4::d, 1 );
			AddField( "_21", &R32_3x4::d, 2 );
			AddField( "_22", &R32_3x4::d, 3 );
			AddField( "_31", &R32_3x4::d, 4 );
			AddField( "_32", &R32_3x4::d, 5 );
		}
	};

	template<>
	class WrapDataDefine<R32_3x4> : WrapDataBase<R32_3x4>
	{
	public:
		static void DefineData()
		{
			AddField( "_11", &R32_3x4::d, 0 );
			AddField( "_12", &R32_3x4::d, 1 );
			AddField( "_13", &R32_3x4::d, 2 );
			AddField( "_14", &R32_3x4::d, 3 );
			AddField( "_21", &R32_3x4::d, 4 );
			AddField( "_22", &R32_3x4::d, 5 );
			AddField( "_23", &R32_3x4::d, 6 );
			AddField( "_24", &R32_3x4::d, 7 );
			AddField( "_31", &R32_3x4::d, 8 );
			AddField( "_32", &R32_3x4::d, 9 );
			AddField( "_33", &R32_3x4::d, 10 );
			AddField( "_34", &R32_3x4::d, 11 );
		}
	};

	namespace __Detail
	{
		class UiR32_B
		{
		public:
			WrapData<R32_3> m_Min;
			WrapData<R32_3> m_Max;
		};
	}

	NavDefineDataByMember_( __Detail::UiR32_B, Min, Max );
	NavDefineTransitByMember_( R32_B, __Detail::UiR32_B, Min, Max );

	namespace __Detail
	{
		class UiR32_F
		{
		public:
			WrapData<R32_3>	m_Origin;
			WrapData<R32_Q>	m_Orient;
			R32				m_SlopeL;
			R32				m_SlopeR;
			R32				m_SlopeT;
			R32				m_SlopeB;
			R32				m_Near;
			R32				m_Far;
		};
	}

	NavDefineDataByMember_( __Detail::UiR32_F, Origin, Orient, SlopeL, SlopeR, SlopeT, SlopeB, Near, Far );
	NavDefineTransitByMember_( R32_F, __Detail::UiR32_F, Origin, Orient, SlopeL, SlopeR, SlopeT, SlopeB, Near, Far );

	namespace __Detail
	{
		class JsTimePoint
		{
		public:
			R64				m_Tick;
		};
	}

	template<>
	class WrapDataTransit<TimePoint> : public WrapDataTransitHelper<TimePoint, __Detail::JsTimePoint>
	{
	public:
		static void Transit( TimePoint& d, const __Detail::JsTimePoint& s )
		{
			d.m_Tick = S64( s.m_Tick ) * 1000;
		}

		static void Transit( __Detail::JsTimePoint& d, const TimePoint& s )
		{
			d.m_Tick = R64( s.m_Tick / 1000 );
		}
	};

	NavDefineDataByMember_( __Detail::JsTimePoint, Tick );
	//NavDefineDataByMember_( TimePoint, Tick );

	class DateTimeFormat
	{
	public:
		WString						m_DateSeparator               /**/;
		WString						m_TimeSeparator               /**/;
		List<WString>				m_DayNameFull                 /**/;
		List<WString>				m_DayNameAbbreviated          /**/;
		List<WString>				m_MonthNameFull               /**/;
		List<WString>				m_MonthNameAbbreviated        /**/;
		WString						m_AmDesignator                /**/;
		WString						m_PmDesignator                /**/;
		U32							m_FirstDayOfWeek              /**/;
		WString						m_PatternFullDateTime         /**/; // U
		WString						m_PatternShortDate            /**/; // d
		WString						m_PatternLongDate             /**/; // D
		WString						m_PatternShortTime            /**/; // t
		WString						m_PatternLongTime             /**/; // T
		WString						m_PatternMonthDay             /**/; // M/m
		WString						m_PatternYearMonthAbbreviated /**/; // y
		WString						m_PatternYearMonthFull        /**/; // Y
		WString						m_PatternLongDateShortTime    /**/; // f
		WString						m_PatternLongDateLongTime     /**/; // F
		WString						m_PatternShortDateShortTime   /**/; // g
		WString						m_PatternShortDateLongTime    /**/; // G
		WString						m_PatternSortableDateTime     /**/; // s
		WString						m_PatternRfc1123              /**/; // R/r
		WString						m_PatternUniversalSortable    /**/; // u

		void ToCultureInfo( CultureInfoDateTime& cidt ) const
		{
			cidt.m_DateSeparator               /**/ = m_DateSeparator               /**/.c_str();
			cidt.m_TimeSeparator               /**/ = m_TimeSeparator               /**/.c_str();
			cidt.m_PatternFullDateTime         /**/ = m_PatternFullDateTime         /**/.c_str();
			cidt.m_PatternShortDate            /**/ = m_PatternShortDate            /**/.c_str();
			cidt.m_PatternLongDate             /**/ = m_PatternLongDate             /**/.c_str();
			cidt.m_PatternShortTime            /**/ = m_PatternShortTime            /**/.c_str();
			cidt.m_PatternLongTime             /**/ = m_PatternLongTime             /**/.c_str();
			cidt.m_PatternMonthDay             /**/ = m_PatternMonthDay             /**/.c_str();
			cidt.m_PatternYearMonthAbbreviated /**/ = m_PatternYearMonthAbbreviated /**/.c_str();
			cidt.m_PatternYearMonthFull        /**/ = m_PatternYearMonthFull        /**/.c_str();
			cidt.m_PatternLongDateShortTime    /**/ = m_PatternLongDateShortTime    /**/.c_str();
			cidt.m_PatternLongDateLongTime     /**/ = m_PatternLongDateLongTime     /**/.c_str();
			cidt.m_PatternShortDateShortTime   /**/ = m_PatternShortDateShortTime   /**/.c_str();
			cidt.m_PatternShortDateLongTime    /**/ = m_PatternShortDateLongTime    /**/.c_str();
			cidt.m_PatternSortableDateTime     /**/ = m_PatternSortableDateTime     /**/.c_str();
			cidt.m_PatternRfc1123              /**/ = m_PatternRfc1123              /**/.c_str();
			cidt.m_PatternUniversalSortable    /**/ = m_PatternUniversalSortable    /**/.c_str();

			cidt.m_AmPmDesignator[0] = m_AmDesignator.c_str();
			cidt.m_AmPmDesignator[1] = m_PmDesignator.c_str();
			cidt.m_FirstDayOfWeek = (DayOfWeek) m_FirstDayOfWeek;

			for ( S32 i = 0; i < Math::Min( 7, (S32) m_DayNameFull.Size() ); ++i )
				cidt.m_DayNameFull[i] = m_DayNameFull[i].c_str();
			for ( S32 i = 0; i < Math::Min( 7, (S32) m_DayNameAbbreviated.Size() ); ++i )
				cidt.m_DayNameAbbreviated[i] = m_DayNameAbbreviated[i].c_str();
			for ( S32 i = 0; i < Math::Min( 12, (S32) m_MonthNameFull.Size() ); ++i )
				cidt.m_MonthNameFull[i] = m_MonthNameFull[i].c_str();
			for ( S32 i = 0; i < Math::Min( 12, (S32) m_MonthNameAbbreviated.Size() ); ++i )
				cidt.m_MonthNameAbbreviated[i] = m_MonthNameAbbreviated[i].c_str();
		}

		void FromCultureInfo( const CultureInfoDateTime& cidt )
		{
			m_DateSeparator               /**/ = cidt.m_DateSeparator               /**/;
			m_TimeSeparator               /**/ = cidt.m_TimeSeparator               /**/;
			m_PatternFullDateTime         /**/ = cidt.m_PatternFullDateTime         /**/;
			m_PatternShortDate            /**/ = cidt.m_PatternShortDate            /**/;
			m_PatternLongDate             /**/ = cidt.m_PatternLongDate             /**/;
			m_PatternShortTime            /**/ = cidt.m_PatternShortTime            /**/;
			m_PatternLongTime             /**/ = cidt.m_PatternLongTime             /**/;
			m_PatternMonthDay             /**/ = cidt.m_PatternMonthDay             /**/;
			m_PatternYearMonthAbbreviated /**/ = cidt.m_PatternYearMonthAbbreviated /**/;
			m_PatternYearMonthFull        /**/ = cidt.m_PatternYearMonthFull        /**/;
			m_PatternLongDateShortTime    /**/ = cidt.m_PatternLongDateShortTime    /**/;
			m_PatternLongDateLongTime     /**/ = cidt.m_PatternLongDateLongTime     /**/;
			m_PatternShortDateShortTime   /**/ = cidt.m_PatternShortDateShortTime   /**/;
			m_PatternShortDateLongTime    /**/ = cidt.m_PatternShortDateLongTime    /**/;
			m_PatternSortableDateTime     /**/ = cidt.m_PatternSortableDateTime     /**/;
			m_PatternRfc1123              /**/ = cidt.m_PatternRfc1123              /**/;
			m_PatternUniversalSortable    /**/ = cidt.m_PatternUniversalSortable    /**/;

			m_AmDesignator = cidt.m_AmPmDesignator[0];
			m_PmDesignator = cidt.m_AmPmDesignator[1];
			m_FirstDayOfWeek = (U32) m_FirstDayOfWeek;

			m_DayNameFull.Resize( 7 );
			m_DayNameAbbreviated.Resize( 7 );
			m_MonthNameFull.Resize( 12 );
			m_MonthNameAbbreviated.Resize( 12 );
			for ( S32 i = 0; i < 7; ++i )
			{
				m_DayNameFull[i] = cidt.m_DayNameFull[i];
				m_DayNameAbbreviated[i] = cidt.m_DayNameAbbreviated[i];
			}
			for ( S32 i = 0; i < 12; ++i )
			{
				m_MonthNameFull[i] = cidt.m_MonthNameFull[i];
				m_MonthNameAbbreviated[i] = cidt.m_MonthNameAbbreviated[i];
			}
		}
	};

	NavDefineDataByMember_( DateTimeFormat, DateSeparator, TimeSeparator, DayNameFull, DayNameAbbreviated, MonthNameFull, MonthNameAbbreviated, AmDesignator, PmDesignator, FirstDayOfWeek, PatternFullDateTime, PatternShortDate, PatternLongDate, PatternShortTime, PatternLongTime, PatternMonthDay, PatternYearMonthAbbreviated, PatternYearMonthFull, PatternLongDateShortTime, PatternLongDateLongTime, PatternShortDateShortTime, PatternShortDateLongTime, PatternSortableDateTime, PatternRfc1123, PatternUniversalSortable );

	class NumberFormatInfo
	{
	public:
		WString						m_Symbol;
		WString						m_DecimalSeparator;
		U32							m_DecimalDigits;
		WString						m_GroupSeparator;
		List<U32>					m_GroupSize; // Size() == 4
		U32							m_PositivePattern;
		U32							m_NegativePattern;

		void FromCultureInfo( const CultureInfoNumberInfo& ci )
		{
			if ( ci.m_Symbol )
				m_Symbol = ci.m_Symbol;
			else
				m_Symbol.Clear();
			m_DecimalSeparator.Clear();
			m_DecimalSeparator += ci.m_DecimalSeparator;
			m_DecimalDigits = ci.m_DecimalDigits;
			m_GroupSeparator.Clear();
			m_GroupSeparator += ci.m_GroupSeparator;
			m_GroupSize.Resize( CountOf( ci.m_GroupSize ) );
			AveCopyMemory( m_GroupSize.Data(), ci.m_GroupSize, sizeof( ci.m_GroupSize ) );
			m_PositivePattern = ci.m_PositivePattern;
			m_NegativePattern = ci.m_NegativePattern;
		}
	};

	NavDefineDataByMember_( NumberFormatInfo, Symbol, DecimalSeparator, DecimalDigits, GroupSeparator, GroupSize, PositivePattern, NegativePattern );

	class NumberFormat
	{
	public:
		WrapData<NumberFormatInfo>	m_Currency;
		WrapData<NumberFormatInfo>	m_Number;
		WrapData<NumberFormatInfo>	m_Percent;

		void FromCultureInfo( const CultureInfoNumber& ci )
		{
			m_Currency.FromCultureInfo( ci.m_Currency );
			m_Number.FromCultureInfo( ci.m_Number );
			m_Percent.FromCultureInfo( ci.m_Percent );
		}
	};

	NavDefineDataByMember_( NumberFormat, Currency, Number, Percent );

	class TextFormat
	{
	public:
		U1							m_IsRtl;
		StringCp					m_AnsiCp;
		StringCp					m_MacCp;
		StringCp					m_OemCp;

		void FromCultureInfo( const CultureInfoText& ci )
		{
			m_IsRtl = ci.m_IsRtl;
			m_AnsiCp = ci.m_AnsiCp;
			m_MacCp = ci.m_MacCp;
			m_OemCp = ci.m_OemCp;
		}
	};

	NavDefineDataByMember_( TextFormat, IsRtl, AnsiCp, MacCp, OemCp );

	class NavCultureInfo
	{
	public:
		CultureId					m_Id          /**/;
		LanguageId					m_Lid         /**/;
		RegionId					m_Rid         /**/;
		S32							m_Lcid        /**/;
		WString						m_NameEnglish /**/;
		WString						m_NameNative  /**/;
		WrapData<DateTimeFormat>	m_DateTime    /**/;
		WrapData<NumberFormat>		m_Number      /**/;
		WrapData<TextFormat>		m_Text        /**/;

		void FromCultureInfo( const CultureInfo& ci )
		{
			m_Id = ci.m_Id;
			m_Lid = ci.m_Lid;
			m_Rid = ci.m_Rid;
			m_Lcid = ci.m_Lcid;
			m_NameEnglish = ci.m_NameEnglish;
			m_NameNative = ci.m_NameNative;
			m_DateTime.FromCultureInfo( ci.m_DateTime );
			m_Number.FromCultureInfo( ci.m_Number );
			m_Text.FromCultureInfo( ci.m_Text );
		}
	};

	NavDefineDataByMember_( NavCultureInfo, Id, Lid, Rid, Lcid, NameEnglish, NameNative, DateTime, Number, Text );

}
