#pragma once

#include "UiCommon.h"

namespace Nav
{

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

		virtual Ui::ITheme&		GetTheme() = 0;
		virtual Ui::Theme		CloneTheme() = 0;

	protected:
		static void __DefineObject();
	};

}
