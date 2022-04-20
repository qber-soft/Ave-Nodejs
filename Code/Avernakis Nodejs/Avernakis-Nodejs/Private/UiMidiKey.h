#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	NavDefineDataByMember_( Ui::MidiKeyItem, Id, Note, Velocity );

	class UiMidiKey : public UiControlHelper<UiMidiKey, Ui::IMidiKey>
	{
	public:
		AveWrapControl( UiMidiKey );

		~UiMidiKey()
		{
		}

		static PCAChar					GetExportName() { return "UiMidiKey"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using Callback_t = JsFuncSafe<void( UiMidiKey* sender, const WrapData<Ui::MidiKeyItem>& key, U1 bPress, U32 nModifier )>;

		Callback_t						m_OnMidiKeyPress;
		Callback_t						m_OnMidiKeyRelease;

		void							__OnMidiKeyPress( Ui::IMidiKey& sender, const Ui::MidiKeyItem& key, U1 bFirstPress, U32 nModifier );
		void							__OnMidiKeyRelease( Ui::IMidiKey& sender, const Ui::MidiKeyItem& key, U1 bLastRelease, U32 nModifier );

	private:
		UiMidiKey*						SetRange( const WrapData<Ons::NoteRange_t>& v ) { GetControlTyped().SetRange( v ); return this; }
		WrapData<Ons::NoteRange_t>		GetRange() const { return GetControlTyped().GetRange(); }

		UiMidiKey*						SetMiddleOctave( S32 nOctave ) { GetControlTyped().SetMiddleOctave( nOctave ); return this; }
		S32								GetMiddleOctave() const { return GetControlTyped().GetMiddleOctave(); }

		UiMidiKey*						SetUniformWidth( U1 b ) { GetControlTyped().SetUniformWidth( b ); return this; }
		U1								GetUniformWidth() const { return GetControlTyped().GetUniformWidth(); }

		UiMidiKey*						SetPerfectWidth( U1 b ) { GetControlTyped().SetPerfectWidth( b ); return this; }
		U1								GetPerfectWidth() const { return GetControlTyped().GetPerfectWidth(); }

		UiMidiKey*						SetWhiteWidthLimit( const WrapData<Ui::DpiSize_2>& v ) { GetControlTyped().SetWhiteWidthLimit( v ); return this; }
		WrapData<Ui::DpiSize_2>			GetWhiteWidthLimit() const { return GetControlTyped().GetWhiteWidthLimit(); }

		UiMidiKey*						SetWhiteWidth( const WrapData<Ui::DpiSize>& nPixelWidth ) { GetControlTyped().SetWhiteWidth( nPixelWidth ); return this; }
		WrapData<Ui::DpiSize>			GetWhiteWidth() const { return GetControlTyped().GetWhiteWidth(); }

		UiMidiKey*						SetBlackSize( const WrapData<R32_2>& vPercentage ) { GetControlTyped().SetBlackSize( vPercentage ); return this; }
		WrapData<R32_2>					GetBlackSize() const { return GetControlTyped().GetBlackSize(); }

		UiMidiKey*						SetOctaveLabel( U1 b ) { GetControlTyped().SetOctaveLabel( b ); return this; }
		U1								GetOctaveLabel() const { return GetControlTyped().GetOctaveLabel(); }

		UiMidiKey*						SetMultiplePress( U1 b ) { GetControlTyped().SetMultiplePress( b ); return this; }
		U1								GetMultiplePress() const { return GetControlTyped().GetMultiplePress(); }

		List<S32>						GetOctaveKeyWidth() const { List<S32> v( 12 ); GetControlTyped().GetOctaveKeyWidth( (S32( & )[12]) v[0] ); return std::move( v ); }

		UiMidiKey*						MarkClear() { GetControlTyped().MarkClear(); return this; }
		UiMidiKey*						MarkSetLabel( Ons::NoteIndex_t nNote, PCWChar szLabel ) { GetControlTyped().MarkSetLabel( nNote, szLabel ); return this; }
		WString							MarkGetLabel( Ons::NoteIndex_t nNote ) const { return GetControlTyped().MarkGetLabel( nNote ); }
		UiMidiKey*						MarkSetLabelColor( Ons::NoteIndex_t nNote, const WrapData<U8_4>& vColor ) { GetControlTyped().MarkSetLabelColor( nNote, vColor ); return this; }
		WrapData<U8_4>					MarkGetLabelColor( Ons::NoteIndex_t nNote ) const { return GetControlTyped().MarkGetLabelColor( nNote ); }
		UiMidiKey*						MarkSetColor( Ons::NoteIndex_t nNote, const WrapData<U8_4>& vColor ) { GetControlTyped().MarkbarSetColor( nNote, vColor ); return this; }
		WrapData<U8_4>					MarkGetColor( Ons::NoteIndex_t nNote ) const { return GetControlTyped().MarkbarGetColor( nNote ); }
		UiMidiKey*						MarkSetIcon( Ons::NoteIndex_t nNote, Ui::IconCache nIcon ) { GetControlTyped().MarkbarSetIcon( nNote, nIcon ); return this; }
		Ui::IconCache					MarkGetIcon( Ons::NoteIndex_t nNote ) const { return GetControlTyped().MarkbarGetIcon( nNote ); }

		UiMidiKey*						MarkbarSetHeight( const WrapData<Ui::DpiSize>& nHeight ) { GetControlTyped().MarkbarSetHeight( nHeight ); return this; }
		WrapData<Ui::DpiSize>			MarkbarGetHeight() const { return GetControlTyped().MarkbarGetHeight(); }
		UiMidiKey*						MarkbarSetMargin( const WrapData<Ui::S32_DpiMargin>& margin ) { GetControlTyped().MarkbarSetMargin( margin ); return this; }
		WrapData<Ui::S32_DpiMargin>		MarkbarGetMargin() const { return GetControlTyped().MarkbarGetMargin(); }
		UiMidiKey*						MarkbarSetColor( Ons::NoteIndex_t nNote, const WrapData<U8_4>& vColor ) { GetControlTyped().MarkbarSetColor( nNote, vColor ); return this; }
		WrapData<U8_4>					MarkbarGetColor( Ons::NoteIndex_t nNote ) const { return GetControlTyped().MarkbarGetColor( nNote ); }
		UiMidiKey*						MarkbarSetColorHeight( Ons::NoteIndex_t nNote, R32 f ) { GetControlTyped().MarkbarSetColorHeight( nNote, f ); return this; }
		R32								MarkbarGetColorHeight( Ons::NoteIndex_t nNote ) const { return GetControlTyped().MarkbarGetColorHeight( nNote ); }
		UiMidiKey*						MarkbarSetIcon( Ons::NoteIndex_t nNote, Ui::IconCache nIcon ) { GetControlTyped().MarkbarSetIcon( nNote, nIcon ); return this; }
		Ui::IconCache					MarkbarGetIcon( Ons::NoteIndex_t nNote ) const { return GetControlTyped().MarkbarGetIcon( nNote ); }

		UiMidiKey*						RangeClear() { GetControlTyped().RangeClear(); return this; }
		UiMidiKey*						RangeAdd( const WrapData<Ons::NoteRange_t>& vRange, const WrapData<U8_4>& vColor ) { GetControlTyped().RangeAdd( vRange, vColor ); return this; }

		Ons::NoteIndex_t				KeyHitTest( const WrapData<S32_2>& pt ) const { return GetControlTyped().KeyHitTest( pt ); }
		WrapData<S32_R>					KeyGetRect( Ons::NoteIndex_t nKey ) const { S32_R rc{}; GetControlTyped().KeyGetRect( nKey, rc ); return rc; }
		UiMidiKey*						KeySetPress( Ons::NoteIndex_t nKey, U1 bPress ) { GetControlTyped().KeySetPress( nKey, bPress ); return this; }
		U1								KeyGetPress( Ons::NoteIndex_t nKey ) const { return GetControlTyped().KeyGetPress( nKey ); }
		UiMidiKey*						KeyClearPress() { GetControlTyped().KeyClearPress(); return this; }

		UiMidiKey*						OnMidiKeyPress( Callback_t&& fn );
		UiMidiKey*						OnMidiKeyRelease( Callback_t&& fn );
	};
}
