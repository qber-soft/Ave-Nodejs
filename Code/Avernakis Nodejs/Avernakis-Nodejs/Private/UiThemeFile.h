#pragma once

#include "IoCommon.h"

namespace Nav
{

	enum class UiThemeType
	{
		Unknown = 0,
		Image = 1,
	};

	class UiTheme;

	class UiThemeFile
	{
	protected:
		UiThemeFile() {}
		~UiThemeFile() {}

	public:
		virtual Napi::Value			GetObjectValue( Napi::Env env ) = 0;

		virtual Ui::IThemeFile&		GetThemeFile() const = 0;

	protected:
		template<class T>
		static void __DefineObject()
		{
#		define AutoAddMethod($x, $y) T::template AddMethod<$y>( #$x, &T::$x )
			AutoAddMethod( GetThemeType, WrapObjectGeneric );
			AutoAddMethod( Open, WrapObjectGeneric );
			AutoAddMethod( SetTheme, WrapObjectUi );
#		undef AutoAddMethod
		}

	private:
		UiThemeType					GetThemeType() const;

		U1							Open( const WrapData<IoResourceSource>& rs );

		U1							SetTheme( WrapPointer<UiTheme> pTheme, U32 nTargetStyle );
	};

}
