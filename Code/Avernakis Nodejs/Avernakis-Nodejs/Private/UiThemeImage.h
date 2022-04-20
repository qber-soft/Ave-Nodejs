#pragma once

#include "UiTheme.h"

namespace Nav
{

	class UiThemeImage : public UiTheme, public WrapObject<UiThemeImage, void()>
	{
	public:
		AveWrapObject( UiThemeImage );

		static PCAChar				GetExportName() { return "UiThemeImage"; }
		static void					DefineObject();

		U1							Ctor();

	public:
		virtual Napi::Value			GetObjectValue( Napi::Env env ) override { return __GetObjectValue( env ); }

	private:
		virtual Ui::ITheme&			GetTheme() override { return *m_Object; }
		virtual Ui::Theme			CloneTheme() override { return m_Object; }

	private:
		Ui::ThemeImage				m_Object;
		Ui::IThemeAnimation*		m_Animation{ nullptr };
		Ui::IThemeInfection*		m_Infection{ nullptr };

	private:
		void						ResetTheme() { m_Object->ThemeClear(); }

		void						SetFont( const WrapData<UiFontDescription>& font );

		void						AnimationSetDuration( U32 nMillisecond );
		U32							AnimationGetDuration();
		void						AnimationSetFps( U32 nFps );
		U32							AnimationGetFps();

		void						InfectionSet( const WrapData<UiThemeInfection>& pi );
		WrapData<UiThemeInfection>	InfectionGet();

	private:
		void						__Init();

	public:
		Ui::IThemeImage*			PublicGetTheme() const { return m_Object; }

		void						SetTheme( Ui::ThemeImage&& theme );
	};

}
