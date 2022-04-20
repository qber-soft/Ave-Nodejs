#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiRibbonGroup;

	class UiRibbonBackstage : public UiControlHelper<UiRibbonBackstage, Ui::IRibbonBackstage>
	{
	public:
		AveWrapControl( UiRibbonBackstage );

		~UiRibbonBackstage()
		{
		}

		static PCAChar					GetExportName() { return "UiRibbonBackstage"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using Callback_t = JsFuncSafe<void( UiRibbonBackstage* sender, U32 nIndex )>;

		Callback_t						m_OnSelect;
		Callback_t						m_OnHighlight;

		void							__OnSelect( Ui::IRibbonBackstage& sender, U32 nIndex );
		void							__OnHighlight( Ui::IRibbonBackstage& sender, S32 nIndex );

	private:
		UiRibbonBackstage*				SetCount( U32 nCount ) { GetControlTyped().SetCount( nCount ); return this; }
		U32								GetCount() const { return GetControlTyped().GetCount(); }
		UiRibbonBackstage*				Add() { GetControlTyped().Add(); return this; }
		UiRibbonBackstage*				Select( S32 nIndex ) { GetControlTyped().Select( nIndex ); return this; }
		S32								GetSelection() const { return GetControlTyped().GetSelection(); }
		S32								GetHighlight() const { return GetControlTyped().GetHighlight(); }

		UiRibbonBackstage*				SetText( U32 nIndex, PCWChar szText ) { GetControlTyped().SetText( nIndex, szText ); return this; }
		WString							GetText( U32 nIndex ) const { return GetControlTyped().GetText( nIndex ); }
		UiRibbonBackstage*				SetIcon( U32 nIndex, Ui::IconCache nIcon ) { GetControlTyped().SetIcon( nIndex, nIcon ); return this; }
		Ui::IconCache					GetIcon( U32 nIndex ) const { return GetControlTyped().GetIcon( nIndex ); }
		WrapPointer<UiControl>			SetContent( U32 nIndex, WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().SetContent( nIndex, pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			GetContent( U32 nIndex ) const { return __ReturnContent( GetControlTyped().GetContent( nIndex ) ); }
		UiRibbonBackstage*				SetItemEnable( U32 nIndex, U1 b ) { GetControlTyped().SetItemEnable( nIndex, b ); return this; }
		U1								GetItemEnable( U32 nIndex ) const { return GetControlTyped().GetItemEnable( nIndex ); }
		WrapData<S32_R>					GetItemRect( U32 nIndex ) const { return GetControlTyped().GetItemRect( nIndex ); }

		UiRibbonBackstage*				SetBannerWidth( const WrapData<Ui::DpiSize>& nWidth ) { GetControlTyped().SetBannerWidth( nWidth ); return this; }
		WrapData<Ui::DpiSize>			GetBannerWidth() const { return GetControlTyped().GetBannerWidth(); }

		UiRibbonBackstage*				SetTextVisible( U1 b ) { GetControlTyped().SetTextVisible( b ); return this; }
		U1								GetTextVisible() const { return GetControlTyped().GetTextVisible(); }

		UiRibbonBackstage*				ClearHighlight() { GetControlTyped().ClearHighlight(); return this; }

		
		UiRibbonBackstage*				OnSelect    /**/( Callback_t&& fn );
		UiRibbonBackstage*				OnHighlight /**/( Callback_t&& fn );

	};
}
