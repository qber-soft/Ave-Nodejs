#include "StdAfx.h"
#include "UiPainter.h"
#include "UiWindow.h"
#include "Byo2Font.h"
#include "Byo2Image.h"

#define ThisMethod($x) &UiPainter::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiPainter::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiPainter> c_obj;
	}

	void UiPainter::DefineObject()
	{
		AutoAddMethod( GetTime );
		AutoAddMethod( IsStable );
		AutoAddMethod( UpdateState );

		AutoAddMethod( TypedSetStyle );
		AutoAddMethod( TypedSetOpacity );
		AutoAddMethod( TypedSetFont );
		AutoAddMethod( TypedSetTextColor );
		AutoAddMethod( TypedClearTextColor );
		AutoAddMethod( TypedSetHintColor );

		AutoAddMethod( GetFontStandard );

		AutoAddMethod( DrawAnimation );

		AutoAddMethod( PushViewport );
		AutoAddMethod( PopViewport );
		AutoAddMethod( GetViewportRect );

		AutoAddMethod( SetPenFillMode );
		AutoAddMethod( GetPenFillMode );
		AutoAddMethod( SetPenColor );
		//AutoAddMethod( SetPenBrush );
		AutoAddMethod( SetPenImage );
		AutoAddMethod( SetPenWidth );

		AutoAddMethod( SetFillFillMode );
		AutoAddMethod( GetFillFillMode );
		AutoAddMethod( SetFillColor );
		//AutoAddMethod( SetFillBrush );
		AutoAddMethod( SetFillImage );

		AutoAddMethod( SetTextFillMode );
		AutoAddMethod( GetTextFillMode );
		AutoAddMethod( SetTextColor );
		//AutoAddMethod( SetTextBrush );
		AutoAddMethod( SetTextImage );
		AutoAddMethod( SetTextReadingDirection );
		AutoAddMethod( GetTextReadingDirection );
		AutoAddMethod( SetTextFlowDirection );
		AutoAddMethod( GetTextFlowDirection );

		AutoAddMethod( SetPolyFillMode );
		AutoAddMethod( SetWorld );

		AutoAddMethod( DrawLine );

		AutoAddMethod( DrawRectangle );
		AutoAddMethod( FillRectangle );

		AutoAddMethod( DrawRoundedRectangle );
		AutoAddMethod( FillRoundedRectangle );

		AutoAddMethod( DrawEllipse );
		AutoAddMethod( FillEllipse );

		AutoAddMethod( DrawArc );
		AutoAddMethod( FillPie );
		
		AutoAddMethod( FillImageMask );

		AutoAddMethod( DrawImage );
		AutoAddMethod( DrawImageEx );
		AutoAddMethod( DrawImageMask );
		AutoAddMethod( DrawImageMaskEx );
		AutoAddMethod( DrawImageLerp );
		AutoAddMethod( DrawImageLerpEx );

		AutoAddMethod( DrawString );
		
		AutoAddMethod( AnnotationBegin );
		AutoAddMethod( AnnotationEnd );
		AutoAddMethod( AnnotationMark );
	}

	U1 UiPainter::UpdateState( Napi::Value v )
	{
		if ( !v.IsObject() )
			return false;
		auto obj = v.As<Napi::Object>();
		auto time = obj.Get( "m_Time" );
		auto speed = obj.Get( "m_Speed" );
		auto ratio = obj.Get( "m_Ratio" );
		if ( !time.IsNumber() || !speed.IsNumber() || !ratio.IsNumber() )
			return false;

		UiPainterStateBase ps{ time.As<Napi::Number>().DoubleValue(), speed.As<Napi::Number>().FloatValue(), ratio.As<Napi::Number>().FloatValue() };

		const auto b = m_Painter->UpdateState( (Ui::PainterStateBase&) ps );
		obj.Set( "m_Time", ps.m_Time );
		obj.Set( "m_Speed", ps.m_Speed );
		obj.Set( "m_Ratio", ps.m_Ratio );
		return b;

		AveStaticAssert( sizeof( ps ) == sizeof( Ui::PainterStateBase ), "Invalid painter state size." );
	}

	void UiPainter::TypedSetFont( Byo2Font * pFont )
	{
		m_Painter->SetFont( pFont->GetFont() );
	}

	Byo2Font * UiPainter::GetFontStandard( const CallbackInfo & ci ) const
	{
		if ( auto p = ci.NewJsObject<Byo2Font>() )
		{
			p->SetFont( Byo2::Font( &m_Painter->GetFontStandard(), true ) );
			return p;
		}
		return nullptr;
	}

	void UiPainter::SetPenImage( Byo2Image * pImage )
	{
	}

	void UiPainter::SetFillImage( Byo2Image * pImage )
	{
	}

	void UiPainter::SetTextImage( Byo2Image * pImage )
	{
	}

	void UiPainter::FillImageMask( const WrapData<R32_R>& rcFill, Byo2Image * pMask, const WrapData<R32_R>& rcMask )
	{
		m_Painter->GetDeviceContext2().FillImageMask( rcFill, *pMask->GetImage(), rcMask );
	}

	void UiPainter::DrawImage( Byo2Image * pImage, const WrapData<R32_2>& pt )
	{
		m_Painter->GetDeviceContext2().DrawImage( *pImage->GetImage(), pt );
	}

	void UiPainter::DrawImageEx( Byo2Image * pImage, const WrapData<R32_2>& pt, U32 nFlag, const WrapData<Byo2DrawImageParam>& pParam )
	{
		Byo2::DrawImageParam dip;
		pParam.ToByo2( dip );
		m_Painter->GetDeviceContext2().DrawImage( *pImage->GetImage(), pt, nFlag, &dip );
	}

	void UiPainter::DrawImageMask( Byo2Image * pImage, const WrapData<R32_2>& ptImage, Byo2Image * pMask, const WrapData<R32_R>& rcMask )
	{
		m_Painter->GetDeviceContext2().DrawImageMask( *pImage->GetImage(), ptImage, *pMask->GetImage(), rcMask );
	}

	void UiPainter::DrawImageMaskEx( Byo2Image * pImage, const WrapData<R32_2>& ptImage, Byo2Image * pMask, const WrapData<R32_R>& rcMask, U32 nFlag, const WrapData<Byo2DrawImageParam>& pParam )
	{
		Byo2::DrawImageParam dip;
		pParam.ToByo2( dip );
		m_Painter->GetDeviceContext2().DrawImageMask( *pImage->GetImage(), ptImage, *pMask->GetImage(), rcMask, nFlag, &dip );
	}

	void UiPainter::DrawImageLerp( Byo2Image * pImage0, Byo2Image * pImage1, const WrapData<R32_2>& pt, R32 fLerp )
	{
		m_Painter->GetDeviceContext2().DrawImageLerp( *pImage0->GetImage(), *pImage1->GetImage(), pt, fLerp );
	}

	void UiPainter::DrawImageLerpEx( Byo2Image * pImage0, Byo2Image * pImage1, const WrapData<R32_2>& pt, R32 fLerp, U32 nFlag, const WrapData<Byo2DrawImageParam>& pParam )
	{
		Byo2::DrawImageParam dip;
		pParam.ToByo2( dip );
		m_Painter->GetDeviceContext2().DrawImageLerp( *pImage0->GetImage(), *pImage1->GetImage(), pt, fLerp, nFlag, &dip );
	}

	WrapData<R32_R> UiPainter::DrawString( Byo2Font * pFont, const WrapData<R32_R>& rc, PCWChar szText, U32 nFlag, S32 nCharCount )
	{
		R32_R rcr = rc;
		m_Painter->GetDeviceContext2().DrawString( *pFont->GetFont(), rcr, szText, nFlag, nCharCount );
		return rcr;
	}

}
