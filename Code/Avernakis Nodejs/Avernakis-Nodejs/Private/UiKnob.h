#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiKnob : public UiControlHelper<UiKnob, Ui::IKnob>
	{
	public:
		AveWrapControl( UiKnob );

		~UiKnob()
		{
		}

		static PCAChar					GetExportName() { return "UiKnob"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnGeneric_t   /**/ = JsFuncSafe<void( UiKnob* sender )>;
		using OnRotateEnd_t /**/ = JsFuncSafe<void( UiKnob* sender, U1 bCanceled )>;

		OnGeneric_t						m_OnChange;
		OnGeneric_t						m_OnRotateBegin;
		OnRotateEnd_t					m_OnRotateEnd;

		void							__OnChange( Ui::IKnob& sender );
		void							__OnRotateBegin( Ui::IKnob& sender );
		void							__OnRotateEnd( Ui::IKnob& sender, U1 bCanceled );

	private:
		UiKnob*							SetText( PCWChar szText ) { GetControlTyped().SetText( szText ? szText : AveWide( "" ) ); return this; }
		WString							GetText() const { return GetControlTyped().GetText(); }

		UiKnob*							ValueSetRange( const WrapData<R64_2>& vRange ) { GetControlTyped().ValueSetRange( vRange ); return this; }
		WrapData<R64_2>					ValueGetRange() const { return GetControlTyped().ValueGetRange(); }

		UiKnob*							ValueSetDefault( R64 fDefault ) { GetControlTyped().ValueSetDefault( fDefault ); return this; }
		R64								ValueGetDefault() const { return GetControlTyped().ValueGetDefault(); }

		UiKnob*							ValueSet( R64 fValue ) { GetControlTyped().ValueSet( fValue ); return this; }
		R64								ValueGet() const { return GetControlTyped().ValueGet(); }

		UiKnob*							StepSetUnlimited( R64 fStep ) { GetControlTyped().StepSetUnlimited( fStep ); return this; }
		R64								StepGetUnlimited() const { return GetControlTyped().StepGetUnlimited(); }

		UiKnob*							ValueSetCycle( U1 b ) { GetControlTyped().ValueSetCycle( b ); return this; }
		U1								ValueGetCycle() const { return GetControlTyped().ValueGetCycle(); }

		UiKnob*							StepSetLarge( R64 fLength ) { GetControlTyped().StepSetLarge( fLength ); return this; }
		R64								StepGetLarge() const { return GetControlTyped().StepGetLarge(); }

		UiKnob*							StepSetSmall( R64 fLength ) { GetControlTyped().StepSetSmall( fLength ); return this; }
		R64								StepGetSmall() const { return GetControlTyped().StepGetSmall(); }

		UiKnob*							ValueSetSplit( R64 fSplit ) { GetControlTyped().ValueSetSplit( fSplit ); return this; }
		R64								ValueGetSplit() const { return GetControlTyped().ValueGetSplit(); }

		UiKnob*							ValueSetTick( const WrapArray<R64>& pTick ) { GetControlTyped().ValueSetTick( pTick, pTick.m_Length ); return this; }
		List<R64>						ValueGetTick() const { return GetControlTyped().ValueGetTick(); }

		UiKnob*							RingSetColor( const WrapData<U8_4>& nColor ) { GetControlTyped().RingSetColor( nColor ); return this; }
		WrapData<U8_4>					RingGetColor() const { return GetControlTyped().RingGetColor(); }

		UiKnob*							RingSetDefaultColor( const WrapData<U8_4>& nColor ) { GetControlTyped().RingSetDefaultColor( nColor ); return this; }
		WrapData<U8_4>					RingGetDefaultColor() const { return GetControlTyped().RingGetDefaultColor(); }

		UiKnob*							RingSetTickColor( const WrapData<U8_4>& nColor ) { GetControlTyped().RingSetTickColor( nColor ); return this; }
		WrapData<U8_4>					RingGetTickColor() const { return GetControlTyped().RingGetTickColor(); }

		WrapPointer<UiVisual>			RingSetVisual( WrapPointer<UiVisual> v ) { return __ChangeContent( GetControlTyped().RingSetVisual( v->TakeVisual() ) ); }
		WrapPointer<UiVisual>			RingGetVisual() const { return __ReturnContent( GetControlTyped().RingGetVisual() ); }


		UiKnob*							OnChange( OnGeneric_t&& fn ) { m_OnChange = std::move( fn ); return this; }
		UiKnob*							OnRotateBegin( OnGeneric_t&& fn ) { m_OnRotateBegin = std::move( fn ); return this; }
		UiKnob*							OnRotateEnd( OnRotateEnd_t&& fn ) { m_OnRotateEnd = std::move( fn ); return this; }
	};
}
