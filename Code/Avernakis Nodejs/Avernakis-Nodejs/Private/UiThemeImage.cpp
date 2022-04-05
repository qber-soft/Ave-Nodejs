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
		UiFontDescriptionByo2 f2;
		f2.FromJs( font, m_Object->GetResourceManager() );
		m_Object->SetFont( f2.m_FontDesc );
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
