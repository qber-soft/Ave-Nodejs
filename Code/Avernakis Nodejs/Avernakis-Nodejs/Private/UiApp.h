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

		U1									Ctor( const CallbackInfo& ci );
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		class ExecuteBlocker
		{
		public:
			Sys::RwLock						m_Lock;
			List<U8>						m_Blocker;
			List<S32>						m_Free;
			U32								m_FreeCount;

			U1 Create()
			{
				if ( !m_Lock.Create() )
					return false;
				m_Blocker.Resize( 32 );
				m_Free.Resize( 32 );
				m_FreeCount = 32;
				for ( U32 i = 0; i < m_FreeCount; ++i )
					m_Free[i] = i;
				return true;
			}

			S32 Acquire()
			{
				Sys::RwLockScoped __Lock( *m_Lock );
				if ( 0 == m_FreeCount )
				{
					m_FreeCount = 32;
					auto nCount = (U32) m_Free.Size();
					m_Blocker.Resize( nCount + m_FreeCount );
					m_Free.Resize( nCount + m_FreeCount );
					for ( U32 i = 0; i < m_FreeCount; ++i )
						m_Free[i] = nCount + i;
				}
				auto n = m_Free[--m_FreeCount];
				m_Blocker[n] = 0;
				return n;
			}

			U1 Release( S32 n )
			{
				Sys::RwLockScoped __Lock( *m_Lock );
				if ( 1 == m_Blocker[n] )
				{
					m_Free[m_FreeCount++] = n;
					return true;
				}
				return false;
			}

			void Signal( S32 n )
			{
				if ( -1 != n )
				{
					Sys::RwLockScoped __Lock( *m_Lock );
					m_Blocker[n] = 1;
				}
			}
		};

		class Work
		{
		public:
			Func<void()>					m_Work;
			S32								m_Blocker;
			IPromiseCall*					m_Promise;
			U1								m_Canceled;
		};

	private:
		using Callback_t = JsFuncSafe<void( S32 )>;

		ApplicationScope					m_Object;

		Sys::Thread							m_Thread;
		Sys::Event							m_InitFinishEvent;
		List<WChar>							m_DefaultStringData;
		List<PCWChar[2]>					m_DefaultString;

		Callback_t							m_OnExit;

		Sys::RwLock							m_UiExecuteLock;
		Sys::Event							m_UiExecuteFinish;
		Queue<Work>							m_UiExecuteFunc;
		std::atomic<S32>					m_UiExecuteBlock{ 0 };
		U1									m_UiExecuteCanceled{ false };

		napi_threadsafe_function			m_JsFunc{ nullptr };
		Sys::RwLock							m_JsExecuteLock;
		Sys::Event							m_JsExecuteFinish;
		Queue<Work>							m_JsExecuteFunc;
		std::atomic<S32>					m_JsExecute{ 0 };

		ExecuteBlocker						m_Blocker;

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
		void								OnAppWakeup( Ave::IApplication& pApplication, const void* pContext );
		S32									OnAppRunStart( Ave::IApplication& pApplication );
		void								OnAppRunEnd( Ave::IApplication& pApplication, S32 nExitCode );

	private:
		void								__UiThread();

		static void							__JsFuncFinalize( napi_env env, void* finalize_data, void* finalize_hint );
		static void							__JsFuncCall( napi_env env, napi_value js_callback, void* context, void* data );

		U1									__UiExecuteQueued( U1 bResetCanceled );
		void								__JsExecuteQueued( U1 bReleaseCounter );

		void								__ExecuteInJsThread( IPromiseCall* p );

	public:
		void								ExecuteInUiThread( Func<void()>&& f );
		void								ExecuteInUiThread( IPromiseCall* p );
		void								ExecuteInJsThread( Func<void()>&& f, U1 bWait, U1 bUiThread );

	};
}
