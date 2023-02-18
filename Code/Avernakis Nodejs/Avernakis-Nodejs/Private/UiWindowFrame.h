﻿#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiMenuItem;

	class UiWindowFrame : public UiControlHelper<UiWindowFrame, Ui::IWindowFrame>
	{
	public:
		AveWrapControl( UiWindowFrame );

		~UiWindowFrame()
		{
		}

		static PCAChar					GetExportName() { return "d424b413e3264deeb9e369a10c3e5b93"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnNcHitTest_t       /**/ = JsFuncSafe<Ui::WindowFrameBackPart( UiWindowFrame* sender, const WrapData<S32_2>& vPos, Ui::WindowFrameBackPart nPart )>;
		using OnNcHitTestResult_t /**/ = JsFuncSafe<void( UiWindowFrame* sender, Ui::WindowFrameBackPart nPart )>;
		using OnSysMenuPopup_t    /**/ = JsFuncSafe<void( UiWindowFrame* sender )>;
		using OnSysMenuClick_t    /**/ = JsFuncSafe<void( UiWindowFrame* sender, U32 nId )>;
		using OnMaximumClick_t    /**/ = JsFuncSafe<void( UiWindowFrame* sender )>;

		OnNcHitTest_t					m_OnNcHitTest       /**/;
		OnNcHitTestResult_t				m_OnNcHitTestResult /**/;
		OnSysMenuPopup_t				m_OnSysMenuPopup    /**/;
		OnSysMenuClick_t				m_OnSysMenuClick    /**/;
		OnMaximumClick_t				m_OnMaximumClick    /**/;

		void							__OnNcHitTest       /**/( Ui::IWindowFrame& sender, const Ui::MessageNcHitTest& mp );
		void							__OnNcHitTestResult /**/( Ui::IWindowFrame& sender, Ui::WindowFrameBackPart nPart );
		void							__OnSysMenuPopup    /**/( Ui::IWindowFrame& sender );
		void							__OnSysMenuClick    /**/( Ui::IWindowFrame& sender, U32 nId );
		void							__OnMaximumClick    /**/( Ui::IWindowFrame& sender );

	private:
		WrapPointer<UiVisual>			SetIcon( WrapPointer<UiVisual> pVisual ) { return __ChangeContent( GetControlTyped().SetIcon( pVisual->TakeVisual() ) ); }
		WrapPointer<UiVisual>			GetIcon() const { return __ReturnContent( GetControlTyped().GetIcon() ); }

		WrapPointer<UiControl>			SetToolBarLeft( WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().SetToolBarLeft( pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			GetToolBarLeft() const { return __ReturnContent( GetControlTyped().GetToolBarLeft() ); }

		WrapPointer<UiControl>			SetToolBarRight( WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().SetToolBarRight( pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			GetToolBarRight() const { return __ReturnContent( GetControlTyped().GetToolBarRight() ); }

		WrapData<S32_R>					GetCaptionRect() const { return GetControlTyped().GetCaptionRect(); }
		WrapData<S32_R>					GetIconRect() const { return GetControlTyped().GetIconRect(); }
		WrapData<S32_R>					GetTextRect() const { return GetControlTyped().GetTextRect(); }
		WrapData<S32_R>					GetNonBorderRect() const { return GetControlTyped().GetNonBorderRect(); }

		UiWindowFrame*					SetBorderVisible( U1 b ) { GetControlTyped().SetBorderVisible( b ); return this; }
		U1								GetBorderVisible() const { return GetControlTyped().GetBorderVisible(); }

		UiWindowFrame*					SetBorderOpacity( R32 f ) { GetControlTyped().SetBorderOpacity( f ); return this; }
		R32								GetBorderOpacity() const { return GetControlTyped().GetBorderOpacity(); }

		UiWindowFrame*					SetCaptionVisible( U1 b ) { GetControlTyped().SetCaptionVisible( b ); return this; }
		U1								GetCaptionVisible() const { return GetControlTyped().GetCaptionVisible(); }

		void							SysMenuReset() { GetControlTyped().SysMenuReset(); }
		U1								SysMenuAppend( const WrapData<UiMenuItem>& pMenu );

		UiWindowFrame*					OnNcHitTest       /**/( OnNcHitTest_t       /**/ && fn );
		UiWindowFrame*					OnNcHitTestResult /**/( OnNcHitTestResult_t /**/ && fn );
		UiWindowFrame*					OnSysMenuPopup    /**/( OnSysMenuPopup_t    /**/ && fn );
		UiWindowFrame*					OnSysMenuClick    /**/( OnSysMenuClick_t    /**/ && fn );
		UiWindowFrame*					OnMaximumClick    /**/( OnMaximumClick_t    /**/ && fn );

	public:
		void							InitCallback();
	};
}
