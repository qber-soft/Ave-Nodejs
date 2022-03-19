#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiWindow;

	template<class T, class TControl, U1 TDefineObject = true>
	class UiVisualHelper : public UiControlHelper<T, TControl, UiVisual, TDefineObject>
	{
	protected:
		UiVisualHelper( const Napi::CallbackInfo& cb ) : UiControlHelper<T, TControl, UiVisual, TDefineObject>( cb )
		{
		}
	};

#define AveWrapVisual($x) friend class UiControl; $x( const Napi::CallbackInfo& cb ) : UiVisualHelper( cb ) { __Ctor( cb ); }

}
