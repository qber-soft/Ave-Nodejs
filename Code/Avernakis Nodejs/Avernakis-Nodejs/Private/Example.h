#pragma once

#include "WrapObject.h"

namespace Nav
{
	class Example : public WrapObject<Example, void()>
	{
	public:
		AveWrapObject(Example);

		static PCAChar	GetExportName() { return "Example"; }
		static void		DefineObject();

		U1				Ctor();

	private:
		S32				GetX() const;
		void			TestThrowJsException(const CallbackInfo& ci);

	};
}
