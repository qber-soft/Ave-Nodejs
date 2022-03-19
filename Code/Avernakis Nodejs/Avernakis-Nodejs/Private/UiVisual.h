#pragma once

#include "UiControl.h"

namespace Nav
{

	class UiVisual : public UiControl
	{
	public:
		AveInline Ui::Visual TakeVisual()
		{
			return Ui::Visual( (Ui::IVisual*) TakeOwnership().Detach() );
		}
	};

}
