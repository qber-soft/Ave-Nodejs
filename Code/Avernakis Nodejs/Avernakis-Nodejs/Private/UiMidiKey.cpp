#include "StdAfx.h"
#include "UiMidiKey.h"

#define ThisMethod($x) &UiMidiKey::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiMidiKey::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiMidiKey> c_obj;
	}

	void UiMidiKey::DefineControl()
	{
		AutoAddMethod( SetRange );
		AutoAddMethod( GetRange );
		AutoAddMethod( SetMiddleOctave );
		AutoAddMethod( GetMiddleOctave );
		AutoAddMethod( SetUniformWidth );
		AutoAddMethod( GetUniformWidth );
		AutoAddMethod( SetPerfectWidth );
		AutoAddMethod( GetPerfectWidth );
		AutoAddMethod( SetWhiteWidthLimit );
		AutoAddMethod( GetWhiteWidthLimit );
		AutoAddMethod( SetWhiteWidth );
		AutoAddMethod( GetWhiteWidth );
		AutoAddMethod( SetBlackSize );
		AutoAddMethod( GetBlackSize );
		AutoAddMethod( SetOctaveLabel );
		AutoAddMethod( GetOctaveLabel );
		AutoAddMethod( SetMultiplePress );
		AutoAddMethod( GetMultiplePress );
		AutoAddMethod( GetOctaveKeyWidth );
		AutoAddMethod( MarkClear );
		AutoAddMethod( MarkSetLabel );
		AutoAddMethod( MarkGetLabel );
		AutoAddMethod( MarkSetLabelColor );
		AutoAddMethod( MarkGetLabelColor );
		AutoAddMethod( MarkSetColor );
		AutoAddMethod( MarkGetColor );
		AutoAddMethod( MarkSetIcon );
		AutoAddMethod( MarkGetIcon );
		AutoAddMethod( MarkbarSetHeight );
		AutoAddMethod( MarkbarGetHeight );
		AutoAddMethod( MarkbarSetMargin );
		AutoAddMethod( MarkbarGetMargin );
		AutoAddMethod( MarkbarSetColor );
		AutoAddMethod( MarkbarGetColor );
		AutoAddMethod( MarkbarSetColorHeight );
		AutoAddMethod( MarkbarGetColorHeight );
		AutoAddMethod( MarkbarSetIcon );
		AutoAddMethod( MarkbarGetIcon );
		AutoAddMethod( RangeClear );
		AutoAddMethod( RangeAdd );
		AutoAddMethod( KeyHitTest );
		AutoAddMethod( KeyGetRect );
		AutoAddMethod( KeySetPress );
		AutoAddMethod( KeyGetPress );
		AutoAddMethod( KeyClearPress );
		AutoAddMethod( OnMidiKeyPress );
		AutoAddMethod( OnMidiKeyRelease );
	}

	U1 UiMidiKey::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().SetIconManager( p->PublicCloneIconManager() );

		GetControlTyped().GetEvent<Ui::IMidiKey::OnMidiKeyPress>() += MakeThisFunc( __OnMidiKeyPress );
		GetControlTyped().GetEvent<Ui::IMidiKey::OnMidiKeyRelease>() += MakeThisFunc( __OnMidiKeyRelease );

		return true;
	}

	void UiMidiKey::__OnMidiKeyPress( Ui::IMidiKey & sender, const Ui::MidiKeyItem & key, U1 bFirstPress, U32 nModifier )
	{
		m_OnMidiKeyPress( this, key, bFirstPress, nModifier );
	}

	void UiMidiKey::__OnMidiKeyRelease( Ui::IMidiKey & sender, const Ui::MidiKeyItem & key, U1 bLastRelease, U32 nModifier )
	{
		m_OnMidiKeyRelease( this, key, bLastRelease, nModifier );
	}

}
