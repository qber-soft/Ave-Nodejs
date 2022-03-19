#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiGroup : public UiControlHelper<UiGroup, Ui::IGroup>
	{
	public:
		AveWrapControl( UiGroup );

		~UiGroup()
		{
		}

		static PCAChar					GetExportName() { return "UiGroup"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:

	private:
		UiGroup*						SetText( PCWChar szText ) { GetControlTyped().SetText( szText ? szText : AveWide( "" ) ); return this; }
		WString							GetText() const { return GetControlTyped().GetText(); }

		WrapPointer<UiControl>			SetHeader( WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().SetHeader( std::move( pControl->TakeOwnership() ) ) ); }
		WrapPointer<UiControl>			GetHeader() const { return __ReturnContent( GetControlTyped().GetHeader() ); }

		WrapPointer<UiControl>			SetContent( WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().SetContent( std::move( pControl->TakeOwnership() ) ) ); }
		WrapPointer<UiControl>			GetContent() const { return __ReturnContent( GetControlTyped().GetContent() ); }

		WrapData<S32_2>					GetContentSize() const { return GetControlTyped().GetContentSize(); }
	};
}
