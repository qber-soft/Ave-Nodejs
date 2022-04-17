#pragma once

#include "WrapBase.h"
#include "App.h"

//----------------------------------------------------------------------------------------------------
// Object Factory
//----------------------------------------------------------------------------------------------------
namespace Nav
{
	namespace __Detail
	{
		class IObjectFactoryHost
		{
		protected:
			IObjectFactoryHost() {}
			~IObjectFactoryHost() {}

		public:
			virtual Napi::FunctionReference*	AllocateFuncRef( Napi::Env env ) = 0;
			virtual void						DeallocateFuncRef() = 0;
		};
	}

	using ObjectFactoryRegister_t = void(*)(Napi::Env, Napi::Object, __Detail::IObjectFactoryHost&);

	class IObjectFactory
	{
	protected:
		IObjectFactory() {}
		~IObjectFactory() {}

	public:
		virtual void Register( ObjectFactoryRegister_t p ) = 0;
		virtual void ExportJsObject( Napi::Env env, Napi::Object exports ) = 0;
	};

	namespace __Detail
	{
		class __ObjectFactory : public IObjectFactory, IObjectFactoryHost
		{
			List<ObjectFactoryRegister_t> m_Object;
			List<UniPtr<Napi::FunctionReference>> m_FuncRef;
			U1 m_Set{ false };

			static void __InstanceDataFinalize( Napi::Env env, IObjectFactoryHost* p )
			{
				p->DeallocateFuncRef();
			}

			virtual void Register( ObjectFactoryRegister_t p ) override
			{
				m_Object.Add( p );
			}

			virtual void ExportJsObject( Napi::Env env, Napi::Object exports ) override
			{
				for ( auto i : m_Object )
					(*i)(env, exports, *this);
			}

			virtual Napi::FunctionReference* AllocateFuncRef( Napi::Env env ) override
			{
				if ( !m_Set )
				{
					m_Set = true;
					env.SetInstanceData<IObjectFactoryHost, __InstanceDataFinalize>( this );
				}
				return m_FuncRef.Add( new Napi::FunctionReference ).Last().GetObject();
			}

			virtual void DeallocateFuncRef() override
			{
				m_FuncRef.Clear();
			}
		};
	}
}

namespace Ave
{
	template<>
	class Singleton<Nav::IObjectFactory>
	{
	public:
		static Nav::IObjectFactory& GetSingleton()
		{
			static Nav::__Detail::__ObjectFactory fac;
			return fac;
		}
	};
}

namespace Nav
{
	using ObjectFactory = Singleton<IObjectFactory>;

	template<class TObject>
	class ObjectRegister
	{
	public:
		AveInline ObjectRegister() { ObjectFactory::GetSingleton().Register( TObject::ExportJsObject ); }
	};
}



//----------------------------------------------------------------------------------------------------
// Wrap Object
//----------------------------------------------------------------------------------------------------

namespace Nav
{

	class WrapObjectGeneric;
	class WrapObjectUi;
	class WrapObjectMix;
	class WrapObjectPromise;

	enum class MixCallStage
	{
		PreUi,
		InUi,
		PostUi,
	};

	class MixCallContext;

	namespace __Detail
	{
		class __MixCall
		{
		protected:
			__MixCall() {}

		protected:
			AveInline void __NextStage( MixCallContext& cc );
		};
	}

	class MixCallContext : public CallbackInfo
	{
		friend class __Detail::__MixCall;

	public:
		MixCallContext( const Napi::CallbackInfo& ci ) : CallbackInfo( ci ) {}

	private:
		MixCallStage	m_Stage{ MixCallStage::PreUi };
		mutable void*	m_UserContext{ nullptr };

	public:
		MixCallStage	GetStage() const { return m_Stage; }
		void			SetUserContext( void* p ) const { m_UserContext = p; }
		void*			GetUserContext() const { return m_UserContext; }
	};

	class IPromiseCall
	{
	protected:
		IPromiseCall() {}
		~IPromiseCall() {}

	public:
		virtual void	Call() = 0;
		virtual void	Resolve() = 0;
	};

	namespace __Detail
	{
		AveInline void __MixCall::__NextStage( MixCallContext& cc )
		{
			if ( MixCallStage::PreUi == cc.m_Stage )
				cc.m_Stage = MixCallStage::InUi;
			else if ( MixCallStage::InUi == cc.m_Stage )
				cc.m_Stage = MixCallStage::PostUi;
		}

		template<class T, class TObj, class TRet, class... TArg>
		class __PromiseCall : public CallbackInfo, public IPromiseCall, public AllocObject<>
		{
		public:
			__PromiseCall( T* p, TObj* po, TRet( TObj::* pf )(TArg...), const Napi::CallbackInfo& ci ) : CallbackInfo( ci ), m_Owner( p ), m_Object( po ), m_Func( pf ), m_Promise( Napi::Promise::Deferred::New( ci.Env() ) )
			{
				if ( !m_Object )
					m_Object = (TObj*) this;
				__PrepareArg( ci, (__Detail::__BuildIndex<sizeof...(TArg)>*) nullptr );
			}

		protected:
			T*								m_Owner;
			TObj*							m_Object;
			TRet( TObj::*					m_Func )(TArg...);
			Napi::Promise::Deferred			m_Promise;
			__Detail::__ArgList<TArg...>	m_Arg{};

		protected:
			template<USize... N>
			void __PrepareArg( const Napi::CallbackInfo& ci, __Detail::__Index<N...>* )
			{
				(__Detail::__ConvertType<TArg>::ToCpp( &m_Arg.__ArgData<TArg, N>::GetArg(), ci[N] ), ...);
			}

			template<USize... N>
			TRet __Call( __Detail::__Index<N...>* )
			{
				return (m_Object->*m_Func)(std::forward<TArg>( m_Arg.__ArgData<TArg, N>::GetArg() )...);
			}

		public:
			virtual void					OnPrepare( const CallbackInfo& ci ) {}

			__Detail::__ArgList<TArg...>&	GetArg() { return m_Arg; }
			Napi::Promise					GetPromise() { return m_Promise.Promise(); }
		};
	}

	template<class, class, class>
	class PromiseCall;

	template<class T, class TObj, class TRet, class... TArg>
	class PromiseCall<T, TObj, TRet( TArg... )> : public __Detail::__PromiseCall<T, TObj, TRet, TArg...>
	{
	public:
		using __Detail::__PromiseCall<T, TObj, TRet, TArg...>::__PromiseCall;

	private:
		virtual void Call() override
		{
			m_Ret = this->__Call( (__Detail::__BuildIndex<sizeof...(TArg)>*) nullptr );
		}

		virtual void Resolve() override
		{
			this->m_Promise.Resolve( __Detail::__ConvertType<TRet>::ToJs( this->m_Promise.Env(), &m_Ret ) );
			delete this;
		}

	private:
		TRet							m_Ret{};
	};

	template<class T, class TObj, class... TArg>
	class PromiseCall<T, TObj, void( TArg... )> : public __Detail::__PromiseCall<T, TObj, void, TArg...>
	{
	public:
		using __Detail::__PromiseCall<T, TObj, void, TArg...>::__PromiseCall;

	private:
		virtual void Call() override
		{
			this->__Call( (__Detail::__BuildIndex<sizeof...(TArg)>*) nullptr );
		}

		virtual void Resolve() override
		{
			this->m_Promise.Resolve( this->m_Promise.Env().Undefined() );
			delete this;
		}
	};

	namespace __Detail
	{

		template<class T, class TType>
		class __WrapObject;

		template<class T>
		class __WrapObject<T, WrapObjectGeneric>
		{
		protected:
			template<class TRet, class... TArg, USize... N>
			AveInline TRet __Call( const Napi::CallbackInfo& cb, TRet( T::*p )(TArg...), __Detail::__Index<N...>* )
			{
				__Detail::__ArgList<TArg...> arg{};
				(__Detail::__ConvertType<TArg>::ToCpp( &arg.__ArgData<TArg, N>::GetArg(), cb[N] ), ...);
				return (((T&) *this).*p)(std::forward<TArg>( arg.__ArgData<TArg, N>::GetArg() )...);
			}

			template<class TRet, class... TArg>
			AveInline TRet __Call( const Napi::CallbackInfo& cb, TRet( T::*p )(TArg...) )
			{
				return __Call( cb, p, (__Detail::__BuildIndex<sizeof...(TArg)>*) nullptr );
			}

			template<class TRet, class... TArg, USize... N>
			AveInline TRet __CallCi( const Napi::CallbackInfo& cb, TRet( T::*p )(const CallbackInfo&, TArg...), __Detail::__Index<N...>* )
			{
				__Detail::__ArgList<TArg...> arg{};
				(__Detail::__ConvertType<TArg>::ToCpp( &arg.__ArgData<TArg, N>::GetArg(), cb[N] ), ...);
				return (((T&) *this).*p)(cb, std::forward<TArg>( arg.__ArgData<TArg, N>::GetArg() )...);
			}

			template<class TRet, class... TArg>
			AveInline TRet __CallCi( const Napi::CallbackInfo& cb, TRet( T::*p )(const CallbackInfo&, TArg...) )
			{
				return __CallCi( cb, p, (__Detail::__BuildIndex<sizeof...(TArg)>*) nullptr );
			}

		};

		template<class T>
		class __WrapObject<T, WrapObjectUi>
		{
		protected:
			template<class TRet, class... TArg, USize... N>
			AveInline TRet __Call( const Napi::CallbackInfo& cb, TRet( T::*p )(TArg...), __Detail::__Index<N...>* )
			{
				__Detail::__ArgList<TArg...> arg{};
				(__Detail::__ConvertType<TArg>::ToCpp( &arg.__ArgData<TArg, N>::GetArg(), cb[N] ), ...);

				TRet r{};
				App::GetSingleton().ExecuteInUiThread( [&r, &arg, this, p]
				{
					r = (((T&) *this).*p)(std::forward<TArg>( arg.__ArgData<TArg, N>::GetArg() )...);
				} );
				return std::move( r );
			}

			template<class... TArg, USize... N>
			AveInline void __Call( const Napi::CallbackInfo& cb, void(T::*p)(TArg...), __Detail::__Index<N...>* )
			{
				__Detail::__ArgList<TArg...> arg{};
				(__Detail::__ConvertType<TArg>::ToCpp( &arg.__ArgData<TArg, N>::GetArg(), cb[N] ), ...);

				App::GetSingleton().ExecuteInUiThread( [&arg, this, p]
				{
					(((T&) *this).*p)(std::forward<TArg>( arg.__ArgData<TArg, N>::GetArg() )...);
				} );
			}

			template<class TRet, class... TArg>
			AveInline TRet __Call( const Napi::CallbackInfo& cb, TRet( T::*p )(TArg...) )
			{
				return __Call( cb, p, (__Detail::__BuildIndex<sizeof...(TArg)>*) nullptr );
			}

			template<class TRet, class... TArg, USize... N>
			AveInline TRet __CallCi( const Napi::CallbackInfo& cb, TRet( T::*p )(const CallbackInfo&, TArg...), __Detail::__Index<N...>* )
			{
				__Detail::__ArgList<TArg...> arg{};
				(__Detail::__ConvertType<TArg>::ToCpp( &arg.__ArgData<TArg, N>::GetArg(), cb[N] ), ...);

				TRet r{};
				App::GetSingleton().ExecuteInUiThread( [&r, &arg, &cb, this, p]
				{
					r = (((T&) *this).*p)(cb, std::forward<TArg>( arg.__ArgData<TArg, N>::GetArg() )...);
				} );
				return std::move( r );
			}

			template<class... TArg, USize... N>
			AveInline void __CallCi( const Napi::CallbackInfo& cb, void(T::*p)(const CallbackInfo&, TArg...), __Detail::__Index<N...>* )
			{
				__Detail::__ArgList<TArg...> arg{};
				(__Detail::__ConvertType<TArg>::ToCpp( &arg.__ArgData<TArg, N>::GetArg(), cb[N] ), ...);

				App::GetSingleton().ExecuteInUiThread( [&arg, this, p]
				{
					(((T&) *this).*p)(cb, std::forward<TArg>( arg.__ArgData<TArg, N>::GetArg() )...);
				} );
			}

			template<class TRet, class... TArg>
			AveInline TRet __CallCi( const Napi::CallbackInfo& cb, TRet( T::*p )(const CallbackInfo&, TArg...) )
			{
				return __CallCi( cb, p, (__Detail::__BuildIndex<sizeof...(TArg)>*) nullptr );
			}
		};

		template<class T>
		class __WrapObject<T, WrapObjectMix> : __Detail::__MixCall
		{
		protected:
			template<class TRet, class... TArg, USize... N>
			AveInline TRet __Call( const Napi::CallbackInfo& cb, TRet( T::*p )(const MixCallContext&, TArg...), __Detail::__Index<N...>* )
			{
				__Detail::__ArgList<TArg...> arg{};
				(__Detail::__ConvertType<TArg>::ToCpp( &arg.__ArgData<TArg, N>::GetArg(), cb[N] ), ...);

				MixCallContext cc( cb );
				(((T&) *this).*p)(cc, std::forward<TArg>( arg.__ArgData<TArg, N>::GetArg() )...);
				__NextStage( cc );
				App::GetSingleton().ExecuteInUiThread( [&arg, &cc, this, p]
				{
					(((T&) *this).*p)(cc, std::forward<TArg>( arg.__ArgData<TArg, N>::GetArg() )...);
				} );
				__NextStage( cc );
				TRet r = (((T&) *this).*p)(cc, std::forward<TArg>( arg.__ArgData<TArg, N>::GetArg() )...);
				return std::move( r );
			}

			template<class... TArg, USize... N>
			AveInline void __Call( const Napi::CallbackInfo& cb, void(T::*p)(const MixCallContext&, TArg...), __Detail::__Index<N...>* )
			{
				__Detail::__ArgList<TArg...> arg{};
				(__Detail::__ConvertType<TArg>::ToCpp( &arg.__ArgData<TArg, N>::GetArg(), cb[N] ), ...);

				MixCallContext cc( cb );
				(((T&) *this).*p)(cc, std::forward<TArg>( arg.__ArgData<TArg, N>::GetArg() )...);
				__NextStage( cc );
				App::GetSingleton().ExecuteInUiThread( [&arg, &cc, this, p]
				{
					(((T&) *this).*p)(cc, std::forward<TArg>( arg.__ArgData<TArg, N>::GetArg() )...);
				} );
				__NextStage( cc );
				(((T&) *this).*p)(cc, std::forward<TArg>( arg.__ArgData<TArg, N>::GetArg() )...);
			}

			template<class TRet, class... TArg>
			AveInline TRet __Call( const Napi::CallbackInfo& cb, TRet( T::*p )(const MixCallContext&, TArg...) )
			{
				return __Call( cb, p, (__Detail::__BuildIndex<sizeof...(TArg)>*) nullptr );
			}
		};

		template<class T>
		class __WrapObject<T, WrapObjectPromise>
		{
		protected:
			template<class TRet, class... TArg>
			AveInline Napi::Value __Call( const Napi::CallbackInfo& cb, TRet( T::*p )(TArg...) )
			{
				auto pc = UniPtr( AveNew PromiseCall<T, T, TRet( TArg... )>( (T*) this, (T*) this, p, cb ) );
				pc->OnPrepare( cb );
				auto pro = pc->GetPromise();
				App::GetSingleton().ExecuteInUiThread( pc.Detach() );
				return pro;
			}

			template<class TType, class TRet, class... TArg>
			AveInline Napi::Value __Call( const Napi::CallbackInfo& cb, TRet( TType::*p )(TArg...) )
			{
				auto pc = UniPtr( AveNew TType( (T*) this, nullptr, p, cb ) );
				pc->OnPrepare( cb );
				auto pro = pc->GetPromise();
				App::GetSingleton().ExecuteInUiThread( pc.Detach() );
				return pro;
			}
		};
	}

	template<class T, class Tctor, class TType = WrapObjectGeneric>
	class WrapObject;


	//template<class T>
	//class ___DebugBreak
	//{
	//public:
	//	static U1 Break( void* p ) { return false; }
	//};


	template<class T, class... Tctor, class TType>
	class WrapObject<T, void( Tctor... ), TType> : public Napi::ObjectWrap<T>, __Detail::__WrapObject<T, WrapObjectGeneric>, __Detail::__WrapObject<T, WrapObjectUi>, __Detail::__WrapObject<T, WrapObjectMix>, __Detail::__WrapObject<T, WrapObjectPromise>
	{
		friend class ObjectRegister<T>;

		using Base_t = Napi::ObjectWrap<T>;

		WrapObject() = delete;
		WrapObject( const WrapObject& ) = delete;
		WrapObject( WrapObject&& ) = delete;
		WrapObject& operator = ( const WrapObject& ) = delete;
		WrapObject& operator = ( WrapObject&& ) = delete;

	protected:
		WrapObject( const Napi::CallbackInfo& cb ) : Base_t( cb )
		{
		}

		virtual ~WrapObject()
		{
		}

		template<class = void>
		void __Ctor( const Napi::CallbackInfo& cb )
		{
			if ( 1 == cb.Length() && cb[0].IsSymbol() )
				return;
			if ( !__CheckType<Tctor...>( cb ) )
				return;
			if ( !this->__WrapObject<T, WrapObjectGeneric>::__Call<U1, Tctor...>( cb, &T::Ctor ) )
			{
				Napi::TypeError::New( cb.Env(), "Failed to construct object." ).ThrowAsJavaScriptException();
				return;
			}
		}

		template<class = void>
		void __CtorCi( const Napi::CallbackInfo& cb )
		{
			if ( 1 == cb.Length() && cb[0].IsSymbol() )
				return;
			if ( !__CheckType<Tctor...>( cb ) )
				return;
			if ( !this->__WrapObject<T, WrapObjectGeneric>::__CallCi<U1, Tctor...>( cb, &T::Ctor ) )
			{
				Napi::TypeError::New( cb.Env(), "Failed to construct object." ).ThrowAsJavaScriptException();
				return;
			}
		}

		Napi::Value __GetObjectValue( Napi::Env env )
		{
			return this->Value();
		}

	private:
		class GlobalMethod
		{
		public:
			AString m_Name;
			Napi::Value( *m_Func ) (const Napi::CallbackInfo& ci);
			void* m_Data;
		};

		static std::vector<Napi::ClassPropertyDescriptor<T>>* __m_Property;
		static List<GlobalMethod>* __m_GlobalMethod;

	public:
		static Napi::FunctionReference* ctor;

	private:
		template<class... TArg>
		static AveInline U1 __CheckType( const Napi::CallbackInfo& cb )
		{
			if constexpr ( (... && __Detail::__CheckCount<TArg>::Value) )
			{
				if ( sizeof...(TArg) != cb.Length() )
				{
					Napi::TypeError::New( cb.Env(), AveStr.Utf16ToUtf8( "Invalid parameter count, expected %0% but received %1%."_strfp % sizeof...(TArg) % cb.Length() ).c_str() ).ThrowAsJavaScriptException();
					return false;
				}
			}
			if ( auto n = __Detail::__ObjectWrapperCheckType<0, TArg...>::Check( cb ); n >= 0 )
			{
				Napi::TypeError::New( cb.Env(), AveStr.Utf16ToUtf8( "Invalid parameter[%0%] type."_strfp % n ).c_str() ).ThrowAsJavaScriptException();
				return false;
			}
			return true;
		}

	private:
		static void ExportJsObject( Napi::Env env, Napi::Object exports, __Detail::IObjectFactoryHost& host )
		{
			std::vector<Napi::ClassPropertyDescriptor<T>> vProperty;
			List<GlobalMethod> vGlobalMethod;

			__m_Property = &vProperty;
			__m_GlobalMethod = &vGlobalMethod;
			T::DefineObject();
			__m_Property = nullptr;
			__m_GlobalMethod = nullptr;

			Napi::Function func = Base_t::DefineClass( env, T::GetExportName(), vProperty );
			ctor = host.AllocateFuncRef( env );
			*ctor = Napi::Persistent( func );
			exports.Set( T::GetExportName(), func );

			for ( auto& i : vGlobalMethod )
				exports.Set( i.m_Name.c_str(), Napi::Function::New( env, i.m_Func, nullptr, i.m_Data ) );
		}

	private:
		template<class TCallType, class TRet, class... TArg>
		Napi::Value __MethodProxy( const Napi::CallbackInfo& cb )
		{
			if ( !__CheckType<TArg...>( cb ) )
				return cb.Env().Null();

			auto p = __Detail::__ConvertFunc<T, TRet, TArg...>( cb.Data() );
			auto r = this->__WrapObject<T, TCallType>::__Call( cb, p );
			return __Detail::__ConvertType<TRet>::ToJs( cb.Env(), &r );
		}

		template<class TCallType, class... TArg>
		void __VoidMethodProxy( const Napi::CallbackInfo& cb )
		{
			if ( !__CheckType<TArg...>( cb ) )
				return;

			auto p = __Detail::__ConvertFunc<T, void, TArg...>( cb.Data() );
			this->__WrapObject<T, TCallType>::__Call( cb, p );
		}

		template<class TCallType, class TRet, class... TArg>
		Napi::Value __MethodProxyCi( const Napi::CallbackInfo& cb )
		{
			if ( !__CheckType<TArg...>( cb ) )
				return cb.Env().Null();

			auto p = __Detail::__ConvertFunc<T, TRet, const CallbackInfo&, TArg...>( cb.Data() );
			auto r = this->__WrapObject<T, TCallType>::__CallCi( cb, p );
			return __Detail::__ConvertType<TRet>::ToJs( cb.Env(), &r );
		}

		template<class TCallType, class... TArg>
		void __VoidMethodProxyCi( const Napi::CallbackInfo& cb )
		{
			if ( !__CheckType<TArg...>( cb ) )
				return;

			auto p = __Detail::__ConvertFunc<T, void, const CallbackInfo&, TArg...>( cb.Data() );
			this->__WrapObject<T, TCallType>::__CallCi( cb, p );
		}

		template<class TRet, class... TArg>
		Napi::Value __MethodProxyMix( const Napi::CallbackInfo& cb )
		{
			if ( !__CheckType<TArg...>( cb ) )
				return cb.Env().Null();

			auto p = __Detail::__ConvertFunc<T, TRet, const MixCallContext&, TArg...>( cb.Data() );
			auto r = this->__WrapObject<T, WrapObjectMix>::__Call( cb, p );
			return __Detail::__ConvertType<TRet>::ToJs( cb.Env(), &r );
		}

		template<class... TArg>
		void __VoidMethodProxyMix( const Napi::CallbackInfo& cb )
		{
			if ( !__CheckType<TArg...>( cb ) )
				return;

			auto p = __Detail::__ConvertFunc<T, void, const MixCallContext&, TArg...>( cb.Data() );
			this->__WrapObject<T, WrapObjectMix>::__Call( cb, p );
		}

		template<class TRet, class... TArg>
		Napi::Value __MethodProxyPromise( const Napi::CallbackInfo& cb )
		{
			if ( !__CheckType<TArg...>( cb ) )
				return cb.Env().Null();

			auto p = __Detail::__ConvertFunc<T, TRet, TArg...>( cb.Data() );
			return this->__WrapObject<T, WrapObjectPromise>::__Call( cb, p );
		}

		template<class TType, class TRet, class... TArg>
		Napi::Value __MethodProxyPromiseComplex( const Napi::CallbackInfo& cb )
		{
			if ( !__CheckType<TArg...>( cb ) )
				return cb.Env().Null();

			auto p = __Detail::__ConvertFunc<TType, TRet, TArg...>( cb.Data() );
			return this->__WrapObject<T, WrapObjectPromise>::__Call<TType, TRet, TArg...>( cb, p );
		}

		template<class TRet, class... TArg, USize... N>
		static AveInline TRet __CallGlobalMethod( const Napi::CallbackInfo& cb, TRet( *p )(TArg...), __Detail::__Index<N...>* )
		{
			__Detail::__ArgList<TArg...> arg{};
			(__Detail::__ConvertType<TArg>::ToCpp( &arg.__ArgData<TArg, N>::GetArg(), cb[N] ), ...);
			return (*p)(std::forward<TArg>( arg.__ArgData<TArg, N>::GetArg() )...);
		}

		template<class TRet, class... TArg>
		static AveInline TRet __CallGlobalMethod( const Napi::CallbackInfo& cb, TRet( *p )(TArg...) )
		{
			return __CallGlobalMethod( cb, p, (__Detail::__BuildIndex<sizeof...(TArg)>*) nullptr );
		}

		template<class TRet, class... TArg, USize... N>
		static AveInline TRet __CallGlobalMethodCi( const Napi::CallbackInfo& cb, TRet( *p )(const CallbackInfo&, TArg...), __Detail::__Index<N...>* )
		{
			__Detail::__ArgList<TArg...> arg{};
			(__Detail::__ConvertType<TArg>::ToCpp( &arg.__ArgData<TArg, N>::GetArg(), cb[N] ), ...);
			return (*p)(cb, std::forward<TArg>( arg.__ArgData<TArg, N>::GetArg() )...);
		}

		template<class TRet, class... TArg>
		static AveInline TRet __CallGlobalMethodCi( const Napi::CallbackInfo& cb, TRet( *p )(const CallbackInfo&, TArg...) )
		{
			return __CallGlobalMethodCi( cb, p, (__Detail::__BuildIndex<sizeof...(TArg)>*) nullptr );
		}

		template<class TRet, class... TArg>
		static Napi::Value __GlobalMethodProxy( const Napi::CallbackInfo& cb )
		{
			if ( !__CheckType<TArg...>( cb ) )
				return cb.Env().Null();

			auto p = (TRet( * )(TArg...)) cb.Data();
			auto r = __CallGlobalMethod<TRet, TArg...>( cb, p );
			return __Detail::__ConvertType<TRet>::ToJs( cb.Env(), &r );
		}

		template<class TRet, class... TArg>
		static Napi::Value __GlobalMethodProxyCi( const Napi::CallbackInfo& cb )
		{
			if ( !__CheckType<TArg...>( cb ) )
				return cb.Env().Null();

			auto p = (TRet( * )(const CallbackInfo&, TArg...)) cb.Data();
			auto r = __CallGlobalMethodCi<TRet, TArg...>( cb, p );
			return __Detail::__ConvertType<TRet>::ToJs( cb.Env(), &r );
		}

		template<class... TArg>
		static Napi::Value __GlobalVoidMethodProxy( const Napi::CallbackInfo& cb )
		{
			if ( !__CheckType<TArg...>( cb ) )
				return cb.Env().Null();

			auto p = (void(*)(TArg...)) cb.Data();
			__CallGlobalMethod<void, TArg...>( cb, p );
			return cb.Env().Undefined();
		}

		template<class... TArg>
		static Napi::Value __GlobalVoidMethodProxyCi( const Napi::CallbackInfo& cb )
		{
			if ( !__CheckType<TArg...>( cb ) )
				return cb.Env().Null();

			auto p = (void(*)(const CallbackInfo&, TArg...)) cb.Data();
			__CallGlobalMethodCi<void, TArg...>( cb, p );
			return cb.Env().Undefined();
		}

		template<class, class, class...>
		class __GetMethodProxy;

		template<class TCallType, class TRet, class... TArg> class __GetMethodProxy<TCallType, TRet, TArg...> { public: static auto __GetMethod() { return &T::template __MethodProxy<TCallType, TRet, TArg...>; } };
		template<class TCallType, class TRet, class... TArg> class __GetMethodProxy<TCallType, TRet, const CallbackInfo&, TArg...> { public: static auto __GetMethod() { return &T::template __MethodProxyCi<TCallType, TRet, TArg...>; } };
		template<class TRet, class... TArg> class __GetMethodProxy<WrapObjectMix, TRet, const MixCallContext&, TArg...> { public: static auto __GetMethod() { return &T::template __MethodProxyMix<TRet, TArg...>; } };
		template<class TRet, class... TArg> class __GetMethodProxy<WrapObjectPromise, TRet, TArg...> { public: static auto __GetMethod() { return &T::template __MethodProxyPromise<TRet, TArg...>; } };
		template<class TCallType, class... TArg> class __GetMethodProxy<TCallType, void, TArg...> { public: static auto __GetMethod() { return &T::template __VoidMethodProxy<TCallType, TArg...>; } };
		template<class TCallType, class... TArg> class __GetMethodProxy<TCallType, void, const CallbackInfo&, TArg...> { public: static auto __GetMethod() { return &T::template __VoidMethodProxyCi<TCallType, TArg...>; } };
		template<class... TArg> class __GetMethodProxy<WrapObjectMix, void, const MixCallContext&, TArg...> { public: static auto __GetMethod() { return &T::template __VoidMethodProxyMix<TArg...>; } };

		template<class TType, class TRet, class... TArg>
		class __GetComplexPromiseMethodProxy
		{
		public:
			static auto __GetMethod()
			{
				return &T::template __MethodProxyPromiseComplex<TType, TRet, TArg...>;
			}
		};

		template<class, class...>
		class __GetGlobalMethodProxy;
		template<class TRet, class... TArg> class __GetGlobalMethodProxy<TRet, TArg...> { public: static auto __GetMethod() { return &T::template __GlobalMethodProxy<TRet, TArg...>; } };
		template<class TRet, class... TArg> class __GetGlobalMethodProxy<TRet, const CallbackInfo&, TArg...> { public: static auto __GetMethod() { return &T::template __GlobalMethodProxyCi<TRet, TArg...>; } };
		template<class... TArg> class __GetGlobalMethodProxy<void, TArg...> { public: static auto __GetMethod() { return &T::template __GlobalVoidMethodProxy<TArg...>; } };
		template<class... TArg> class __GetGlobalMethodProxy<void, const CallbackInfo&, TArg...> { public: static auto __GetMethod() { return &T::template __GlobalVoidMethodProxyCi<TArg...>; } };

	protected:
		template<class TCallType = TType, class TRet, class... TArg>
		static void AddMethod( PCAChar szName, TRet( T::*p )(TArg...) )
		{
			if ( __m_Property )
				__m_Property->push_back( Base_t::InstanceMethod( szName, __GetMethodProxy<TCallType, TRet, TArg...>::__GetMethod(), (napi_property_attributes) (napi_property_attributes::napi_writable | napi_property_attributes::napi_configurable), __Detail::__ConvertFunc( p ) ) );
		}

		template<class TCallType = TType, class TRet, class... TArg>
		static void AddMethod( PCAChar szName, TRet( T::*p )(TArg...) const )
		{
			if ( __m_Property )
				__m_Property->push_back( Base_t::InstanceMethod( szName, __GetMethodProxy<TCallType, TRet, TArg...>::__GetMethod(), (napi_property_attributes) (napi_property_attributes::napi_writable | napi_property_attributes::napi_configurable), __Detail::__ConvertFunc( p ) ) );
		}

		template<class TType, class TRet, class... TArg>
		static void AddComplexPromiseMethod( PCAChar szName, TRet( TType::*p )(TArg...) )
		{
			if ( __m_Property )
				__m_Property->push_back( Base_t::InstanceMethod( szName, __GetComplexPromiseMethodProxy<TType, TRet, TArg...>::__GetMethod(), (napi_property_attributes) (napi_property_attributes::napi_writable | napi_property_attributes::napi_configurable), __Detail::__ConvertFunc( p ) ) );
		}

		template<class TType, class TRet, class... TArg>
		static void AddComplexPromiseMethod( PCAChar szName, TRet( TType::*p )(TArg...) const )
		{
			if ( __m_Property )
				__m_Property->push_back( Base_t::InstanceMethod( szName, __GetComplexPromiseMethodProxy<TType, TRet, TArg...>::__GetMethod(), (napi_property_attributes) (napi_property_attributes::napi_writable | napi_property_attributes::napi_configurable), __Detail::__ConvertFunc( p ) ) );
		}

		template<class TType>
		static void AddComplexPromiseMethod( PCAChar szName )
		{
			AddComplexPromiseMethod( szName, &TType::operator () );
		}
		
		template<class TRet, class... TArg>
		static void AddGlobalMethod( PCAChar szName, TRet( *p )(TArg...) )
		{
			if ( __m_GlobalMethod )
				__m_GlobalMethod->Add( { szName, __GetGlobalMethodProxy<TRet, TArg...>::__GetMethod(), p } );
		}
	};

	template<class T, class... Tctor, class TType>
	std::vector<Napi::ClassPropertyDescriptor<T>>* WrapObject<T, void( Tctor... ), TType>::__m_Property;

	template<class T, class... Tctor, class TType>
	List<typename WrapObject<T, void( Tctor... ), TType>::GlobalMethod>* WrapObject<T, void( Tctor... ), TType>::__m_GlobalMethod;

	template<class T, class... Tctor, class TType>
	Napi::FunctionReference* WrapObject<T, void( Tctor... ), TType>::ctor;

#	define AveWrapObject($x) $x( const Napi::CallbackInfo& cb ) : WrapObject( cb ) { __Ctor( cb ); }

}
