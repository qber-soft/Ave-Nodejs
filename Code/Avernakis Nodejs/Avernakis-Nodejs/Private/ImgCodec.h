#pragma once

#include "IoCommon.h"

namespace Nav
{

	class ImgImage;

	enum class ImgContainerType
	{
		AVE = 0,
		BMP = 1,
		JPG = 2,
		PNG = 3,
		DDS = 4,
		TGA = 5,
		TIF = 6,
		GIF = 7,

		__Count,
	};

	class ImgCodec : public WrapObject<ImgCodec, void()>
	{
	public:
		AveWrapObject( ImgCodec );

		static PCAChar						GetExportName() { return "ff5defcbefba417e8434652b7a736fcb"; }
		static void							DefineObject();

		U1									Ctor();
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		class ContainerItem
		{
		public:
			ImgContainerType				m_Type;
			Guid							m_Guid;
			Img::Container					m_Container;
		};

		using Container_t = List<ContainerItem>;

		Img::ILoader*						m_Loader;
		Container_t							m_Container;

	private:
		ImgImage*							Open( const CallbackInfo& ci, const WrapData<IoResourceSource>& rs );
		WrapData<Img::Metadata>				GetMetadata( const WrapData<IoResourceSource>& rs );

		U1									SaveFile( PCWChar szFile, ImgImage* img, ImgContainerType nType );
		ArrayBuffer							SaveArrayBuffer( ImgImage* img, ImgContainerType nType );

	};

}
