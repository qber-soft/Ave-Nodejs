#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiPlaceholder : public UiControlHelper<UiPlaceholder, Ui::IPlaceholder>
	{
	public:
		AveWrapControl( UiPlaceholder );

		~UiPlaceholder()
		{
		}

		static PCAChar					GetExportName() { return "UiPlaceholder"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:

	private:
	};
}
