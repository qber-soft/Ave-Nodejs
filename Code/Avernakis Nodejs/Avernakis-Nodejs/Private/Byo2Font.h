#pragma once

#include "UiCommon.h"
#include "IoCommon.h"

namespace Nav
{

	class UiWindow;

	class Byo2FontCreation
	{
	public:
		WString							m_Name;
		R32								m_Size;
		U32								m_Flag;
	};

	NavDefineDataByMember_( Byo2FontCreation, Name, Size, Flag );

	class Byo2Font : public WrapObject<Byo2Font, void( UiWindow*, const WrapData<Byo2FontCreation>& )>
	{
	public:
		AveWrapObject( Byo2Font );

		static PCAChar						GetExportName() { return "Byo2Font"; }
		static void							DefineObject();

		U1									Ctor( UiWindow* p, const WrapData<Byo2FontCreation>& c );
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Byo2::Font							m_Font;

	private:
		R32									GetAscent() const { return m_Font->GetAscent(); }
		R32									GetDescent() const { return m_Font->GetDescent(); }
		R32									GetHeight() const { return m_Font->GetHeight(); }
		R32									GetWidth() const { return m_Font->GetWidth(); }
		R32									GetLeadingExternal() const { return m_Font->GetLeadingExternal(); }
		R32									GetLeadingInternal() const { return m_Font->GetLeadingInternal(); }

		void								SetReadingDirection( Byo2::ReadingDirection nDir ) { m_Font->SetReadingDirection( nDir ); }
		Byo2::ReadingDirection				GetReadingDirection() const { return m_Font->GetReadingDirection(); }
		void								SetFlowDirection( Byo2::FlowDirection nDir ) { m_Font->SetFlowDirection( nDir ); }
		Byo2::FlowDirection					GetFlowDirection() const { return m_Font->GetFlowDirection(); }

		List<R32>							Measure( PCWChar szText ) const;

	public:
		void								SetFont( Byo2::Font&& font ) { m_Font = std::move( font ); }
		Byo2::IFont*						GetFont() { return m_Font; }
		Byo2::Font							CloneFont() { return m_Font; }
	};
}
