#pragma once

#include "WrapObject.h"
#include "UiWindow.h"

namespace Nav
{

	class UiWindow;

	class UiWindowTaskbar : public WrapObject<UiWindowTaskbar, void(), WrapObjectUi>
	{
	public:
		AveWrapObject( UiWindowTaskbar );

		static PCAChar					GetExportName() { return "8f7a23b9d1644244b73b3c0a050c02a9"; }
		static void						DefineObject();

		U1								Ctor() { return true; }
		Napi::Value						GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		UiWindow*						m_Window;
		Ui::IWindowTaskbar*				m_Taskbar;

	private:
		UiWindow*						GetWindow() { return m_Window; }

		UiWindowTaskbar*				SetState( Ui::ProgressBarState n ) { m_Taskbar->SetState( n ); return this; }
		Ui::ProgressBarState 			GetState() { return m_Taskbar->GetState(); }

		UiWindowTaskbar*				SetMaximum( U64 nValue ) { m_Taskbar->SetMaximum( nValue ); return this; }
		U64								GetMaximum() const { return m_Taskbar->GetMaximum(); }

		UiWindowTaskbar*				SetValue( U64 nValue ) { m_Taskbar->SetValue( nValue ); return this; }
		U64								GetValue() const { return m_Taskbar->GetValue(); }

		UiWindowTaskbar*				SetStep( U64 nValue ) { m_Taskbar->SetStep( nValue ); return this; }
		U64								GetStep() const { return m_Taskbar->GetStep(); }
		UiWindowTaskbar*				Step() { m_Taskbar->Step(); return this; }

		UiWindowTaskbar*				SetForceBigIconSize100( U32 nSize ) { m_Taskbar->SetForceBigIconSize100( nSize ); return this; }
		U32								GetForceBigIconSize100() const { return m_Taskbar->GetForceBigIconSize100(); }

	public:
		AveInline UiWindowTaskbar*		SetTaskbar( UiWindow* pWindow, Ui::IWindowTaskbar* pTaskbar ) { m_Window = pWindow; m_Taskbar = pTaskbar; return this; }
	};

}
