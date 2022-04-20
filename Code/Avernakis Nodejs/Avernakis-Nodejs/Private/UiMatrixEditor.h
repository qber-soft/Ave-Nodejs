#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiMatrixEditorDoc;
	class UiMatrixEditorView;

	class UiMatrixEditor : public UiControlHelper<UiMatrixEditor, Ui::IMatrixEditor>
	{
	public:
		AveWrapControlCi( UiMatrixEditor );

		~UiMatrixEditor()
		{
		}

		static PCAChar						GetExportName() { return "UiMatrixEditor"; }
		static void							DefineControl();

		U1									Ctor( const CallbackInfo& ci, UiWindow* p, Napi::Value v );

	private:
		using UnitCallback_t    /**/ = JsFuncSafe<void( UiMatrixEditor* sender, S32 x, S32 y, const WrapData<Ui::MatrixUnit>& u )>;
		using OnUnitChangeEnd_t /**/ = JsFuncSafe<U1( UiMatrixEditor* sender, S32 x, S32 y, const WrapData<Ui::MatrixUnit>& u, U1 bCanceled )>;

		UnitCallback_t						m_OnUnitClick;
		UnitCallback_t						m_OnUnitRightClick;
		UnitCallback_t						m_OnUnitChange;
		UnitCallback_t						m_OnUnitChangeBegin;
		OnUnitChangeEnd_t					m_OnUnitChangeEnd;

		JsObject<UiMatrixEditorDoc>			m_Doc{ nullptr };
		UiWindow*							m_Window{ nullptr };

		void								__OnUnitClick( Ui::IMatrixEditor& sender, S32 x, S32 y, const Ui::MatrixUnit& u );
		void								__OnUnitRightClick( Ui::IMatrixEditor& sender, S32 x, S32 y, const Ui::MatrixUnit& u );
		void								__OnUnitChange( Ui::IMatrixEditor& sender, S32 x, S32 y, const Ui::MatrixUnit& u );
		void								__OnUnitChangeBegin( Ui::IMatrixEditor& sender, S32 x, S32 y, const Ui::MatrixUnit& u );
		void								__OnUnitChangeEnd( Ui::IMatrixEditor& sender, S32 x, S32 y, const Ui::MatrixUnit& u, U1& bCanceled );

	private:
		AveInline Ui::IMatrixEditorView&	__GetView() const { return GetControlTyped().GetView(); }

	private:
		UiMatrixEditor*						DocNew();
		UiMatrixEditorDoc*					DocGet() const { return m_Doc; }
		UiMatrixEditor*						DocLink( UiMatrixEditor* p );


		UiMatrixEditor*						ViewReset() { __GetView().Reset(); return this; }
		UiMatrixEditor*						ViewCopyFrom( UiMatrixEditor* p ) { __GetView().CopyFrom( p->__GetView() ); return this; }

		UiMatrixEditor*						ColSetSizeAll( const WrapData<Ui::DpiSize>& nSize ) { __GetView().ColSetSize( nSize ); return this; }
		WrapData<Ui::DpiSize>				ColGetSizeAll() const { return __GetView().ColGetSize(); }
		UiMatrixEditor*						ColSetSize( S32 n, const WrapData<Ui::DpiSize>& nSize ) { __GetView().ColSetSize( n, nSize ); return this; }
		WrapData<Ui::DpiSize>				ColGetSize( S32 n ) const { return __GetView().ColGetSize( n ); }
		UiMatrixEditor*						ColSetVertical( U1 b ) { __GetView().ColSetVertical( b ); return this; }
		U1									ColGetVertical() const { return __GetView().ColGetVertical(); }

		UiMatrixEditor*						RowSetSizeAll( const WrapData<Ui::DpiSize>& nSize ) { __GetView().RowSetSize( nSize ); return this; }
		WrapData<Ui::DpiSize>				RowGetSizeAll() const { return __GetView().RowGetSize(); }
		UiMatrixEditor*						RowSetSize( S32 n, const WrapData<Ui::DpiSize>& nSize ) { __GetView().RowSetSize( n, nSize ); return this; }
		WrapData<Ui::DpiSize>				RowGetSize( S32 n ) const { return __GetView().RowGetSize( n ); }

		UiMatrixEditor*						ViewSetCornerSize( const WrapData<Ui::DpiSize_2>& vSize ) { __GetView().ViewSetCornerSize( vSize ); return this; }
		WrapData<Ui::DpiSize_2>				ViewGetCornerSize() const { return __GetView().ViewGetCornerSize(); }
		WrapPointer<UiControl>				ViewSetCornerContent( WrapPointer<UiControl> c ) { return __ChangeContent( __GetView().ViewSetCornerContent( c->TakeOwnership() ) ); }
		WrapPointer<UiControl>				ViewGetCornerContent() const { return __ReturnContent( __GetView().ViewGetCornerContent() ); }
		UiMatrixEditor*						ViewSetBack( U1 b ) { __GetView().ViewSetBack( b ); return this; }
		U1									ViewGetBack() const { return __GetView().ViewGetBack(); }
		UiMatrixEditor*						ViewSetUnit( U1 b ) { __GetView().ViewSetUnit( b ); return this; }
		U1									ViewGetUnit() const { return __GetView().ViewGetUnit(); }
		UiMatrixEditor*						ViewSetPanel( U1 b ) { __GetView().ViewSetPanel( b ); return this; }
		U1									ViewGetPanel() const { return __GetView().ViewGetPanel(); }
		UiMatrixEditor*						ViewSetColHeader( U1 b ) { __GetView().ViewSetColHeader( b ); return this; }
		U1									ViewGetColHeader() const { return __GetView().ViewGetColHeader(); }
		UiMatrixEditor*						ViewSetRowHeader( U1 b ) { __GetView().ViewSetRowHeader( b ); return this; }
		U1									ViewGetRowHeader() const { return __GetView().ViewGetRowHeader(); }
		UiMatrixEditor*						ViewSetUnitBack( U1 b ) { __GetView().ViewSetUnitBack( b ); return this; }
		U1									ViewGetUnitBack() const { return __GetView().ViewGetUnitBack(); }
		UiMatrixEditor*						ViewSetCursor( U1 b ) { __GetView().ViewSetCursor( b ); return this; }
		U1									ViewGetCursor() const { return __GetView().ViewGetCursor(); }
		UiMatrixEditor*						ViewSetCursorEmpty( U1 b ) { __GetView().ViewSetCursorEmpty( b ); return this; }
		U1									ViewGetCursorEmpty() const { return __GetView().ViewGetCursorEmpty(); }
		UiMatrixEditor*						ViewSetGridX( U1 b ) { __GetView().ViewSetGridX( b ); return this; }
		U1									ViewGetGridX() const { return __GetView().ViewGetGridX(); }
		UiMatrixEditor*						ViewSetGridY( U1 b ) { __GetView().ViewSetGridY( b ); return this; }
		U1									ViewGetGridY() const { return __GetView().ViewGetGridY(); }
		UiMatrixEditor*						ViewSetScrollX( U1 b ) { __GetView().ViewSetScrollX( b ); return this; }
		U1									ViewGetScrollX() const { return __GetView().ViewGetScrollX(); }
		UiMatrixEditor*						ViewSetScrollY( U1 b ) { __GetView().ViewSetScrollY( b ); return this; }
		U1									ViewGetScrollY() const { return __GetView().ViewGetScrollY(); }

		WrapData<S32_R>						UnitGetRect( S32 x, S32 y ) const { S32_R rc{}; __GetView().UnitGetRect( x, y, rc ); return rc; }

		UiMatrixEditor*						SetKnobControlType( Ui::KnobControlType nType ) { __GetView().SetKnobControlType( nType ); return this; }
		Ui::KnobControlType					GetKnobControlType() const { return __GetView().GetKnobControlType(); }

		WrapData<S32_R>						GetEditorRect() const { return __GetView().GetEditorRect(); }

		UiMatrixEditor*						OnUnitClick       /**/( UnitCallback_t    /**/ && fn );
		UiMatrixEditor*						OnUnitRightClick  /**/( UnitCallback_t    /**/ && fn );
		UiMatrixEditor*						OnUnitChange      /**/( UnitCallback_t    /**/ && fn );
		UiMatrixEditor*						OnUnitChangeBegin /**/( UnitCallback_t    /**/ && fn );
		UiMatrixEditor*						OnUnitChangeEnd   /**/( OnUnitChangeEnd_t /**/ && fn );
	};
}
