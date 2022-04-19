#include "StdAfx.h"
#include "UiThemeFile.h"
#include "UiTheme.h"

namespace Nav
{
	
	UiThemeType UiThemeFile::GetThemeType() const
	{
		auto& t = GetThemeFile().GetThemeType();
		if ( t == AveGuidOf( Ui::IThemeFileImage ) )
			return UiThemeType::Image;
		else
			return UiThemeType::Unknown;
	}
	
	U1 UiThemeFile::Open( const WrapData<IoResourceSource>& rs )
	{
		if ( auto p = App::GetSingleton().OpenResourceAsStream( rs ) )
			return GetThemeFile().Open( *p );
		return false;
	}
	
	U1 UiThemeFile::SetTheme( WrapPointer<UiTheme> pTheme, U32 nTargetStyle )
	{
		if ( !pTheme )
			return false;
		return GetThemeFile().SetTheme( pTheme->GetTheme(), nTargetStyle );
	}

}
