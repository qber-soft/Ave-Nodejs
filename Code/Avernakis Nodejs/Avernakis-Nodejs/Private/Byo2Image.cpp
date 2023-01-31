#include "StdAfx.h"
#include "Byo2Image.h"
#include "UiWindow.h"

#define ThisMethod($x) &Byo2Image::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, ThisMethod( $x ) )

namespace Nav
{

	namespace
	{
		ObjectRegister<Byo2Image> c_obj;
	}

	void Byo2Image::DefineObject()
	{
		AutoAddMethod( GetWidth );
		AutoAddMethod( GetHeight );
		AutoAddMethod( Invalidate );
		AutoAddMethod( Prepare );
		AutoAddMethod( Upload );

		AutoAddMethod( SetOpacity );
		AutoAddMethod( SetTransform );
		AutoAddMethod( SetAddress );
		AutoAddMethod( SetFilter );
	}

	U1 Byo2Image::Ctor( UiWindow* p, const WrapData<Byo2ImageCreation>& c )
	{
		Byo2::IImage::CreationParam cp{};
		cp.m_DataType = c.m_DataType;
		cp.m_Data = c.m_Data.ToResourceSource();
		cp.m_Width = c.m_Width;
		cp.m_Height = c.m_Height;
		cp.m_Format = c.m_Format;
		m_Image = p->PublicGetWindow().GetDevice().GetFactory().Create<Byo2::IImage>( cp );
		if ( !m_Image )
			return false;

		return true;
	}

}
