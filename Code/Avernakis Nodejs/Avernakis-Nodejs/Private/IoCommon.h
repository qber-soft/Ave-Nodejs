#pragma once

#include "WrapObject.h"
#include "WrapData.h"

namespace Nav
{

	enum class IoResourceSourceType
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

	class IoResourceSource
	{
	public:
		IoResourceSourceType	m_Type;
		U32						m_ResourceId;
		WString					m_FilePath;
		WrapData<InMemoryData>	m_InMemory;

		Io::ResourceSource ToResourceSource() const
		{
			if ( IoResourceSourceType::Resource == m_Type )
				return Io::ResourceSource::FromResource( m_ResourceId );
			else if ( IoResourceSourceType::FilePath == m_Type )
				return Io::ResourceSource::FromFilePath( m_FilePath.c_str() );
			else if ( IoResourceSourceType::InMemory == m_Type )
				return Io::ResourceSource::FromMemory( m_InMemory.m_Data.m_Pointer, (U32) m_InMemory.m_Data.m_Length, m_InMemory.m_RowPitch, m_InMemory.m_SlicePitch );
			else
				return Io::ResourceSource::FromMemory( nullptr, 0 );
		}
	};

	NavDefineDataByMember_( IoResourceSource, Type, ResourceId, FilePath, InMemory );


	class IoFileInfo
	{
	public:
		Io::StreamSize_t		m_Size;
		WrapData<TimePoint>		m_TimeCreate;
		WrapData<TimePoint>		m_TimeModify;
		WrapData<TimePoint>		m_TimeAccess;
		Io::FileAttribute_t		m_Attribute;
	};

	NavDefineDataByMember_( IoFileInfo, Size, TimeCreate, TimeModify, TimeAccess, Attribute );

	class IoFileFindItem
	{
	public:
		WrapData<IoFileInfo>	m_Info;
		WString					m_Name;
	};

	NavDefineDataByMember_( IoFileFindItem, Info, Name );

}
