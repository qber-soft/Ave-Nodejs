#include "StdAfx.h"
#include "ImgImage.h"

#define ThisMethod($x) &ImgImage::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, ThisMethod( $x ) )

namespace Nav
{

	namespace
	{
		ObjectRegister<ImgImage> c_obj;
	}

	void ImgImage::DefineObject()
	{
		AutoAddMethod( CreateFromMeta );
		AutoAddMethod( CreateFromMetaArray );
		AutoAddMethod( Create1D );
		AutoAddMethod( Create2D );
		AutoAddMethod( Create3D );
		AutoAddMethod( CreateCube );

		AutoAddMethod( CreateFromImage );
		AutoAddMethod( CreateFromImages );
		AutoAddMethod( CreateCheckerGrid );

		AutoAddMethod( GetMetadataCount );
		AutoAddMethod( GetMetadata );

		AutoAddMethod( GetIndexBySize2 );
		AutoAddMethod( GetIndexBySize );

		AutoAddMethod( GetAnimationInfo );
		AutoAddMethod( SetAnimationInfo );
		AutoAddMethod( GetFrameInfo );
		AutoAddMethod( SetFrameInfo );
		
		AutoAddMethod( GetImageCount );
		AutoAddMethod( GetImage );

		AutoAddMethod( Clone );

		AutoAddMethod( Blend );
		AutoAddMethod( CopyFrom );
		AutoAddMethod( CopyTo );
		AutoAddMethod( PremultiplyAlpha );
		AutoAddMethod( DetectAlpha );

		AutoAddMethod( FlipRotate );
		AutoAddMethod( Convert );
		AutoAddMethod( ComputeNormal );

		AutoAddMethod( Resize );

		AutoAddMethod( GenerateMipMaps );
	}

	U1 ImgImage::Ctor()
	{
		if ( !m_Image.Create() )
			return false;

		return true;
	}

	U1 ImgImage::CreateFromMetaArray( const List<WrapData<Img::Metadata>>& md )
	{
		if ( md.IsEmpty() )
			return false;
		List<Img::Metadata> v;
		v.Reserve( md.Size() );
		for ( auto& i : md )
			v.Add( i );
		return m_Image->CreateFromMetaArray( v.Data(), (U32) v.Size() );
	}

	U1 ImgImage::CreateFromImage( Img::Dimension nDimension, const WrapData<ImgImageData>& pImage )
	{
		if ( pImage.m_Data.m_Null )
			return false;
		return m_Image->CreateFromImage( nDimension, pImage.ToImageData() );
	}

	U1 ImgImage::CreateFromImages( Img::Dimension nDimension, const List<WrapData<ImgImageData>>& vImage, U1 bIsCube )
	{
		if ( vImage.IsEmpty() || bIsCube && 0 != (vImage.Size() % 6) )
			return false;
		List<Img::ImageData> v;
		v.Reserve( vImage.Size() );
		for ( auto& i : vImage )
			v.Add( i.ToImageData() );
		return m_Image->CreateFromImages( nDimension, v.Data(), v.Size(), bIsCube );
	}

	U1 ImgImage::CreateCheckerGrid( Img::PixFormat nFormat, Img::Dimension nDimension, U32 nImageSize, U32 nGridSize, const WrapData<R32_4>& vColor0, const WrapData<R32_4>& vColor1 )
	{
		auto img = AveKak.Create<Img::IImage>();
		if ( !img )
			return false;
		if ( !img->Create1D( Img::PixFormat::R32G32B32A32_FLOAT, 2, 1, 1 ) )
			return false;
		auto data = img->GetImage( 0, 0 );
		auto& p = *(R32_4(*)[2]) data->m_Data;
		p[0] = vColor0;
		p[1] = vColor1;
		img = img->Convert( nFormat );
		if ( !img )
			return false;
		data = img->GetImage( 0, 0 );
		return m_Image->CreateCheckerGrid( nFormat, nDimension, nImageSize, nGridSize, data->Offset2D( 0, 0 ), data->Offset2D( 0, 1 ) );
	}

	List<WrapData<Img::AnimationFrame>> ImgImage::GetFrameInfo() const
	{
		List<Img::AnimationFrame> vData( m_Image->GetAnimationInfo().m_FrameCount );
		if ( vData.IsEmpty() )
			return {};
		if ( !m_Image->GetFrameInfo( vData.Data(), (U32) vData.Size() ) )
			return {};

		List<WrapData<Img::AnimationFrame>> v;
		v.Reserve( vData.Size() );
		for ( auto& i : vData )
			v.Add( i );
		return std::move( v );
	}

	U1 ImgImage::SetFrameInfo( const List<WrapData<Img::AnimationFrame>>& pFrame )
	{
		if ( pFrame.Size() != m_Image->GetAnimationInfo().m_FrameCount )
			return false;
		List<Img::AnimationFrame> vData;
		vData.Reserve( pFrame.Size() );
		for ( auto& i : pFrame )
			vData.Add( i );
		return m_Image->SetFrameInfo( vData.Data(), (U32) vData.Size() );
	}

	WrapData<ImgImageData> ImgImage::GetImage( U32 nMip, U32 nArrayItem, U32 nIndex ) const
	{
		auto p = m_Image->GetImage( nIndex, nArrayItem, nIndex );
		if ( !p )
			return {};
		return ImgImageData::FromImageData( *p );
	}

	ImgImage * ImgImage::Clone( const CallbackInfo & ci ) const
	{
		if ( auto p = ci.NewJsObject<ImgImage>() )
		{
			p->m_Image = m_Image->Clone();
			return p;
		}
		return nullptr;
	}

	U1 ImgImage::Blend( U32 nDestSubresource, U32 nDestX, U32 nDestY, U32 nDestZ, const WrapData<ImgImageData>& pSrc, const WrapData<Img::BlendOption>& opt, const WrapData<Img::Box>& pSrcBox, U32 nDestIndex )
	{
		return m_Image->Blend( nDestIndex, nDestX, nDestY, nDestZ, pSrc.ToImageData(), opt, __IsBoxEmpty( pSrcBox ) ? nullptr : &pSrcBox, 0, nDestIndex );
	}

	U1 ImgImage::CopyFrom( U32 nDestSubresource, U32 nDestX, U32 nDestY, U32 nDestZ, const WrapData<ImgImageData>& pSrc, const WrapData<Img::Box>& pSrcBox, U32 nDestIndex )
	{
		return m_Image->CopyFrom( nDestSubresource, nDestX, nDestY, nDestZ, pSrc.ToImageData(), __IsBoxEmpty( pSrcBox ) ? nullptr : &pSrcBox, 0, nDestIndex );
	}

	WrapData<ImgImageData> ImgImage::CopyTo( const WrapData<ImgImageData>& pDest, U32 nDestX, U32 nDestY, U32 nDestZ, U32 nSrcSubresource, const WrapData<Img::Box>& pSrcBox, U32 nSrcIndex ) const
	{
		WrapData<ImgImageData> r = pDest;
		auto data = r.ToImageData();
		if ( m_Image->CopyTo( data, nDestX, nDestY, nDestZ, nSrcSubresource, __IsBoxEmpty( pSrcBox ) ? nullptr : &pSrcBox, 0, nSrcIndex ) )
			return std::move( r );
		return {};
	}

}
