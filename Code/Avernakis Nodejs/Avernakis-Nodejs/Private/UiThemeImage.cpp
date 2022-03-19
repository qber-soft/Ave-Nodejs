#include "StdAfx.h"
#include "UiThemeImage.h"

#define ThisMethod($x) &UiThemeImage::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, ThisMethod( $x ) )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiThemeImage> c_obj;
	}

	void UiThemeImage::DefineObject()
	{
		AutoAddMethod( ResetTheme, WrapObjectUi );

		AutoAddMethod( SetFont, WrapObjectUi );

		AutoAddMethod( AnimationSetDuration );
		AutoAddMethod( AnimationGetDuration );
		AutoAddMethod( AnimationSetFps );
		AutoAddMethod( AnimationGetFps );

		AutoAddMethod( InfectionSet );
		AutoAddMethod( InfectionGet );
	}

	U1 UiThemeImage::Ctor()
	{
		m_Object = AveKak.Create<Ui::IThemeImage>();
		if ( !m_Object )
			return false;

		m_Object->QueryInterface( &m_Animation );
		m_Object->QueryInterface( &m_Infection );

		Ui::IThemeAnimation* pAni;
		if ( m_Object->QueryInterface( &pAni ) )
		{
			pAni->SetFps( 30 );
			pAni->SetDuration( 300 );
		}

		return true;
	}

	void UiThemeImage::SetFont( const WrapData<UiFontDescription>& font )
	{
		WString s;
		List<Io::AveStream> vStream;
		List<Io::IAveStream*> vStreamPointer;
		if ( FontResourceType::Name == font.m_Type )
		{
			if ( font.m_Name.IsEmpty() )
				return;
			if ( !font.m_Index.IsEmpty() && font.m_Index.Size() != font.m_Name.Size() )
				return;
			for ( auto& i : font.m_Name )
			{
				if ( AveStr.Find( i.c_str(), AveWide( "/" ) ) )
					return;
				s += i + AveWide( "/" );
			}
			s.pop_back();
		}
		else if ( FontResourceType::File == font.m_Type )
		{
			if ( font.m_File.IsEmpty() )
				return;
			if ( !font.m_Index.IsEmpty() && font.m_Index.Size() != font.m_File.Size() )
				return;
			for ( auto& i : font.m_Name )
			{
				if ( AveStr.Find( i.c_str(), AveWide( "/" ) ) )
					return;
				auto fs = AveKak.Create<Io::IStreamFile>( i.c_str() );
				if ( !fs )
					return;
				vStreamPointer.Add( fs );
				vStream.Add( std::move( fs ) );
				s += WString( AveWide( "a:" ) ) + i + AveWide( "/" );
			}
			s.pop_back();
		}
		else if ( FontResourceType::ResourceId == font.m_Type )
		{
			if ( font.m_ResourceId.IsEmpty() )
				return;
			if ( !font.m_Index.IsEmpty() && font.m_Index.Size() != font.m_ResourceId.Size() )
				return;
			for ( auto& i : font.m_ResourceId )
			{
				auto fs = m_Object->GetResourceManager().Open( i );
				if ( !fs )
					return;
				vStreamPointer.Add( fs );
				vStream.Add( std::move( fs ) );
				s += AveWide( "a/" );
			}
			s.pop_back();
		}

		Byo2::FontDesc fd{};
		fd.m_Res.m_Name = s.c_str();
		if ( !vStreamPointer.IsEmpty() )
			fd.m_Res.m_Stream = vStreamPointer.Data();
		if ( !font.m_Index.IsEmpty() )
			fd.m_Res.m_Index = font.m_Index.Data();
		fd.m_Size = font.m_Size;
		fd.m_Flag = font.m_Flag;
		m_Object->SetFont( fd );
	}

	void UiThemeImage::AnimationSetDuration( U32 nMillisecond )
	{
		if ( m_Animation )
			m_Animation->SetDuration( Math::Clamp<U32>( nMillisecond, 0, 10000 ) );
	}

	U32 UiThemeImage::AnimationGetDuration()
	{
		return m_Animation ? m_Animation->GetDuration() : 0;
	}

	void UiThemeImage::AnimationSetFps( U32 nFps )
	{
		if ( m_Animation )
			m_Animation->SetFps( Math::Clamp<U32>( nFps, 8, 240 ) );
	}

	U32 UiThemeImage::AnimationGetFps()
	{
		return m_Animation ? m_Animation->GetFps() : 0;
	}

	void UiThemeImage::InfectionSet( const WrapData<UiThemeInfection>& pi )
	{
		if ( pi.m_InfectionRadius.IsSlice() )
			return;
		if ( m_Infection )
		{
			Ui::ThemeInfection ti{};
			ti.m_InfectionSpread = pi.m_InfectionSpread ? 1 : 0;
			ti.m_InfectionRadius = pi.m_InfectionRadius;
			ti.m_InfectionRadius.SetValue( Math::Clamp( ti.m_InfectionRadius.GetValue(), 0, 8192 ) );
			ti.m_InfectionOpacity = Math::Saturate( pi.m_InfectionOpacity );
			ti.m_InfectionActiveRatio = Math::Saturate( pi.m_InfectionActiveRatio );
			m_Infection->SetInfection( ti );
		}
	}

	WrapData<UiThemeInfection> UiThemeImage::InfectionGet()
	{
		WrapData<UiThemeInfection> r{};
		if ( m_Infection )
		{
			auto& ti = m_Infection->GetInfection();
			r.m_InfectionSpread = 0 != ti.m_InfectionSpread;
			r.m_InfectionRadius = ti.m_InfectionRadius;
			r.m_InfectionOpacity = ti.m_InfectionOpacity;
			r.m_InfectionActiveRatio = ti.m_InfectionActiveRatio;
		}
		return r;
	}

}
