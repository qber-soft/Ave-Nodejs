#pragma once

#include "UiWindow.h"

namespace Nav
{

	namespace __Detail
	{
		template<U1 = true> class __GetCtorType { public: using Type_t = void( UiWindow*, Napi::Value ); };
		template<> class __GetCtorType<false> { public: using Type_t = void(); };
	}

	class UiWindow;

	template<class T, class TControl, class TBase = UiControl, U1 TDefineObject = true>
	class UiControlHelper : public TBase, public WrapObject<T, typename __Detail::__GetCtorType<TDefineObject>::Type_t, WrapObjectUi>
	{
		friend class WrapObject<T, typename __Detail::__GetCtorType<TDefineObject>::Type_t, WrapObjectUi>;

	protected:
		UiControlHelper( const Napi::CallbackInfo& cb ) : WrapObject<T, typename __Detail::__GetCtorType<TDefineObject>::Type_t, WrapObjectUi>( cb )
		{
		}

		U1 __CreateControl( UiWindow* p, Napi::Value v )
		{
			if constexpr ( TDefineObject )
			{
				StringKey key;
				UniPtr<TControl> ctl;
				if ( key.Set( v ) )
				{
					if ( key.m_Count > 0 )
					{
						if ( key.m_IdKey )
							ctl = p->PublicGetControlManager().CreateControlEx<TControl>( key.m_Offset, key.m_IdKey, key.m_Count );
						else
							ctl = p->PublicGetControlManager().CreateControlEx<TControl>( key.m_StrKey.c_str(), key.m_Offset, key.m_Count );
					}
					else
					{
						if ( key.m_IdKey )
							ctl = p->PublicGetControlManager().CreateControl<TControl>( key.m_IdKey );
						else
							ctl = p->PublicGetControlManager().CreateControl<TControl>( key.m_StrKey.c_str() );
					}
				}
				else
				{
					ctl = p->GetFactoryUi().Create<TControl>();
				}
				if ( !ctl )
					return false;
				__m_Control = ctl;
				__m_Control->SetUserContext( static_cast<UiControl*>(this) );
				__m_ControlData = std::move( ctl );
			}
			return true;
		}

	private:
		static void DefineObject()
		{
			if constexpr ( TDefineObject )
			{
				UiControl::__DefineObject<T>();
				T::DefineControl();
			}
		}

	public:
		virtual Napi::Value		GetObjectValue( Napi::Env env ) override final { return this->__GetObjectValue( env ); }

		virtual Ui::IControl&	GetControl() override final { return *__m_Control; }
		virtual Ui::Control		TakeOwnership() override { return std::move( __m_ControlData ); }
		virtual void			GiveOwnership( Ui::Control c ) { __m_ControlData = std::move( c ); }

		virtual void			SetSharedControl( Ui::IControl* c ) { if ( !__m_Control ) __m_Control = (TControl*) c; }

	private:
		TControl*				__m_Control{ nullptr };
		Ui::Control				__m_ControlData;

	protected:
		TControl&				GetControlTyped() { return *__m_Control; }
		const TControl&			GetControlTyped() const { return *__m_Control; }

		void					GiveControl( UniPtr<TControl>&& p ) { if ( p ) p->SetUserContext( static_cast<UiControl*>(this) ); __m_Control = p; __m_ControlData = std::move( p ); }
	};

#define AveWrapControl($x) friend class UiControl; $x( const Napi::CallbackInfo& cb ) : UiControlHelper( cb ) { __Ctor( cb ); }
#define AveWrapControlCi($x) friend class UiControl; $x( const Napi::CallbackInfo& cb ) : UiControlHelper( cb ) { __CtorCi( cb ); }

}
