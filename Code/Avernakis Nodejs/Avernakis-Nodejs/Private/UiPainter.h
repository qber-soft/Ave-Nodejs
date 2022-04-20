#pragma once

#include "UiCommon.h"

namespace Nav
{

	class Byo2Font;
	class Byo2Brush;
	class Byo2Image;
	class Byo2ImageList;
	class Byo2Geometry;

	class Byo2DrawImageParam
	{
	public:
		WrapData<R32_R>					m_SourceRect;
		WrapData<R32_2>					m_TargetSize;
		R32								m_SourceAlpha;
		WrapData<R32_R>					m_SourceRect2;
		Byo2::DrawImageFilter			m_Filter;
		Byo2::DrawImageAddress			m_Address;
		Byo2::DrawImageAddress			m_Address2;
		WrapData<R32_3x2>				m_Transform;
		WrapData<R32_3x2>				m_Transform2;

		void ToByo2( Byo2::DrawImageParam& r ) const
		{
			r.m_SourceRect = m_SourceRect;
			r.m_TargetSize = m_TargetSize;
			r.m_SourceAlpha = m_SourceAlpha;
			r.m_SourceRect2 = m_SourceRect2;
			r.m_Filter = m_Filter;
			r.m_Address = m_Address;
			r.m_Address2 = m_Address2;
			r.m_Transform = m_Transform;
			r.m_Transform2 = m_Transform2;
		}
	};

	NavDefineDataByMember_( Byo2DrawImageParam, SourceRect, TargetSize, SourceAlpha, SourceRect2, Filter, Address, Address2, Transform, Transform2 );

	class UiPainter : public WrapObject<UiPainter, void(), WrapObjectGeneric>
	{
	public:
		AveWrapObject( UiPainter );

		static PCAChar					GetExportName() { return "6497d460d30e4e8f88599e38bc17ed8b"; }
		static void						DefineObject();

		U1								Ctor() { return true; }
		Napi::Value						GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Ui::IPainter*					m_Painter;

	private:
		//----------------------------------------------------------------------------------------------------
		// Retrieve methods
		//----------------------------------------------------------------------------------------------------

		R64								GetTime() const { return m_Painter->GetTime(); }
		U1								IsStable() const { return m_Painter->IsStable(); }
		U1								UpdateState( Napi::Value v );

		//----------------------------------------------------------------------------------------------------
		// Common methods
		//----------------------------------------------------------------------------------------------------

		void							TypedSetStyle( U32 nStyle ) { m_Painter->SetStyle( nStyle ); }
		void							TypedSetOpacity( R32 fOpacity ) { m_Painter->SetOpacity( fOpacity ); }
		void							TypedSetFont( Byo2Font* pFont );
		void							TypedSetTextColor( const WrapData<U8_4>& vColor ) { m_Painter->SetTextColor( &vColor ); }
		void							TypedClearTextColor() { m_Painter->SetTextColor( nullptr ); }
		void							TypedSetHintColor( const WrapData<U8_4>& vColor ) { m_Painter->SetHintColor( vColor ); }

		Byo2Font*						GetFontStandard( const CallbackInfo& ci ) const;

		void							DrawAnimation() { m_Painter->DrawAnimation(); }

		//----------------------------------------------------------------------------------------------------
		// Typed draw methods
		//----------------------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------------------
		// Byo2 methods
		//----------------------------------------------------------------------------------------------------

		void							PushViewport( const WrapData<R32_R>& rc, const WrapData<R32_2>& vOffset, R32 fOpacity, R32 fRotation ) { m_Painter->GetDeviceContext2().PushViewport( rc, &vOffset, fOpacity, fRotation ); }
		void							PopViewport() { m_Painter->GetDeviceContext2().PopViewport(); }
		WrapData<R32_R>					GetViewportRect() const { return m_Painter->GetDeviceContext2().GetViewportRect(); }

		void							SetPenFillMode( Byo2::FillMode nMode ) { m_Painter->GetDeviceContext2().SetPenFillMode( nMode ); }
		Byo2::FillMode					GetPenFillMode() const { return m_Painter->GetDeviceContext2().GetPenFillMode(); }
		void							SetPenColor( const WrapData<U8_4>& vColor ) { m_Painter->GetDeviceContext2().SetPenColor( vColor ); }
		void							SetPenBrush( Byo2Brush* pBrush );
		void							SetPenImage( Byo2Image* pImage );
		void							SetPenWidth( R32 fWidth ) { m_Painter->GetDeviceContext2().SetPenWidth( fWidth ); }

		void							SetFillFillMode( Byo2::FillMode nMode ) { m_Painter->GetDeviceContext2().SetFillFillMode( nMode ); }
		Byo2::FillMode					GetFillFillMode() const { return m_Painter->GetDeviceContext2().GetFillFillMode(); }
		void							SetFillColor( const WrapData<U8_4>& vColor ) { m_Painter->GetDeviceContext2().SetFillColor( vColor ); }
		void							SetFillBrush( Byo2Brush* pBrush );
		void							SetFillImage( Byo2Image* pImage );

		void							SetTextFillMode( Byo2::FillMode nMode ) { m_Painter->GetDeviceContext2().SetTextFillMode( nMode ); }
		Byo2::FillMode					GetTextFillMode() const { return m_Painter->GetDeviceContext2().GetTextFillMode(); }
		void							SetTextColor( const WrapData<U8_4>& vColor ) { m_Painter->GetDeviceContext2().SetTextColor( vColor ); }
		void							SetTextBrush( Byo2Brush* pBrush );
		void							SetTextImage( Byo2Image* pImage );
		void							SetTextReadingDirection( Byo2::ReadingDirection nDir ) { m_Painter->GetDeviceContext2().SetTextReadingDirection( nDir ); }
		Byo2::ReadingDirection			GetTextReadingDirection() const { return m_Painter->GetDeviceContext2().GetTextReadingDirection(); }
		void							SetTextFlowDirection( Byo2::FlowDirection nDir ) { m_Painter->GetDeviceContext2().SetTextFlowDirection( nDir ); }
		Byo2::FlowDirection				GetTextFlowDirection() const { return m_Painter->GetDeviceContext2().GetTextFlowDirection(); }

		void							SetPolyFillMode( Byo2::PolyFillMode nMode ) { m_Painter->GetDeviceContext2().SetPolyFillMode( nMode ); }
		void							SetWorld( const WrapData<R32_3x2>& mWorld ) { m_Painter->GetDeviceContext2().SetWorld( mWorld ); }

		void							DrawLine( R32 x0, R32 y0, R32 x1, R32 y1 ) { m_Painter->GetDeviceContext2().DrawLine( x0, y0, x1, y1 ); }

		void							DrawRectangle( R32 x, R32 y, R32 w, R32 h ) { m_Painter->GetDeviceContext2().DrawRectangle( x, y, w, h ); }
		void							FillRectangle( R32 x, R32 y, R32 w, R32 h ) { m_Painter->GetDeviceContext2().FillRectangle( x, y, w, h ); }

		void							DrawRoundedRectangle( R32 x, R32 y, R32 w, R32 h, R32 rx, R32 ry ) { m_Painter->GetDeviceContext2().DrawRoundedRectangle( x, y, w, h, rx, ry ); }
		void							FillRoundedRectangle( R32 x, R32 y, R32 w, R32 h, R32 rx, R32 ry ) { m_Painter->GetDeviceContext2().FillRoundedRectangle( x, y, w, h, rx, ry ); }

		void							DrawEllipse( R32 x, R32 y, R32 w, R32 h ) { m_Painter->GetDeviceContext2().DrawEllipse( x, y, w, h ); }
		void							FillEllipse( R32 x, R32 y, R32 w, R32 h ) { m_Painter->GetDeviceContext2().FillEllipse( x, y, w, h ); }

		void							DrawArc( R32 x, R32 y, R32 w, R32 h, R32 r0, R32 r1 ) { m_Painter->GetDeviceContext2().DrawArc( x, y, w, h, r0, r1 ); }
		void							FillPie( R32 x, R32 y, R32 w, R32 h, R32 r0, R32 r1 ) { m_Painter->GetDeviceContext2().FillPie( x, y, w, h, r0, r1 ); }

		void							DrawPolygon( const WrapArray<R32_2>& pt, U32 nCount );
		void							FillPolygon( const WrapArray<R32_2>& pt, U32 nCount );

		void							DrawGeometry( Byo2Geometry* pGeometry );
		void							FillGeometry( Byo2Geometry* pGeometry );

		void							FillImageMask( const WrapData<R32_R>& rcFill, Byo2Image* pMask, const WrapData<R32_R>& rcMask );

		void							DrawImage( Byo2Image* pImage, const WrapData<R32_2>& pt );
		void							DrawImageEx( Byo2Image* pImage, const WrapData<R32_2>& pt, U32 nFlag, const WrapData<Byo2DrawImageParam>& pParam );
		void							DrawImageList( Byo2ImageList* pImage, U32 nIndex, const WrapData<R32_2>& pt, U8 nAlpha );
		void							DrawImageMask( Byo2Image* pImage, const WrapData<R32_2>& ptImage, Byo2Image* pMask, const WrapData<R32_R>& rcMask );
		void							DrawImageMaskEx( Byo2Image* pImage, const WrapData<R32_2>& ptImage, Byo2Image* pMask, const WrapData<R32_R>& rcMask, U32 nFlag, const WrapData<Byo2DrawImageParam>& pParam );
		void							DrawImageLerp( Byo2Image* pImage0, Byo2Image* pImage1, const WrapData<R32_2>& pt, R32 fLerp );
		void							DrawImageLerpEx( Byo2Image* pImage0, Byo2Image* pImage1, const WrapData<R32_2>& pt, R32 fLerp, U32 nFlag, const WrapData<Byo2DrawImageParam>& pParam );

		WrapData<R32_R>					DrawString( Byo2Font* pFont, const WrapData<R32_R>& rc, PCWChar szText, U32 nFlag, S32 nCharCount );

		void							AnnotationBegin( PCWChar szName ) { m_Painter->GetDeviceContext2().AnnotationBegin( szName ); }
		void							AnnotationEnd() { m_Painter->GetDeviceContext2().AnnotationEnd(); }
		void							AnnotationMark( PCWChar szName ) { m_Painter->GetDeviceContext2().AnnotationMark( szName ); }

	public:
		AveInline void					SetPainter( Ui::IPainter* p ) { m_Painter = p; }
	};
}
