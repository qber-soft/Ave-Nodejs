#include "StdAfx.h"
#include "UiWindowFrame.h"
#include "UiMenu.h"

#define ThisMethod($x) &UiWindowFrame::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiWindowFrame::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiWindowFrame> c_obj;
	}

	void UiWindowFrame::DefineControl()
	{
		AutoAddMethod( SetIcon );
		AutoAddMethod( GetIcon, WrapObjectGeneric );

		AutoAddMethod( SetToolBarLeft );
		AutoAddMethod( GetToolBarLeft, WrapObjectGeneric );

		AutoAddMethod( SetToolBarRight );
		AutoAddMethod( GetToolBarRight, WrapObjectGeneric );

		AutoAddMethod( GetCaptionRect, WrapObjectGeneric );
		AutoAddMethod( GetIconRect, WrapObjectGeneric );
		AutoAddMethod( GetTextRect, WrapObjectGeneric );
		AutoAddMethod( GetNonBorderRect, WrapObjectGeneric );

		AutoAddMethod( SetBorderVisible );
		AutoAddMethod( GetBorderVisible, WrapObjectGeneric );

		AutoAddMethod( SetCaptionVisible );
		AutoAddMethod( GetCaptionVisible, WrapObjectGeneric );

		AutoAddMethod( SysMenuReset );
		AutoAddMethod( SysMenuAppend );

		AutoAddMethod( OnSysMenuClick, WrapObjectGeneric );
	}

	U1 UiWindowFrame::Ctor( UiWindow * p, Napi::Value v )
	{
		// No need to create control here
		//if ( !__CreateControl( p, v ) )
		//	return false;

		return true;
	}

	void UiWindowFrame::__OnSysMenuClick( Ui::IWindowFrame & sender, U32 nId )
	{
		m_OnSysMenuClick( this, nId );
	}

	U1 UiWindowFrame::SysMenuAppend( const WrapData<UiMenuItem>& pMenu )
	{
		Ui::MenuItem mi{};
		WrapDataTransit<Ui::MenuItem>::Transit( mi, pMenu );
		return GetControlTyped().SysMenuAppend( mi );
	}

	UiWindowFrame* UiWindowFrame::OnSysMenuClick( OnSysMenuClick_t&& fn ) { m_OnSysMenuClick = SetEventCallback<Ui::IWindowFrame::OnSysMenuClick>( std::move( fn ), MakeThisFunc( __OnSysMenuClick ) ); return this; }

}
