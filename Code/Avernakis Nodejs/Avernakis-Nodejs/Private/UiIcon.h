#pragma once

#include "UiVisualHelper.h"

namespace Nav
{

	class UiIcon : public UiVisualHelper<UiIcon, Ui::IIcon, false>
	{
	public:
		AveWrapVisual( UiIcon );

		static PCAChar					GetExportName() { return "d99d5f57b3914526af888bf75d19e84d"; }
		static void						DefineObject() {}

		U1								Ctor() { return true; }

	private:

	private:

	public:
		AveInline UiIcon*				SetIcon( Ui::Icon&& icon ) { GiveControl( std::move( icon ) ); return this; }
	};

}
