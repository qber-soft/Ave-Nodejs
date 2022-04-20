#include "StdAfx.h"
#include "UiStatusBar.h"

#define ThisMethod($x) &UiStatusBar::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiStatusBar::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiStatusBar> c_obj;
	}

	void UiStatusBar::DefineControl()
	{
		AutoAddMethod( SetPart );
		AutoAddMethod( GetPart, WrapObjectGeneric );
		AutoAddMethod( SetWidth );
		AutoAddMethod( GetWidth, WrapObjectGeneric );
		AutoAddMethod( GetWidthReal, WrapObjectGeneric );
		AutoAddMethod( SetMaxWidth );
		AutoAddMethod( GetMaxWidth, WrapObjectGeneric );
		AutoAddMethod( SetReducePriority );
		AutoAddMethod( GetReducePriority, WrapObjectGeneric );
		AutoAddMethod( SetText );
		AutoAddMethod( GetText, WrapObjectGeneric );
		AutoAddMethod( SetPartToolTip );
		AutoAddMethod( SetAlign );
		AutoAddMethod( GetAlign, WrapObjectGeneric );
		AutoAddMethod( SetIcon );
		AutoAddMethod( GetIcon, WrapObjectGeneric );
		AutoAddMethod( SetClickable );
		AutoAddMethod( GetClickable, WrapObjectGeneric );
		AutoAddMethod( SetContent );
		AutoAddMethod( GetContent, WrapObjectGeneric );
		AutoAddMethod( SetContentMargin );
		AutoAddMethod( GetContentMargin, WrapObjectGeneric );
		AutoAddMethod( HitTest, WrapObjectGeneric );
		AutoAddMethod( GetItemRect, WrapObjectGeneric );
		AutoAddMethod( SetBackground );
		AutoAddMethod( GetBackground, WrapObjectGeneric );
		AutoAddMethod( SetBackColor );
		AutoAddMethod( GetBackColor, WrapObjectGeneric );
		AutoAddMethod( OnClick, WrapObjectGeneric );
	}

	U1 UiStatusBar::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().SetIconManager( p->PublicCloneIconManager() );

		return true;
	}

	void UiStatusBar::__OnClick( Ui::IStatusBar & sender, S32 nIndex )
	{
		m_OnClick( this, nIndex );
	}

	UiStatusBar * UiStatusBar::SetPart( const List<WrapData<Ui::DpiSize>>& vPartWidth )
	{
		List<Ui::DpiSize> v( vPartWidth.Size() );
		for ( auto& i : vPartWidth.RangeIndexAll() )
			v[i.Index] = *i;
		GetControlTyped().SetPart( v.Data(), (U32) v.Size() );
		return this;
	}

	List<WrapData<Ui::DpiSize>> UiStatusBar::GetPart() const
	{
		List<Ui::DpiSize> v( GetControlTyped().GetPart( nullptr, 0 ) );
		if ( !v.IsEmpty() )
		{
			GetControlTyped().GetPart( v.Data(), (U32) v.Size() );
			List<WrapData<Ui::DpiSize>> vr( v.Size() );
			for ( auto& i : v.RangeIndexAll() )
				vr[i.Index] = *i;
			return std::move( vr );
		}
		return {};
	}

	UiStatusBar * UiStatusBar::OnClick( OnClick_t && fn ) { m_OnClick = SetEventCallback<Ui::IStatusBar::OnClick>( std::move( fn ), MakeThisFunc( __OnClick ) ); return this; }

}
