#include "StdAfx.h"
#include "ImgCodec.h"
#include "ImgCommon.h"
#include "ImgImage.h"

#define ThisMethod($x) &ImgCodec::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &ImgCodec::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<ImgCodec> c_obj;
	}

	void ImgCodec::DefineObject()
	{
		AutoAddMethod( Open );
		AutoAddMethod( GetMetadata );
		AutoAddMethod( SaveFile );
		AutoAddMethod( SaveArrayBuffer );
	}

	U1 ImgCodec::Ctor()
	{
		m_Loader = &App::GetSingleton().GetImageLoader();

		m_Container.Resize( (S32) ImgContainerType::__Count );
		m_Container[(U32) ImgContainerType::AVE].m_Guid = AveGuidOf( Ave::Img::IContainer_AveImage );
		m_Container[(U32) ImgContainerType::BMP].m_Guid = AveGuidOf( Ave::Img::IContainer_BMP );
		m_Container[(U32) ImgContainerType::JPG].m_Guid = AveGuidOf( Ave::Img::IContainer_JPG );
		m_Container[(U32) ImgContainerType::PNG].m_Guid = AveGuidOf( Ave::Img::IContainer_PNG );
		m_Container[(U32) ImgContainerType::DDS].m_Guid = AveGuidOf( Ave::Img::IContainer_DDS );
		m_Container[(U32) ImgContainerType::TGA].m_Guid = AveGuidOf( Ave::Img::IContainer_TGA );
		m_Container[(U32) ImgContainerType::TIF].m_Guid = AveGuidOf( Ave::Img::IContainer_TIF );
		m_Container[(U32) ImgContainerType::GIF].m_Guid = AveGuidOf( Ave::Img::IContainer_GIF );

		return true;
	}

	ImgImage * ImgCodec::Open( const CallbackInfo & ci, const WrapData<IoResourceSource>& rs )
	{
		if ( auto ps = App::GetSingleton().OpenResourceAsStream( rs ) )
		{
			if ( auto img = m_Loader->Open( *ps ) )
			{
				if ( auto js = ci.NewJsObject<ImgImage>() )
				{
					js->SetImage( std::move( img ) );
					return js;
				}
			}
		}
		return nullptr;
	}

	WrapData<Img::Metadata> ImgCodec::GetMetadata( const WrapData<IoResourceSource>& rs )
	{
		if ( auto ps = App::GetSingleton().OpenResourceAsStream( rs ) )
		{
			Img::Metadata md;
			if ( m_Loader->GetMetadata( *ps, md ) )
				return md;
		}
		return {};
	}

	U1 ImgCodec::SaveFile( PCWChar szFile, ImgImage * img, ImgContainerType nType )
	{
		if ( (U32) nType >= m_Container.Size() )
			return false;
		auto& c = m_Container[(U32) nType];
		if ( !c.m_Container )
		{
			c.m_Container = AveKak.CreateWithGuid<Img::IContainer>( c.m_Guid );
			if ( !c.m_Container )
				return false;
		}
		return c.m_Container->Save( *img->Get(), szFile );
	}

	ArrayBuffer ImgCodec::SaveArrayBuffer( PCWChar szFile, ImgImage * img, ImgContainerType nType )
	{
		ArrayBuffer ab{};
		ab.m_Null = true;
		if ( (U32) nType >= m_Container.Size() )
			return std::move( ab );
		auto& c = m_Container[(U32) nType];
		if ( !c.m_Container )
		{
			c.m_Container = AveKak.CreateWithGuid<Img::IContainer>( c.m_Guid );
			if ( !c.m_Container )
				return std::move( ab );
		}
		Io::StreamListDirect sld( ab.m_Data );
		if ( !c.m_Container->Save( *img->Get(), sld ) )
			return std::move( ab );
		ab.m_Null = false;
		return std::move( ab );
	}

}
