#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiPager : public UiControlHelper<UiPager, Ui::IPager>
	{
	public:
		AveWrapControl( UiPager );

		~UiPager()
		{
		}

		static PCAChar					GetExportName() { return "UiPager"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:

	private:
		WrapPointer<UiControl>			SetContent( WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().SetContent( pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			GetContent() const { return __ReturnContent( GetControlTyped().GetContent() ); }

		UiPager*						SetContentSize( const WrapData<S32_2>& vSize ) { GetControlTyped().SetContentSize( vSize ); return this; }
		WrapData<S32_2>					GetContentSize() const { return GetControlTyped().GetContentSize(); }
		WrapData<S32_2>					GetRealContentSize() const { return GetControlTyped().GetRealContentSize(); }

		UiPager*						SetAdjustment( Ui::PagerAdjustment nAdjust ) { GetControlTyped().SetAdjustment( nAdjust ); return this; }
		Ui::PagerAdjustment				GetAdjustment() const { return GetControlTyped().GetAdjustment(); }

		UiPager*						SetAutoHideScroll( U1 b ) { GetControlTyped().SetAutoHideScroll( b ); return this; }
		U1								GetAutoHideScroll() const { return GetControlTyped().GetAutoHideScroll(); }

		UiPager*						SetPointerScroll( U1 b ) { GetControlTyped().SetPointerScroll( b ); return this; }
		U1								GetPointerScroll() const { return GetControlTyped().GetPointerScroll(); }
	};
}
