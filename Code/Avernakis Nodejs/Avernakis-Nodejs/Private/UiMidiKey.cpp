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
		AutoAddMethod( GetRange, WrapObjectGeneric );
		AutoAddMethod( SetMiddleOctave );
		AutoAddMethod( GetMiddleOctave, WrapObjectGeneric );
		AutoAddMethod( SetUniformWidth );
		AutoAddMethod( GetUniformWidth, WrapObjectGeneric );
		AutoAddMethod( SetPerfectWidth );
		AutoAddMethod( GetPerfectWidth, WrapObjectGeneric );
		AutoAddMethod( SetWhiteWidthLimit );
		AutoAddMethod( GetWhiteWidthLimit, WrapObjectGeneric );
		AutoAddMethod( SetWhiteWidth );
		AutoAddMethod( GetWhiteWidth, WrapObjectGeneric );
		AutoAddMethod( SetBlackSize );
		AutoAddMethod( GetBlackSize, WrapObjectGeneric );
		AutoAddMethod( SetOctaveLabel );
		AutoAddMethod( GetOctaveLabel, WrapObjectGeneric );
		AutoAddMethod( SetMultiplePress );
		AutoAddMethod( GetMultiplePress, WrapObjectGeneric );
		AutoAddMethod( GetOctaveKeyWidth, WrapObjectGeneric );
		AutoAddMethod( MarkClear );
		AutoAddMethod( MarkSetLabel );
		AutoAddMethod( MarkGetLabel, WrapObjectGeneric );
		AutoAddMethod( MarkSetLabelColor );
		AutoAddMethod( MarkGetLabelColor, WrapObjectGeneric );
		AutoAddMethod( MarkSetColor );
		AutoAddMethod( MarkGetColor, WrapObjectGeneric );
		AutoAddMethod( MarkSetIcon );
		AutoAddMethod( MarkGetIcon, WrapObjectGeneric );
		AutoAddMethod( MarkbarSetHeight );
		AutoAddMethod( MarkbarGetHeight, WrapObjectGeneric );
		AutoAddMethod( MarkbarSetMargin );
		AutoAddMethod( MarkbarGetMargin, WrapObjectGeneric );
		AutoAddMethod( MarkbarSetColor );
		AutoAddMethod( MarkbarGetColor, WrapObjectGeneric );
		AutoAddMethod( MarkbarSetColorHeight );
		AutoAddMethod( MarkbarGetColorHeight, WrapObjectGeneric );
		AutoAddMethod( MarkbarSetIcon );
		AutoAddMethod( MarkbarGetIcon, WrapObjectGeneric );
		AutoAddMethod( RangeClear );
		AutoAddMethod( RangeAdd );
		AutoAddMethod( KeyHitTest, WrapObjectGeneric );
		AutoAddMethod( KeyGetRect, WrapObjectGeneric );
		AutoAddMethod( KeySetPress );
		AutoAddMethod( KeyGetPress, WrapObjectGeneric );
		AutoAddMethod( KeyClearPress );
		AutoAddMethod( OnMidiKeyPress, WrapObjectGeneric );
		AutoAddMethod( OnMidiKeyRelease, WrapObjectGeneric );
	}

	U1 UiMidiKey::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().SetIconManager( p->PublicCloneIconManager() );

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

	UiMidiKey* UiMidiKey::OnMidiKeyPress( Callback_t&& fn ) { m_OnMidiKeyPress = SetEventCallback<Ui::IMidiKey::OnMidiKeyPress>( std::move( fn ), MakeThisFunc( __OnMidiKeyPress ) ); return this; }
	UiMidiKey* UiMidiKey::OnMidiKeyRelease( Callback_t&& fn ) { m_OnMidiKeyRelease = SetEventCallback<Ui::IMidiKey::OnMidiKeyRelease>( std::move( fn ), MakeThisFunc( __OnMidiKeyRelease ) ); return this; }
}
