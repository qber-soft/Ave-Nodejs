#include "StdAfx.h"
#include "UiRichLabel.h"
#include "Byo2Font.h"
#include "Byo2Image.h"
#include "ImgImage.h"

#define ThisMethod($x) &UiRichLabel::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiRichLabel::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiRichLabel> c_obj;
	}

	void UiRichLabel::DefineControl()
	{
		AutoAddMethod( SetText );
		AutoAddMethod( GetText, WrapObjectGeneric );
		AutoAddMethod( GetTextData, WrapObjectGeneric );
		AutoAddMethod( IsTextValid, WrapObjectGeneric );
		AutoAddMethod( Recompile );

		AutoAddMethod( SetAlignHorz );
		AutoAddMethod( GetAlignHorz, WrapObjectGeneric );

		AutoAddMethod( SetAlignVert );
		AutoAddMethod( GetAlignVert, WrapObjectGeneric );

		AutoAddMethod( SetWrappable );
		AutoAddMethod( GetWrappable, WrapObjectGeneric );

		AutoAddMethod( FmReset );

		AutoAddMethod( FmSetDefaultTextColor );
		AutoAddMethod( FmGetDefaultTextColor, WrapObjectGeneric );

		AutoAddMethod( FmSetDefaultBackColor );
		AutoAddMethod( FmGetDefaultBackColor, WrapObjectGeneric );

		AutoAddMethod( FmSetDefaultFont );
		AutoAddMethod( FmGetDefaultFont, WrapObjectGeneric );

		AutoAddMethod( FmSetRubyFont );
		AutoAddMethod( FmGetRubyFont, WrapObjectGeneric );

		AutoAddMethod( FmSetRubyForceSpace );
		AutoAddMethod( FmGetRubyForceSpace, WrapObjectGeneric );

		AutoAddMethod( FmSetRubyTextColor );
		AutoAddMethod( FmGetRubyTextColor, WrapObjectGeneric );

		AutoAddMethod( FmSetRubyBackColor );
		AutoAddMethod( FmGetRubyBackColor, WrapObjectGeneric );

		AutoAddMethod( FmSetSScriptSize );
		AutoAddMethod( FmGetSScriptSize, WrapObjectGeneric );

		AutoAddMethod( FmSetBorderOffset );
		AutoAddMethod( FmGetBorderOffset, WrapObjectGeneric );

		AutoAddMethod( FmSetShadowOffset );
		AutoAddMethod( FmGetShadowOffset, WrapObjectGeneric );

		AutoAddMethod( FmSetEmphasisNearSpace );
		AutoAddMethod( FmGetEmphasisNearSpace, WrapObjectGeneric );

		AutoAddMethod( FmSetEmphasisFarSpace );
		AutoAddMethod( FmGetEmphasisFarSpace, WrapObjectGeneric );

		AutoAddMethod( FmSetMaskResource );
		AutoAddMethod( FmSetMaskImageData );
		AutoAddMethod( FmSetMaskImage );

		AutoAddMethod( FmSetUnderline );
		AutoAddMethod( FmGetUnderline, WrapObjectGeneric );

		AutoAddMethod( FmSetStrikethrough );
		AutoAddMethod( FmGetStrikethrough, WrapObjectGeneric );

		AutoAddMethod( FmSetEmphasis );
		AutoAddMethod( FmGetEmphasis, WrapObjectGeneric );

		AutoAddMethod( FmSetTextColor );
		AutoAddMethod( FmGetTextColor, WrapObjectGeneric );
		AutoAddMethod( FmGetTextColorByName, WrapObjectGeneric );

		AutoAddMethod( FmSetBackColor );
		AutoAddMethod( FmGetBackColor, WrapObjectGeneric );
		AutoAddMethod( FmGetBackColorByName, WrapObjectGeneric );

		AutoAddMethod( FmSetTextFont );
		AutoAddMethod( FmGetTextFont );
		AutoAddMethod( FmGetTextFontByName );

		AutoAddMethod( FmSetTextEffect );
		AutoAddMethod( FmGetTextEffect, WrapObjectGeneric );
		AutoAddMethod( FmGetTextEffectByName, WrapObjectGeneric );
		AutoAddMethod( FmSetTextEffectCustom );

		AutoAddMethod( IconClear );
		AutoAddMethod( IconSetId );
		AutoAddMethod( IconGetId, WrapObjectGeneric );
		AutoAddMethod( IconRemoveId );
		AutoAddMethod( IconClearOffset );
		AutoAddMethod( IconRemoveOffset );
		AutoAddMethod( IconSetOffset );
		AutoAddMethod( IconGetOffset, WrapObjectGeneric );
		AutoAddMethod( IconSetManager );

		AutoAddMethod( IconSetDefaultSize );
		AutoAddMethod( IconGetDefaultSize, WrapObjectGeneric );

		AutoAddMethod( VaClear );
		AutoAddMethod( VaSetById );
		AutoAddMethod( VaGetById, WrapObjectGeneric );
		AutoAddMethod( VaSetByName );
		AutoAddMethod( VaGetByName, WrapObjectGeneric );
		AutoAddMethod( VaSetManager );

		AutoAddMethod( PlStart, WrapObjectGeneric );
		AutoAddMethod( PlStop, WrapObjectGeneric );
		AutoAddMethod( PlIsPlaying, WrapObjectGeneric );

		AutoAddMethod( PlSetPosition, WrapObjectGeneric );
		AutoAddMethod( PlGetPosition, WrapObjectGeneric );

		AutoAddMethod( PlSetAdvanceSpeed, WrapObjectGeneric );
		AutoAddMethod( PlGetAdvanceSpeed, WrapObjectGeneric );

		AutoAddMethod( PlSetClusterSpeed, WrapObjectGeneric );
		AutoAddMethod( PlGetClusterSpeed, WrapObjectGeneric );

		AutoAddMethod( PlSetCustom );
		AutoAddMethod( PlGetFirstCluster, WrapObjectGeneric );
		AutoAddMethod( PlGetLastCluster, WrapObjectGeneric );
	}

	U1 UiRichLabel::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().SetIconManager( p->PublicCloneIconManager() );

		return true;
	}

	void UiRichLabel::__OnCustomTextFx( Ui::IRichLabel & sender, const Ui::RichLabelTextFxCustom & fx, Ui::RichLabelDisplay & cd )
	{
		UiRichLabelTextFxCustom_t f;
		UiRichLabelDisplay_t d;
		UiRichLabelDisplay_t r;
		f.FromAve( fx );
		d.FromAve( cd );
		m_OnCustomTextFx.BlockCall( this, f, d, r );
		r.ToAve( cd );
	}

	U32 UiRichLabel::__OnQueryIconId( Ui::IRichLabel & sender, PCWChar szName )
	{
		U32 nId = 0;
		m_OnQueryIconId.BlockCall( this, szName, nId );
		return nId;
	}

	PCWChar UiRichLabel::__OnQueryVariable( Ui::IRichLabel & sender, const Ui::RichLabelQueryVariable & qv )
	{
		UiRichLabelQueryVariable_t q;
		q.FromAve( qv );
		m_QueryVariableResult.Clear();
		m_OnQueryVariable.BlockCall( this, q, m_QueryVariableResult );
		return m_QueryVariableResult.c_str();
	}

	void UiRichLabel::__OnCustomPlay( Ui::IRichLabel & sender, const Ui::RichLabelCustomPlay & cp, Ui::RichLabelDisplay & cd )
	{
		UiRichLabelCustomPlay_t c;
		UiRichLabelDisplay_t d;
		UiRichLabelDisplay_t r;
		c.FromAve( cp );
		d.FromAve( cd );
		m_OnCustomPlay.BlockCall( this, c, d, r );
		r.ToAve( cd );
	}

	UiRichLabel * UiRichLabel::FmSetDefaultFont( WrapPointer<Byo2Font> pFont )
	{
		if ( pFont )
			GetControlTyped().FmSetDefaultFont( pFont->CloneFont() );
		return this;
	}

	Byo2Font * UiRichLabel::FmGetDefaultFont( const CallbackInfo & ci ) const
	{
		if ( auto pFont = GetControlTyped().FmGetDefaultFont() )
		{
			if ( auto p = ci.NewJsObject<Byo2Font>() )
			{
				p->SetFont( Byo2::Font( pFont, true ) );
				return p;
			}
		}
		return nullptr;
	}

	UiRichLabel * UiRichLabel::FmSetRubyFont( WrapPointer<Byo2Font> pFont )
	{
		if ( pFont )
			GetControlTyped().FmSetRubyFont( pFont->CloneFont() );
		return this;
	}

	Byo2Font * UiRichLabel::FmGetRubyFont( const CallbackInfo & ci ) const
	{
		if ( auto pFont = GetControlTyped().FmGetRubyFont() )
		{
			if ( auto p = ci.NewJsObject<Byo2Font>() )
			{
				p->SetFont( Byo2::Font( pFont, true ) );
				return p;
			}
		}
		return nullptr;
	}

	UiRichLabel * UiRichLabel::FmSetMaskImageData( ImgImage * img )
	{
		GetControlTyped().FmSetMask( img->CloneImage() );
		return nullptr;
	}

	UiRichLabel * UiRichLabel::FmSetMaskImage( Byo2Image * img )
	{
		GetControlTyped().FmSetMask( img->CloneImage() );
		return nullptr;
	}

	UiRichLabel * UiRichLabel::FmSetStrikethrough( U32 nIndex, const UiRichLabelStrike_t & p )
	{
		Ui::RichLabelStrike d{};
		d.m_LineCount = Math::Min( (S32) CountOf( d.m_Color ), (S32) p.Size() ); 
		for ( S32 i = 0; i < d.m_LineCount; ++i )
		{
			p[i].m_Color.ToAve( d.m_Color[i] );
			d.m_Shape[i] = p[i].m_Shape;
		}
		GetControlTyped().FmSetStrikethrough( nIndex, d );
		return this;
	}

	UiRichLabelStrike_t UiRichLabel::FmGetStrikethrough( U32 nIndex )
	{
		UiRichLabelStrike_t v;
		auto& d = GetControlTyped().FmGetStrikethrough( nIndex );
		v.Resize( d.m_LineCount );
		for ( S32 i = 0; i < d.m_LineCount; ++i )
		{
			v[i].m_Color.FromAve( d.m_Color[i] );
			v[i].m_Shape = d.m_Shape[i];
		}
		return std::move( v );
	}

	UiRichLabel * UiRichLabel::FmSetTextFont( U32 nIndex, WrapPointer<Byo2Font> p, Nullable<PCWChar> szName )
	{
		if ( p )
			GetControlTyped().FmSetTextFont( nIndex, p->CloneFont(), szName );
		return this;
	}

	Byo2Font* UiRichLabel::FmGetTextFont( const CallbackInfo & ci, U32 nIndex ) const
	{
		if ( auto pFont = GetControlTyped().FmGetTextFont( nIndex ) )
		{
			if ( auto p = ci.NewJsObject<Byo2Font>() )
			{
				p->SetFont( Byo2::Font( pFont, true ) );
				return p;
			}
		}
		return nullptr;
	}

	Byo2Font* UiRichLabel::FmGetTextFontByName( const CallbackInfo & ci, PCWChar szName ) const
	{
		if ( szName )
		{
			if ( auto pFont = GetControlTyped().FmGetTextFont( szName ) )
			{
				if ( auto p = ci.NewJsObject<Byo2Font>() )
				{
					p->SetFont( Byo2::Font( pFont, true ) );
					return p;
				}
			}
		}
		return nullptr;
	}

	UiRichLabel * UiRichLabel::FmSetTextEffectCustom( OnCustomTextFx_t && fn )
	{
		m_OnCustomTextFx = std::move( fn );
		if ( m_OnCustomTextFx )
			GetControlTyped().FmSetTextEffectCustom( MakeThisFunc( __OnCustomTextFx ) );
		else
			GetControlTyped().FmSetTextEffectCustom( {} );
		return this;
	}

	UiRichLabel * UiRichLabel::IconSetManager( OnQueryIconId_t && fn )
	{
		m_OnQueryIconId = std::move( fn );
		if ( m_OnQueryIconId )
			GetControlTyped().IconSetManager( MakeThisFunc( __OnQueryIconId ) );
		else
			GetControlTyped().IconSetManager( {} );
		return this;
	}

	UiRichLabel * UiRichLabel::VaSetManager( OnQueryVariable_t && fn )
	{
		m_OnQueryVariable = std::move( fn );
		if ( m_OnQueryVariable )
			GetControlTyped().VaSetManager( MakeThisFunc( __OnQueryVariable ) );
		else
			GetControlTyped().VaSetManager( {} );
		return this;
	}

	UiRichLabel * UiRichLabel::PlSetCustom( OnCustomPlay_t && fn )
	{
		m_OnCustomPlay = std::move( fn );
		if ( m_OnCustomPlay )
			GetControlTyped().PlSetCustom( MakeThisFunc( __OnCustomPlay ) );
		else
			GetControlTyped().PlSetCustom( {} );
		return this;
	}

}
