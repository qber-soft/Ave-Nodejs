#pragma once

#include "App.h"

namespace Nav
{
	template<class TData>
	class WrapData;

	template<class TData>
	class WrapPointer
	{
	public:
		TData* m_Pointer;

		AveInline TData* operator -> () const { return m_Pointer; }
		AveInline operator TData* () const { return m_Pointer; }
		AveInline operator U1 () const { return nullptr != m_Pointer; }
	};

	template<class TData>
	class WrapArray
	{
	public:
		const TData*	m_Pointer;
		USize			m_Length;

		AveInline operator U1 () const { return m_Pointer && m_Length > 0; }
		AveInline operator const TData* () const { return m_Pointer; }
		AveInline const TData& operator [] ( USize nIndex ) const { return m_Pointer[nIndex]; }
	};

	class ReturnBuffer
	{
	public:
		List<U8>		m_Data;
		U1				m_Null{ false };
	};

	// Don't use Napi::ObjectReference, this class doesn't allow copy
	template<class TObject>
	class JsObject
	{
	public:
		JsObject()
		{
		}

		JsObject( std::nullptr_t )
		{
		}

		JsObject( const Napi::Object& obj )
		{
			m_Object = Napi::ObjectReference::New( obj, 1 );
			m_TypedObject = Napi::ObjectWrap<TObject>::Unwrap( obj );
		}

	private:
		Napi::ObjectReference	m_Object;
		TObject*				m_TypedObject{ nullptr };

	public:
		operator TObject* () const { return m_TypedObject; }
		TObject* operator -> () const { return m_TypedObject; }
	};

	class CallbackInfo
	{
		CallbackInfo( const CallbackInfo& ) = delete;
		CallbackInfo( CallbackInfo&& ) = delete;

	public:
		CallbackInfo( const Napi::CallbackInfo& cb ) : m_cb( cb ) {}
	protected:

	private:
		const Napi::CallbackInfo& m_cb;

	public:
		AveInline void ThrowJsException( PCAChar szError ) const
		{
			Napi::TypeError::New( m_cb.Env(), szError ).ThrowAsJavaScriptException();
		}

		AveInline void ThrowJsException( PCWChar szError ) const
		{
			Napi::TypeError::New( m_cb.Env(), AveStr.Utf16ToUtf8( szError ).c_str() ).ThrowAsJavaScriptException();
		}

		AveInline Napi::Env GetEnv() const
		{
			return m_cb.Env();
		}

		template<class T>
		AveInline T* NewJsObject() const
		{
			Napi::Object obj;
			{
				Napi::EscapableHandleScope scope( m_cb.Env() );
				auto v = scope.Escape( T::ctor->New( { Napi::Symbol::New( m_cb.Env(), "" ) } ) );
				//if ( bPersist )
				//{
				//	auto vp = Napi::Persistent( v.ToObject() );
				//	vp.SuppressDestruct();
				//	v = vp.Value();
				//}
				obj = v.ToObject();
			}
			return Napi::ObjectWrap<T>::Unwrap( obj );
		}

		template<class T>
		AveInline JsObject<T> NewJsObjectWithOwnership() const
		{
			return JsObject<T>( T::ctor->New( { Napi::Symbol::New( m_cb.Env(), "" ) } ) );
		}
	};

	namespace __Detail
	{

		class IFuncSafe
		{
		protected:
			IFuncSafe() {}
			~IFuncSafe() {}

		public:
			virtual void					ReleaseFunc() = 0;
		};

		class __EventManger
		{
			List<Sys::Event>				m_EventData;
			List<Sys::IEvent*>				m_EventValid;
			U32								m_EventCount{ 0 };
			Sys::RwLock						m_EventLock;

			Set<IFuncSafe*>					m_FuncSafe;
			Sys::RwLock						m_FuncLock;

			static __EventManger	c_Blocker;

			__EventManger()
			{
				m_EventLock.Create();
				m_FuncLock.Create();
			}

		public:
			AveInline Sys::IEvent* Alloc()
			{
				Sys::RwLockScoped __Lock( *m_EventLock );
				if ( 0 == m_EventCount )
				{
					++m_EventCount;
					if ( m_EventCount >= m_EventValid.Size() )
						m_EventValid.Resize( m_EventCount );
					m_EventData.Add( AveKak.Create<Sys::IEvent>() );
					m_EventValid[m_EventCount - 1] = m_EventData.Last();
				}
				return m_EventValid[--m_EventCount];
			}

			AveInline void Free( Sys::IEvent* evt )
			{
				Sys::RwLockScoped __Lock( *m_EventLock );
				m_EventValid[m_EventCount++] = evt;
			}

			AveInline void AddFuncSafe( IFuncSafe* fn )
			{
				Sys::RwLockScoped __Lock( *m_FuncLock );
				m_FuncSafe.Add( fn );
			}

			AveInline void RemoveFuncSafe( IFuncSafe* fn )
			{
				Sys::RwLockScoped __Lock( *m_FuncLock );
				m_FuncSafe.Remove( fn );
			}

			AveInline void ReplaceFuncSafe( IFuncSafe* pOld, IFuncSafe* pNew )
			{
				Sys::RwLockScoped __Lock( *m_FuncLock );
				m_FuncSafe.Remove( pOld );
				m_FuncSafe.Add( pNew );
			}

			AveInline void ReleaseFuncSafe()
			{
				Set<IFuncSafe*> v;
				{
					Sys::RwLockScoped __Lock( *m_FuncLock );
					v = std::move( m_FuncSafe );
				}
				for ( auto i : v )
					i->ReleaseFunc();
			}

			static __EventManger& GetSingleton()
			{
				static __EventManger b;
				return b;
			}
		};

		template<class TRet, class... TArg>
		class __JsFuncSafe : public IFuncSafe
		{
		protected:
			// Napi::ThreadSafeFunction is not fully implemented the c++ class version, don't use it here
			//Napi::ThreadSafeFunction m_JsFunc;

			napi_threadsafe_function				m_JsFunc{ nullptr };
			std::atomic<napi_threadsafe_function>	m_JsFuncNew{ nullptr };
			std::atomic<U1>							m_IsBusy{ false };
			Func<void( Napi::Env, Napi::Function )>	m_Target;

			__JsFuncSafe( const __JsFuncSafe& r ) = delete;
			__JsFuncSafe& operator = ( const __JsFuncSafe& r ) = delete;

			static void __Finalize( napi_env env, void* finalize_data, void* finalize_hint )
			{
			}

			static void __Call( napi_env env, napi_value js_callback, void* context, void* data )
			{
				auto pThis = (__JsFuncSafe*) data;
				pThis->m_Target( Napi::Env( env ), Napi::Function( env, js_callback ) );
				pThis->__CallEnd();
			}

			virtual void ReleaseFunc() override
			{
				Reset();
			}

			AveInline void __Call( Func<void( Napi::Env, Napi::Function )>&& fn )
			{
				if ( m_JsFunc )
				{
					m_Target = std::move( fn );
					auto r = napi_call_threadsafe_function( m_JsFunc, this, napi_threadsafe_function_call_mode::napi_tsfn_blocking );
					if ( napi_ok != r )
						__CallEnd();
				}
			}

			AveInline U1 __CallStart()
			{
				U1 bExpected = false;
				return m_IsBusy.compare_exchange_weak( bExpected, true );
			}

			AveInline void __CallEnd()
			{
				if ( auto pFuncNew = m_JsFuncNew.exchange( nullptr ) )
				{
					if ( m_JsFunc )
						napi_release_threadsafe_function( m_JsFunc, napi_threadsafe_function_release_mode::napi_tsfn_release );
					m_JsFunc = pFuncNew;
				}
				U1 bExpected = true;
				m_IsBusy.compare_exchange_strong( bExpected, false );
			}

		public:
			AveInline __JsFuncSafe()
			{
			}

			AveInline ~__JsFuncSafe()
			{
				Reset();
			}

			AveInline __JsFuncSafe( __JsFuncSafe&& r ) { *this = std::move( r ); }
			AveInline __JsFuncSafe& operator = ( __JsFuncSafe&& r )
			{
				if ( this != &r )
				{
					if ( r )
						__EventManger::GetSingleton().ReplaceFuncSafe( &r, this );
					if ( m_IsBusy )
					{
						m_JsFuncNew = r.m_JsFunc;
						r.m_JsFunc = nullptr;
					}
					else
					{
						if ( m_JsFunc )
							napi_release_threadsafe_function( m_JsFunc, napi_threadsafe_function_release_mode::napi_tsfn_release );
						m_JsFunc = r.m_JsFunc;
						m_IsBusy.exchange( r.m_IsBusy );
						r.m_JsFunc = nullptr;
					}
				}
				return *this;
			}

			AveInline void Reset()
			{
				if ( m_JsFunc )
				{
					napi_release_threadsafe_function( m_JsFunc, napi_threadsafe_function_release_mode::napi_tsfn_release );
					m_JsFunc = nullptr;
					m_IsBusy = false;
					__EventManger::GetSingleton().RemoveFuncSafe( this );
				}
			}

			AveInline void SetFunc( const Napi::Value& v )
			{
				Reset();
				if ( !v.IsNull() )
				{
					napi_create_threadsafe_function( v.Env(), v.As<Napi::Function>(), Napi::Object(), Napi::String::New( v.Env(), "" ), 0, 1, nullptr, __Finalize, nullptr, __Call, &m_JsFunc );
					if ( m_JsFunc )
						__EventManger::GetSingleton().AddFuncSafe( this );
				}
			}

			AveInline void SetEmptyFunc( Napi::Env env )
			{
				Reset();
				napi_create_threadsafe_function( env, nullptr, Napi::Object(), Napi::String::New( env, "" ), 0, 1, nullptr, __Finalize, nullptr, __Call, &m_JsFunc );
				if ( m_JsFunc )
					__EventManger::GetSingleton().AddFuncSafe( this );
			}

			AveInline operator U1 () const { return m_JsFunc; }

			AveInline void operator () ( TArg... p, U1 bWait = false );
		};

		template<class TRet, class... TArg>
		class __JsFuncDirect
		{
		protected:
			Napi::FunctionReference m_JsFunc;

			__JsFuncDirect( const __JsFuncDirect& r ) = delete;
			__JsFuncDirect& operator = ( const __JsFuncDirect& r ) = delete;

		public:
			AveInline __JsFuncDirect() {}
			AveInline ~__JsFuncDirect() { Reset(); }

			AveInline __JsFuncDirect( __JsFuncDirect&& r ) { *this = std::move( r ); }
			AveInline __JsFuncDirect& operator = ( __JsFuncDirect&& r )
			{
				if ( this != &r )
				{
					m_JsFunc = std::move( r.m_JsFunc );
				}
				return *this;
			}

			AveInline void Reset()
			{
				m_JsFunc = Napi::FunctionReference();
			}

			AveInline void SetFunc( const Napi::Value& v )
			{
				if ( v.IsNull() )
					Reset();
				else
				{
					m_JsFunc = Napi::Persistent( v.As<Napi::Function>() );
				}
			}

			AveInline operator U1 () const { return m_JsFunc; }
		};
	}

	template<class>
	class JsFuncSafe;

	template<class TRet, class... TArg>
	class JsFuncSafe<TRet( TArg... )> : public __Detail::__JsFuncSafe<TRet, TArg...>
	{
	public:
		using __Detail::__JsFuncSafe<TRet, TArg...>::__JsFuncSafe;

		AveInline void WaitAsyncCall( TArg... p, Func<void( const TRet& )>&& fnWait );
		AveInline void BlockAsyncCall( TArg... p, Func<void( const TRet& )>&& fnWait );
	};

	template<class... TArg>
	class JsFuncSafe<void( TArg... )> : public __Detail::__JsFuncSafe<void, TArg...>
	{
	public:
		using __Detail::__JsFuncSafe<void, TArg...>::__JsFuncSafe;

		AveInline void WaitAsyncCall( TArg... p, Func<void()>&& fnWait );
		AveInline void BlockAsyncCall( TArg... p, Func<void()>&& fnWait );
	};

	template<class>
	class JsFuncDirect;

	template<class TRet, class... TArg>
	class JsFuncDirect<TRet( TArg... )> : public __Detail::__JsFuncDirect<TRet, TArg...>
	{
	public:
		using __Detail::__JsFuncDirect<TRet, TArg...>::__JsFuncDirect;

		AveInline TRet operator () ( TArg... p );
	};

	template<class... TArg>
	class JsFuncDirect<void( TArg... )> : public __Detail::__JsFuncDirect<void, TArg...>
	{
	public:
		using __Detail::__JsFuncDirect<void, TArg...>::__JsFuncDirect;

		AveInline void operator () ( TArg... p );
	};

	namespace __Detail
	{
		template<class T, class TEnable = void>
		class __CheckType;

		template<U1( Napi::Value::*TCheck )() const>
		class __CheckTypeHelper
		{
		public:
			static AveInline U1 Check( const Napi::Value & v ) { return !v.IsNull() && (v.*TCheck)(); }
		};

		template<> class __CheckType<U1      /**/> : public __CheckTypeHelper<&Napi::Number::IsBoolean> {};
		template<> class __CheckType<S8      /**/> : public __CheckTypeHelper<&Napi::Number::IsNumber> {};
		template<> class __CheckType<S16     /**/> : public __CheckTypeHelper<&Napi::Number::IsNumber> {};
		template<> class __CheckType<S32     /**/> : public __CheckTypeHelper<&Napi::Number::IsNumber> {};
		template<> class __CheckType<S64     /**/> : public __CheckTypeHelper<&Napi::Number::IsNumber> {};
		template<> class __CheckType<U8      /**/> : public __CheckTypeHelper<&Napi::Number::IsNumber> {};
		template<> class __CheckType<U16     /**/> : public __CheckTypeHelper<&Napi::Number::IsNumber> {};
		template<> class __CheckType<U32     /**/> : public __CheckTypeHelper<&Napi::Number::IsNumber> {};
		template<> class __CheckType<U64     /**/> : public __CheckTypeHelper<&Napi::Number::IsNumber> {};
		template<> class __CheckType<R32     /**/> : public __CheckTypeHelper<&Napi::Number::IsNumber> {};
		template<> class __CheckType<R64     /**/> : public __CheckTypeHelper<&Napi::Number::IsNumber> {};
		template<> class __CheckType<PCWChar /**/> : public __CheckTypeHelper<&Napi::Number::IsString> {};
		template<> class __CheckType<WString /**/> : public __CheckTypeHelper<&Napi::Number::IsString> {};

		template<class T>
		class __CheckType<WrapData<T>>
		{
		public:
			static AveInline U1 Check( const Napi::Value & v )
			{
				return v.IsObject() && WrapData<T>::__Check( v.As<Napi::Object>() );
			}
		};

		template<class T>
		class __CheckType<const WrapData<T>&>
		{
		public:
			static AveInline U1 Check( const Napi::Value & v )
			{
				return v.IsObject() && WrapData<T>::__Check( v.As<Napi::Object>() );
			}
		};

		template<class T>
		class __CheckType<T*>
		{
			AveStaticAssert( std::is_base_of<Napi::ObjectWrap<T>, T>::value, "Direct object pointer must be a defined object." );

		public:
			static AveInline U1 Check( const Napi::Value & v )
			{
				if ( v.IsNull() || v.IsUndefined() )
					return true;
				if ( !v.IsObject() )
					return false;
				return true;
			}
		};

		template<class T>
		class __CheckType<WrapPointer<T>>
		{
		public:
			static AveInline U1 Check( const Napi::Value & v )
			{
				return v.IsNull() || v.IsUndefined() || v.IsObject();
			}
		};

		template<class TRet, class... TArg>
		class __CheckType<JsFuncSafe<TRet( TArg... )>&&>
		{
		public:
			static AveInline U1 Check( const Napi::Value & v )
			{
				return v.IsNull() || v.IsUndefined() || v.IsFunction();
			}
		};

		template<class TRet, class... TArg>
		class __CheckType<JsFuncDirect<TRet( TArg... )>&&>
		{
		public:
			static AveInline U1 Check( const Napi::Value & v )
			{
				return v.IsNull() || v.IsUndefined() || v.IsFunction();
			}
		};

		template<class T>
		class __CheckType<T, typename std::enable_if<std::is_enum<T>::value && sizeof( U32 ) == sizeof( T )>::type>
		{
		public:
			static AveInline U1 Check( const Napi::Value & v )
			{
				return v.IsNumber();
			}
		};

		template<>
		class __CheckType<Napi::Value>
		{
		public:
			static AveInline U1 Check( const Napi::Value & v )
			{
				return true;
			}
		};

		template<class T>
		class __CheckType<List<T>>
		{
		public:
			static AveInline U1 Check( const Napi::Value & v )
			{
				return v.IsNull() || v.IsUndefined() || v.IsArray();
			}
		};

		template<class T>
		class __CheckType<const List<T>&>
		{
		public:
			static AveInline U1 Check( const Napi::Value & v )
			{
				return v.IsNull() || v.IsUndefined() || v.IsArray();
			}
		};

		class __CheckArrayHelper
		{
		public:
			static AveInline U1 Check( const Napi::Value & v ) { return v.IsNull() || v.IsUndefined() || v.IsArrayBuffer(); }
		};

		template<> class __CheckType<WrapArray<S8    /**/>> : public __CheckArrayHelper {};
		template<> class __CheckType<WrapArray<S16   /**/>> : public __CheckArrayHelper {};
		template<> class __CheckType<WrapArray<S32   /**/>> : public __CheckArrayHelper {};
		template<> class __CheckType<WrapArray<U8    /**/>> : public __CheckArrayHelper {};
		template<> class __CheckType<WrapArray<U16   /**/>> : public __CheckArrayHelper {};
		template<> class __CheckType<WrapArray<U32   /**/>> : public __CheckArrayHelper {};
		template<> class __CheckType<WrapArray<R32   /**/>> : public __CheckArrayHelper {};
		template<> class __CheckType<WrapArray<R64   /**/>> : public __CheckArrayHelper {};
		template<> class __CheckType<WrapArray<R32_2 /**/>> : public __CheckArrayHelper {};
		template<> class __CheckType<WrapArray<R32_3 /**/>> : public __CheckArrayHelper {};
		template<> class __CheckType<WrapArray<R32_4 /**/>> : public __CheckArrayHelper {};

		template<> class __CheckType<const WrapArray<S8    /**/>&> : public __CheckArrayHelper {};
		template<> class __CheckType<const WrapArray<S16   /**/>&> : public __CheckArrayHelper {};
		template<> class __CheckType<const WrapArray<S32   /**/>&> : public __CheckArrayHelper {};
		template<> class __CheckType<const WrapArray<U8    /**/>&> : public __CheckArrayHelper {};
		template<> class __CheckType<const WrapArray<U16   /**/>&> : public __CheckArrayHelper {};
		template<> class __CheckType<const WrapArray<U32   /**/>&> : public __CheckArrayHelper {};
		template<> class __CheckType<const WrapArray<R32   /**/>&> : public __CheckArrayHelper {};
		template<> class __CheckType<const WrapArray<R64   /**/>&> : public __CheckArrayHelper {};
		template<> class __CheckType<const WrapArray<R32_2 /**/>&> : public __CheckArrayHelper {};
		template<> class __CheckType<const WrapArray<R32_3 /**/>&> : public __CheckArrayHelper {};
		template<> class __CheckType<const WrapArray<R32_4 /**/>&> : public __CheckArrayHelper {};

		template<USize TIndex, class... T>
		class __ObjectWrapperCheckType
		{
		public:
			static AveInline S32 Check( const Napi::CallbackInfo& cb )
			{
				return -1;
			}
		};

		template<USize TIndex, class T0, class... T>
		class __ObjectWrapperCheckType<TIndex, T0, T...>
		{
		public:
			static AveInline S32 Check( const Napi::CallbackInfo& cb )
			{
				if ( !__CheckType<T0>::Check( cb[TIndex] ) )
					return TIndex;
				return __ObjectWrapperCheckType<TIndex + 1, T...>::Check( cb );
			}
		};

		template<class = Napi::Value>
		class __CheckCount
		{
		public:
			static const U1 Value = true;
		};

		template<>
		class __CheckCount<>
		{
		public:
			static const U1 Value = false;
		};

		template<class T, class TEnable = void>
		class __ConvertType;

		template<class T, class U, U (Napi::Number::*TMember)() const>
		class __ConvertNumber
		{
		public:
			using TargetType_t = T;
			static AveInline void ToCpp( void* p, const Napi::Value& v ) { *(T*) p = (T) (v.As<Napi::Number>().*TMember)(); }
			static AveInline Napi::Value ToJs( Napi::Env env, const void* v ) { return Napi::Number::New( env, (R64) *(T*) v ); }
		};

		template<> class __ConvertType<S8  /**/> : public __ConvertNumber<S8  /**/, S32, &Napi::Number::Int32Value> {};
		template<> class __ConvertType<S16 /**/> : public __ConvertNumber<S16 /**/, S32, &Napi::Number::Int32Value> {};
		template<> class __ConvertType<S32 /**/> : public __ConvertNumber<S32 /**/, S32, &Napi::Number::Int32Value> {};
		template<> class __ConvertType<S64 /**/> : public __ConvertNumber<S64 /**/, S64, &Napi::Number::Int64Value> {};
		template<> class __ConvertType<U8  /**/> : public __ConvertNumber<U8  /**/, U32, &Napi::Number::Uint32Value> {};
		template<> class __ConvertType<U16 /**/> : public __ConvertNumber<U16 /**/, U32, &Napi::Number::Uint32Value> {};
		template<> class __ConvertType<U32 /**/> : public __ConvertNumber<U32 /**/, U32, &Napi::Number::Uint32Value> {};
		template<> class __ConvertType<U64 /**/> : public __ConvertNumber<U64 /**/, R64, &Napi::Number::DoubleValue> {};
		template<> class __ConvertType<R32 /**/> : public __ConvertNumber<R32 /**/, R32, &Napi::Number::FloatValue> {};
		template<> class __ConvertType<R64 /**/> : public __ConvertNumber<R64 /**/, R64, &Napi::Number::DoubleValue> {};

		template<> class __ConvertType<U1>
		{
		public:
			using TargetType_t = U1;
			static AveInline void ToCpp( void* p, const Napi::Value& v ) { *(TargetType_t*) p = v.As<Napi::Boolean>().Value(); }
			static AveInline Napi::Value ToJs( Napi::Env env, const void* v ) { return Napi::Boolean::New( env, *(TargetType_t*) v ); }
		};

		template<> class __ConvertType<WString>
		{
		public:
			using TargetType_t = WString;
			static AveInline void ToCpp( void* p, const Napi::Value& v ) { *(TargetType_t*) p = (PCWChar) v.As<Napi::String>().Utf16Value().c_str(); }
			static AveInline Napi::Value ToJs( Napi::Env env, const void* v ) { return Napi::String::New( env, (char16_t*) ((TargetType_t*) v)->c_str() ); }
		};

		class __WString : WString
		{
		public:
			using WString::WString;
			operator PCWChar() const { return c_str(); }
		};

		// This type only support js to c++ conversion
		template<> class __ConvertType<PCWChar>
		{
		public:
			using TargetType_t = __WString;
			static AveInline void ToCpp( void* p, const Napi::Value& v ) { *(TargetType_t*) p = (PCWChar) v.As<Napi::String>().Utf16Value().c_str(); }
		};

		template<class T>
		class __ConvertType<WrapData<T>>
		{
		public:
			using TargetType_t = WrapData<T>;
			static AveInline void ToCpp( void* p, const Napi::Value& v ) { ((TargetType_t*) p)->__SetData( v.As<Napi::Object>() ); }
			static AveInline Napi::Value ToJs( Napi::Env env, const void* v ) { return ((TargetType_t*) v)->__GetData( env ); }
		};

		template<class T>
		class __ConvertType<const WrapData<T>&>
		{
		public:
			using TargetType_t = WrapData<T>;
			static AveInline void ToCpp( void* p, const Napi::Value& v ) { ((TargetType_t*) p)->__SetData( v.As<Napi::Object>() ); }
			static AveInline Napi::Value ToJs( Napi::Env env, const void* v ) { return ((TargetType_t*) v)->__GetData( env ); }
		};

		template<class T>
		class __ConvertType<T*>
		{
		public:
			using TargetType_t = T*;
			static AveInline void ToCpp( void* p, const Napi::Value& v ) { *(TargetType_t*) p = v.IsNull() ? nullptr : Napi::ObjectWrap<T>::Unwrap( v.As<Napi::Object>() ); }
			static AveInline Napi::Value ToJs( Napi::Env env, const void* v ) { auto& p = *(TargetType_t*) v; return p ? p->GetObjectValue( env ) : env.Undefined(); }
		};

		template<class T>
		class __ConvertType<WrapPointer<T>>
		{
		public:
			using TargetType_t = WrapPointer<T>;
			static AveInline void ToCpp( void* p, const Napi::Value& v ) { *(TargetType_t*) p = { v.IsNull() ? nullptr : Napi::ObjectWrap<T>::Unwrap( v.As<Napi::Object>() ) }; }
			static AveInline Napi::Value ToJs( Napi::Env env, const void* v ) { auto& p = *(TargetType_t*) v; return p ? p->GetObjectValue( env ) : env.Undefined(); }
		};

		template<class TRet, class... TArg>
		class __ConvertType<JsFuncSafe<TRet( TArg... )>&&>
		{
		public:
			using TargetType_t = JsFuncSafe<TRet( TArg... )>;
			static AveInline void ToCpp( void* p, const Napi::Value& v ) { ((TargetType_t*) p)->SetFunc( v ); }
			static AveInline Napi::Value ToJs( Napi::Env env, const void* v ) { return env.Undefined(); } // This method should never be called
		};

		template<class TRet, class... TArg>
		class __ConvertType<JsFuncDirect<TRet( TArg... )>&&>
		{
		public:
			using TargetType_t = JsFuncDirect<TRet( TArg... )>;
			static AveInline void ToCpp( void* p, const Napi::Value& v ) { ((TargetType_t*) p)->SetFunc( v ); }
			static AveInline Napi::Value ToJs( Napi::Env env, const void* v ) { return env.Undefined(); } // This method should never be called
		};

		template<class T>
		class __ConvertType<T, typename std::enable_if<std::is_enum<T>::value && sizeof( U32 ) == sizeof( T )>::type>
		{
		public:
			using TargetType_t = T;
			static AveInline void ToCpp( void* p, const Napi::Value& v ) { *(TargetType_t*) p = (T) (v.As<Napi::Number>().Uint32Value()); }
			static AveInline Napi::Value ToJs( Napi::Env env, const void* v ) { return Napi::Number::New( env, (R64) (U32) *(T*) v ); }
		};

		template<>
		class __ConvertType<Napi::Value>
		{
		public:
			using TargetType_t = Napi::Value;
			static AveInline void ToCpp( void* p, const Napi::Value& v ) { *(TargetType_t*) p = v; }
			static AveInline Napi::Value ToJs( Napi::Env env, const void* v ) { return *(TargetType_t*) v; }
		};

		// This type only support js to c++ conversion
		template<class T>
		class __ConvertType<const List<T>&>
		{
		public:
			using TargetType_t = List<T>;

			static AveInline void ToCpp( void* p, const Napi::Value& v )
			{
				auto& vList = *(TargetType_t*) p;
				vList.Clear();
				if ( v.IsNull() )
					return;
				auto arr = v.As<Napi::Array>();
				const auto nCount = arr.Length();
				for ( U32 i = 0; i < nCount; ++i )
				{
					auto val = arr.Get( i );
					if ( __CheckType<T>::Check( val ) )
						__ConvertType<T>::ToCpp( &vList.Add( {} ).Last(), val );
				}
			}

			static AveInline Napi::Value ToJs( Napi::Env env, const void* v )
			{
				return env.Undefined();
			}
		};

		template<class T>
		class __ConvertType<List<T>>
		{
		public:
			using TargetType_t = List<T>;

			static AveInline void ToCpp( void* p, const Napi::Value& v )
			{
				__ConvertType<const List<T>&>::ToCpp( p, v );
			}

			static AveInline Napi::Value ToJs( Napi::Env env, const void* v )
			{
				auto& vList = *(TargetType_t*) v;
				const auto nCount = (U32) vList.Size();
				auto arr = Napi::Array::New( env, nCount );
				for ( U32 i = 0; i < nCount; ++i )
					arr.Set( (U32) i, __ConvertType<T>::ToJs( env, &vList[i] ) );
				return arr;
			}
		};

		// This type only support js to c++ conversion
		template<class T>
		class __ConvertArray
		{
		public:
			using TargetType_t = WrapArray<T>;

			static AveInline void ToCpp( void* p, const Napi::Value& v )
			{
				auto& arr = *(TargetType_t*) p;
				if ( v.IsNull() || v.IsUndefined() )
				{
					arr = {};
					return;
				}
				auto ab = v.As<Napi::ArrayBuffer>();
				arr.m_Pointer = (const T*) ab.Data();
				arr.m_Length = ab.ByteLength() / sizeof( T );
			}

			static AveInline Napi::Value ToJs( Napi::Env env, const void* v )
			{
				return env.Undefined();
			}
		};

		template<class T>
		class __ConvertType<const WrapArray<T>&> : public __ConvertArray<T> {};

		template<class T>
		class __ConvertType<WrapArray<T>> : public __ConvertArray<T> {};

		template<>
		class __ConvertType<ReturnBuffer>
		{
		public:
			using TargetType_t = ReturnBuffer;

			static AveInline void ToCpp( void* p, const Napi::Value& v )
			{
			}

			static AveInline Napi::Value ToJs( Napi::Env env, const void* v )
			{
				auto& rb = *(ReturnBuffer*) v;
				if ( rb.m_Null )
					return env.Undefined();
				auto buf = Napi::ArrayBuffer::New( env, rb.m_Data.Size() );
				AveCopyMemory( buf.Data(), rb.m_Data.Data(), rb.m_Data.Size() );
				return buf;
			}
		};

		template<class T, class TRet, class... TArg>
		void* __ConvertFunc( TRet( T::*p )(TArg...) )
		{
			union
			{
				TRet( T::*p )(TArg...);
				void* Result;
			} u{ p };
			return u.Result;
		}

		template<class T, class TRet, class... TArg>
		void* __ConvertFunc( TRet( T::*p )(TArg...) const )
		{
			union
			{
				TRet( T::*p )(TArg...) const;
				void* Result;
			} u{ p };
			return u.Result;
		}

		template<class T, class TRet, class... TArg>
		TRet( T::*__ConvertFunc( void* p ) ) (TArg...)
		{
			union
			{
				void* p;
				TRet( T::*Result )(TArg...);
			} u{ p };
			return u.Result;
		}

		template<USize...>
		class __Index {};

		template<USize N0, USize... N>
		class __BuildIndex : public __BuildIndex<N0 - 1, N0 - 1, N...> {};

		template<USize... N>
		class __BuildIndex<0, N...> : public __Index<N...> {};

		template<class T, USize TIndex>
		class __ArgData
		{
		private:
			using Type_t = typename __ConvertType<T>::TargetType_t;
			Type_t m_Arg;

		public:
			AveInline Type_t& GetArg() { return m_Arg; }
			AveInline const Type_t& GetArg() const { return m_Arg; }
		};

		template<USize TIndex, class... TArg>
		class ___ArgList {};

		template<USize TIndex, class TArg0, class... TArg>
		class ___ArgList<TIndex, TArg0, TArg...> : public ___ArgList<TIndex + 1, TArg...>, public __ArgData<TArg0, TIndex> {};

		template<class... TArg>
		using __ArgList = ___ArgList<0, TArg...>;
	}

	template<class TRet, class... TArg>
	AveInline void __Detail::__JsFuncSafe<TRet, TArg...>::operator () ( TArg... p, U1 bWait )
	{
		if ( m_JsFunc )
		{
			if ( __CallStart() )
			{
				Sys::Event evt;
				if ( bWait )
					evt = __Detail::__EventManger::GetSingleton().Alloc();
				__Call( [&evt, bWait, p...]( Napi::Env env, Napi::Function fn )
				{
					fn.Call( { __Detail::__ConvertType<TArg>::ToJs( env, &p )... } );
					if ( bWait )
						evt->Set();
				} );
				if ( bWait )
				{
					evt->Wait();
					__Detail::__EventManger::GetSingleton().Free( evt );
				}
			}
		}
	}

	template<class TRet, class... TArg>
	AveInline void JsFuncSafe<TRet( TArg... )>::WaitAsyncCall( TArg... p, Func<void( const TRet& )>&& fnWait )
	{
		if ( this->m_JsFunc )
		{
			if ( this->__CallStart() )
			{
				this->__Call( [=]( Napi::Env env, Napi::Function fn )
				{
					auto val = fn.Call( { __Detail::__ConvertType<TArg>::ToJs( env, &p )... } );
					TRet r{};
					__Detail::__ConvertType<TRet>::ToCpp( &r, val );
					App::GetSingleton().ExecuteInUiThread( [r, &fnWait]
					{
						fnWait( r );
					}, false );
				} );
			}
		}
	}

	template<class TRet, class... TArg>
	AveInline void JsFuncSafe<TRet( TArg... )>::BlockAsyncCall( TArg... p, Func<void( const TRet& )>&& fnWait )
	{
		if ( this->m_JsFunc )
		{
			if ( this->__CallStart() )
			{
				auto evt = __Detail::__EventManger::GetSingleton().Alloc();
				TRet r{};
				App::GetSingleton().BlockCallEnter();
				this->__Call( [&]( Napi::Env env, Napi::Function fn )
				{
					auto val = fn.Call( { __Detail::__ConvertType<TArg>::ToJs( env, &p )... } );
					__Detail::__ConvertType<TRet>::ToCpp( &r, val );
					evt->Set();
				} );
				App::GetSingleton().BlockCallLeave( evt );
				__Detail::__EventManger::GetSingleton().Free( evt );
				fnWait( r );
			}
		}
	}

	template<class... TArg>
	AveInline void JsFuncSafe<void( TArg... )>::WaitAsyncCall( TArg... p, Func<void()>&& fnWait )
	{
		if ( this->m_JsFunc )
		{
			if ( this->__CallStart() )
			{
				this->__Call( [=]( Napi::Env env, Napi::Function fn )
				{
					fn.Call( { __Detail::__ConvertType<TArg>::ToJs( env, &p )... } );
					App::GetSingleton().ExecuteInUiThread( [fnWait]
					{
						fnWait();
					}, false );
				} );
			}
		}
	}

	template<class... TArg>
	AveInline void JsFuncSafe<void( TArg... )>::BlockAsyncCall( TArg... p, Func<void()>&& fnWait )
	{
		if ( this->m_JsFunc )
		{
			if ( this->__CallStart() )
			{
				auto evt = __Detail::__EventManger::GetSingleton().Alloc();
				App::GetSingleton().BlockCallEnter();
				this->__Call( [&]( Napi::Env env, Napi::Function fn )
				{
					fn.Call( { __Detail::__ConvertType<TArg>::ToJs( env, &p )... } );
					evt->Set();
				} );
				App::GetSingleton().BlockCallLeave( evt );
				__Detail::__EventManger::GetSingleton().Free( evt );
				fnWait();
			}
		}
	}

	template<class TRet, class... TArg>
	AveInline TRet JsFuncDirect<TRet( TArg... )>::operator () ( TArg... p )
	{
		if ( *this )
		{
			auto env = this->m_JsFunc.Env();
			auto v = this->m_JsFunc.Call( { __Detail::__ConvertType<TArg>::ToJs( env, &p )... } );
			TRet r{};
			__Detail::__ConvertType<TRet>::ToCpp( &r, v );
			return r;
		}
		return {};
	}

	template<class... TArg>
	AveInline void JsFuncDirect<void( TArg... )>::operator () ( TArg... p )
	{
		if ( *this )
		{
			auto env = this->m_JsFunc.Env();
			this->m_JsFunc.Call( { __Detail::__ConvertType<TArg>::ToJs( env, &p )... } );
		}
	}

}
