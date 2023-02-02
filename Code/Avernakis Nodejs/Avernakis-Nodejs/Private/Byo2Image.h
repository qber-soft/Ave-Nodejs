#pragma once

#include "UiCommon.h"
#include "IoCommon.h"

namespace Nav
{

	class UiWindow;

	class Byo2ImageCreation
	{
	public:
		Byo2::ImageDataType					m_DataType;
		WrapData<IoResourceSource>			m_Data;
		S32									m_Width;
		S32									m_Height;
		Img::PixFormat						m_Format;
	};

	NavDefineDataByMember_( Byo2ImageCreation, DataType, Data, Width, Height, Format );

	class Byo2Image : public WrapObject<Byo2Image, void( UiWindow*, const WrapData<Byo2ImageCreation>& )>
	{
	public:
		AveWrapObject( Byo2Image );

		static PCAChar						GetExportName() { return "Byo2Image"; }
		static void							DefineObject();

		U1									Ctor( UiWindow* p, const WrapData<Byo2ImageCreation>& c );
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Byo2::Image							m_Image;

	private:
		U32									GetWidth() const { return m_Image->GetWidth(); }
		U32									GetHeight() const { return m_Image->GetHeight(); }
		void								Invalidate() { m_Image->Invalidate(); }
		void								Prepare( U1 bIncludeGrayed ) { m_Image->Prepare( bIncludeGrayed ); }
		void								Upload( const WrapData<S32_R>& rc, const WrapData<InMemoryData>& pData ) { m_Image->Upload( rc.IsEmpty() ? nullptr : &rc, { pData.m_Data.m_Pointer, pData.m_RowPitch, pData.m_SlicePitch } ); }

		void								SetOpacity( R32 fAlpha ) { m_Image->SetOpacity( fAlpha ); }
		void								SetTransform( const WrapData<R32_3x2>& m ) { m_Image->SetTransform( m ); }
		void								SetAddress( Byo2::DrawImageAddress nAddr ) { m_Image->SetAddress( nAddr ); }
		void								SetFilter( Byo2::DrawImageFilter nFilter ) { m_Image->SetFilter( nFilter ); }

	public:
		Byo2::IImage*						GetImage() { return m_Image; }
		Byo2::Image							CloneImage() { return m_Image; }
	};
}
