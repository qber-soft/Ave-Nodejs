#pragma once

#include "UiControl.h"
#include "UiVisual.h"
#include "UiTheme.h"

#include "../../../External/Avernakis/Code/Avernakis-AppFeature/Include/AppHelperWindow.h"

namespace Nav
{

	class UiWindow;

	enum class UiWindowDevice
	{
		Default2D,
		Default3D,

		// Windows 2D
		GDI = 100,
		D2D1,

		// Windows 3D
		D3D11 = 200,
		D3D12,

		// macOS 2D
		CG = 300,

		// macOS 3D
		Metal = 400,
	};

	class UiWindowCreation
	{
	public:
		WString					m_Title;
		WString					m_Icon;
		WrapData<S32_R>			m_Layout;
		U32						m_Flag;
		UiWindow*				m_ParentWindow;
		WrapPointer<UiTheme>	m_Theme;
		UiWindowDevice			m_Device;
	};

	NavDefineDataByMember_( UiWindowCreation, Title, Icon, Layout, Flag, ParentWindow, Theme, Device );

	using UiWindowCreation_t = WrapData<UiWindowCreation>;

	using UiWindowFeature = AppHelper::WindowFeature<AppHelper::WindowIconManager, AppHelper::WindowDpiware, AppHelper::WindowCommonUi>;

	class UiThemeImage;
	class UiCommonUi;
	class UiPlatform;
	class UiControlManager;
	class UiIconManager;
	class UiIcon;
	class UiWindowDragDrop;
	class UiWindowSysTray;
	class UiWindowTaskbar;
	
	class UiWindowFrame;

	class UiWindow : public UiControl, public WrapObject<UiWindow, void( const UiWindowCreation_t& ), WrapObjectUi>, AppHelper::Window<UiWindowFeature>
	{
		friend class UiControl;

	public:
		UiWindow( const Napi::CallbackInfo& cb ) : WrapObject( cb )
		{
			__CtorCi( cb );
		}

		~UiWindow()
		{
		}

		static PCAChar						GetExportName() { return "UiWindow"; }
		static void							DefineObject();

		U1									Ctor( const CallbackInfo& ci, const UiWindowCreation_t& cp );

	public:
		virtual Napi::Value					GetObjectValue( Napi::Env env ) override final { return __GetObjectValue( env ); }

	private:
		virtual Ui::IControl&				GetControl() override { return GetWindow(); }
		virtual Ui::Control					TakeOwnership() override { return nullptr; }
		virtual void						GiveOwnership( Ui::Control c ) {}
		virtual void						SetSharedControl( Ui::IControl* c ) {}

		// AppHelper::Window
		virtual U1							OnCreate( Ui::IWindow::CreationParam& cp ) override;
		virtual U1							OnCreateWindowContent() override;

		virtual void						OnWindowDestroy() override;
		virtual U1							OnWindowClose() override;
		virtual void						OnWindowCancel() override;
		virtual void						OnWindowOk() override;
		virtual U1							OnWindowHotkey( U32 nId, Ui::Key nKey, U32 nModifier ) override;

		virtual void						OnDpiChange() override;

	private:
		using OnCreateContent_t				/**/ = JsFuncDirect<U1( UiWindow* sender )>;
		using OnHotkey_t					/**/ = JsFuncSafe<void( UiWindow* sender, U32 nId, Ui::Key nKey, U32 nInputModifier )>;

		using CallbackBool_t				/**/ = JsFuncSafe<U1( UiWindow* sender )>;
		using CallbackGeneric_t				/**/ = JsFuncSafe<void( UiWindow* sender )>;

	public:
		using SysTrayCallback_t				/**/ = JsFuncSafe<void( UiWindow* sender )>;

	private:
		UiWindowCreation_t					m_Param;

		OnCreateContent_t					m_OnCreateContent;
		CallbackBool_t						m_OnClosing;
		CallbackGeneric_t					m_OnClose;

		CallbackGeneric_t					m_OnWindowOk;
		CallbackGeneric_t					m_OnWindowCancel;
		OnHotkey_t							m_OnWindowHotkey;

		CallbackGeneric_t					m_OnScaleChange;
		CallbackGeneric_t					m_OnLanguageChange;

		SysTrayCallback_t					m_OnSysTrayClick;
		SysTrayCallback_t					m_OnSysTrayRightClick;

		CallbackGeneric_t					m_OnDeviceChange;
		U1									m_DeviceNotificationEnable{ false };

		OnDrag_t							m_OnDragEnter;
		OnDrag_t							m_OnDragMove;
		OnDrag_t							m_OnDragLeave;
		OnDrag_t							m_OnDragDrop;
		OnDragEnd_t							m_OnDragEnd;
		UiControl*							m_DragControl{ nullptr };
		JsObject<UiDragContext>				m_DragContext;

		JsFuncSafe<void()>					m_Keep;

		S32									m_OnClosingResult{ 0 };

		U32									m_IconResId{ 0 };

		JsObject<UiThemeImage>				m_ThemeDefaultData;
		WrapPointer<UiTheme>				m_Theme{ nullptr };
		JsObject<UiWindowFrame>				m_Frame;

		JsObject<UiControlManager>			m_ControlManager;
		JsObject<UiIconManager>				m_IconManager;
		JsObject<UiCommonUi>				m_CommonUi;
		JsObject<UiWindowDragDrop>			m_DragDrop;
		JsObject<UiWindowSysTray>			m_SysTray;
		JsObject<UiWindowTaskbar>			m_Taskbar;
		JsObject<UiPlatform>				m_Platform;

	private:
		void								__OnDragEnter( Ui::IWindowDragContext& sender );
		void								__OnDragMove( Ui::IWindowDragContext& sender );
		void								__OnDragLeave( Ui::IWindowDragContext& sender );
		void								__OnDragDrop( Ui::IWindowDragContext& sender );
		void								__OnDragEnd( const Ui::IWindowDragContext& sender, U1 bOk );

		void								OnSysTrayClick( Ui::IWindowSysTray& sender, const S32_2& vPos );
		void								OnSysTrayRightClick( Ui::IWindowSysTray& sender, const S32_2& vPos );

		void								__OnDeviceChange( Ui::IWindowDeviceNotification& sender );

		void								__ApplyLanguage();

	private:
		U1									CreateWindow( const CallbackInfo& ci );
		void								CloseWindow() { GetWindow().Close(); }

		UiWindowDevice						GetDeviceType() const { return m_Param.m_Device; }

		UiWindow*							Activate() { GetNativeWindow().Activate(); return this; }
		U1									IsActive() const { return GetNativeWindow().IsActive(); }

		UiWindow*							SetTitle( PCWChar szTitle ) { GetNativeWindow().SetTitle( szTitle ); GetWindow().Redraw(); return this; }
		WString								GetTitle() const { return GetNativeWindow().GetTitle(); }

		UiWindow*							SetPosition( const WrapData<S32_2>& v ) { GetNativeWindow().SetPosition( v ); return this; }
		UiWindow*							SetSize( const WrapData<S32_2>& v ) { GetNativeWindow().SetSize( v ); return this; }

		UiWindow*							SetClientPosition( const WrapData<S32_2>& v ) { GetNativeWindow().SetPosition( v, true ); return this; }
		WrapData<S32_2>						GetClientPosition() { return GetNativeWindow().GetPosition( true ); }

		UiWindow*							SetClientSize( const WrapData<S32_2>& v ) { GetNativeWindow().SetSize( v, true ); return this; }
		WrapData<S32_2>						GetClientSize() { return GetNativeWindow().GetSize( true ); }

		UiWindow*							SetMinimumSize( const WrapData<Ui::DpiSize_2>& v ) { GetWindow().SetMinimumSize( v ); return this; }
		WrapData<Ui::DpiSize_2>				GetMinimumSize() { return GetWindow().GetMinimumSize(); }

		UiWindow*							SetSizeState( Ui::WindowSizeState n ) { GetNativeWindow().SetSizeState( n ); return this; }
		Ui::WindowSizeState					GetSizeState() { return GetNativeWindow().GetSizeState(); }
		U1									IsMinimizable() { return GetNativeWindow().IsMinimizable(); }
		U1									IsSizeable() { return GetNativeWindow().IsSizeable(); }

		UiWindow*							SetTopMost( U1 b ) { GetNativeWindow().SetTopMost( b ); return this; }
		U1									GetTopMost() { return GetNativeWindow().GetTopMost(); }

		UiWindow*							SetIme( U1 b ) { GetNativeWindow().SetIme( b ); return this; }
		U1									GetIme() { return GetNativeWindow().GetIme(); }

		UiWindow*							SetBackground( U1 b ) { GetWindow().SetBackground( b ); return this; }
		U1									GetBackground() const { return GetWindow().GetBackground(); }

		UiWindow*							SetRtl( U1 b ) { GetWindow().SetRtl( b ); return this; }
		U1									GetRtl() { return GetWindow().GetRtl(); }

		UiWindow*							SetScale( AppHelper::DpiId n ) { SetDpiId( n ); return this; }
		AppHelper::DpiId					GetScale() { return GetDpiId(); }

		UiWindow*							SetKeyTipEnable( U1 b ) { GetWindow().SetKeyTipEnable( b ); return this; }
		U1									GetKeyTipEnable() { return GetWindow().GetKeyTipEnable(); }

		UiWindow*							SetDirectKeyTip( U1 b ) { GetWindow().SetDirectKeyTip( b ); return this; }
		U1									GetDirectKeyTip() { return GetWindow().GetDirectKeyTip(); }

		WrapPointer<UiControl>				SetContent( WrapPointer<UiControl> c ) { return __ChangeContent( GetWindow().SetContent( std::move( c->TakeOwnership() ) ) ); }
		WrapPointer<UiControl>				GetContent() const { return { (UiControl*) GetWindow().GetContent()->GetUserContext() }; }

		UiWindow*							SetIcon( U32 nResId ) { GetWindow().GetFrame()->SetIcon( CreateManagedIcon( 16_icon / nResId ) ); GetNativeWindow().SetIcon( CreateIconAsImage( nResId ) ); m_IconResId = nResId; return this; }
		U32									GetIcon() { return m_IconResId; }

		UiWindow*							SetAppId( PCWChar szId ) { GetNativeWindow().SetAppId( szId ); return this; }

		UiWindow*							SetDeviceNotification( U1 b );
		U1									GetDeviceNotification() const { return m_DeviceNotificationEnable; }

		WrapPointer<UiTheme>				GetTheme() const { return m_Theme; }
		UiWindowFrame*						GetFrame() const { return m_Frame; }

		UiControlManager*					__GetControlManager( const CallbackInfo& ci ) { return m_ControlManager; }
		UiIconManager*						__GetIconManager() const { return m_IconManager; }
		UiCommonUi*							__GetCommonUi() const { return m_CommonUi; }
		UiWindowDragDrop*					GetDragDrop() const { return m_DragDrop; }
		UiWindowSysTray*					GetSysTray() const { return m_SysTray; }
		UiWindowTaskbar*					GetTaskbar() const { return m_Taskbar; }
		UiPlatform*							GetPlatform() const { return m_Platform; }

		R64									GetTime() { return GetNativeWindow().GetTime(); }

		Ui::IconCache						__CacheIcon( const WrapData<Ui::IconSource>& is ) { return CacheIcon( is ); }
		UiIcon*								__CreateManagedIcon( const CallbackInfo& ci, const WrapData<Ui::IconSource>& is );

		U32									__HotkeyRegister( Ui::Key nKey, U32 nModifier ) { return HotkeyRegister( nKey, nModifier ); }
		U1									__HotkeyDeregister( U32 nId ) { return HotkeyDeregister( nId ); }
		UiWindow*							__HotkeySetEnable( U1 b ) { HotkeySetEnable( b ); return this; }
		U1									__HotkeyGetEnable() { return HotkeyGetEnable(); }
		UiWindow*							__HotkeyClear() { HotkeyClear(); return this; }

		UiWindow*							OnCreateContent( OnCreateContent_t&& fn ) { m_OnCreateContent = std::move( fn ); return this; }
		UiWindow*							OnClosing( CallbackBool_t&& fn ) { m_OnClosing = std::move( fn ); return this; }
		UiWindow*							OnClose( CallbackGeneric_t&& fn ) { m_OnClose = std::move( fn ); return this; }
		UiWindow*							__OnWindowOk( CallbackGeneric_t&& fn ) { m_OnWindowOk = std::move( fn ); return this; }
		UiWindow*							__OnWindowCancel( CallbackGeneric_t&& fn ) { m_OnWindowCancel = std::move( fn ); return this; }
		UiWindow*							__OnWindowHotkey( OnHotkey_t&& fn ) { m_OnWindowHotkey = std::move( fn ); return this; }
		UiWindow*							OnScaleChange( CallbackGeneric_t&& fn ) { m_OnScaleChange = std::move( fn ); return this; }
		UiWindow*							OnLanguageChange( CallbackGeneric_t&& fn ) { m_OnLanguageChange = std::move( fn ); return this; }
		UiWindow*							OnDeviceChange( CallbackGeneric_t&& fn ) { m_OnDeviceChange = std::move( fn ); return this; }

		UiWindow*							OnDragEnter( OnDrag_t&& fn ) { m_OnDragEnter = std::move( fn ); return this; }
		UiWindow*							OnDragMove( OnDrag_t&& fn ) { m_OnDragMove = std::move( fn ); return this; }
		UiWindow*							OnDragLeave( OnDrag_t&& fn ) { m_OnDragLeave = std::move( fn ); return this; }
		UiWindow*							OnDragDrop( OnDrag_t&& fn ) { m_OnDragDrop = std::move( fn ); return this; }
		UiWindow*							OnDragEnd( OnDragEnd_t&& fn ) { m_OnDragEnd = std::move( fn ); return this; }

	public:
		AveInline IAveFactoryCreation&		GetFactoryUi() const { return GetUiFactory(); }
		AveInline Ui::IControlManager&		PublicGetControlManager() const { return GetControlManager(); }
		AveInline Ui::IWindow&				PublicGetWindow() const { return GetWindow(); }
		AveInline Ui::IWindowNative&		PublicGetNativeWindow() const { return GetNativeWindow(); }
		AveInline Ui::IconManager			PublicCloneIconManager() const { return CloneIconManager(); }

		AveInline void						SetSysTrayClick( SysTrayCallback_t&& fn ) { m_OnSysTrayClick = std::move( fn ); }
		AveInline void						SetSysTrayRightClick( SysTrayCallback_t&& fn ) { m_OnSysTrayRightClick = std::move( fn ); }
	};
}
