#pragma once

#include "WrapObject.h"
#include "UiWindow.h"

namespace Nav
{

	class UiWindowDragDrop : public WrapObject<UiWindowDragDrop, void(), WrapObjectUi>
	{
	public:
		AveWrapObject( UiWindowDragDrop );

		static PCAChar					GetExportName() { return "cdab9ac4ae164c78aa6e2e2cfd935f23"; }
		static void						DefineObject();

		U1								Ctor() { return true; }
		Napi::Value						GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		UiWindow*						m_Window;
		Ui::IWindowDragDrop*			m_DragDrop;

	private:
		UiWindow*						GetWindow() { return m_Window; }

	public:
		AveInline UiWindowDragDrop*		SetDragDrop( UiWindow* pWindow, Ui::IWindowDragDrop* pDragDrop ) { m_Window = pWindow; m_DragDrop = pDragDrop; return this; }
	};

}
