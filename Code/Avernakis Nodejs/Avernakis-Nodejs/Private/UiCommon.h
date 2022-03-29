﻿#pragma once

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
	NavDefineDataByMember( R32_Q, x, y, z, w );

	NavDefineDataByMember( R32_4x4, _11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44 );

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

	NavDefineDataByMember_( Ui::DpiSize, Data );

	namespace __Detail
	{
		class UiDpi2
		{
		public:
			WrapData<Ui::DpiSize>	x;
			WrapData<Ui::DpiSize>	y;
		};
	}

	NavDefineDataByMember( __Detail::UiDpi2, x, y );
	NavDefineTransitByMember( Ui::DpiSize_2, __Detail::UiDpi2, x, y );


	namespace __Detail
	{
		class UiDpiMargin
		{
		public:
			WrapData<Ui::DpiSize>	m_Left;
			WrapData<Ui::DpiSize>	m_Top;
			WrapData<Ui::DpiSize>	m_Right;
			WrapData<Ui::DpiSize>	m_Bottom;
		};
	}
	NavDefineDataByMember_( __Detail::UiDpiMargin, Left, Top, Right, Bottom );
	NavDefineTransitByMember_( Ui::S32_DpiMargin, __Detail::UiDpiMargin, Left, Top, Right, Bottom );

	namespace __Detail
	{
		class UiHotkey
		{
		public:
			U16 m_Key;
			U16 m_Modifier;
		};
	}

	NavDefineDataByMember_( __Detail::UiHotkey, Key, Modifier );
	NavDefineTransitByMemberC_( Ui::Hotkey, __Detail::UiHotkey, Key, Modifier );


	enum class UiResourceSourceType
	{
		Resource,
		FilePath,
		InMemory,
	};

	class InMemoryData
	{
	public:
		WrapArray<U8>			m_Data;
		U32						m_RowPitch;
		U32						m_SlicePitch;
	};

	NavDefineDataByMember_( InMemoryData, Data, RowPitch, SlicePitch );

	class UiResourceSource
	{
	public:
		UiResourceSourceType	m_Type;
		U32						m_ResourceId;
		WString					m_FilePath;
		WrapData<InMemoryData>	m_InMemory;

		Io::ResourceSource ToResourceSource() const
		{
			if ( UiResourceSourceType::Resource == m_Type )
				return Io::ResourceSource::FromResource( m_ResourceId );
			else if ( UiResourceSourceType::FilePath == m_Type )
				return Io::ResourceSource::FromFilePath( m_FilePath.c_str() );
			else if ( UiResourceSourceType::InMemory == m_Type )
				return Io::ResourceSource::FromMemory( m_InMemory.m_Data.m_Pointer, (U32) m_InMemory.m_Data.m_Length, m_InMemory.m_RowPitch, m_InMemory.m_SlicePitch );
			else
				return Io::ResourceSource::FromMemory( nullptr, 0 );
		}
	};

	NavDefineDataByMember_( UiResourceSource, Type, ResourceId, FilePath, InMemory );

	NavDefineDataByMember_( Ui::IconSource, ResId, PixelSize );

	class StringKey
	{
	public:
		WString m_StrKey;
		U32 m_IdKey{ 0 };
		U32 m_Offset{ 0 };
		U32 m_Count{ 0 };

		U1 Set( Napi::Value v )
		{
			if ( v.IsNull() || v.IsUndefined() )
				return false;
			if ( v.IsString() )
			{
				m_StrKey = (PCWChar) v.As<Napi::String>().Utf16Value().c_str();
			}
			else if ( v.IsNumber() )
			{
				m_IdKey = v.As<Napi::Number>().Uint32Value();
			}
			else if ( v.IsObject() )
			{
				auto obj = v.As<Napi::Object>();
				auto key = obj.Get( "BaseKey" );
				auto offset = obj.Get( "Offset" );
				auto count = obj.Get( "Count" );
				if ( key.IsNull() || !offset.IsNumber() || !count.IsNumber() )
					return false;
				if ( key.IsString() )
					m_StrKey = (PCWChar) key.As<Napi::String>().Utf16Value().c_str();
				else if ( key.IsNumber() )
					m_IdKey = key.As<Napi::Number>().Uint32Value();
				m_Offset = offset.As<Napi::Number>().Uint32Value();
				m_Count = count.As<Napi::Number>().Uint32Value();
			}
			else
				return false;
			return true;
		}
	};


	class UiDateTimeFormat
	{
	public:
		WString					m_DateSeparator               /**/;
		WString					m_TimeSeparator               /**/;
		List<WString>			m_DayNameFull                 /**/;
		List<WString>			m_DayNameAbbreviated          /**/;
		List<WString>			m_MonthNameFull               /**/;
		List<WString>			m_MonthNameAbbreviated        /**/;
		WString					m_AmDesignator                /**/;
		WString					m_PmDesignator                /**/;
		U32						m_FirstDayOfWeek              /**/;
		WString					m_PatternFullDateTime         /**/; // U
		WString					m_PatternShortDate            /**/; // d
		WString					m_PatternLongDate             /**/; // D
		WString					m_PatternShortTime            /**/; // t
		WString					m_PatternLongTime             /**/; // T
		WString					m_PatternMonthDay             /**/; // M/m
		WString					m_PatternYearMonthAbbreviated /**/; // y
		WString					m_PatternYearMonthFull        /**/; // Y
		WString					m_PatternLongDateShortTime    /**/; // f
		WString					m_PatternLongDateLongTime     /**/; // F
		WString					m_PatternShortDateShortTime   /**/; // g
		WString					m_PatternShortDateLongTime    /**/; // G
		WString					m_PatternSortableDateTime     /**/; // s
		WString					m_PatternRfc1123              /**/; // R/r
		WString					m_PatternUniversalSortable    /**/; // u

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

			for ( S32 i = 0; i < 7; ++i )
			{
				cidt.m_DayNameFull[i] = m_DayNameFull[i].c_str();
				cidt.m_DayNameAbbreviated[i] = m_DayNameAbbreviated[i].c_str();
			}
			for ( S32 i = 0; i < 12; ++i )
			{
				cidt.m_MonthNameFull[i] = m_MonthNameFull[i].c_str();
				cidt.m_MonthNameAbbreviated[i] = m_MonthNameAbbreviated[i].c_str();
			}
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

	NavDefineDataByMember_( UiDateTimeFormat, DateSeparator, TimeSeparator, DayNameFull, DayNameAbbreviated, MonthNameFull, MonthNameAbbreviated, AmDesignator, PmDesignator, FirstDayOfWeek, PatternFullDateTime, PatternShortDate, PatternLongDate, PatternShortTime, PatternLongTime, PatternMonthDay, PatternYearMonthAbbreviated, PatternYearMonthFull, PatternLongDateShortTime, PatternLongDateLongTime, PatternShortDateShortTime, PatternShortDateLongTime, PatternSortableDateTime, PatternRfc1123, PatternUniversalSortable );

}
