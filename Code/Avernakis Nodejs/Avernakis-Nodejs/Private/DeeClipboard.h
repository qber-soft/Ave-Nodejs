#pragma once

#include "WrapObject.h"
#include "WrapData.h"

#include "IoCommon.h"

namespace Nav
{

	class ImgImage;
	class IoStream;

	class DeeClipboardVirtualFile : public WrapObject<DeeClipboardVirtualFile, void()>
	{
	public:
		AveWrapObject( DeeClipboardVirtualFile );

		static PCAChar						GetExportName() { return "45fb22f51a2c4a9ea70a4508a759c045"; }
		static void							DefineObject();

		U1									Ctor() { return true; }
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Dee::ClipboardVirtualFile			m_File;

	private:
		U32									GetCount() const { return m_File->GetCount(); }
		WrapData<IoFileFindItem>			GetInfo( const CallbackInfo& cc, U32 nIndex ) const;
		IoStream*							Open( const CallbackInfo& cc, U32 nIndex ) const;

	public:
		AveInline void						SetFile( Dee::ClipboardVirtualFile&& f ) { m_File = std::move( f ); }
	};

	class DeeClipboardCopy : public WrapObject<DeeClipboardCopy, void()>
	{
	public:
		AveWrapObject( DeeClipboardCopy );

		static PCAChar						GetExportName() { return "84d226fdcf58432eb2c664180818f17b"; }
		static void							DefineObject();

		U1									Ctor() { return true; }
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Dee::ClipboardCopying				m_Copy;

	private:
		U1									Commit() { return m_Copy->Commit(); }

		void								SetText( PCWChar szText ) const { m_Copy->SetText( szText ); }
		void								SetImage( ImgImage* img ) const;
		void								SetFile( const List<WString>& vFile ) const { auto v = vFile; m_Copy->SetFile( std::move( v ) ); }
		void								AddFile( PCWChar szFile ) const { m_Copy->AddFile( szFile ); }
		void								AddFiles( const List<WString>& vFile ) const { m_Copy->AddFile( vFile ); }

	public:
		AveInline void						SetCopy( Dee::ClipboardCopying&& c ) { m_Copy = std::move( c ); }
	};

	class DeeClipboard : public WrapObject<DeeClipboard, void()>
	{
	public:
		AveWrapObject( DeeClipboard );

		static PCAChar						GetExportName() { return "ff5defcbefba417e8434652b7a736fcb"; }
		static void							DefineObject();

		U1									Ctor();
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Dee::IClipboard*					m_Clip;

	private:
		U1									SetText( PCWChar szText ) const { return m_Clip->SetText( szText ); }
		WString								GetText() const { return m_Clip->GetText(); }
		U1									HasText() const { return m_Clip->HasText(); }

		U1									SetImage( ImgImage* img ) const;
		ImgImage*							GetImage( const CallbackInfo& ci ) const;
		U1									HasImage() const { return m_Clip->HasImage(); }

		U1									SetFile( const List<WString>& vFile ) const { return m_Clip->SetFile( vFile ); }
		List<WString>						GetFile() const { return m_Clip->GetFile(); }
		U1									HasFile() const { return m_Clip->HasFile(); }

		DeeClipboardVirtualFile*			GetVirtualFile( const CallbackInfo& ci ) const;
		U1									HasVirtualFile() const { return m_Clip->HasVirtualFile(); }

		DeeClipboardCopy*					StartCopy( const CallbackInfo& ci );
	};

}
