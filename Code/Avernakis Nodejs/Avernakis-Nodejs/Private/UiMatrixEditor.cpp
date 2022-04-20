#include "StdAfx.h"
#include "UiMatrixEditor.h"
#include "UiMatrixEditorDoc.h"

#define ThisMethod($x) &UiMatrixEditor::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiMatrixEditor::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiMatrixEditor> c_obj;
	}

	void UiMatrixEditor::DefineControl()
	{
		//AutoAddMethod( SetText );


		AutoAddMethod( DocNew );
		AutoAddMethod( DocGet );
		AutoAddMethod( DocLink );

		AutoAddMethod( ViewReset );
		AutoAddMethod( ViewCopyFrom );

		AutoAddMethod( ColSetSizeAll );
		AutoAddMethod( ColGetSizeAll, WrapObjectGeneric );
		AutoAddMethod( ColSetSize );
		AutoAddMethod( ColGetSize, WrapObjectGeneric );
		AutoAddMethod( ColSetVertical );
		AutoAddMethod( ColGetVertical, WrapObjectGeneric );

		AutoAddMethod( RowSetSizeAll );
		AutoAddMethod( RowGetSizeAll, WrapObjectGeneric );
		AutoAddMethod( RowSetSize );
		AutoAddMethod( RowGetSize, WrapObjectGeneric );

		AutoAddMethod( ViewSetCornerSize );
		AutoAddMethod( ViewGetCornerSize, WrapObjectGeneric );
		AutoAddMethod( ViewSetCornerContent );
		AutoAddMethod( ViewGetCornerContent, WrapObjectGeneric );
		AutoAddMethod( ViewSetBack );
		AutoAddMethod( ViewGetBack, WrapObjectGeneric );
		AutoAddMethod( ViewSetUnit );
		AutoAddMethod( ViewGetUnit, WrapObjectGeneric );
		AutoAddMethod( ViewSetPanel );
		AutoAddMethod( ViewGetPanel, WrapObjectGeneric );
		AutoAddMethod( ViewSetColHeader );
		AutoAddMethod( ViewGetColHeader, WrapObjectGeneric );
		AutoAddMethod( ViewSetRowHeader );
		AutoAddMethod( ViewGetRowHeader, WrapObjectGeneric );
		AutoAddMethod( ViewSetUnitBack );
		AutoAddMethod( ViewGetUnitBack, WrapObjectGeneric );
		AutoAddMethod( ViewSetCursor );
		AutoAddMethod( ViewGetCursor, WrapObjectGeneric );
		AutoAddMethod( ViewSetCursorEmpty );
		AutoAddMethod( ViewGetCursorEmpty, WrapObjectGeneric );
		AutoAddMethod( ViewSetGridX );
		AutoAddMethod( ViewGetGridX, WrapObjectGeneric );
		AutoAddMethod( ViewSetGridY );
		AutoAddMethod( ViewGetGridY, WrapObjectGeneric );
		AutoAddMethod( ViewSetScrollX );
		AutoAddMethod( ViewGetScrollX, WrapObjectGeneric );
		AutoAddMethod( ViewSetScrollY );
		AutoAddMethod( ViewGetScrollY, WrapObjectGeneric );

		AutoAddMethod( UnitGetRect, WrapObjectGeneric );

		AutoAddMethod( SetKnobControlType );
		AutoAddMethod( GetKnobControlType, WrapObjectGeneric );

		AutoAddMethod( GetEditorRect, WrapObjectGeneric );

		AutoAddMethod( OnUnitClick, WrapObjectGeneric );
		AutoAddMethod( OnUnitRightClick, WrapObjectGeneric );
		AutoAddMethod( OnUnitChange, WrapObjectGeneric );
		AutoAddMethod( OnUnitChangeBegin, WrapObjectGeneric );
		AutoAddMethod( OnUnitChangeEnd, WrapObjectGeneric );
	}

	U1 UiMatrixEditor::Ctor( const CallbackInfo& ci, UiWindow * p, Napi::Value v )
	{
		m_Doc = ci.NewJsObjectWithOwnership<UiMatrixEditorDoc>();
		if ( !m_Doc )
			return false;

		if ( !__CreateControl( p, v ) )
			return false;

		m_Window = p;

		GetControlTyped().GetDoc().SetIconManager( p->PublicCloneIconManager() );
		m_Doc->SetDoc( &GetControlTyped().GetDoc() );

		return true;
	}

	void UiMatrixEditor::__OnUnitClick( Ui::IMatrixEditor & sender, S32 x, S32 y, const Ui::MatrixUnit & u )
	{
		m_OnUnitClick( this, x, y, u );
	}

	void UiMatrixEditor::__OnUnitRightClick( Ui::IMatrixEditor & sender, S32 x, S32 y, const Ui::MatrixUnit & u )
	{
		m_OnUnitRightClick( this, x, y, u );
	}

	void UiMatrixEditor::__OnUnitChange( Ui::IMatrixEditor & sender, S32 x, S32 y, const Ui::MatrixUnit & u )
	{
		m_OnUnitChange( this, x, y, u );
	}

	void UiMatrixEditor::__OnUnitChangeBegin( Ui::IMatrixEditor & sender, S32 x, S32 y, const Ui::MatrixUnit & u )
	{
		m_OnUnitChangeBegin( this, x, y, u );
	}

	void UiMatrixEditor::__OnUnitChangeEnd( Ui::IMatrixEditor & sender, S32 x, S32 y, const Ui::MatrixUnit & u, U1 & bCanceled )
	{
		U1 r = true;
		m_OnUnitChangeEnd.BlockCall( this, x, y, u, bCanceled, r );
		bCanceled = !r;
	}

	UiMatrixEditor * UiMatrixEditor::DocNew()
	{
		GetControlTyped().NewDoc();
		GetControlTyped().GetDoc().SetIconManager( m_Window->PublicCloneIconManager() );
		m_Doc->SetDoc( &GetControlTyped().GetDoc() );
		return this;
	}

	UiMatrixEditor * UiMatrixEditor::DocLink( UiMatrixEditor * p )
	{
		GetControlTyped().SetDoc( p->GetControlTyped().CloneDoc() );
		m_Doc->SetDoc( &GetControlTyped().GetDoc() );
		return this;
	}

	UiMatrixEditor* UiMatrixEditor::OnUnitClick       /**/( UnitCallback_t    /**/ && fn ) { m_OnUnitClick       /**/ = SetEventCallback<Ui::IMatrixEditor::OnUnitClick       /**/>( std::move( fn ), MakeThisFunc( __OnUnitClick       /**/ ) ); return this; }
	UiMatrixEditor* UiMatrixEditor::OnUnitRightClick  /**/( UnitCallback_t    /**/ && fn ) { m_OnUnitRightClick  /**/ = SetEventCallback<Ui::IMatrixEditor::OnUnitRightClick  /**/>( std::move( fn ), MakeThisFunc( __OnUnitRightClick  /**/ ) ); return this; }
	UiMatrixEditor* UiMatrixEditor::OnUnitChange      /**/( UnitCallback_t    /**/ && fn ) { m_OnUnitChange      /**/ = SetEventCallback<Ui::IMatrixEditor::OnUnitChange      /**/>( std::move( fn ), MakeThisFunc( __OnUnitChange      /**/ ) ); return this; }
	UiMatrixEditor* UiMatrixEditor::OnUnitChangeBegin /**/( UnitCallback_t    /**/ && fn ) { m_OnUnitChangeBegin /**/ = SetEventCallback<Ui::IMatrixEditor::OnUnitChangeBegin /**/>( std::move( fn ), MakeThisFunc( __OnUnitChangeBegin /**/ ) ); return this; }
	UiMatrixEditor* UiMatrixEditor::OnUnitChangeEnd   /**/( OnUnitChangeEnd_t /**/ && fn ) { m_OnUnitChangeEnd   /**/ = SetEventCallback<Ui::IMatrixEditor::OnUnitChangeEnd   /**/>( std::move( fn ), MakeThisFunc( __OnUnitChangeEnd   /**/ ) ); return this; }

}
