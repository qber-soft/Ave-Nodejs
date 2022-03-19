#pragma once

#include "WrapObject.h"

namespace Nav
{
	class Test : public WrapObject<Test, void( S32, S32 )>
	{
	public:
		AveWrapObject( Test );

		static PCAChar	GetExportName() { return "Test"; }
		static void		DefineObject();

		U1				Ctor( S32 x, S32 y );

	private:
		S32_2			m_Pos{ NT<S32_2>::Zero };

	private:
		void			SetX( S32 x );
		void			SetY( S32 y );
		S32				GetX() const;
		S32				GetY() const;

		WString			TestString( PCWChar szMessage ) const;

		WString			ShowTestWindow();

		void			ThrowJsException( const CallbackInfo& ci, S32 x );
	};
}
