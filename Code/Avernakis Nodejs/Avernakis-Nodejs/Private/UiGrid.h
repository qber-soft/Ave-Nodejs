#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiGridDef
	{
	public:
		WrapData<Ui::DpiSize>	m_Size;
		WrapData<Ui::DpiSize>	m_Minimum;
		WrapData<Ui::DpiSize>	m_Maximum;

		static AveInline UiGridDef From( const Ui::GridDefinition& gd ) { return { gd.m_Size, gd.m_Minimum, gd.m_Maximum }; }
		AveInline operator Ui::GridDefinition() const { return { m_Size, m_Minimum, m_Maximum }; }
	};

	NavDefineDataByMember_( UiGridDef, Size, Minimum, Maximum );

	class UiGridControl : public WrapObject<UiGridControl, void(), WrapObjectUi>
	{
	public:
		AveWrapObject( UiGridControl );

		static PCAChar					GetExportName() { return "650663d972fd4a0b8f7d2b3c0193f93c"; }
		static void						DefineObject();

		U1								Ctor() { return true; }
		Napi::Value						GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Ui::IGridControl*				m_Control;

	private:
		WrapPointer<UiControl>			GetControl() { return { (UiControl*) m_Control->GetControl()->GetUserContext() }; }

		UiGridControl*					SetDock( Ui::DockMode n ) { m_Control->SetDock( n ); return this; }
		Ui::DockMode					GetDock() { return m_Control->GetDock(); }
		UiGridControl*					SetAnchor( U32 n ) { m_Control->SetAnchor( n ); return this; }
		U32								GetAnchor() { return m_Control->GetAnchor(); }
		UiGridControl*					SetMargin( const WrapData<Ui::S32_DpiMargin>& v ) { m_Control->SetMargin( v ); return this; }
		WrapData<Ui::S32_DpiMargin>		GetMargin() { return m_Control->GetMargin(); }
		UiGridControl*					SetGrid( S32 x, S32 y, S32 xspan, S32 yspan ) { m_Control->SetGrid( x, y, xspan, yspan ); return this; }
		WrapData<S32_4>					GetGrid() { auto& t = m_Control->GetGrid(); return S32_4{ t.m_Col, t.m_Row, t.m_ColSpan, t.m_RowSpan }; }
		UiGridControl*					SetPos( const WrapData<Ui::DpiSize_2>& v ) { m_Control->SetPosition( v ); return this; }
		UiGridControl*					SetSize( const WrapData<Ui::DpiSize_2>& v ) { m_Control->SetSize( v ); return this; }
		UiGridControl*					SetPosZ( S32 z ) { m_Control->SetPositionZ( z ); return this; }
		S32								GetPosZ() { return m_Control->GetPositionZ(); }
		UiGridControl*					BringToFront() { m_Control->BringToFront(); return this; }
		UiGridControl*					BringToBack() { m_Control->BringToBack(); return this; }

	public:
		AveInline void					SetControl( Ui::IGridControl* p ) { m_Control = p; }
	};

	class UiGrid : public UiControlHelper<UiGrid, Ui::IGrid>
	{
	public:
		AveWrapControl( UiGrid );

		static PCAChar					GetExportName() { return "UiGrid"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		UiGridControl*					__GridGetControl( const MixCallContext& cc, UiControl* p );

	private:
		UiGrid*							SetBackground( U1 b ) { GetControlTyped().SetBackground( b ); return this; }
		U1								GetBackground() const { return GetControlTyped().GetBackground(); }

		UiGrid*							SetBackColor( const WrapData<U8_4>& v ) { GetControlTyped().SetBackColor( v ); return this; }
		WrapData<U8_4>					GetBackColor() const { return GetControlTyped().GetBackColor(); }

		UiGrid*							SetSplitterX( const WrapData<Ui::DpiSize>& v ) { GetControlTyped().GridSetSplitterX( v ); return this; }
		WrapData<Ui::DpiSize>			GetSplitterX() const { return GetControlTyped().GridGetSplitterX(); }
		UiGrid*							SetSplitterY( const WrapData<Ui::DpiSize>& v ) { GetControlTyped().GridSetSplitterY( v ); return this; }
		WrapData<Ui::DpiSize>			GetSplitterY() const { return GetControlTyped().GridGetSplitterY(); }

		UiGrid*							RowClear() { GetControlTyped().GridClearRow(); return this; }
		U32								RowGetCount() const { return GetControlTyped().GridGetRowCount(); }
		S32								RowGetOffset( U32 nIndex ) const { return GetControlTyped().GridGetRowOffset( nIndex ); }
		S32								RowGetSize( U32 nIndex ) const { return GetControlTyped().GridGetRowSize( nIndex ); }
		WrapData<UiGridDef>				RowGetDef( U32 nIndex ) const { return UiGridDef::From( GetControlTyped().GridGetRowDef( nIndex ) ); }
		UiGrid*							RowAdd( const WrapData<UiGridDef>& def ) { GetControlTyped().GridAddRow( def ); return this; }
		UiGrid*							RowInsert( S32 nInsertBefore, const WrapData<UiGridDef>& def ) { GetControlTyped().GridInsertRow( nInsertBefore, def ); return this; }
		UiGrid*							RowRemove( S32 nIndex ) { GetControlTyped().GridRemoveRow( nIndex ); return this; }
		UiGrid*							RowSet( U32 nIndex, const WrapData<Ui::DpiSize>& n ) { GetControlTyped().GridSetRow( nIndex, n ); return this; }
		UiGrid*							RowSetDef( U32 nIndex, const WrapData<UiGridDef>& def ) { GetControlTyped().GridSetRow( nIndex, def ); return this; }

		UiGrid*							ColClear() { GetControlTyped().GridClearColumn(); return this; }
		U32								ColGetCount() const { return GetControlTyped().GridGetColumnCount(); }
		S32								ColGetOffset( U32 nIndex ) const { return GetControlTyped().GridGetColumnOffset( nIndex ); }
		S32								ColGetSize( U32 nIndex ) const { return GetControlTyped().GridGetColumnSize( nIndex ); }
		WrapData<UiGridDef>				ColGetDef( U32 nIndex ) const { return UiGridDef::From( GetControlTyped().GridGetColumnDef( nIndex ) ); }
		UiGrid*							ColAdd( const WrapData<UiGridDef>& def ) { GetControlTyped().GridAddColumn( def ); return this; }
		UiGrid*							ColInsert( S32 nInsertBefore, const WrapData<UiGridDef>& def ) { GetControlTyped().GridInsertColumn( nInsertBefore, def ); return this; }
		UiGrid*							ColRemove( S32 nIndex ) { GetControlTyped().GridRemoveColumn( nIndex ); return this; }
		UiGrid*							ColSet( U32 nIndex, const WrapData<Ui::DpiSize>& n ) { GetControlTyped().GridSetColumn( nIndex, n ); return this; }
		UiGrid*							ColSetDef( U32 nIndex, const WrapData<UiGridDef>& def ) { GetControlTyped().GridSetColumn( nIndex, def ); return this; }

		U1								ControlAdd( WrapPointer<UiControl> c, U1 bParasite ) { return !!GetControlTyped().ControlAdd( std::move( c->TakeOwnership() ), bParasite ); }
		UiGridControl*					ControlGet( const MixCallContext& cc, WrapPointer<UiControl> c ) { return __GridGetControl( cc, c ); }
		WrapPointer<UiControl>			ControlRemove( WrapPointer<UiControl> c ) { return __ChangeContent( GetControlTyped().ControlRemove( &c->GetControl() ) ); }
		UiGrid*							ControlRemoveAll() { GetControlTyped().ControlRemoveAll(); return this; }
	};
}
