#pragma once

#include "ImgCommon.h"

namespace Nav
{

	class ImgImage : public WrapObject<ImgImage, void()>
	{
	public:
		AveWrapObject( ImgImage );

		static PCAChar						GetExportName() { return "ImgImage"; }
		static void							DefineObject();

		U1									Ctor();
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Img::Image							m_Image;

	private:
		U1									CreateFromMeta( const WrapData<Img::Metadata>& md ) { return m_Image->CreateFromMeta( md ); }
		U1									CreateFromMetaArray( const List<WrapData<Img::Metadata>>& md );
		U1									Create1D( Img::PixFormat nFormat, U32 nLength, U32 nArray, U32 nMipLevel ) { return m_Image->Create1D( nFormat, nLength, nArray, nMipLevel ); }
		U1									Create2D( Img::PixFormat nFormat, U32 nWidth, U32 nHeight, U32 nArray, U32 nMipLevel ) { return m_Image->Create2D( nFormat, nWidth, nHeight, nArray, nMipLevel ); }
		U1									Create3D( Img::PixFormat nFormat, U32 nWidth, U32 nHeight, U32 nDepth, U32 nMipLevel ) { return m_Image->Create3D( nFormat, nWidth, nHeight, nDepth, nMipLevel ); }
		U1									CreateCube( Img::PixFormat nFormat, U32 nLength, U32 nArray, U32 nMipLevel ) { return m_Image->CreateCube( nFormat, nLength, nArray, nMipLevel ); }

		U1									CreateFromImage( Img::Dimension nDimension, const WrapData<ImgImageData>& pImage );
		U1									CreateFromImages( Img::Dimension nDimension, const List<WrapData<ImgImageData>>& vImage, U1 bIsCube );
		U1									CreateCheckerGrid( Img::PixFormat nFormat, Img::Dimension nDimension, U32 nImageSize, U32 nGridSize, const WrapData<R32_4>& vColor0, const WrapData<R32_4>& vColor1 );

		U32									GetMetadataCount() const { return m_Image->GetMetadataCount(); }
		WrapData<Img::Metadata>				GetMetadata( U32 nIndex ) const { return m_Image->GetMetadata( nIndex ); }
		WrapData<Img::AnimationInfo>		GetAnimationInfo() const { return m_Image->GetAnimationInfo(); }
		void								SetAnimationInfo( const WrapData<Img::AnimationInfo>& ai ) { return m_Image->SetAnimationInfo( ai ); }
		List<WrapData<Img::AnimationFrame>>	GetFrameInfo() const;
		U1									SetFrameInfo( const List<WrapData<Img::AnimationFrame>>& pFrame );

		U32									GetImageCount() const { return m_Image->GetImageCount(); }
		WrapData<ImgImageData>				GetImage( U32 nMip, U32 nArrayItem, U32 nIndex ) const;

		ImgImage*							Clone( const CallbackInfo& ci ) const;

		U1									Blend( U32 nDestSubresource, U32 nDestX, U32 nDestY, U32 nDestZ, const WrapData<ImgImageData>& pSrc, const WrapData<Img::BlendOption>& opt, const WrapData<Img::Box>& pSrcBox, U32 nDestIndex );
		U1									CopyFrom( U32 nDestSubresource, U32 nDestX, U32 nDestY, U32 nDestZ, const WrapData<ImgImageData>& pSrc, const WrapData<Img::Box>& pSrcBox, U32 nDestIndex );
		WrapData<ImgImageData>				CopyTo( const WrapData<ImgImageData>& pDest, U32 nDestX, U32 nDestY, U32 nDestZ, U32 nSrcSubresource, const WrapData<Img::Box>& pSrcBox, U32 nSrcIndex ) const;
		U1									PremultiplyAlpha() { return m_Image->PremultiplyAlpha(); }
		U1									DetectAlpha() const { return m_Image->DetectAlpha(); }

		ImgImage*							FlipRotate( const CallbackInfo& ci, U1 bFlipX, U1 bFlipY, U1 bFlipZ, Img::RotateType nRotateZ, Img::RotateType nRotateX, Img::RotateType nRotateY ) const { return __ReturnImage( ci, m_Image->FlipRotate( bFlipX, bFlipY, bFlipZ, nRotateZ, nRotateX, nRotateY ) ); }
		ImgImage*							Convert( const CallbackInfo& ci, Img::PixFormat nFormat, R32 fAlphaRef ) const { return __ReturnImage( ci, m_Image->Convert( nFormat, fAlphaRef ) ); }
		ImgImage*							ComputeNormal( const CallbackInfo& ci, Img::PixFormat nFormat, Img::Channel nChannel, R32 fAmplitude ) const { return __ReturnImage( ci, m_Image->ComputeNormal( nFormat, nChannel, fAmplitude ) ); }

		ImgImage*							Resize( const CallbackInfo& ci, U32 nWidth, U32 nHeight, Img::FilterType nFilter ) const { return __ReturnImage( ci, m_Image->Resize( nWidth, nHeight, nFilter ) ); }

		ImgImage*							GenerateMipMaps( const CallbackInfo& ci, U32 nLevels, Img::FilterType nFilter, U1 bIndependent3DSlice ) const { return __ReturnImage( ci, m_Image->GenerateMipMaps( nLevels, nFilter, 0, bIndependent3DSlice ) ); }

	private:
		static AveInline U1					__IsBoxEmpty( const Img::Box& box ) { return 0 == box.m_Left && 0 == box.m_Top && 0 == box.m_Front && 0 == box.m_Right && 0 == box.m_Bottom && 0 == box.m_Back; }

		static AveInline ImgImage* __ReturnImage( const CallbackInfo& ci, Img::Image&& img )
		{
			if ( img )
			{
				if ( auto p = ci.NewJsObject<ImgImage>() )
				{
					p->m_Image = std::move( img );
					return p;
				}
			}
			return nullptr;
		}

	public:
		AveInline Img::IImage*				Get() { return m_Image; }
		AveInline Img::Image				CloneImage() { return m_Image; }
		AveInline void						SetImage( Img::Image&& img ) { m_Image = std::move( img ); }
	};
}
