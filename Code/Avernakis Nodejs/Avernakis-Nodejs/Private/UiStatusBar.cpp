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
		AutoAddMethod( GetPart );
		AutoAddMethod( SetWidth );
		AutoAddMethod( GetWidth );
		AutoAddMethod( GetWidthReal );
		AutoAddMethod( SetMaxWidth );
		AutoAddMethod( GetMaxWidth );
		AutoAddMethod( SetReducePriority );
		AutoAddMethod( GetReducePriority );
		AutoAddMethod( SetText );
		AutoAddMethod( GetText );
		AutoAddMethod( SetPartToolTip );
		AutoAddMethod( SetAlign );
		AutoAddMethod( GetAlign );
		AutoAddMethod( SetIcon );
		AutoAddMethod( GetIcon );
		AutoAddMethod( SetClickable );
		AutoAddMethod( GetClickable );
		AutoAddMethod( SetContent );
		AutoAddMethod( GetContent );
		AutoAddMethod( SetContentMargin );
		AutoAddMethod( GetContentMargin );
		AutoAddMethod( HitTest );
		AutoAddMethod( GetItemRect );
		AutoAddMethod( SetBackground );
		AutoAddMethod( GetBackground );
		AutoAddMethod( SetBackColor );
		AutoAddMethod( GetBackColor );
		AutoAddMethod( OnClick );
	}

	U1 UiStatusBar::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().SetIconManager( p->PublicCloneIconManager() );

		GetControlTyped().GetEvent<Ui::IStatusBar::OnClick>() += MakeThisFunc( __OnClick );

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

}
