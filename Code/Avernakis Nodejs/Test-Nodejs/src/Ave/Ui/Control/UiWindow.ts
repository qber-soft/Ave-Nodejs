import { AveLib } from "../../AveLib";
import { DropBehavior, IControl, IShellData } from "../UiControl";
import { DpiSize_2, IconCache, IconSource, IIconManager, InputModifier, KbKey, ProgressBarState, Rect, StringKey } from "../UiCommon";
import { Theme, UiThemeInfection } from "../Theme/UiTheme";
import { ICommonUi } from "../UiCommonUi";
import { Vec2, Vec4 } from "../../Math/Vector";
import { IPlatform, MonitorItem } from "../UiPlatform";
import { IWindowFrame } from "./UiWindowFrame";
import { IIcon } from "../Visual/UiIcon";
import { AveImage } from "../../Image";

//----------------------------------------------------------------------------------------------------
// Window related objects
//----------------------------------------------------------------------------------------------------

export enum WindowFlag {
	MainWindow /**/ = 0x00000001,
	FullScreen /**/ = 0x00000002,
	Sizable /**/ = 0x00000004,
	Minimum /**/ = 0x00000008,
	TopMost /**/ = 0x00000010,
	Layered /**/ = 0x00000040,
	ToolWindow /**/ = 0x00000080,
	Indicator /**/ = 0x00000800,
	Transparent /**/ = 0x00001000,
	WindowSize /**/ = 0x00010000,
	Default /**/ = MainWindow | Sizable | Minimum,
}

export enum WindowDevice {
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
}

export enum WindowScale {
	SystemDefault = 0,
	MonitorOptimized,
	Percent100,
	Percent125,
	Percent150,
	Percent175,
	Percent200,
	Percent225,
	Percent250,
	Percent300,
	Percent350,
	Percent400,
}

export enum WindowSizeState {
	Normal,
	Minimized,
	Maximized,
}

//----------------------------------------------------------------------------------------------------
// Window extensions
//----------------------------------------------------------------------------------------------------

export interface IWindowExtension {
	GetWindow(): Window;
}

export interface IWindowDragDrop extends IWindowExtension {
	BeginDragDrop(pData: IShellData, n: DropBehavior): DropBehavior;
}

export interface IWindowSysTray extends IWindowExtension {
	SetVisible(b: boolean): IWindowSysTray;
	GetVisible(): boolean;

	SetText(b: string): IWindowSysTray;
	GetText(): string;

	OnClick(fn: (sender: Window) => void): IWindowSysTray;
	OnRightClick(fn: (sender: Window) => void): IWindowSysTray;
}

export interface IWindowDeviceNotification extends IWindowExtension {
	// An USB device is changed (both plug and unplug)
	OnChange(fn: (sender: Window) => void): IWindowDeviceNotification;
}

export enum WindowTaskbarIconicType {
	Thumbnail,
	LivePreview,
}

export type WindowTaskbarIconicImage = {
	Type: WindowTaskbarIconicType;
	Size: Vec2;
}

export interface IWindowTaskbar {
	SetState(n: ProgressBarState): IWindowTaskbar;
	GetState(): ProgressBarState;

	SetMaximum(n: number): IWindowTaskbar;
	GetMaximum(): number;

	SetValue(n: number): IWindowTaskbar;
	GetValue(): number;

	SetStep(n: number): IWindowTaskbar;
	GetStep(): number;
	Step(): IWindowTaskbar;

	SetForceBigIconSize100(n: number): IWindowTaskbar;
	GetForceBigIconSize100(): number;

	SetIconicImage(b: boolean): IWindowTaskbar;
	GetIconicImage(): boolean;

	SetIconicThumbnail(img: AveImage): IWindowTaskbar;
	SetIconicLivePreview(img: AveImage): IWindowTaskbar;

	GetButtonCount(): number;
	SetButtonVisible(index: number, b: boolean): IWindowTaskbar;
	GetButtonVisible(index: number): boolean;
	SetButtonEnable(index: number, b: boolean): IWindowTaskbar;
	GetButtonEnable(index: number): boolean;
	SetButtonIcon(index: number, nIconIndex: number): IWindowTaskbar;
	GetButtonIcon(index: number): number;
	SetButtonTooltip(index: number, tip: string): IWindowTaskbar;
	GetButtonTooltip(index: number): string;

	SetIconCount(count: number): IWindowTaskbar;
	GetIconCount(): number;
	SetIcon(index: number, img: AveImage);
	GetIcon(index: number): AveImage;

	OnIconicUpdate(fn: (sender: IWindowTaskbar, ii: WindowTaskbarIconicImage) => void): IWindowTaskbar;
	OnButtonClick(fn: (sender: IWindowTaskbar, nIndex: number) => void): IWindowTaskbar;
}

/* Localized control manager, support these controls
 * Button
 * CheckBox
 * ComboBox
 * Group
 * Header
 * Knob
 * Label
 * ListBox
 * Menu
 * RadioBox
 * StatusBar
 * Tab
 * TextBox
 * ToolBar
 * RibbonBackstage
 * RibbonTab
 * RibbonGroup
 * RibbonButton
 */
export interface IWindowControlManager {
	AddControl(c: IControl, key: string | number | StringKey): boolean;
	RemoveControl(c: IControl): boolean;
}

//----------------------------------------------------------------------------------------------------
// Window
//----------------------------------------------------------------------------------------------------

export class WindowCreation {
	Title: string = "";
	Icon: string = "";
	Layout: Rect = new Rect(-2147483648, -2147483648, 1280, 720);
	Flag: WindowFlag = WindowFlag.Default;
	ParentWindow: Window = null;
	Theme: Theme = null;
	Device: WindowDevice = WindowDevice.Default2D;
}

export class WindowPlacementLayout {
	Virtual: Rect = Rect.Empty;
	WorkPos: Vec2 = Vec2.Zero;
	Percent: Vec4 = Vec4.Zero;

	static FromNative(raw: WindowPlacementLayout) {
		const layout = new WindowPlacementLayout();
		layout.Virtual = Rect.FromNative(raw.Virtual);
		layout.WorkPos = Vec2.FromNative(raw.WorkPos);
		layout.Percent = Vec4.FromNative(raw.Percent);
		return layout;
	}
}

export class WindowPlacement {
	State: WindowSizeState = WindowSizeState.Normal;
	StateNonMin: WindowSizeState = WindowSizeState.Normal;
	LayoutNormal: WindowPlacementLayout = new WindowPlacementLayout();
	LayoutMin: WindowPlacementLayout = new WindowPlacementLayout();
	LayoutMax: WindowPlacementLayout = new WindowPlacementLayout();
	VirtualRect: Rect = Rect.Empty;
	MonitorLayoutChecksum: number = 0;
	MonitorLayoutWithoutWorkAreaChecksum: number = 0;

	static FromNative(raw: WindowPlacement) {
		const placement = new WindowPlacement();
		placement.State = raw.State;
		placement.StateNonMin = raw.StateNonMin;
		placement.LayoutNormal = WindowPlacementLayout.FromNative(raw.LayoutNormal);
		placement.LayoutMin = WindowPlacementLayout.FromNative(raw.LayoutMin);
		placement.LayoutMax = WindowPlacementLayout.FromNative(raw.LayoutMax);
		placement.VirtualRect = Rect.FromNative(raw.VirtualRect);
		placement.MonitorLayoutChecksum = raw.MonitorLayoutChecksum;
		placement.MonitorLayoutWithoutWorkAreaChecksum = raw.MonitorLayoutWithoutWorkAreaChecksum;
		return placement;
	}
}

export interface IWindowConstructor<T, Internal = any> {
	new (cp: WindowCreation): IWindow<T> & IControl & Internal;
}

export type IWindow<T> = {
	IsWindowCreated(): boolean;
	GetDeviceType(): WindowDevice;

	Activate(): T;
	IsActive(): boolean;

	SetTitle(s: string): T;
	GetTitle(): string;

	SetPosition(vPos: Vec2): T;
	SetSize(vSize: Vec2): T;

	SetClientPosition(vPos: Vec2): T;
	GetClientPosition(): Vec2;

	SetClientSize(vSize: Vec2): T;
	GetClientSize(): Vec2;

	SetMinimumSize(vSize: DpiSize_2): T;
	SetMinimumSize(): DpiSize_2;

	SetSizeState(n: WindowSizeState): T;
	GetSizeState(): WindowSizeState;
	IsMinimizable(): boolean;
	IsSizeable(): boolean;

	SetTopMost(b: boolean): T;
	GetTopMost(): boolean;

	SetIme(b: boolean): T;
	GetIme(): boolean;

	SetBackground(b: boolean): T;
	GetBackground(): boolean;

	SetRtl(b: boolean): T;
	GetRtl(): boolean;

	SetScale(n: WindowScale): T;
	GetScale(): WindowScale;

	SetKeyTipEnable(b: boolean): T;
	GetKeyTipEnable(): boolean;

	SetDirectKeyTip(b: boolean): T;
	GetDirectKeyTip(): boolean;

	SetContent(c: IControl): IControl; // returns the previous content
	GetContent(): IControl;

	SetIcon(nResId: number): T;
	GetIcon(): number;

	SetPlacement(wp: WindowPlacement): boolean;
	GetPlacement(): WindowPlacement;

	SetInfectionOverride(b: boolean): T;
	GetInfectionOverride(): boolean;

	SetInfection(infection: UiThemeInfection): T;
	GetInfection(): UiThemeInfection;

	SetImportantRender(b: boolean): T;
	GetImportantRender(): boolean;

	SetManualRender(b: boolean): T;
	GetManualRender(): boolean;
	ManualRender(): void;

	Update(): void;

	SetAppId(s: string): T;

	SetDeviceNotification(b: boolean): T;
	GetDeviceNotification(): boolean;

	GetTheme(): Theme;
	GetFrame(): IWindowFrame;
	GetControlManager(): IWindowControlManager;
	GetIconManager(): IIconManager;
	GetCommonUi(): ICommonUi;
	GetDragDrop(): IWindowDragDrop;
	GetSysTray(): IWindowSysTray;
	GetTaskbar(): IWindowTaskbar;
	GetPlatform(): IPlatform;

	GetTime(): number;

	CacheIcon(icon: IconSource): IconCache;
	CreateManagedIcon(icon: IconSource): IIcon;
	CreateIconAsImage(nIconId: number, nSubCount: number): AveImage;

	// Hotkey
	HotkeyRegister(key: KbKey, n: InputModifier): number;
	HotkeyDeregister(nId: number): boolean;
	HotkeySetEnable(b: boolean): T;
	HotkeyGetEnable(): boolean;
	HotkeyClear(): T;

	// Window events
	OnCreateContent(fn: (sender: T) => boolean): T;
	OnClosing(fn: (sender: T) => boolean): T;
	OnClose(fn: (sender: T) => void): T;

	// Occurs when press Enter key is pressed if there was no other control process it
	OnWindowOk(fn: (sender: T) => void): T;
	// Occurs when press Esc key is pressed if there was no other control process it
	OnWindowCancel(fn: (sender: T) => void): T;

	OnWindowHotkey(fn: (sender: T, nId: number, key: KbKey, n: InputModifier) => void): T;

	OnScaleChange(fn: (sender: T) => void): T;
	OnLanguageChange(fn: (sender: T) => void): T;

	OnDeviceChange(fn: (sender: T) => void): T;
};

class WindowBase extends (AveLib.UiWindow as IWindowConstructor<WindowBase>) {
	protected m_Content: IControl;

	// prevent gc
	protected m_Frame: IWindowFrame;
	protected m_FrameToolBarLeft: IControl;
	protected m_FrameToolBarRight: IControl;

	GetInfection(): UiThemeInfection {
		return UiThemeInfection.FromNative(super.GetInfection());
	}

	GetPlacement(): WindowPlacement {
		return WindowPlacement.FromNative(super.GetPlacement());
	}

	SetContent(c: IControl) {
		this.m_Content = c;
		return super.SetContent(c);
	}

	GetClientSize(): Vec2 {
		return Vec2.FromNative(super.GetClientSize());
	}

	GetClientPosition(): Vec2 {
		return Vec2.FromNative(super.GetClientPosition());
	}

	GetCommonUi(): ICommonUi {
		const commonUi = super.GetCommonUi();

		const OriginalPickColor = commonUi.PickColor.bind(commonUi) as typeof commonUi.PickColor;
		commonUi.PickColor = async (vColor: Vec4, bAllowAlpha: boolean) => Vec4.FromNative(await OriginalPickColor(vColor, bAllowAlpha));

		const OriginalPickColorEx = commonUi.PickColorEx.bind(commonUi) as typeof commonUi.PickColorEx;
		commonUi.PickColorEx = async (vColor: Vec4, bAllowAlpha: boolean, fnPreview: (vColor: Vec4) => void) => Vec4.FromNative(await OriginalPickColorEx(vColor, bAllowAlpha, (vColor: Vec4) => fnPreview(Vec4.FromNative(vColor))));

		return commonUi;
	}

	GetPlatform(): IPlatform {
		const platform = super.GetPlatform();
		const OriginalGetArea: typeof platform.ScreenGetArea = platform.ScreenGetArea.bind(platform);
		platform.ScreenGetArea = () => Rect.FromNative(OriginalGetArea());

		const OriginalMonitorEnumerate: typeof platform.MonitorEnumerate = platform.MonitorEnumerate.bind(platform);
		platform.MonitorEnumerate = () => OriginalMonitorEnumerate().map((item) => MonitorItem.FromNative(item));

		const OriginalPointerGetPosition: typeof platform.PointerGetPosition = platform.PointerGetPosition.bind(platform);
		platform.PointerGetPosition = () => Vec2.FromNative(OriginalPointerGetPosition());

		return platform;
	}

	GetFrame() {
		if (!this.m_Frame) {
			this.m_Frame = super.GetFrame();

			const OriginalSetToolBarLeft = this.m_Frame.SetToolBarLeft.bind(this.m_Frame);
			this.m_Frame.SetToolBarLeft = (control: IControl) => {
				this.m_FrameToolBarLeft = control;
				return OriginalSetToolBarLeft(control);
			};

			const OriginalSetToolBarRight = this.m_Frame.SetToolBarRight.bind(this.m_Frame);
			this.m_Frame.SetToolBarRight = (control: IControl) => {
				this.m_FrameToolBarRight = control;
				return OriginalSetToolBarRight(control);
			};

			const OriginalGetCaptionRect = this.m_Frame.GetCaptionRect.bind(this.m_Frame);
			this.m_Frame.GetCaptionRect = () => Rect.FromNative(OriginalGetCaptionRect());

			const OriginalGetIconRect = this.m_Frame.GetIconRect.bind(this.m_Frame);
			this.m_Frame.GetIconRect = () => Rect.FromNative(OriginalGetIconRect());

			const OriginalGetTextRect = this.m_Frame.GetTextRect.bind(this.m_Frame);
			this.m_Frame.GetTextRect = () => Rect.FromNative(OriginalGetTextRect());

			const OriginalGetNonBorderRect = this.m_Frame.GetNonBorderRect.bind(this.m_Frame);
			this.m_Frame.GetNonBorderRect = () => Rect.FromNative(OriginalGetNonBorderRect());
		}

		return this.m_Frame;
	}
}

export type WindowLike = Window | Dialog;

interface IWindowInternal {
	CreateWindow(pByoLinker: WindowLike, bIndependent?: boolean): boolean;
	CloseWindow(): void;
}

export class Window extends (WindowBase as any as IWindowConstructor<Window, IWindowInternal>) {
	CreateWindow(pByoLinker: Window = null, bIndependent = false): boolean {
		return super.CreateWindow(pByoLinker, bIndependent);
	}

	CloseWindow(): void {
		super.CloseWindow();
	}
}

interface IDialogInternal {
	ShowDialog(pByoLinker?: WindowLike): Promise<number>;
	CloseDialog(nCode: number): void;
}

type CreateDialog_t = (pByoLinker: WindowLike) => boolean;

export class Dialog extends (WindowBase as any as IWindowConstructor<Dialog, IDialogInternal>) {
	ShowDialog(pByoLinker: WindowLike): Promise<number> {
		if (!(super["CreateDialog"] as CreateDialog_t)(pByoLinker)) return null;
		return super.ShowDialog();
	}

	CloseDialog(nCode: number): void {
		return super.CloseDialog(nCode);
	}
}
