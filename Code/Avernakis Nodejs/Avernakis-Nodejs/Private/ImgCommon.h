#pragma once

#include "Common.h"

namespace Nav
{

	NavDefineDataByMember_( Img::Metadata, Width, Height, Depth, MipLevel, Format, Dimension, Flags );
	NavDefineDataByMember_( Img::AnimationInfo, FrameCount, RepeatCount );
	NavDefineDataByMember_( Img::AnimationFrame, DelaySecond );
	NavDefineDataByMember_( Img::Box, Left, Top, Front, Right, Bottom, Back );
	
	namespace __Detail
	{
		class ImgBlendOption
		{
		public:
			Img::BlendType							m_Src;
			Img::BlendType							m_Dest;
			Img::BlendOp							m_Op;
			Img::BlendType							m_AlphaSrc;
			Img::BlendType							m_AlphaDest;
			Img::BlendOp							m_AlphaOp;
			U32										m_WriteMask;
			WrapData<R32_4>							m_BlendFactor;
		};
	}

	NavDefineDataByMember_( __Detail::ImgBlendOption, Src, Dest, Op, AlphaSrc, AlphaDest, AlphaOp, WriteMask, BlendFactor );
	NavDefineTransitByMember_( Img::BlendOption, __Detail::ImgBlendOption, Src, Dest, Op, AlphaSrc, AlphaDest, AlphaOp, WriteMask, BlendFactor );

	class ImgImageData
	{
	public:
		U32							m_Width{ 0 };
		U32							m_Height{ 0 };
		U32							m_Depth{ 0 };
		Img::PixFormat				m_Format{ Img::PixFormat::UNKNOWN };
		U32							m_RowPitch{ 0 };
		U32							m_SlicePitch{ 0 };
		ArrayBuffer					m_Data{ {}, true };

		AveInline Img::ImageData ToImageData() const
		{
			Img::ImageData data{};
			data.m_Width = m_Width;
			data.m_Height = m_Height;
			data.m_Depth = m_Depth;
			data.m_Format = m_Format;
			data.m_RowPitch = m_RowPitch;
			data.m_SlicePitch = m_SlicePitch;
			data.m_Data = (U8*) m_Data.m_Data.Data();
			return data;
		}

		static AveInline ImgImageData FromImageData( const Img::ImageData& data )
		{
			ImgImageData r{};
			r.m_Width = data.m_Width;
			r.m_Height = data.m_Height;
			r.m_Depth = data.m_Depth;
			r.m_Format = data.m_Format;
			r.m_RowPitch = data.m_RowPitch;
			r.m_SlicePitch = data.m_SlicePitch;
			r.m_Data.m_Data.Resize( data.m_SlicePitch * data.m_Depth );
			AveCopyMemoryAuto( r.m_Data.m_Data.Data(), data.m_Data, r.m_Data.m_Data.DataSize() );
			r.m_Data.m_Null = false;
			return std::move( r );
		}
	};

	NavDefineDataByMember_( ImgImageData, Width, Height, Depth, Format, RowPitch, SlicePitch, Data );

}
