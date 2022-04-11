#pragma once

#include "../../../External/Avernakis/Code/Avernakis-AppFeature/Include/AppCore.h"
#include "../../../External/Avernakis/Code/Avernakis-AppFeature/Include/AppFeatureService.h"
#include "../../../External/Avernakis/Code/Avernakis-AppFeature/Include/AppFeatureDpiware.h"
#include "../../../External/Avernakis/Code/Avernakis-AppFeature/Include/AppFeatureLocalStringIni.h"

namespace Nav
{

	class UiApp;
	class IPromiseCall;

	enum class AppLangType
	{
		Text,
		Binary,
	};

	class __App : public AppFeature::AppCore
		< AppFeature::AppService<Sys::IInformation, Io::IFileSystem, Ui::ISysDialog>
		, AppFeature::AppDpiware
		, AppFeature::AppLocalStringIni
		>
	{
		AveSingleton( __App );

		friend class UiApp;

		virtual U1								OnInitializeModule() override;
		virtual U1								OnInitializeDpiware( IInitializeDpiware& p ) const override;
		virtual U1								OnInitializeStringIni( IInitializeDefaultStringIni& init ) override;
		virtual U1								OnInitialize() override;

		__App();
		~__App();

		UiApp*									m_App{ nullptr };
		AppLangType								m_LangType{ AppLangType::Text };
		U1										m_LangSetText{ false };
		U1										m_LangSetBinary{ false };

		IInitializeDpiware mutable*				m_InitDpiware{ nullptr };
		IInitializeDefaultStringIni mutable*	m_InitStringIni{ nullptr };
		List<U32>								m_IconSizeList{ 16, 32 };

	public:
		AveInline UiApp*						operator -> () const { return m_App; }

		AveInline AppLangType					GetLangType() const { return m_LangType; }
		AveInline U1							IsLangSet() const { return AppLangType::Text == m_LangType && m_LangSetText || AppLangType::Binary == m_LangType && m_LangSetBinary; }

		U1										CreateUiApp( UiApp* app );
		void									DestroyUiApp();

		void									SetDpiwareSizeList( Ui::IIconManager & im );

		void									ExecuteInUiThread( Func<void()>&& f );
		void									ExecuteInUiThread( IPromiseCall* p );
		void									ExecuteInJsThread( Func<void()>&& f, U1 bWait, U1 bUiThread = true );

#	if 1 == AveDebug
		AveInline void WaitForDebugger()
		{
			GetSysInfo().DebugWaitDebugger( 10000 );
		}
#	endif
	};

	using App = Singleton<__App>;

}

namespace Ave
{

	template<>
	class Singleton<Nav::__App>
	{
	public:
		static Nav::__App& GetSingleton()
		{
			static Nav::__App app;
			return app;
		}
	};

}

namespace Nav
{

#	define __AppCore__ ::Nav::App
#	include "../../../External/Avernakis/Code/Avernakis-AppFeature/Include/AppFeatureLocalStringIniMacro.h"

}
