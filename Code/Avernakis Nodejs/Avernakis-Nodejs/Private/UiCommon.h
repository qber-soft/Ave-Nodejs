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

	enum class FontResourceType
	{
		Name,
		File,
		ResourceId,
	};

	class UiFontDescription
	{
	public:
		FontResourceType		m_Type;
		List<WString>			m_Name;
		List<WString>			m_File;
		List<U32>				m_ResourceId;
		List<U32>				m_Index;
		R32						m_Size;
		U32						m_Flag;
	};

	class UiFontDescriptionByo2
	{
	public:
		WString					m_String;
		List<Io::AveStream>		m_Stream;
		List<Io::IAveStream*>	m_StreamPointer;
		Byo2::FontDesc			m_FontDesc;

		void FromJs( const WrapData<UiFontDescription>& font, Io::IResourceManager& rm )
		{
			m_String.clear();
			m_Stream.Clear();
			m_StreamPointer.Clear();
			AveZeroObject( m_FontDesc );

			if ( FontResourceType::Name == font.m_Type )
			{
				if ( font.m_Name.IsEmpty() )
					return;
				if ( !font.m_Index.IsEmpty() && font.m_Index.Size() != font.m_Name.Size() )
					return;
				for ( auto& i : font.m_Name )
				{
					if ( AveStr.Find( i.c_str(), AveWide( "/" ) ) )
						return;
					m_String += i + AveWide( "/" );
				}
				m_String.pop_back();
			}
			else if ( FontResourceType::File == font.m_Type )
			{
				if ( font.m_File.IsEmpty() )
					return;
				if ( !font.m_Index.IsEmpty() && font.m_Index.Size() != font.m_File.Size() )
					return;
				for ( auto& i : font.m_Name )
				{
					if ( AveStr.Find( i.c_str(), AveWide( "/" ) ) )
						return;
					auto fs = AveKak.Create<Io::IStreamFile>( i.c_str() );
					if ( !fs )
						return;
					m_StreamPointer.Add( fs );
					m_Stream.Add( std::move( fs ) );
					m_String += WString( AveWide( "a:" ) ) + i + AveWide( "/" );
				}
				m_String.pop_back();
			}
			else if ( FontResourceType::ResourceId == font.m_Type )
			{
				if ( font.m_ResourceId.IsEmpty() )
					return;
				if ( !font.m_Index.IsEmpty() && font.m_Index.Size() != font.m_ResourceId.Size() )
					return;
				for ( auto& i : font.m_ResourceId )
				{
					auto fs = rm.Open( i );
					if ( !fs )
						return;
					m_StreamPointer.Add( fs );
					m_Stream.Add( std::move( fs ) );
					m_String += AveWide( "a/" );
				}
				m_String.pop_back();
			}

			m_FontDesc.m_Res.m_Name = m_String.c_str();
			if ( !m_StreamPointer.IsEmpty() )
				m_FontDesc.m_Res.m_Stream = m_StreamPointer.Data();
			if ( !font.m_Index.IsEmpty() )
				m_FontDesc.m_Res.m_Index = font.m_Index.Data();
			m_FontDesc.m_Size = font.m_Size;
			m_FontDesc.m_Flag = font.m_Flag;
		}
	};

	NavDefineDataByMember_( UiFontDescription, Type, Name, File, ResourceId, Index, Size, Flag );

}
