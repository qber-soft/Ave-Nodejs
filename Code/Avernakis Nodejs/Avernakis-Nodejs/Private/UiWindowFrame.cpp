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
		AutoAddMethod( GetIcon );

		AutoAddMethod( SetToolBarLeft );
		AutoAddMethod( GetToolBarLeft );

		AutoAddMethod( SetToolBarRight );
		AutoAddMethod( GetToolBarRight );

		AutoAddMethod( GetCaptionRect );
		AutoAddMethod( GetIconRect );
		AutoAddMethod( GetTextRect );
		AutoAddMethod( GetNonBorderRect );

		AutoAddMethod( SetBorderVisible );
		AutoAddMethod( GetBorderVisible );

		AutoAddMethod( SetCaptionVisible );
		AutoAddMethod( GetCaptionVisible );

		AutoAddMethod( SysMenuReset );
		AutoAddMethod( SysMenuAppend );

		AutoAddMethod( OnSysMenuClick );
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

	void UiWindowFrame::InitCallback()
	{
		GetControlTyped().GetEvent<Ui::IWindowFrame::OnSysMenuClick>() += MakeThisFunc( __OnSysMenuClick );
	}

}
