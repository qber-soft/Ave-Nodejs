#include "StdAfx.h"
#include "UiPicture.h"
#include "Byo2Image.h"
#include "ImgImage.h"

#define ThisMethod($x) &UiPicture::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiPicture::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiPicture> c_obj;
	}

	void UiPicture::DefineControl()
	{
		AutoAddMethod( SetStretchMode );
		AutoAddMethod( GetStretchMode, WrapObjectGeneric );
		
		AutoAddMethod( SetImageFilter );
		AutoAddMethod( GetImageFilter, WrapObjectGeneric );

		AutoAddMethod( SetPicture );
		AutoAddMethod( SetImageData );
		AutoAddMethod( SetImage );

		AutoAddMethod( GetAnimationInfo, WrapObjectGeneric );
		AutoAddMethod( GetDuration, WrapObjectGeneric );

		AutoAddMethod( Play, WrapObjectGeneric );
		AutoAddMethod( Stop, WrapObjectGeneric );
		AutoAddMethod( IsPlaying, WrapObjectGeneric );

		AutoAddMethod( SetPlayPosition );
		AutoAddMethod( GetPlayPosition, WrapObjectGeneric );
		
		AutoAddMethod( SetPlayFrame );
		AutoAddMethod( GetPlayFrame, WrapObjectGeneric );
	}

	U1 UiPicture::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		return true;
	}

	UiPicture * UiPicture::SetImageData( ImgImage * img )
	{
		GetControlTyped().SetImageData( img->CloneImage() );
		return this;
	}

	UiPicture * UiPicture::SetImage( Byo2Image * img )
	{
		GetControlTyped().SetImage( img->CloneImage() );
		return this;
	}

	WrapData<Img::AnimationInfo> UiPicture::GetAnimationInfo() const
	{
		return GetControlTyped().GetAnimationInfo();
	}

}
