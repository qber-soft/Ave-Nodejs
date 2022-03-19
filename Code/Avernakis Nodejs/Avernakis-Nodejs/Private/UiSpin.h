#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiSpin : public UiControlHelper<UiSpin, Ui::ISpin>
	{
	public:
		AveWrapControl( UiSpin );

		~UiSpin()
		{
		}

		static PCAChar					GetExportName() { return "UiSpin"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnClick_t     /**/ = JsFuncSafe<void( UiSpin* sender, S32 nDelta )>;
		using OnSpinStart_t /**/ = JsFuncSafe<void( UiSpin* sender )>;
		using OnSpinEnd_t   /**/ = JsFuncSafe<void( UiSpin* sender, U1 bCanceled )>;
		using OnSpin_t      /**/ = JsFuncSafe<void( UiSpin* sender, S32 nDelta )>;

		OnClick_t						m_OnClick     /**/;
		OnSpinStart_t					m_OnSpinStart /**/;
		OnSpinEnd_t						m_OnSpinEnd   /**/;
		OnSpin_t						m_OnSpin      /**/;
		
		void							__OnClick     /**/( Ui::ISpin& sender, S32 nDelta );
		void							__OnSpinStart /**/( Ui::ISpin& sender );
		void							__OnSpinEnd   /**/( Ui::ISpin& sender, U1 bCanceled );
		void							__OnSpin      /**/( Ui::ISpin& sender, S32 nDelta );

	private:
		UiSpin*							OnClick     /**/( OnClick_t     /**/ && fn ) { m_OnClick     /**/ = std::move( fn ); return this; }
		UiSpin*							OnSpinStart /**/( OnSpinStart_t /**/ && fn ) { m_OnSpinStart /**/ = std::move( fn ); return this; }
		UiSpin*							OnSpinEnd   /**/( OnSpinEnd_t   /**/ && fn ) { m_OnSpinEnd   /**/ = std::move( fn ); return this; }
		UiSpin*							OnSpin      /**/( OnSpin_t      /**/ && fn ) { m_OnSpin      /**/ = std::move( fn ); return this; }
	};
}
