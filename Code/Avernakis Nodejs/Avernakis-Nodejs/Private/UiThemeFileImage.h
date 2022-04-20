#pragma once

#include "UiThemeFile.h"

namespace Nav
{

	class UiThemeImage;

	class UiThemeFileImage : public UiThemeFile, public WrapObject<UiThemeFileImage, void()>
	{
		friend class UiThemeFile;

	public:
		AveWrapObject( UiThemeFileImage );

		static PCAChar				GetExportName() { return "UiThemeFileImage"; }
		static void					DefineObject();

		U1							Ctor();

	private:
		virtual Napi::Value			GetObjectValue( Napi::Env env ) override { return __GetObjectValue( env ); }

		virtual Ui::IThemeFile&		GetThemeFile() const { return *m_File; }

	private:
		Ui::ThemeFileImage			m_File;

	private:
		UiThemeImage*				CreateTheme( const CallbackInfo& ci );
	};

}
