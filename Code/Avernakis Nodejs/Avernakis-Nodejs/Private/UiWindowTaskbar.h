#pragma once

#include "WrapObject.h"
#include "UiWindow.h"

namespace Nav
{

	class UiWindowTaskbarIconicImage
	{
	public:
		Ui::WindowTaskbarIconicType		m_Type;
		WrapData<S32_2>					m_Size;
	};
	NavDefineDataByMember_( UiWindowTaskbarIconicImage, Type, Size );
	NavDefineTransitByMember_( Ui::WindowTaskbarIconicImage, UiWindowTaskbarIconicImage, Type, Size );

	class UiWindow;
	
	class ImgImage;

	class UiWindowTaskbar : public WrapObject<UiWindowTaskbar, void(), WrapObjectUi>
	{
	public:
		AveWrapObject( UiWindowTaskbar );

		static PCAChar					GetExportName() { return "8f7a23b9d1644244b73b3c0a050c02a9"; }
		static void						DefineObject();

		U1								Ctor() { return true; }
		Napi::Value						GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		using OnIconicUpdate_t			/**/ = JsFuncSafe<void( UiWindowTaskbar* sender, const WrapData<Ui::WindowTaskbarIconicImage>& ii )>;
		using OnButtonClick_t			/**/ = JsFuncSafe<void( UiWindowTaskbar* sender, U32 nIndex )>;

		UiWindow*						m_Window;
		Ui::IWindowTaskbar*				m_Taskbar;

		OnIconicUpdate_t				m_OnIconicUpdate;
		OnButtonClick_t					m_OnButtonClick;

		void							__OnIconicUpdate( Ui::IWindowTaskbar& sender, const Ui::WindowTaskbarIconicImage& ii );
		void							__OnButtonClick( Ui::IWindowTaskbar& sender, U32 nIndex );

	private:
		UiWindow*						GetWindow() { return m_Window; }

		UiWindowTaskbar*				SetState( Ui::ProgressBarState n ) { m_Taskbar->SetState( n ); return this; }
		Ui::ProgressBarState 			GetState() { return m_Taskbar->GetState(); }

		UiWindowTaskbar*				SetMaximum( U64 nValue ) { m_Taskbar->SetMaximum( nValue ); return this; }
		U64								GetMaximum() const { return m_Taskbar->GetMaximum(); }

		UiWindowTaskbar*				SetValue( U64 nValue ) { m_Taskbar->SetValue( nValue ); return this; }
		U64								GetValue() const { return m_Taskbar->GetValue(); }

		UiWindowTaskbar*				SetStep( U64 nValue ) { m_Taskbar->SetStep( nValue ); return this; }
		U64								GetStep() const { return m_Taskbar->GetStep(); }
		UiWindowTaskbar*				Step() { m_Taskbar->Step(); return this; }

		UiWindowTaskbar*				SetForceBigIconSize100( U32 nSize ) { m_Taskbar->SetForceBigIconSize100( nSize ); return this; }
		U32								GetForceBigIconSize100() const { return m_Taskbar->GetForceBigIconSize100(); }

		UiWindowTaskbar*				SetIconicImage( U1 b ) { m_Taskbar->SetIconicImage( b ); return this; }
		U1								GetIconicImage() const { return m_Taskbar->GetIconicImage(); }

		UiWindowTaskbar*				SetIconicThumbnail( ImgImage* img );
		UiWindowTaskbar*				SetIconicLivePreview( ImgImage* img );

		U32								GetButtonCount() const { return m_Taskbar->GetButtonCount(); }
		UiWindowTaskbar*				SetButtonVisible( U32 nIndex, U1 b ) { m_Taskbar->SetButtonVisible( nIndex, b ); return this; }
		U1								GetButtonVisible( U32 nIndex ) const { return m_Taskbar->GetButtonVisible( nIndex ); }
		UiWindowTaskbar*				SetButtonEnable( U32 nIndex, U1 b ) { m_Taskbar->SetButtonEnable( nIndex, b ); return this; }
		U1								GetButtonEnable( U32 nIndex ) const { return m_Taskbar->GetButtonEnable( nIndex ); }
		UiWindowTaskbar*				SetButtonIcon( U32 nIndex, U32 nIcon ) { m_Taskbar->SetButtonIcon( nIndex, nIcon ); return this; }
		U32								GetButtonIcon( U32 nIndex ) const { return m_Taskbar->GetButtonIcon( nIndex ); }
		UiWindowTaskbar*				SetButtonTooltip( U32 nIndex, PCWChar szTip ) { m_Taskbar->SetButtonTooltip( nIndex, szTip ); return this; }
		WString							GetButtonTooltip( U32 nIndex ) const { return m_Taskbar->GetButtonTooltip( nIndex ); }

		UiWindowTaskbar*				SetIconCount( U32 nCount ) { m_Taskbar->SetIconCount( nCount ); return this; }
		U32								GetIconCount() const { return m_Taskbar->GetIconCount(); }
		UiWindowTaskbar*				SetIcon( U32 nIndex, ImgImage* img );
		ImgImage*						GetIcon( const CallbackInfo& ci, U32 nIndex ) const;


		UiWindowTaskbar*				OnIconicUpdate( OnIconicUpdate_t&& fn );
		UiWindowTaskbar*				OnButtonClick( OnButtonClick_t&& fn );

	public:
		AveInline UiWindowTaskbar*		SetTaskbar( UiWindow* pWindow, Ui::IWindowTaskbar* pTaskbar ) { m_Window = pWindow; m_Taskbar = pTaskbar; return this; }
	};

}
