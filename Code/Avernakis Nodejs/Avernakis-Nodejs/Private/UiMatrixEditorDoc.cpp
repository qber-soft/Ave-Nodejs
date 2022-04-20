#include "StdAfx.h"
#include "UiMatrixEditorDoc.h"

#define ThisMethod($x) &UiMatrixEditorDoc::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiMatrixEditorDoc::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiMatrixEditorDoc> c_obj;
	}

	void UiMatrixEditorDoc::DefineObject()
	{
		AutoAddMethod( SetDimension );
		AutoAddMethod( GetDimension, WrapObjectGeneric );

		AutoAddMethod( SetVirtualUnit );
		AutoAddMethod( SetVirtualColHeader );
		AutoAddMethod( SetVirtualRowHeader );

		AutoAddMethod( SetUnit );
		AutoAddMethod( GetUnit, WrapObjectGeneric );
		AutoAddMethod( SetUnitBackColor );
		AutoAddMethod( GetUnitBackColor, WrapObjectGeneric );
		AutoAddMethod( SetUnitForeColor );
		AutoAddMethod( GetUnitForeColor, WrapObjectGeneric );
		AutoAddMethod( SetUnitFillColor );
		AutoAddMethod( GetUnitFillColor, WrapObjectGeneric );

		AutoAddMethod( ColClearName );
		AutoAddMethod( ColSetName );
		AutoAddMethod( ColGetName, WrapObjectGeneric );
		AutoAddMethod( ColClearSplitter );
		AutoAddMethod( ColSetSplitter );
		AutoAddMethod( ColGetSplitter, WrapObjectGeneric );
		AutoAddMethod( ColSetIcon );
		AutoAddMethod( ColGetIcon, WrapObjectGeneric );
		AutoAddMethod( ColSetBackColor );
		AutoAddMethod( ColGetBackColor, WrapObjectGeneric );
		AutoAddMethod( ColSetVisible );
		AutoAddMethod( ColGetVisible, WrapObjectGeneric );
		AutoAddMethod( ColSetEnable );
		AutoAddMethod( ColGetEnable, WrapObjectGeneric );

		AutoAddMethod( RowClearName );
		AutoAddMethod( RowSetName );
		AutoAddMethod( RowGetName, WrapObjectGeneric );
		AutoAddMethod( RowClearSplitter );
		AutoAddMethod( RowSetSplitter );
		AutoAddMethod( RowGetSplitter, WrapObjectGeneric );
		AutoAddMethod( RowSetIcon );
		AutoAddMethod( RowGetIcon, WrapObjectGeneric );
		AutoAddMethod( RowSetBackColor );
		AutoAddMethod( RowGetBackColor, WrapObjectGeneric );
		AutoAddMethod( RowSetVisible );
		AutoAddMethod( RowGetVisible, WrapObjectGeneric );
		AutoAddMethod( RowSetEnable );
		AutoAddMethod( RowGetEnable, WrapObjectGeneric );

		AutoAddMethod( ViewSetValueFormat );

		AutoAddMethod( Redraw );
	}

	void UiMatrixEditorDoc::OnVirtualUnit( Ui::IMatrixEditorDoc & sender, S32 x, S32 y, Ui::MatrixUnit & u )
	{
		WrapData<Ui::MatrixUnit> r;
		m_VirtualUnit.BlockCall( this, x, y, r );
		u = r;
	}

	void UiMatrixEditorDoc::OnVirtualCol( Ui::IMatrixEditorDoc & sender, S32 n, WString & s )
	{
		m_VirtualCol.BlockCall( this, n, s );
	}

	void UiMatrixEditorDoc::OnVirtualRow( Ui::IMatrixEditorDoc & sender, S32 n, WString & s )
	{
		m_VirtualRow.BlockCall( this, n, s );
	}

	void UiMatrixEditorDoc::OnVirtualFormat( Ui::IMatrixEditorDoc & sender, S32 x, S32 y, R32 v, WString & s )
	{
		m_VirtualFormat.BlockCall( this, x, y, v, s );
	}

	UiMatrixEditorDoc * UiMatrixEditorDoc::SetVirtualUnit( VirtualUnit_t && unit )
	{
		m_VirtualUnit = std::move( unit );
		if ( m_VirtualUnit )
			m_Doc->SetVirtualUnit( MakeThisFunc( OnVirtualUnit ) );
		else
			m_Doc->SetVirtualUnit( {} );
		return this;
	}

	UiMatrixEditorDoc * UiMatrixEditorDoc::SetVirtualColHeader( VirtualHeader_t && header )
	{
		m_VirtualCol = std::move( header );
		if ( m_VirtualCol )
			m_Doc->SetVirtualColHeader( MakeThisFunc( OnVirtualCol ) );
		else
			m_Doc->SetVirtualColHeader( {} );
		return this;
	}

	UiMatrixEditorDoc * UiMatrixEditorDoc::SetVirtualRowHeader( VirtualHeader_t && header )
	{
		m_VirtualRow = std::move( header );
		if ( m_VirtualRow )
			m_Doc->SetVirtualRowHeader( MakeThisFunc( OnVirtualRow ) );
		else
			m_Doc->SetVirtualRowHeader( {} );
		return this;
	}

	UiMatrixEditorDoc * UiMatrixEditorDoc::ViewSetValueFormat( VirtualFormat_t && fmt )
	{
		m_VirtualFormat = std::move( fmt );
		if ( m_VirtualFormat )
			m_Doc->ViewSetValueFormat( MakeThisFunc( OnVirtualFormat ) );
		else
			m_Doc->ViewSetValueFormat( {} );
		return this;
	}

	void UiMatrixEditorDoc::SetDoc( Ui::IMatrixEditorDoc * p )
	{
		if ( m_Doc )
		{
			m_Doc->SetVirtualUnit( {} );
			m_Doc->SetVirtualColHeader( {} );
			m_Doc->SetVirtualRowHeader( {} );
			m_Doc->ViewSetValueFormat( {} );
		}
		m_Doc = p;
		if ( m_Doc )
		{
			if ( m_VirtualUnit )
				m_Doc->SetVirtualUnit( MakeThisFunc( OnVirtualUnit ) );
			if ( m_VirtualCol )
				m_Doc->SetVirtualColHeader( MakeThisFunc( OnVirtualCol ) );
			if ( m_VirtualRow )
				m_Doc->SetVirtualRowHeader( MakeThisFunc( OnVirtualRow ) );
			if ( m_VirtualFormat )
				m_Doc->ViewSetValueFormat( MakeThisFunc( OnVirtualFormat ) );
		}
	}

}
