#include "StdAfx.h"
#include "IoStream.h"

#define ThisMethod($x) &IoStream::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, ThisMethod( $x ) )

namespace Nav
{

	namespace
	{
		ObjectRegister<IoStream> c_obj;
	}

	void IoStream::DefineObject()
	{
		AutoAddMethod( Truncate );
		AutoAddMethod( Flush );
		AutoAddMethod( Size );
		AutoAddMethod( Seek );
		AutoAddMethod( ReadBinary );
		AutoAddMethod( WriteBinary );
	}

	ArrayBuffer IoStream::ReadBinary( U32 nSize )
	{
		ArrayBuffer rb;
		rb.m_Data.Resize( nSize );
		if ( !rb.m_Data.IsEmpty() )
		{
			U32 nRead;
			if ( m_Stream->ReadBinary( rb.m_Data.Data(), nSize, nRead ) )
				rb.m_Data.Resize( nRead );
			else
				rb.m_Null = true;
		}
		return rb;
	}

	U32 IoStream::WriteBinary( const WrapArray<U8>& pData )
	{
		if ( !pData || 0 == pData.m_Length )
			return 0;
		U32 nWritten;
		if ( !m_Stream->WriteBinary( pData, (U32) pData.m_Length, nWritten ) )
			return 0;
		return nWritten;
	}

}
