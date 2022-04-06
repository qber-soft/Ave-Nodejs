#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiToolBar;
	class UiRibbonApp;
	class UiRibbonTab;

	class UiRibbon : public UiControlHelper<UiRibbon, Ui::IRibbon>
	{
	public:
		AveWrapControlCi( UiRibbon );

		~UiRibbon()
		{
		}

		static PCAChar					GetExportName() { return "UiRibbon"; }
		static void						DefineControl();

		U1								Ctor( const CallbackInfo& ci, UiWindow* p, Napi::Value v );

	private:
		JsObject<UiRibbonApp>			m_App;
		JsObject<UiToolBar>				m_ToolBar;

	private:
		UiRibbonApp*					GetApp() const { return m_App; }
		UiToolBar*						GetToolBar() const { return m_ToolBar; }

		UiRibbon*						SetBackground( U1 b ) { GetControlTyped().SetBackground( b ); return this; }
		U1								GetBackground() const { return GetControlTyped().GetBackground(); }

		UiRibbon*						SetMinimized( U1 b ) { GetControlTyped().SetMinimized( b ); return this; }
		U1								GetMinimized() const { return GetControlTyped().GetMinimized(); }

		UiRibbon*						SetCanMinimize( U1 b ) { GetControlTyped().SetCanMinimize( b ); return this; }
		U1								GetCanMinimize() const { return GetControlTyped().GetCanMinimize(); }

		U32								TabGetCount() const { return GetControlTyped().TabGetCount(); }
		U1								TabAdd( UiRibbonTab* pChild );
		U1								TabInsert( U32 nInsertBefore, UiRibbonTab* pChild );
		UiRibbonTab*					TabGetByIndex( U32 nIndex ) const { if ( auto p = GetControlTyped().TabGetByIndex( nIndex ) ) return (UiRibbonTab*) p->GetUserContext(); return nullptr; }
		UiRibbonTab*					TabGetById( U32 nId ) const { if ( auto p = GetControlTyped().TabGetById( nId ) ) return (UiRibbonTab*) p->GetUserContext(); return nullptr; }
		UiRibbonTab*					TabRemoveByIndex( U32 nIndex ) { return (UiRibbonTab*) (UiControl*) __ChangeContent( (Ui::Control&&) GetControlTyped().TabRemoveByIndex( nIndex ) ); }
		UiRibbonTab*					TabRemoveById( U32 nId ) { return (UiRibbonTab*) (UiControl*) __ChangeContent( (Ui::Control&&) GetControlTyped().TabRemoveById( nId ) ); }
		UiRibbonTab*					TabRemove( UiRibbonTab* pChild );
		UiRibbon*						TabRemoveAll() { GetControlTyped().TabRemoveAll(); return this; }
		UiRibbon*						TabSelect( U32 nIndex ) { GetControlTyped().TabSelect( nIndex ); return this; }
		WrapData<S32_R>					TabGetRect( U32 nIndex ) const { return GetControlTyped().TabGetRect( nIndex ); }
		WrapData<S32_R>					TabGetContentRect() const { return GetControlTyped().TabGetContentRect(); }
		S32								TabGetIndex( UiRibbonTab* p );

		WrapPointer<UiControl>			SetContent( WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().SetContent( pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			GetContent() const { return __ReturnContent( GetControlTyped().GetContent() ); }

		WrapPointer<UiControl>			SetAppMenu( WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().SetAppMenu( pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			GetAppMenu() const { return __ReturnContent( GetControlTyped().GetAppMenu() ); }

		WrapPointer<UiControl>			SetBackstage( WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().SetBackstage( pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			GetBackstage() const { return __ReturnContent( GetControlTyped().GetBackstage() ); }

		UiRibbon*						SetBackstageVisible( U1 b ) { GetControlTyped().SetBackstageVisible( b ); return this; }
		U1								GetBackstageVisible() const { return GetControlTyped().GetBackstageVisible(); }
	};
}
