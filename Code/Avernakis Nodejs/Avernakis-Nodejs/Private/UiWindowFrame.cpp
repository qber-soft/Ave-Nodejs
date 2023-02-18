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

		AutoAddMethod( SetBorderOpacity );
		AutoAddMethod( GetBorderOpacity, WrapObjectGeneric );

		AutoAddMethod( SetCaptionVisible );
		AutoAddMethod( GetCaptionVisible, WrapObjectGeneric );

		AutoAddMethod( SysMenuReset );
		AutoAddMethod( SysMenuAppend );

		AutoAddMethod( OnNcHitTest       /**/, WrapObjectGeneric );
		AutoAddMethod( OnNcHitTestResult /**/, WrapObjectGeneric );
		AutoAddMethod( OnSysMenuPopup    /**/, WrapObjectGeneric );
		AutoAddMethod( OnSysMenuClick    /**/, WrapObjectGeneric );
		AutoAddMethod( OnMaximumClick    /**/, WrapObjectGeneric );
	}

	U1 UiWindowFrame::Ctor( UiWindow * p, Napi::Value v )
	{
		// No need to create control here
		//if ( !__CreateControl( p, v ) )
		//	return false;

		return true;
	}

	void UiWindowFrame::__OnNcHitTest( Ui::IWindowFrame & sender, const Ui::MessageNcHitTest & mp )
	{
		Ui::WindowFrameBackPart nPart = *mp.m_Area;
		m_OnNcHitTest.BlockCall( this, mp.m_Position, nPart, nPart );
		*mp.m_Area = nPart;
	}

	void UiWindowFrame::__OnNcHitTestResult( Ui::IWindowFrame & sender, Ui::WindowFrameBackPart nPart )
	{
		m_OnNcHitTestResult( this, nPart );
	}

	void UiWindowFrame::__OnSysMenuPopup( Ui::IWindowFrame & sender )
	{
		m_OnSysMenuPopup( this );
	}

	void UiWindowFrame::__OnSysMenuClick( Ui::IWindowFrame & sender, U32 nId )
	{
		m_OnSysMenuClick( this, nId );
	}

	void UiWindowFrame::__OnMaximumClick( Ui::IWindowFrame & sender )
	{
		m_OnMaximumClick( this );
	}

	U1 UiWindowFrame::SysMenuAppend( const WrapData<UiMenuItem>& pMenu )
	{
		Ui::MenuItem mi{};
		WrapDataTransit<Ui::MenuItem>::Transit( mi, pMenu );
		return GetControlTyped().SysMenuAppend( mi );
	}

	UiWindowFrame * UiWindowFrame::OnNcHitTest       /**/( OnNcHitTest_t       /**/ && fn ) { SetEventCallback<Ui::IWindowFrame::OnNcHitTest       /**/>( m_OnNcHitTest       /**/, std::move( fn ), MakeThisFunc( __OnNcHitTest       /**/ ) ); return this; }
	UiWindowFrame * UiWindowFrame::OnNcHitTestResult /**/( OnNcHitTestResult_t /**/ && fn ) { SetEventCallback<Ui::IWindowFrame::OnNcHitTestResult /**/>( m_OnNcHitTestResult /**/, std::move( fn ), MakeThisFunc( __OnNcHitTestResult /**/ ) ); return this; }
	UiWindowFrame * UiWindowFrame::OnSysMenuPopup    /**/( OnSysMenuPopup_t    /**/ && fn ) { SetEventCallback<Ui::IWindowFrame::OnSysMenuPopup    /**/>( m_OnSysMenuPopup    /**/, std::move( fn ), MakeThisFunc( __OnSysMenuPopup    /**/ ) ); return this; }
	UiWindowFrame * UiWindowFrame::OnSysMenuClick    /**/( OnSysMenuClick_t    /**/ && fn ) { SetEventCallback<Ui::IWindowFrame::OnSysMenuClick    /**/>( m_OnSysMenuClick    /**/, std::move( fn ), MakeThisFunc( __OnSysMenuClick    /**/ ) ); return this; }
	UiWindowFrame * UiWindowFrame::OnMaximumClick    /**/( OnMaximumClick_t    /**/ && fn ) { SetEventCallback<Ui::IWindowFrame::OnMaximumClick    /**/>( m_OnMaximumClick    /**/, std::move( fn ), MakeThisFunc( __OnMaximumClick    /**/ ) ); return this; }

}
