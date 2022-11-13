#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiCodeEditorColor
	{
	public:
		WrapData<U8_4>						m_Back;
		WrapData<U8_4>						m_Fore;
		WrapData<U8_4>						m_Text;
	};
	NavDefineDataByMember_( UiCodeEditorColor, Back, Fore, Text );
	NavDefineTransitByMember_( Ui::CodeEditorColor, UiCodeEditorColor, Back, Fore, Text );

	class UiCodeEditorMargin
	{
	public:
		Ui::CodeEditorMarginType				m_Type;
		Ui::CodeEditorStyle						m_Style;
		union
		{
			U32									m_MarkerMask;
			U32									m_TextLine;
		};
		WrapData<Ui::DpiSize>					m_PixelWidth;
		Ui::AlignType							m_Align;
		Ui::CursorType							m_Cursor;
	};
	NavDefineDataByMember_( UiCodeEditorMargin, Type, Style, MarkerMask, TextLine, PixelWidth, Align, Cursor );
	NavDefineTransitByMember_( Ui::CodeEditorMargin, UiCodeEditorMargin, Type, Style, MarkerMask, TextLine, PixelWidth, Align, Cursor );

	class UiCodeEditorStyleItem
	{
	public:
		WrapData<UiCodeEditorColor>				m_Color;
		U1										m_Hidden;
		U1										m_ReadOnly;
		U1										m_Click;
	};
	NavDefineDataByMember_( UiCodeEditorStyleItem, Color, Hidden, ReadOnly, Click );
	//NavDefineTransitByMember_( Ui::CodeEditorStyleItem, UiCodeEditorStyleItem, Color, Hidden, ReadOnly, Click );

	template<>
	class WrapDataTransit<Ui::CodeEditorStyleItem> : public WrapDataTransitHelper<Ui::CodeEditorStyleItem, UiCodeEditorStyleItem>
	{
	public:
		static void Transit( Ui::CodeEditorStyleItem& d, const UiCodeEditorStyleItem& s )
		{
			WrapDataTransit<Ui::CodeEditorColor>::Transit( d.m_Color, s.m_Color );
			d.m_Hidden = s.m_Hidden;
			d.m_ReadOnly = s.m_ReadOnly;
			d.m_Click = s.m_Click;
		}

		static void Transit( UiCodeEditorStyleItem& d, const Ui::CodeEditorStyleItem& s )
		{
			WrapDataTransit<Ui::CodeEditorColor>::Transit( d.m_Color, s.m_Color );
			d.m_Hidden = s.m_Hidden;
			d.m_ReadOnly = s.m_ReadOnly;
			d.m_Click = s.m_Click;
		}
	};

	class UiCodeEditorDoc;
	class Byo2Image;

	class UiCodeEditor : public UiControlHelper<UiCodeEditor, Ui::ICodeEditor>
	{
	public:
		AveWrapControlCi( UiCodeEditor );

		~UiCodeEditor()
		{
		}

		static PCAChar						GetExportName() { return "UiCodeEditor"; }
		static void							DefineControl();

		U1									Ctor( const CallbackInfo& ci, UiWindow* p, Napi::Value v );

	private:
		JsObject<UiCodeEditorDoc>			m_Doc{ nullptr };

	private:
		AveInline Ui::ICodeEditorView&		__GetView() const { return GetControlTyped().GetView(); }
		AveInline Ui::ICodeEditorMargin&	__GetMargin() const { return GetControlTyped().GetView().GetMargin(); }
		AveInline Ui::ICodeEditorStyle&		__GetStyle() const { return GetControlTyped().GetView().GetStyle(); }
		AveInline Ui::ICodeEditorDisplay&	__GetDisp() const { return GetControlTyped().GetView().GetDisplay(); }
		AveInline Ui::ICodeEditorKey&		__GetKey() const { return GetControlTyped().GetKey(); }

	private:
		//====================================================================================================
		// Common

		UiCodeEditor*						SetIme( U1 b ) { GetControlTyped().SetIme( b ); return this; }
		U1									GetIme() const { return GetControlTyped().GetIme(); }

		UiCodeEditor*						DocNew();
		UiCodeEditorDoc*					DocGet() const { return m_Doc; }
		UiCodeEditor*						DocLink( UiCodeEditor* p );

		U1									ExecuteCommand( Ui::CodeEditorCommand nCommand ) { return GetControlTyped().ExecuteCommand( nCommand ); }

		//====================================================================================================
		// View

		UiCodeEditor*						ViewReset() { __GetView().Reset(); return this; }
		UiCodeEditor*						ViewCopyFrom( UiCodeEditor* p ) { __GetView().CopyFrom( p->__GetView() ); return this; }

		Ui::IconCache						ViewGetMarkerIcon( U32 nIndex ) const { return __GetView().GetMarkerIcon( nIndex ); }
		UiCodeEditor*						ViewSetMarkerIcon( U32 nIndex, Ui::IconCache pIcon ) { __GetView().SetMarkerIcon( nIndex, pIcon ); return this; }

		UiCodeEditor*						ViewSetBackImage( Byo2Image* img );

		R32									ViewGetBackImageOpacity() const { return __GetView().GetBackImageOpacity(); }
		UiCodeEditor*						ViewSetBackImageOpacity( R32 fOpacity ) { __GetView().SetBackImageOpacity( fOpacity ); return this; }

		WrapData<U8_4> 						ViewGetBackColor() const { return __GetView().GetBackColor(); }
		UiCodeEditor*						ViewSetBackColor( const WrapData<U8_4>& nColor ) { __GetView().SetBackColor( nColor ); return this; }

		WrapData<Ui::CodeEditorColor>		ViewGetLineColor() const { return __GetView().GetLineColor(); }
		UiCodeEditor*						ViewSetLineColor( const WrapData<Ui::CodeEditorColor>& nColor ) { __GetView().SetLineColor( nColor ); return this; }

		WrapData<U8_4> 						ViewGetSelectionColor() const { return __GetView().GetSelectionColor(); }
		UiCodeEditor*						ViewSetSelectionColor( const WrapData<U8_4>& nColor ) { __GetView().SetSelectionColor( nColor ); return this; }

		WrapData<U8_4> 						ViewGetNoFocusSelectionColor() const { return __GetView().GetNoFocusSelectionColor(); }
		UiCodeEditor*						ViewSetNoFocusSelectionColor( const WrapData<U8_4>& nColor ) { __GetView().SetNoFocusSelectionColor( nColor ); return this; }

		WrapData<U8_4> 						ViewGetCaretColor() const { return __GetView().GetCaretColor(); }
		UiCodeEditor*						ViewSetCaretColor( const WrapData<U8_4>& nColor ) { __GetView().SetCaretColor( nColor ); return this; }

		WrapData<U8_4> 						ViewGetSecondaryCaretColor() const { return __GetView().GetSecondaryCaretColor(); }
		UiCodeEditor*						ViewSetSecondaryCaretColor( const WrapData<U8_4>& nColor ) { __GetView().SetSecondaryCaretColor( nColor ); return this; }

		WrapData<Ui::CodeEditorColor> 		ViewGetEolColor() const { return __GetView().GetEolColor(); }
		UiCodeEditor*						ViewSetEolColor( const WrapData<Ui::CodeEditorColor>& nColor ) { __GetView().SetEolColor( nColor ); return this; }

		WrapData<Ui::CodeEditorColor> 		ViewGetSpaceColor() const { return __GetView().GetSpaceColor(); }
		UiCodeEditor*						ViewSetSpaceColor( const WrapData<Ui::CodeEditorColor>& nColor ) { __GetView().SetSpaceColor( nColor ); return this; }

		WrapData<Ui::CodeEditorColor> 		ViewGetFoldedColor() const { return __GetView().GetFoldedColor(); }
		UiCodeEditor*						ViewSetFoldedColor( const WrapData<Ui::CodeEditorColor>& nColor ) { __GetView().SetFoldedColor( nColor ); return this; }

		Ui::CodeEditorWrapMode				ViewGetWrapMode() const { return __GetView().GetWrapMode(); }
		UiCodeEditor*						ViewSetWrapMode( Ui::CodeEditorWrapMode nMode ) { __GetView().SetWrapMode( nMode ); return this; }

		U1									ViewGetViewEolSelection() const { return __GetView().GetViewEolSelection(); }
		UiCodeEditor*						ViewSetViewEolSelection( U1 b ) { __GetView().SetViewEolSelection( b ); return this; }

		U1									ViewGetViewEol() const { return __GetView().GetViewEol(); }
		UiCodeEditor*						ViewSetViewEol( U1 b ) { __GetView().SetViewEol( b ); return this; }

		U1									ViewGetViewSpace() const { return __GetView().GetViewSpace(); }
		UiCodeEditor*						ViewSetViewSpace( U1 b ) { __GetView().SetViewSpace( b ); return this; }

		Ui::CodeEditorAnnotationView		ViewGetAnnotationView() const { return __GetView().GetAnnotationView(); };
		UiCodeEditor*						ViewSetAnnotationView( Ui::CodeEditorAnnotationView nView ) { __GetView().SetAnnotationView( nView ); return this; }

		Byo2::FlowDirection					ViewGetFlowDirection() const { return __GetView().GetFlowDirection(); }
		UiCodeEditor*						ViewSetFlowDirection( Byo2::FlowDirection nDir ) { __GetView().SetFlowDirection( nDir ); return this; }

		//====================================================================================================
		// View - Margin

		UiCodeEditor*						VmClear() { __GetMargin().Clear(); return this; }
		U32									VmGetCount() const { return __GetMargin().GetCount(); }
		UiCodeEditor*						VmAdd( const WrapData<Ui::CodeEditorMargin>& item ) { __GetMargin().Add( item ); return this; }
		U1									VmRemove( U32 nIndex ) { return __GetMargin().Remove( nIndex ); }
		WrapData<Ui::CodeEditorMargin>		VmGet( U32 nIndex ) const { Ui::CodeEditorMargin m{}; if ( __GetMargin().Get( nIndex, m ) ) return m; return nullptr; }
		U1									VmSet( U32 nIndex, const WrapData<Ui::CodeEditorMargin>& item ) { return __GetMargin().Set( nIndex, item ); }

		//====================================================================================================
		// View - Style

		U1									VsReset( U32 nCount ) { return __GetStyle().Reset( nCount ); }
		U32									VsGetCount() const { return __GetStyle().GetCount(); }
		UiCodeEditor*						VsAdd( const WrapData<Ui::CodeEditorStyleItem>& sty, Byo2Font* font );
		WrapData<Ui::CodeEditorStyleItem>	VsGetStyle( U32 nIndex ) const { Ui::CodeEditorStyleItem vs{}; if ( __GetStyle().GetStyle( nIndex, vs ) ) return vs; return nullptr; }
		U1									VsSetStyle( U32 nIndex, const WrapData<Ui::CodeEditorStyleItem>& item ) { return __GetStyle().SetStyle( nIndex, item ); }
		Byo2Font*							VsGetFont( const CallbackInfo& ci, U32 nIndex ) const;
		UiCodeEditor*						VsSetFont( U32 nIndex, Byo2Font* pFont );

		//====================================================================================================
		// View - Display

		U1									VdGetLineExpand( S32 nLine ) const { return __GetDisp().GetLineExpand( nLine ); }
		U1									VdSetLineExpand( S32 nLine, Ui::ExpandAction nAction ) { return __GetDisp().SetLineExpand( nLine, nAction ); }

		UiCodeEditor*						VdShowAll() { __GetDisp().ShowAll(); return this; }

		//====================================================================================================
		// Selection

		//====================================================================================================
		// Key

		UiCodeEditor*						KeyDefault() { __GetKey().KeyDefault(); return this; }
		UiCodeEditor*						KeyClear() { __GetKey().KeyClear(); return this; }
		U1									KeySet( Ui::Key nKey, U32 nModifer, Ui::CodeEditorCommand nCommand ) { return __GetKey().KeySet( nKey, nModifer, nCommand ); }
		U1									KeyRemove( Ui::Key nKey, U32 nModifer ) { return __GetKey().KeyRemove( nKey, nModifer ); }

	};
}
