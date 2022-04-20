#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiTrackBar : public UiControlHelper<UiTrackBar, Ui::ITrackBar>
	{
	public:
		AveWrapControl( UiTrackBar );

		~UiTrackBar()
		{
		}

		static PCAChar					GetExportName() { return "UiTrackBar"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using Callback_t = JsFuncSafe<void( UiTrackBar* sender )>;

		Callback_t						m_OnThumbChange  /**/;
		Callback_t						m_OnThumbRelease /**/;
		Callback_t						m_OnPageChange   /**/;

		void							__OnThumbChange  /**/( Ui::ITrackBar& sender );
		void							__OnThumbRelease /**/( Ui::ITrackBar& sender );
		void							__OnPageChange   /**/( Ui::ITrackBar& sender );

	private:
		UiTrackBar*						SetOrientation( Ui::TrackBarOrientation nOrient ) { GetControlTyped().SetOrientation( nOrient ); return this; }
		Ui::TrackBarOrientation			GetOrientation() const { return GetControlTyped().GetOrientation(); }
		Ui::TrackBarOrientation			GetOrientationActually() const { return GetControlTyped().GetOrientationActually(); }

		UiTrackBar*						SetMinimum( S64 nValue ) { GetControlTyped().SetMinimum( nValue ); return this; }
		S64								GetMinimum() const { return GetControlTyped().GetMinimum(); }

		UiTrackBar*						SetMaximum( S64 nValue ) { GetControlTyped().SetMaximum( nValue ); return this; }
		S64								GetMaximum() const { return GetControlTyped().GetMaximum(); }

		UiTrackBar*						SetValue( S64 nValue ) { GetControlTyped().SetValue( nValue ); return this; }
		UiTrackBar*						SetValueForce( S64 nValue ) { GetControlTyped().SetValueForce( nValue ); return this; }
		S64								GetValue() const { return GetControlTyped().GetValue(); }

		UiTrackBar*						SetPage( S64 nValue ) { GetControlTyped().SetPage( nValue ); return this; }
		S64								GetPage() const { return GetControlTyped().GetPage(); }

		UiTrackBar*						OnThumbChange  /**/( Callback_t&& fn );
		UiTrackBar*						OnThumbRelease /**/( Callback_t&& fn );
		UiTrackBar*						OnPageChange   /**/( Callback_t&& fn );
	};
}
