#pragma once

#include "Common.h"

namespace Nav
{

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

}
