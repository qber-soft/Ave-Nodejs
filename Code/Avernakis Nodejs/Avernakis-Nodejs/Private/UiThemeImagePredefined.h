#pragma once

#include "UiThemeImage.h"

namespace Nav
{

	class UiThemeImagePredefined
	{
	protected:
		UiThemeImagePredefined() {}
		~UiThemeImagePredefined() {}

	public:
		virtual Napi::Value							GetWrapValue() = 0;

		virtual Ui::IThemeImagePredefinedStyle&		GetPredefined() = 0;

	protected:
		template<class T>
		static void __DefineObject()
		{
#		define AutoAddMethod($x) T::template AddMethod<WrapObjectUi>( #$x, &T::$x )

			AutoAddMethod( SetStyle );

#		undef AutoAddMethod
		}

	private:
		void					SetStyle( UiThemeImage* p, U32 nStyle ) { if ( p->GetTheme() ) GetPredefined().SetStyle( *p->GetTheme(), nStyle, {} ); }
	};

	template<class T, class TStyle>
	class UiThemeImagePredefinedStyle : public UiThemeImagePredefined, public WrapObject<T, void()>
	{
		friend class WrapObject<T, void()>;

	public:
		UiThemeImagePredefinedStyle( const Napi::CallbackInfo& cb ) : WrapObject<T, void()>( cb )
		{
			this->__Ctor( cb );
		}

		U1 Ctor()
		{
			m_Style = AveKak.Create<TStyle>();
			if ( !m_Style )
				return false;
			return true;
		}

	private:
		static void DefineObject()
		{
			__DefineObject<T>();
		}

	private:
		virtual Napi::Value							GetWrapValue() override final { return this->Value(); }

		virtual Ui::IThemeImagePredefinedStyle&		GetPredefined() override { return *m_Style; }

	private:
		RefPtr<TStyle>								m_Style;
	};

	class UiThemeImagePredefinedStyle_Dark : public UiThemeImagePredefinedStyle<UiThemeImagePredefinedStyle_Dark, Ui::IThemeImagePredefinedStyle_HyperOnyx>
	{
		friend class UiThemeImagePredefined;
	public:
		using UiThemeImagePredefinedStyle::UiThemeImagePredefinedStyle;
		static PCAChar GetExportName() { return "UiThemePredefined_Dark"; }
	};

}
