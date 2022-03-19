#pragma once

#include "WrapObject.h"
#include "UiWindow.h"

namespace Nav
{

	class UiWindow;

	class UiWindowSysTray : public WrapObject<UiWindowSysTray, void(), WrapObjectUi>
	{
	public:
		AveWrapObject( UiWindowSysTray );

		static PCAChar					GetExportName() { return "794b4f88fd6d405885b78cf591e71f6d"; }
		static void						DefineObject();

		U1								Ctor() { return true; }
		Napi::Value						GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		using Callback_t = UiWindow::SysTrayCallback_t;

		UiWindow*						m_Window;
		Ui::IWindowSysTray*				m_SysTray;

	private:
		UiWindow*						GetWindow() { return m_Window; }

		UiWindowSysTray*				SetVisible( U1 b ) { m_SysTray->SetVisible( b ); return this; }
		U1								GetVisible() { return m_SysTray->GetVisible(); }

		UiWindowSysTray*				SetText( PCWChar szText ) { m_SysTray->SetText( szText ); return this; }
		WString							GetText() { return m_SysTray->GetText(); }

		UiWindowSysTray*				OnClick( Callback_t&& fn ) { m_Window->SetSysTrayClick( std::move( fn ) ); return this; }
		UiWindowSysTray*				OnRightClick( Callback_t&& fn ) { m_Window->SetSysTrayRightClick( std::move( fn ) ); return this; }

	public:
		AveInline UiWindowSysTray*		SetSysTray( UiWindow* pWindow, Ui::IWindowSysTray* pSysTray ) { m_Window = pWindow; m_SysTray = pSysTray; return this; }
	};

}
