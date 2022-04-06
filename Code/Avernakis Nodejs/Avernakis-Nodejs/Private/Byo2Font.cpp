#include "StdAfx.h"
#include "Byo2Font.h"
#include "UiWindow.h"

#define ThisMethod($x) &Byo2Font::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, ThisMethod( $x ) )

namespace Nav
{

	namespace
	{
		ObjectRegister<Byo2Font> c_obj;
	}

	void Byo2Font::DefineObject()
	{
		AutoAddMethod( GetAscent );
		AutoAddMethod( GetDescent );
		AutoAddMethod( GetHeight );
		AutoAddMethod( GetWidth );
		AutoAddMethod( GetLeadingExternal );
		AutoAddMethod( GetLeadingInternal );

		AutoAddMethod( SetReadingDirection );
		AutoAddMethod( GetReadingDirection );

		AutoAddMethod( SetFlowDirection );
		AutoAddMethod( GetFlowDirection );

		AutoAddMethod( Measure );
	}

	U1 Byo2Font::Ctor( UiWindow* p, const WrapData<UiFontDescription>& c )
	{
		UiFontDescriptionByo2 f2;
		f2.FromJs( c, p->PublicGetWindow().GetDevice().GetResourceManager() );
		m_Font = p->PublicGetWindow().GetDevice().GetFactory().Create<Byo2::IFont>( f2.m_FontDesc );
		if ( !m_Font )
			return false;

		return true;
	}

	List<R32> Byo2Font::Measure( PCWChar szText ) const
	{
		List<R32> v( AveStr.Length( szText ) );
		m_Font->Measure( szText, v.Data() );
		return std::move( v );
	}

}
