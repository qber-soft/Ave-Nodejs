#pragma once

#include "WrapObject.h"

namespace Nav
{

	class Empty : public WrapObject<Empty, void()>
	{
	public:
		AveWrapObject( Empty );

		static PCAChar	GetExportName() { return "__Empty__"; }
		static void		DefineObject();

		U1				Ctor();

	};

}
