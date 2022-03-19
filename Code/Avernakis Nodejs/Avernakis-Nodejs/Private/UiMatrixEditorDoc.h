#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiMatrixUnit
	{
	public:
		U32					m_Type;
		U8					m_Flag;
		R32					m_DataValue;
		Ui::IconCache		m_DataIcon;
		WrapData<U8_4>		m_DataColor;
		WrapData<U8_4>		m_BackColor;
		WrapData<U8_4>		m_ForeColor;
		WrapData<U8_4>		m_FillColor;
	};

	NavDefineDataByMember_( UiMatrixUnit, Type, Flag, DataValue, DataIcon, DataColor, BackColor, ForeColor, FillColor );

	template<>
	class WrapDataTransit<Ui::MatrixUnit> : public WrapDataTransitHelper<Ui::MatrixUnit, UiMatrixUnit>
	{
	public:
		static void Transit( Ui::MatrixUnit& d, const UiMatrixUnit& s )
		{
			AveZeroObject( d );
			d.m_Type = (Ui::MatrixUnitType) s.m_Type;
			d.m_Flag = s.m_Flag;
			switch ( d.m_Type )
			{
			case Ui::MatrixUnitType::Empty  /**/: break;
			case Ui::MatrixUnitType::Switch /**/: d.m_DataSwitch = 0 != s.m_DataValue; break;
			case Ui::MatrixUnitType::Pointer/**/: [[fallthrough]];
			case Ui::MatrixUnitType::Value  /**/: [[fallthrough]];
			case Ui::MatrixUnitType::Pie    /**/: [[fallthrough]];
			case Ui::MatrixUnitType::Pan    /**/: d.m_DataValue = s.m_DataValue; break;
			case Ui::MatrixUnitType::Icon   /**/: d.m_DataIcon = s.m_DataIcon; break;
			case Ui::MatrixUnitType::Color  /**/: d.m_DataColor = s.m_DataColor; break;
			}
			d.m_BackColor = s.m_BackColor;
			d.m_ForeColor = s.m_ForeColor;
			d.m_FillColor = s.m_FillColor;
		}

		static void Transit( UiMatrixUnit& d, const Ui::MatrixUnit& s )
		{
			d.m_Type = (U32) s.m_Type;
			d.m_Flag = s.m_Flag;
			d.m_DataValue = 0.f;
			d.m_DataIcon = 0;
			d.m_DataColor = {};
			switch ( s.m_Type )
			{
			case Ui::MatrixUnitType::Empty  /**/: break;
			case Ui::MatrixUnitType::Switch /**/: d.m_DataValue = s.m_DataSwitch ? 1.f : 0.f; break;
			case Ui::MatrixUnitType::Pointer/**/: [[fallthrough]];
			case Ui::MatrixUnitType::Value  /**/: [[fallthrough]];
			case Ui::MatrixUnitType::Pie    /**/: [[fallthrough]];
			case Ui::MatrixUnitType::Pan    /**/: d.m_DataValue = s.m_DataValue; break;
			case Ui::MatrixUnitType::Icon   /**/: d.m_DataIcon = s.m_DataIcon; break;
			case Ui::MatrixUnitType::Color  /**/: d.m_DataColor = s.m_DataColor; break;
			}
			d.m_BackColor = s.m_BackColor;
			d.m_ForeColor = s.m_ForeColor;
			d.m_FillColor = s.m_FillColor;
		}
	};

	class UiMatrixEditorDoc : public WrapObject<UiMatrixEditorDoc, void(), WrapObjectUi>
	{
	public:
		AveWrapObject( UiMatrixEditorDoc );

		static PCAChar					GetExportName() { return "bb18e623a032413b865d94b3827672d6"; }
		static void						DefineObject();

		U1								Ctor() { return true; }
		Napi::Value						GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		void							OnVirtualUnit( Ui::IMatrixEditorDoc& sender, S32 x, S32 y, Ui::MatrixUnit& u );
		void							OnVirtualCol( Ui::IMatrixEditorDoc& sender, S32 n, WString& s );
		void							OnVirtualRow( Ui::IMatrixEditorDoc& sender, S32 n, WString& s );
		void							OnVirtualFormat( Ui::IMatrixEditorDoc& sender, S32 x, S32 y, R32 v, WString& s );

	private:
		using VirtualUnit_t   /**/ = JsFuncSafe<WrapData<Ui::MatrixUnit>( UiMatrixEditorDoc* sender, S32 x, S32 y )>;
		using VirtualHeader_t /**/ = JsFuncSafe<WString( UiMatrixEditorDoc* sender, S32 n )>;
		using VirtualFormat_t /**/ = JsFuncSafe<WString( UiMatrixEditorDoc* sender, S32 x, S32 y, R32 v )>;

		Ui::IMatrixEditorDoc*			m_Doc{ nullptr };

		VirtualUnit_t					m_VirtualUnit;
		VirtualHeader_t					m_VirtualCol;
		VirtualHeader_t					m_VirtualRow;
		VirtualFormat_t					m_VirtualFormat;

	private:
		UiMatrixEditorDoc*				SetDimension( const WrapData<S32_2>& vSize ) { m_Doc->SetDimension( vSize ); return this; }
		WrapData<S32_2>					GetDimension() const { return m_Doc->GetDimension(); }

		UiMatrixEditorDoc*				SetVirtualUnit( VirtualUnit_t&& unit );
		UiMatrixEditorDoc*				SetVirtualColHeader( VirtualHeader_t&& header );
		UiMatrixEditorDoc*				SetVirtualRowHeader( VirtualHeader_t&& header );

		UiMatrixEditorDoc*				SetUnit( S32 x, S32 y, const WrapData<Ui::MatrixUnit>& u ) { m_Doc->SetUnit( x, y, u ); return this; }
		WrapData<Ui::MatrixUnit>		GetUnit( S32 x, S32 y ) const { return m_Doc->GetUnit( x, y ); }
		UiMatrixEditorDoc*				SetUnitBackColor( const WrapData<U8_4>& vColor ) { m_Doc->SetUnitBackColor( vColor ); return this; }
		WrapData<U8_4>					GetUnitBackColor() const { return m_Doc->GetUnitBackColor(); }
		UiMatrixEditorDoc*				SetUnitForeColor( const WrapData<U8_4>& vColor ) { m_Doc->SetUnitForeColor( vColor ); return this; }
		WrapData<U8_4>					GetUnitForeColor() const { return m_Doc->GetUnitForeColor(); }
		UiMatrixEditorDoc*				SetUnitFillColor( const WrapData<U8_4>& vColor ) { m_Doc->SetUnitFillColor( vColor ); return this; }
		WrapData<U8_4>					GetUnitFillColor() const { return m_Doc->GetUnitFillColor(); }

		UiMatrixEditorDoc*				ColClearName() { m_Doc->ColClearName(); return this; }
		UiMatrixEditorDoc*				ColSetName( S32 n, PCWChar szName ) { m_Doc->ColSetName( n, szName ); return this; }
		WString							ColGetName( S32 n ) const { return m_Doc->ColGetName( n ); }
		UiMatrixEditorDoc*				ColClearSplitter() { m_Doc->ColClearSplitter(); return this; }
		UiMatrixEditorDoc*				ColSetSplitter( S32 n, const WrapData<Ui::DpiSize>& nSize ) { m_Doc->ColSetSplitter( n, nSize ); return this; }
		WrapData<Ui::DpiSize>			ColGetSplitter( S32 n ) const { return m_Doc->ColGetSplitter( n ); }
		UiMatrixEditorDoc*				ColSetIcon( S32 n, Ui::IconCache nIcon ) { m_Doc->ColSetIcon( n, nIcon ); return this; }
		Ui::IconCache					ColGetIcon( S32 n ) const { return m_Doc->ColGetIcon( n ); }
		UiMatrixEditorDoc*				ColSetBackColor( S32 n, const WrapData<U8_4>& vColor ) { m_Doc->ColSetBackColor( n, vColor ); return this; }
		WrapData<U8_4>					ColGetBackColor( S32 n ) const { return m_Doc->ColGetBackColor( n ); }
		UiMatrixEditorDoc*				ColSetVisible( S32 n, U1 b ) { m_Doc->ColSetVisible( n, b ); return this; }
		U1								ColGetVisible( S32 n ) const { return m_Doc->ColGetVisible( n ); }
		UiMatrixEditorDoc*				ColSetEnable( S32 n, U1 b ) { m_Doc->ColSetEnable( n, b ); return this; }
		U1								ColGetEnable( S32 n ) const { return m_Doc->ColGetEnable( n ); }

		UiMatrixEditorDoc*				RowClearName() { m_Doc->RowClearName(); return this; }
		UiMatrixEditorDoc*				RowSetName( S32 n, PCWChar szName ) { m_Doc->RowSetName( n, szName ); return this; }
		WString							RowGetName( S32 n ) const { return m_Doc->RowGetName( n ); }
		UiMatrixEditorDoc*				RowClearSplitter() { m_Doc->RowClearSplitter(); return this; }
		UiMatrixEditorDoc*				RowSetSplitter( S32 n, const WrapData<Ui::DpiSize>& nSize ) { m_Doc->RowSetSplitter( n, nSize ); return this; }
		WrapData<Ui::DpiSize>			RowGetSplitter( S32 n ) const { return m_Doc->RowGetSplitter( n ); }
		UiMatrixEditorDoc*				RowSetIcon( S32 n, Ui::IconCache nIcon ) { m_Doc->RowSetIcon( n, nIcon ); return this; }
		Ui::IconCache					RowGetIcon( S32 n ) const { return m_Doc->RowGetIcon( n ); }
		UiMatrixEditorDoc*				RowSetBackColor( S32 n, const WrapData<U8_4>& vColor ) { m_Doc->RowSetBackColor( n, vColor ); return this; }
		WrapData<U8_4>					RowGetBackColor( S32 n ) const { return m_Doc->RowGetBackColor( n ); }
		UiMatrixEditorDoc*				RowSetVisible( S32 n, U1 b ) { m_Doc->RowSetVisible( n, b ); return this; }
		U1								RowGetVisible( S32 n ) const { return m_Doc->RowGetVisible( n ); }
		UiMatrixEditorDoc*				RowSetEnable( S32 n, U1 b ) { m_Doc->RowSetEnable( n, b ); return this; }
		U1								RowGetEnable( S32 n ) const { return m_Doc->RowGetEnable( n ); }

		UiMatrixEditorDoc*				ViewSetValueFormat( VirtualFormat_t&& fmt );

		UiMatrixEditorDoc*				Redraw() { m_Doc->Redraw(); return this; }

	public:
		void							SetDoc( Ui::IMatrixEditorDoc* p );
	};
}
