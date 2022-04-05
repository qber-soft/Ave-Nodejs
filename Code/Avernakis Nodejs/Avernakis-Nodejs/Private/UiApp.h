#pragma once

#include "UiCommon.h"

namespace Nav
{

	class AppLanguageItem
	{
	public:
		WString		m_Path;
		CultureId	m_Cid;
		WString		m_NameEnglish;
		WString		m_NameNative;
	};

	NavDefineDataByMember_( AppLanguageItem, Path, Cid, NameEnglish, NameNative );

	class UiWindow;

	class UiApp : public WrapObject<UiApp, void()>
	{
	public:
		UiApp( const Napi::CallbackInfo& cb );
		~UiApp();

		static PCAChar						GetExportName() { return "UiApp"; }
		static void							DefineObject();

		U1									Ctor();
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		using Callback_t = JsFuncSafe<void( S32 )>;

		ApplicationScope					m_Object;

		Sys::Thread							m_Thread;
		Sys::Event							m_InitFinishEvent;
		List<WChar>							m_DefaultStringData;
		List<PCWChar[2]>					m_DefaultString;

		Sys::RwLock							m_ExecuteLock;
		Queue<Func<void()>>					m_Execute;
		List<Func<void()>>					m_ExecuteBuffer;
		Sys::Event							m_ExecuteFinishEvent;

		Callback_t							m_OnExit;

		std::atomic<U32>					m_BlockCall{ 0 };
		Sys::IEvent*						m_BlockEvent{ nullptr };
		U1									m_BlockExecuteInUi{ false };

	private:
		void								__UiThread();
		void								__ExecuteQueued();

		void								OnAppWakeup( Ave::IApplication& pApplication, const void* pContext );

	private:
		U1									ResAddPackageIndex( PCWChar szFile, PCWChar szRoot );
		U1									ResAddPackage( PCWChar szFile );
		UiApp*								ResSetIconSizeList( const List<U32>& v );

		UiApp*								LangSetType( AppLangType nType );
		UiApp*								LangSetFileRoot( PCWChar szFolder, PCWChar szExt );
		UiApp*								LangSetDefaultString( CultureId cid, Napi::Value v );
		UiApp*								LangRefresh();
		List<WrapData<AppLanguageItem>>		LangGet() const;
		void*								LangCreateMenu( UiWindow* window, U1 bIncludeExportMenuItem ) const;
		void								LangExport( UiWindow* window ) const;
		UiApp*								LangSetCurrent( CultureId cid );
		CultureId							LangGetCurrent() const;
		WString								LangGetString( Napi::Value key );
		Napi::Value							LangGetStringTable( const CallbackInfo& ci );

		void								OnExit( Callback_t&& fn ) { m_OnExit = std::move( fn ); }

	public:
		void								ExecuteInUiThread( Func<void()>&& f, U1 bWait );
		void								BlockCallEnter();
		void								BlockCallLeave( Sys::IEvent* pEvent );
	};
}
