#pragma once

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
		using OnSysMenuClick_t = JsFuncSafe<void( UiWindowFrame* sender, U32 nId )>;

		OnSysMenuClick_t				m_OnSysMenuClick;

		void							__OnSysMenuClick( Ui::IWindowFrame& sender, U32 nId );

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

		UiWindowFrame*					SetCaptionVisible( U1 b ) { GetControlTyped().SetCaptionVisible( b ); return this; }
		U1								GetCaptionVisible() const { return GetControlTyped().GetCaptionVisible(); }

		void							SysMenuReset() { GetControlTyped().SysMenuReset(); }
		U1								SysMenuAppend( const WrapData<UiMenuItem>& pMenu );

		UiWindowFrame*					OnSysMenuClick( OnSysMenuClick_t&& fn ) { m_OnSysMenuClick = std::move( fn ); return this; }

	public:
		void							InitCallback();
	};
}
