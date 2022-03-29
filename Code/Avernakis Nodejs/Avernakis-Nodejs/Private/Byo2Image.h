#pragma once

#include "UiCommon.h"

namespace Nav
{

	class UiWindow;

	class Byo2ImageCreation
	{
	public:
		Byo2::ImageDataType					m_DataType;
		WrapData<UiResourceSource>			m_Data;
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
		void								Upload( const WrapData<S32_R>& rc, const WrapData<InMemoryData>& pData ) { m_Image->Upload( rc.IsEmpty() ? nullptr : &rc, { pData.m_Data.m_Pointer, pData.m_RowPitch, pData.m_SlicePitch } ); }

	public:
		Byo2::Image							CloneImage() { return m_Image; }
	};
}
