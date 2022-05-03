#pragma once

#include "UiVisualHelper.h"
#include "IoCommon.h"

namespace Nav
{

	class ImgImage;
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

		UiPicture*						SetImageFilter( Byo2::DrawImageFilter nFilter ) { GetControlTyped().SetImageFilter( nFilter ); return this; }
		Byo2::DrawImageFilter 			GetImageFilter() const { return GetControlTyped().GetImageFilter(); }

		UiPicture*						SetPicture( const WrapData<IoResourceSource>& rs ) { GetControlTyped().SetPicture( rs.ToResourceSource() ); return this; }
		UiPicture*						SetImageData( ImgImage* img );
		UiPicture*						SetImage( Byo2Image* img );

		WrapData<Img::AnimationInfo>	GetAnimationInfo() const;
		R64								GetDuration() const { return GetControlTyped().GetDuration(); }

		UiPicture*						Play() { GetControlTyped().Play(); return this; }
		UiPicture*						Stop() { GetControlTyped().Stop(); return this; }
		U1								IsPlaying() const { return GetControlTyped().IsPlaying(); }

		UiPicture*						SetPlayPosition( R64 fTime ) { GetControlTyped().SetPlayPosition( fTime ); return this; }
		R64								GetPlayPosition() const { return GetControlTyped().GetPlayPosition(); }

		UiPicture*						SetPlayFrame( U32 nFrame ) { GetControlTyped().SetPlayFrame( nFrame ); return this; }
		U32								GetPlayFrame() const { return GetControlTyped().GetPlayFrame(); }
	};
}
