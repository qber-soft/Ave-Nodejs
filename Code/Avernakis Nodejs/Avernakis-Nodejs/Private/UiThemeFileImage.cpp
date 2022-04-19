#include "StdAfx.h"
#include "UiThemeFileImage.h"
#include "UiThemeImage.h"
#include "Common.h"

#define ThisMethod($x) &UiThemeFileImage::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, ThisMethod( $x ) )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiThemeFileImage> c_obj;
	}

	void UiThemeFileImage::DefineObject()
	{
		UiThemeFile::__DefineObject<UiThemeFileImage>();

		AutoAddMethod( CreateTheme );
	}

	U1 UiThemeFileImage::Ctor()
	{
		m_File = AveKak.Create<Ui::IThemeFileImage>();
		if ( !m_File )
			return false;

		return true;
	}

	UiThemeImage * UiThemeFileImage::CreateTheme( const CallbackInfo& ci )
	{
		if ( auto theme = Ui::ThemeImage( (Ui::IThemeImage*) m_File->CreateTheme().Detach(), false ) )
		{
			if ( auto js = ci.NewJsObject<UiThemeImage>() )
			{
				js->SetTheme( std::move( theme ) );
				return js;
			}
		}
		return nullptr;
	}

}
