#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiScrollBar : public UiControlHelper<UiScrollBar, Ui::IScrollBar>
	{
	public:
		AveWrapControl( UiScrollBar );

		~UiScrollBar()
		{
		}

		static PCAChar					GetExportName() { return "UiScrollBar"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnScroll_t				= JsFuncSafe<void( UiScrollBar*, U1 )>;
		using OnScrolling_t				= JsFuncSafe<void( UiScrollBar* )>;
		using OnPageChange_t			= JsFuncSafe<void( UiScrollBar*, R32 )>;

		OnScroll_t						m_OnScroll;
		OnScrolling_t					m_OnScrolling;
		OnPageChange_t					m_OnPageChange;

	private:
		void							__OnScroll    ( Ui::IScrollBar& sender, U1 bThumb );
		void							__OnScrolling ( Ui::IScrollBar& sender );
		void							__OnPageChange( Ui::IScrollBar& sender, R32 fPagePercent );

	private:
		UiScrollBar*					SetOrientation( Ui::ScrollOrientation nOrient ) { GetControlTyped().SetOrientation( nOrient ); return this; }
		Ui::ScrollOrientation			GetOrientation() const { return GetControlTyped().GetOrientation(); }
		Ui::ScrollOrientation			GetOrientationActually() const { return GetControlTyped().GetOrientationActually(); }

		UiScrollBar*					SetShrink( U1 b ) { GetControlTyped().SetShrink( b ); return this; }
		U1								GetShrink() const { return GetControlTyped().GetShrink(); }

		UiScrollBar*					SetArrowVisible( U1 b ) { GetControlTyped().SetArrowVisible( b ); return this; }
		U1								GetArrowVisible() const { return GetControlTyped().GetArrowVisible(); }

		UiScrollBar*					SetDynamicPage( U1 b ) { GetControlTyped().SetDynamicPage( b ); return this; }
		U1								GetDynamicPage() const { return GetControlTyped().GetDynamicPage(); }

		UiScrollBar*					SetMinimumExtend( U1 b ) { GetControlTyped().SetMinimumExtend( b ); return this; }
		U1								GetMinimumExtend() const { return GetControlTyped().GetMinimumExtend(); }

		UiScrollBar*					SetMaximumExtend( U1 b ) { GetControlTyped().SetMaximumExtend( b ); return this; }
		U1								GetMaximumExtend() const { return GetControlTyped().GetMaximumExtend(); }

		UiScrollBar*					SetMinimum( S32 nValue ) { GetControlTyped().SetMinimum( nValue ); return this; }
		S32								GetMinimum() const { return GetControlTyped().GetMinimum(); }
		S32								GetMinimumVirtual() const { return GetControlTyped().GetMinimumVirtual(); }

		UiScrollBar*					SetMaximum( S32 nValue ) { GetControlTyped().SetMaximum( nValue ); return this; }
		S32								GetMaximum() const { return GetControlTyped().GetMaximum(); }
		S32								GetMaximumVirtual() const { return GetControlTyped().GetMaximumVirtual(); }

		UiScrollBar*					SetValue( S32 nValue ) { GetControlTyped().SetValue( nValue ); return this; }
		UiScrollBar*					SetValueForce( S32 nValue ) { GetControlTyped().SetValueForce( nValue ); return this; }
		S32								GetValue() const { return GetControlTyped().GetValue(); }
		S32								GetValueFinal() const { return GetControlTyped().GetValueFinal(); }
		R32								GetValuePercent() const { return GetControlTyped().GetValuePercent(); }
		R32								GetValuePercentFinal() const { return GetControlTyped().GetValuePercentFinal(); }

		UiScrollBar*					SetPage( S32 nValue ) { GetControlTyped().SetPage( nValue ); return this; }
		S32								GetPage() const { return GetControlTyped().GetPage(); }

		UiScrollBar*					SetStep( S32 nValue ) { GetControlTyped().SetStep( nValue ); return this; }
		S32								GetStep() const { return GetControlTyped().GetStep(); }

		UiScrollBar*					Scroll() { GetControlTyped().Scroll(); return this; }

		UiScrollBar*					OnScroll     /**/( OnScroll_t     /**/ && fn );
		UiScrollBar*					OnScrolling  /**/( OnScrolling_t  /**/ && fn );
		UiScrollBar*					OnPageChange /**/( OnPageChange_t /**/ && fn );
	};
}
