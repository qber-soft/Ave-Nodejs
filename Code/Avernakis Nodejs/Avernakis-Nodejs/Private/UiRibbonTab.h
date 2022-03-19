#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiRibbonGroup;

	class UiRibbonTab : public UiControlHelper<UiRibbonTab, Ui::IRibbonTab>
	{
	public:
		AveWrapControl( UiRibbonTab );

		~UiRibbonTab()
		{
		}

		static PCAChar					GetExportName() { return "UiRibbonTab"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:


	private:
		UiRibbonTab*					SetText( PCWChar szText ) { GetControlTyped().SetText( szText ); return this; }
		WString							GetText() const { return GetControlTyped().GetText(); }

		S32								GroupGetCount() const { return GetControlTyped().GroupGetCount(); }
		U1								GroupAdd( UiRibbonGroup* pChild );
		U1								GroupInsert( U32 nInsertBefore, UiRibbonGroup* pChild );
		UiRibbonGroup*					GroupGetByIndex( U32 nIndex ) { if ( auto p = GetControlTyped().GroupGetByIndex( nIndex ) ) return (UiRibbonGroup*) p->GetUserContext(); return nullptr; }
		UiRibbonGroup*					GroupGetById( U32 nId ) { if ( auto p = GetControlTyped().GroupGetById( nId ) ) return (UiRibbonGroup*) p->GetUserContext(); return nullptr; }
		UiRibbonGroup*					GroupRemoveByIndex( U32 nIndex ) { return (UiRibbonGroup*) (UiControl*) __ChangeContent( (Ui::Control&&) GetControlTyped().GroupRemoveByIndex( nIndex ) ); }
		UiRibbonGroup*					GroupRemoveById( U32 nId ) { return (UiRibbonGroup*) (UiControl*) __ChangeContent( (Ui::Control&&) GetControlTyped().GroupRemoveById( nId ) ); }
		UiRibbonGroup*					GroupRemove( UiRibbonGroup* pChild );
		UiRibbonTab*					GroupRemoveAll() { GetControlTyped().GroupRemoveAll(); return this; }
	};
}
