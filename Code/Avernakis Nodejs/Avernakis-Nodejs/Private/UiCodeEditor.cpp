#include "StdAfx.h"
#include "UiCodeEditor.h"
#include "UiCodeEditorDoc.h"
#include "UiPainter.h"

#include "Byo2Image.h"
#include "Byo2Font.h"

#define ThisMethod($x) &UiCodeEditor::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiCodeEditor::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiCodeEditor> c_obj;
	}

	void UiCodeEditor::DefineControl()
	{
		AutoAddMethod( SetIme, WrapObjectGeneric);
		AutoAddMethod( GetIme, WrapObjectGeneric);
		AutoAddMethod( DocNew );
		AutoAddMethod( DocGet, WrapObjectGeneric );
		AutoAddMethod( DocLink );
		AutoAddMethod( ExecuteCommand );
		AutoAddMethod( ViewReset );
		AutoAddMethod( ViewCopyFrom );
		AutoAddMethod( ViewGetMarkerIcon, WrapObjectGeneric );
		AutoAddMethod( ViewSetMarkerIcon );
		AutoAddMethod( ViewSetBackImage );
		AutoAddMethod( ViewGetBackImageOpacity, WrapObjectGeneric );
		AutoAddMethod( ViewSetBackImageOpacity );
		AutoAddMethod( ViewGetBackColor, WrapObjectGeneric );
		AutoAddMethod( ViewSetBackColor );
		AutoAddMethod( ViewGetLineColor, WrapObjectGeneric );
		AutoAddMethod( ViewSetLineColor );
		AutoAddMethod( ViewGetSelectionColor, WrapObjectGeneric );
		AutoAddMethod( ViewSetSelectionColor );
		AutoAddMethod( ViewGetNoFocusSelectionColor, WrapObjectGeneric );
		AutoAddMethod( ViewSetNoFocusSelectionColor );
		AutoAddMethod( ViewGetCaretColor, WrapObjectGeneric );
		AutoAddMethod( ViewSetCaretColor );
		AutoAddMethod( ViewGetSecondaryCaretColor, WrapObjectGeneric );
		AutoAddMethod( ViewSetSecondaryCaretColor );
		AutoAddMethod( ViewGetEolColor, WrapObjectGeneric );
		AutoAddMethod( ViewSetEolColor );
		AutoAddMethod( ViewGetSpaceColor, WrapObjectGeneric );
		AutoAddMethod( ViewSetSpaceColor );
		AutoAddMethod( ViewGetFoldedColor, WrapObjectGeneric );
		AutoAddMethod( ViewSetFoldedColor );
		AutoAddMethod( ViewGetWrapMode, WrapObjectGeneric );
		AutoAddMethod( ViewSetWrapMode );
		AutoAddMethod( ViewGetViewEolSelection, WrapObjectGeneric );
		AutoAddMethod( ViewSetViewEolSelection );
		AutoAddMethod( ViewGetViewEol, WrapObjectGeneric );
		AutoAddMethod( ViewSetViewEol );
		AutoAddMethod( ViewGetViewSpace, WrapObjectGeneric );
		AutoAddMethod( ViewSetViewSpace );
		AutoAddMethod( ViewGetAnnotationView, WrapObjectGeneric );
		AutoAddMethod( ViewSetAnnotationView );
		AutoAddMethod( ViewGetFlowDirection, WrapObjectGeneric );
		AutoAddMethod( ViewSetFlowDirection );
		AutoAddMethod( VmClear );
		AutoAddMethod( VmGetCount, WrapObjectGeneric );
		AutoAddMethod( VmAdd );
		AutoAddMethod( VmRemove );
		AutoAddMethod( VmGet, WrapObjectGeneric );
		AutoAddMethod( VmSet );
		AutoAddMethod( VsReset );
		AutoAddMethod( VsGetCount, WrapObjectGeneric );
		AutoAddMethod( VsAdd );
		AutoAddMethod( VsGetStyle, WrapObjectGeneric );
		AutoAddMethod( VsSetStyle );
		AutoAddMethod( VsGetFont, WrapObjectGeneric );
		AutoAddMethod( VsSetFont );
		AutoAddMethod( VdGetLineExpand, WrapObjectGeneric );
		AutoAddMethod( VdSetLineExpand );
		AutoAddMethod( VdShowAll );
		AutoAddMethod( KeyDefault, WrapObjectGeneric );
		AutoAddMethod( KeyClear, WrapObjectGeneric );
		AutoAddMethod( KeySet, WrapObjectGeneric );
		AutoAddMethod( KeyRemove, WrapObjectGeneric );
	}

	U1 UiCodeEditor::Ctor( const CallbackInfo & ci, UiWindow * p, Napi::Value v )
	{
		m_Doc = ci.NewJsObjectWithOwnership<UiCodeEditorDoc>();
		if ( !m_Doc )
			return false;

		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().GetView().SetMarkerIconManager( p->PublicCloneIconManager() );
		m_Doc->SetDoc( &GetControlTyped().GetDoc() );

		return true;
	}

	UiCodeEditor * UiCodeEditor::DocNew()
	{
		GetControlTyped().NewDoc();
		m_Doc->SetDoc( &GetControlTyped().GetDoc() );
		return this;
	}

	UiCodeEditor * UiCodeEditor::DocLink( UiCodeEditor * p )
	{
		GetControlTyped().SetDoc( p->GetControlTyped().CloneDoc() );
		m_Doc->SetDoc( &GetControlTyped().GetDoc() );
		return this;
	}

	UiCodeEditor * UiCodeEditor::ViewSetBackImage( Byo2Image * img )
	{
		if ( img )
			__GetView().SetBackImage( img->CloneImage() );
		else
			__GetView().SetBackImage( nullptr );
		return this;
	}

	UiCodeEditor * UiCodeEditor::VsAdd( const WrapData<Ui::CodeEditorStyleItem>& sty, Byo2Font * font )
	{
		__GetStyle().Add( sty, font ? font->CloneFont() : nullptr );
		return this;
	}

	Byo2Font * UiCodeEditor::VsGetFont( const CallbackInfo & ci, U32 nIndex ) const
	{
		if ( auto pFont = __GetStyle().GetFont( nIndex ) )
		{
			if ( auto p = ci.NewJsObject<Byo2Font>() )
			{
				p->SetFont( Byo2::Font( pFont, true ) );
				return p;
			}
		}
		return nullptr;
	}

	UiCodeEditor * UiCodeEditor::VsSetFont( U32 nIndex, Byo2Font* pFont )
	{
		__GetStyle().SetFont( nIndex, pFont ? pFont->CloneFont() : nullptr );
		return this;
	}

}
