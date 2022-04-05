import { AveLib } from "../../AveLib";
import { DropBehavior, IControl, IShellData } from "../UiControl";
import {
    DpiSize_2,
    IconCache,
    IconSource,
    IIconManager,
    InputModifier,
    KbKey,
    ProgressBarState,
    Rect,
    StringKey,
} from "../UiCommon";
import { Theme } from "../Theme/UiTheme";
import { ICommonUi } from "../UiCommonUi";
import { Vec2 } from "../../Math/Vector";
import { IPlatform, MonitorItem } from "../UiPlatform";
import { IWindowFrame } from "./UiWindowFrame";
import { IIcon } from "../Visual/UiIcon";

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

export interface IWindow extends IControl {
    new (cp: WindowCreation): IWindow;

    // Window methods
    CreateWindow(): boolean;
    CloseWindow(): void;

    GetDeviceType(): WindowDevice;

    Activate(): Window;
    IsActive(): boolean;

    SetTitle(s: string): Window;
    GetTitle(): string;

    SetPosition(vPos: Vec2): Window;
    SetSize(vSize: Vec2): Window;

    SetClientPosition(vPos: Vec2): Window;
    GetClientPosition(): Vec2;

    SetClientSize(vSize: Vec2): Window;
    GetClientSize(): Vec2;

    SetMinimumSize(vSize: DpiSize_2): Window;
    SetMinimumSize(): DpiSize_2;

    SetSizeState(n: WindowSizeState): Window;
    GetSizeState(): WindowSizeState;
    IsMinimizable(): boolean;
    IsSizeable(): boolean;

    SetTopMost(b: boolean): Window;
    GetTopMost(): boolean;

    SetIme(b: boolean): Window;
    GetIme(): boolean;

    SetBackground(b: boolean): Window;
    GetBackground(): boolean;

    SetRtl(b: boolean): Window;
    GetRtl(): boolean;

    SetScale(n: WindowScale): Window;
    GetScale(): WindowScale;

    SetKeyTipEnable(b: boolean): Window;
    GetKeyTipEnable(): boolean;

    SetDirectKeyTip(b: boolean): Window;
    GetDirectKeyTip(): boolean;

    SetContent(c: IControl): IControl; // returns the previous content
    GetContent(): IControl;

    SetIcon(nResId: number): Window;
    GetIcon(): number;

    SetAppId(s: string): Window;

    SetDeviceNotification(b: boolean): Window;
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

    // Hotkey
    HotkeyRegister(key: KbKey, n: InputModifier): number;
    HotkeyDeregister(nId: number): boolean;
    HotkeySetEnable(b: boolean): Window;
    HotkeyGetEnable(): boolean;
    HotkeyClear(): Window;

    // Window events
    OnCreateContent(fn: (sender: Window) => boolean): Window;
    OnClosing(fn: (sender: Window) => boolean): Window;
    OnClose(fn: (sender: Window) => void): Window;

    // Occurs when press Enter key is pressed if there was no other control process it
    OnWindowOk(fn: (sender: Window) => void): Window;
    // Occurs when press Esc key is pressed if there was no other control process it
    OnWindowCancel(fn: (sender: Window) => void): Window;

    OnWindowHotkey(
        fn: (sender: Window, nId: number, key: KbKey, n: InputModifier) => void
    ): Window;

    OnScaleChange(fn: (sender: Window) => void): Window;
    OnLanguageChange(fn: (sender: Window) => void): Window;

    OnDeviceChange(fn: (sender: Window) => void): Window;
}

export class Window extends (AveLib.UiWindow as IWindow) {
    private m_Content: IControl;

    // prevent gc
    private m_Frame: IWindowFrame;
    private m_FrameToolBarLeft: IControl;
    private m_FrameToolBarRight: IControl;

    SetContent(c: IControl) {
        this.m_Content = c;
        return super.SetContent(c);
    }

    GetPlatform(): IPlatform {
        const platform = super.GetPlatform();
        const OriginalGetArea: typeof platform.ScreenGetArea =
            platform.ScreenGetArea.bind(platform);
        platform.ScreenGetArea = () => Rect.FromNative(OriginalGetArea());

        const OriginalMonitorEnumerate: typeof platform.MonitorEnumerate =
            platform.MonitorEnumerate.bind(platform);
        platform.MonitorEnumerate = () =>
            OriginalMonitorEnumerate().map((item) =>
                MonitorItem.FromNative(item)
            );
        return platform;
    }

    GetFrame() {
        if (!this.m_Frame) {
            this.m_Frame = super.GetFrame();

            const OriginalSetToolBarLeft = this.m_Frame.SetToolBarLeft.bind(
                this.m_Frame
            );
            this.m_Frame.SetToolBarLeft = (control: IControl) => {
                this.m_FrameToolBarLeft = control;
                return OriginalSetToolBarLeft(control);
            };

            const OriginalSetToolBarRight = this.m_Frame.SetToolBarRight.bind(
                this.m_Frame
            );
            this.m_Frame.SetToolBarRight = (control: IControl) => {
                this.m_FrameToolBarRight = control;
                return OriginalSetToolBarRight(control);
            };

            const OriginalGetCaptionRect = this.m_Frame.GetCaptionRect.bind(
                this.m_Frame
            );
            this.m_Frame.GetCaptionRect = () =>
                Rect.FromNative(OriginalGetCaptionRect());

            const OriginalGetIconRect = this.m_Frame.GetIconRect.bind(
                this.m_Frame
            );
            this.m_Frame.GetIconRect = () =>
                Rect.FromNative(OriginalGetIconRect());

            const OriginalGetTextRect = this.m_Frame.GetTextRect.bind(
                this.m_Frame
            );
            this.m_Frame.GetTextRect = () =>
                Rect.FromNative(OriginalGetTextRect());

            const OriginalGetNonBorderRect = this.m_Frame.GetNonBorderRect.bind(
                this.m_Frame
            );
            this.m_Frame.GetNonBorderRect = () =>
                Rect.FromNative(OriginalGetNonBorderRect());
        }

        return this.m_Frame;
    }
}
