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
		AutoAddMethod( ColGetSizeAll );
		AutoAddMethod( ColSetSize );
		AutoAddMethod( ColGetSize );
		AutoAddMethod( ColSetVertical );
		AutoAddMethod( ColGetVertical );

		AutoAddMethod( RowSetSizeAll );
		AutoAddMethod( RowGetSizeAll );
		AutoAddMethod( RowSetSize );
		AutoAddMethod( RowGetSize );

		AutoAddMethod( ViewSetCornerSize );
		AutoAddMethod( ViewGetCornerSize );
		AutoAddMethod( ViewSetCornerContent );
		AutoAddMethod( ViewGetCornerContent );
		AutoAddMethod( ViewSetBack );
		AutoAddMethod( ViewGetBack );
		AutoAddMethod( ViewSetUnit );
		AutoAddMethod( ViewGetUnit );
		AutoAddMethod( ViewSetPanel );
		AutoAddMethod( ViewGetPanel );
		AutoAddMethod( ViewSetColHeader );
		AutoAddMethod( ViewGetColHeader );
		AutoAddMethod( ViewSetRowHeader );
		AutoAddMethod( ViewGetRowHeader );
		AutoAddMethod( ViewSetUnitBack );
		AutoAddMethod( ViewGetUnitBack );
		AutoAddMethod( ViewSetCursor );
		AutoAddMethod( ViewGetCursor );
		AutoAddMethod( ViewSetCursorEmpty );
		AutoAddMethod( ViewGetCursorEmpty );
		AutoAddMethod( ViewSetGridX );
		AutoAddMethod( ViewGetGridX );
		AutoAddMethod( ViewSetGridY );
		AutoAddMethod( ViewGetGridY );
		AutoAddMethod( ViewSetScrollX );
		AutoAddMethod( ViewGetScrollX );
		AutoAddMethod( ViewSetScrollY );
		AutoAddMethod( ViewGetScrollY );

		AutoAddMethod( UnitGetRect );

		AutoAddMethod( SetKnobControlType );
		AutoAddMethod( GetKnobControlType );

		AutoAddMethod( GetEditorRect );

		AutoAddMethod( OnUnitClick );
		AutoAddMethod( OnUnitRightClick );
		AutoAddMethod( OnUnitChange );
		AutoAddMethod( OnUnitChangeBegin );
		AutoAddMethod( OnUnitChangeEnd );
	}

	U1 UiMatrixEditor::Ctor( const CallbackInfo& ci, UiWindow * p, Napi::Value v )
	{
		m_Doc = ci.NewJsObjectWithOwnership<UiMatrixEditorDoc>();
		if ( !m_Doc )
			return false;

		if ( !__CreateControl( p, v ) )
			return false;

		m_Window = p;

		GetControlTyped().GetEvent<Ui::IMatrixEditor::OnUnitClick       /**/>() += MakeThisFunc( __OnUnitClick       /**/ );
		GetControlTyped().GetEvent<Ui::IMatrixEditor::OnUnitRightClick  /**/>() += MakeThisFunc( __OnUnitRightClick  /**/ );
		GetControlTyped().GetEvent<Ui::IMatrixEditor::OnUnitChange      /**/>() += MakeThisFunc( __OnUnitChange      /**/ );
		GetControlTyped().GetEvent<Ui::IMatrixEditor::OnUnitChangeBegin /**/>() += MakeThisFunc( __OnUnitChangeBegin /**/ );
		GetControlTyped().GetEvent<Ui::IMatrixEditor::OnUnitChangeEnd   /**/>() += MakeThisFunc( __OnUnitChangeEnd   /**/ );

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

}
