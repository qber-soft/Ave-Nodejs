#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiRibbonGroup : public UiControlHelper<UiRibbonGroup, Ui::IRibbonGroup>
	{
	public:
		AveWrapControl( UiRibbonGroup );

		~UiRibbonGroup()
		{
		}

		static PCAChar					GetExportName() { return "UiRibbonGroup"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using Callback_t = JsFuncSafe<void( UiRibbonGroup* sender )>;

		Callback_t						m_OnClick;

		void							__OnDetailClick( Ui::IRibbonGroup& sender );

	private:
		UiRibbonGroup*					SetText( PCWChar szText ) { GetControlTyped().SetText( szText ); return this; }
		WString							GetText() const { return GetControlTyped().GetText(); }

		UiRibbonGroup*					SetDetailButton( U1 bDetailButton ) { GetControlTyped().SetDetailButton( bDetailButton ); return this; }
		U1								GetDetailButton() const { return GetControlTyped().GetDetailButton(); }

		WrapPointer<UiVisual>			SetVisual( WrapPointer<UiVisual> pv ) { return __ChangeContent( GetControlTyped().SetVisual( pv->TakeVisual() ) ); }
		WrapPointer<UiVisual>			GetVisual() const { return __ReturnContent( GetControlTyped().GetVisual() ); }

		U1								ControlAdd( WrapPointer<UiControl> pChild ) { return nullptr != GetControlTyped().ControlAdd( pChild->TakeOwnership() ); }
		U1								ControlInsert( U32 nInsertBefore, WrapPointer<UiControl> pChild ) { return nullptr != GetControlTyped().ControlInsert( nInsertBefore, pChild->TakeOwnership() ); }
		WrapPointer<UiControl>			ControlGetByIndex( U32 nIndex ) { return __ReturnContent( GetControlTyped().ControlGetByIndex( nIndex ) ); }
		WrapPointer<UiControl>			ControlGetById( U32 nId ) { return __ReturnContent( GetControlTyped().ControlGetById( nId ) ); }
		WrapPointer<UiControl>			ControlRemoveByIndex( U32 nIndex ) { return __ChangeContent( GetControlTyped().ControlRemoveByIndex( nIndex ) ); }
		WrapPointer<UiControl>			ControlRemoveById( U32 nId ) { return __ChangeContent( GetControlTyped().ControlRemoveById( nId ) ); }
		WrapPointer<UiControl>			ControlRemove( WrapPointer<UiControl> pChild ) { return __ChangeContent( GetControlTyped().ControlRemove( &pChild->GetControl() ) ); }
		UiRibbonGroup*					ControlRemoveAll() { GetControlTyped().ControlRemoveAll(); return this; }

		UiRibbonGroup*					OnDetailClick( Callback_t&& fn );
	};
}
