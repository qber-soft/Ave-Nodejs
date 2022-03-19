#pragma once

#include "WrapObject.h"

namespace Nav
{

	class UiCommonUiWait : public WrapObject<UiCommonUiWait, void(), WrapObjectUi>
	{
	public:
		AveWrapObject( UiCommonUiWait );

		static PCAChar					GetExportName() { return "34b9b2fe6b1c4a488b2f1b090f3aa27f"; }
		static void						DefineObject();

		U1								Ctor() { return true; }
		Napi::Value						GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Ui::IDialogWaitOp*				m_Op;

	private:
		U32								GetThreadIndex() { return m_Op->GetThreadIndex(); }
		void							SyncBarrier() { m_Op->SyncBarrier(); }
		U1								IsCanceled() { return m_Op->GetAsyncOp().IsCanceled(); }
		U1								IsPaused() { return m_Op->GetAsyncOp().IsPaused(); }
		void							Pause() { m_Op->GetAsyncOp().Pause(); }
		void							SetMaximum( U64 n ) { m_Op->GetAsyncOp().SetMaximum( n ); }
		void							SetPosition( U64 n ) { m_Op->GetAsyncOp().SetPosition( n ); }
		void							AddPosition( U64 n ) { m_Op->GetAsyncOp().AddPosition( n ); }
		void							SetState( PCWChar s ) { m_Op->GetAsyncOp().SetState( s ? s : AveWide( "" ) ); }
		void							Fail() { m_Op->GetAsyncOp().Fail(); }
		void							UpdateUi() { m_Op->UpdateUi(); }

	public:
		AveInline UiCommonUiWait*		SetOp( Ui::IDialogWaitOp* p ) { m_Op = p; return this; }
	};

}
