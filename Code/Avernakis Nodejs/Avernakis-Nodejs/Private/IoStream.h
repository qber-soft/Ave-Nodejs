#pragma once

#include "WrapObject.h"
#include "WrapData.h"

namespace Nav
{

	class IoStream : public WrapObject<IoStream, void()>
	{
	public:
		AveWrapObject( IoStream );

		static PCAChar						GetExportName() { return "c6595b89d1b14e049b48eb86037f4c0d"; }
		static void							DefineObject();

		U1									Ctor() { return true; }
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Io::AveStream						m_Stream;

	private:

	private:
		U1									Truncate() { return m_Stream->Truncate(); }
		U1									Flush() { return m_Stream->Flush(); }

		Io::StreamSize_t					Size() const { return m_Stream->Size(); }
		Io::StreamSize_t					Seek( Io::StreamSize_t nPos, Io::SeekMode nSeekMode ) const { return m_Stream->Seek( nPos, nSeekMode ); }

		ReturnBuffer						ReadBinary( U32 nSize );
		U32									WriteBinary( const WrapArray<U8>& pData );

	public:
		AveInline void						SetStream( Io::AveStream&& p ) { m_Stream = std::move( p ); }
	};
}
