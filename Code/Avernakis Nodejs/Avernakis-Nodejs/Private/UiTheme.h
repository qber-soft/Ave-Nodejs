#pragma once

#include "UiCommon.h"

namespace Nav
{

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

	NavDefineDataByMember_( UiFontDescription, Type, Name, File, ResourceId, Index, Size, Flag );

	class UiThemeInfection
	{
	public:
		U1							m_InfectionSpread;
		WrapData<Ui::DpiSize>		m_InfectionRadius;
		R32							m_InfectionOpacity;
		R32							m_InfectionActiveRatio;
	};

	NavDefineDataByMember_( UiThemeInfection, InfectionSpread, InfectionRadius, InfectionOpacity, InfectionActiveRatio );

	class UiTheme
	{
	protected:
		UiTheme() {}
		~UiTheme() {}

	public:
		virtual Napi::Value		GetObjectValue( Napi::Env env ) = 0;

		virtual Ui::Theme		CloneTheme() = 0;

	protected:
		static void __DefineObject();
	};

}
