#pragma once

#include "UiVisualHelper.h"

namespace Nav
{

	class Byo2Image;

	class UiPicture : public UiVisualHelper<UiPicture, Ui::IPicture>
	{
	public:
		AveWrapVisual( UiPicture );

		~UiPicture()
		{
		}

		static PCAChar					GetExportName() { return "UiPicture"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:

	private:
		UiPicture*						SetStretchMode( Ui::StretchMode nMode ) { GetControlTyped().SetStretchMode( nMode ); return this; }
		Ui::StretchMode					GetStretchMode() const { return GetControlTyped().GetStretchMode(); }

		UiPicture*						SetPicture( const WrapData<UiResourceSource>& rs ) { GetControlTyped().SetPicture( rs.ToResourceSource() ); return this; }

		void							SetImage( Byo2Image* img );

	};
}
