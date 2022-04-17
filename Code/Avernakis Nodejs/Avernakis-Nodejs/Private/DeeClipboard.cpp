#include "StdAfx.h"
#include "DeeClipboard.h"

#include "IoStream.h"
#include "ImgImage.h"

#define ThisMethod($x) &DeeClipboard::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &DeeClipboard::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<DeeClipboard> c_obj;
		ObjectRegister<DeeClipboardVirtualFile> c_vf;
		ObjectRegister<DeeClipboardCopy> c_cp;
	}

	DeeClipboard* AveGetClipboard( const CallbackInfo& ci )
	{
		if ( auto cb = ci.NewJsObject<DeeClipboard>() )
		{
			cb->Ctor();
			return cb;
		}
		return nullptr;
	}

	//----------------------------------------------------------------------------------------------------
	// Virtual File
	//----------------------------------------------------------------------------------------------------

	void DeeClipboardVirtualFile::DefineObject()
	{
#	define __AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, &DeeClipboardVirtualFile::$x )
		__AutoAddMethod( GetCount );
		__AutoAddMethod( GetInfo );
		__AutoAddMethod( Open );
#	undef __AutoAddMethod
	}

	WrapData<IoFileFindItem> DeeClipboardVirtualFile::GetInfo( const CallbackInfo & cc, U32 nIndex ) const
	{
		IoFileFindItem r{};
		r.m_Info.m_Attribute = Io::FileAttribute::Invalid;
		Io::FileFinderItem<512> ffi;
		if ( m_File->GetInfo( nIndex, ffi ) )
		{
			r.m_Info.m_Size = ffi.m_Info.m_Size;
			r.m_Info.m_TimeCreate = ffi.m_Info.m_TimeCreate;
			r.m_Info.m_TimeModify = ffi.m_Info.m_TimeModify;
			r.m_Info.m_TimeAccess = ffi.m_Info.m_TimeAccess;
			r.m_Info.m_Attribute = ffi.m_Info.m_Attribute;
			r.m_Name = ffi.m_Name;
		}
		return r;
	}

	IoStream * DeeClipboardVirtualFile::Open( const CallbackInfo & cc, U32 nIndex ) const
	{
		if ( auto p = m_File->Open( nIndex ) )
		{
			if ( auto js = cc.NewJsObject<IoStream>() )
			{
				js->SetStream( std::move( p ) );
				return js;
			}
		}
		return nullptr;
	}

	//----------------------------------------------------------------------------------------------------
	// Copy
	//----------------------------------------------------------------------------------------------------

	void DeeClipboardCopy::DefineObject()
	{
#	define __AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, &DeeClipboardCopy::$x )
		__AutoAddMethod( Commit );
		__AutoAddMethod( SetText );
		__AutoAddMethod( SetImage );
		__AutoAddMethod( SetFile );
		__AutoAddMethod( AddFile );
		__AutoAddMethod( AddFiles );
#	undef __AutoAddMethod
	}

	void DeeClipboardCopy::SetImage( ImgImage * img ) const
	{
		m_Copy->SetImage( *img->Get() );
	}

	//----------------------------------------------------------------------------------------------------
	// Clipboard
	//----------------------------------------------------------------------------------------------------

	void DeeClipboard::DefineObject()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText );
		AutoAddMethod( HasText );

		AutoAddMethod( SetImage );
		AutoAddMethod( GetImage );
		AutoAddMethod( HasImage );

		AutoAddMethod( SetFile );
		AutoAddMethod( GetFile );
		AutoAddMethod( HasFile );

		AutoAddMethod( GetVirtualFile );
		AutoAddMethod( HasVirtualFile );

		AutoAddMethod( StartCopy );

		AddGlobalMethod( "AveGetClipboard", AveGetClipboard );
	}

	U1 DeeClipboard::Ctor()
	{
		m_Clip = &App::GetSingleton().GetClipboard();
		return true;
	}

	U1 DeeClipboard::SetImage( ImgImage * img ) const
	{
		return m_Clip->SetImage( *img->Get() );
	}

	ImgImage * DeeClipboard::GetImage( const CallbackInfo& ci ) const
	{
		if ( auto img = m_Clip->GetImage() )
		{
			if ( auto js = ci.NewJsObject<ImgImage>() )
			{
				js->SetImage( std::move( img ) );
				return js;
			}
		}
		return nullptr;
	}

	DeeClipboardVirtualFile * DeeClipboard::GetVirtualFile( const CallbackInfo & ci ) const
	{
		if ( auto vf = m_Clip->GetVirtualFile() )
		{
			if ( auto js = ci.NewJsObject<DeeClipboardVirtualFile>() )
			{
				js->SetFile( std::move( vf ) );
				return js;
			}
		}
		return nullptr;
	}

	DeeClipboardCopy * DeeClipboard::StartCopy( const CallbackInfo& ci )
	{
		if ( auto cp = m_Clip->StartCopy() )
		{
			if ( auto js = ci.NewJsObject<DeeClipboardCopy>() )
			{
				js->SetCopy( std::move( cp ) );
				return js;
			}
		}
		return nullptr;
	}

}
