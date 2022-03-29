import { Vec2, Vec4 } from "../Math/Vector";
import { Rect } from "./UiCommon";
import { IControlExtension } from "../AveLib";

export enum DropBehavior {
    None = 0b0000,
    Copy = 0b0001,
    Move = 0b0010,
    Link = 0b0100,
}

export enum DragDropImage {
    Invalid,
    No, // no image
    None, // can't drop (a red "no" circle typically)
    Copy,
    Move,
    Link,
    Label,
    Warning,
}

export interface IShellData {}

// prettier-ignore
export enum ControlMessage {
    None                   /**/,
    Create                 /**/, // Occurs when a window is created
    Destroy                /**/, // Occurs when a window is being destroyed
    Destroyed              /**/, // Occurs when a window is destroyed
    Closing                /**/, // Occurs when a window is closing, the message processor can block the closing
    Activate               /**/, // Occurs when a window is activating or deactivating
    Enable                 /**/, // Occurs when a window is enabling or or disenabling
    Show                   /**/, // Occurs when a window is showing or hiding
    Paint                  /**/, // Occurs when a control is redrawn
    PointerEnter           /**/, // Occurs when the pointer enters the control
    PointerLeave           /**/, // Occurs when the pointer leaves the control
    PointerPress           /**/, // Occurs when the pointer button is pressed
    PointerRelease         /**/, // Occurs when the pointer button is release
    PointerClickNdc        /**/, // Occurs when the pointer button is clicked without double-click possibly, this occurs after a short time (double-clicking time in system settings) after PointerRelease.
    PointerMove            /**/, // Occurs when the pointer is moved
    PointerVWheel          /**/, // Occurs when the pointer vertical wheel is moved
    PointerHWheel          /**/, // Occurs when the pointer horizontal wheel is moved
    PointerHover           /**/, // Occurs when the pointer rests on the control
    PointerLost            /**/, // Occurs when the pointer is lost
    PointerCursor          /**/, // Occurs when the host requests the cursor type
    PointerTypeHint        /**/, // Occurs when the pointer is doing interaction
    KeyPress               /**/, // Occurs when a key is pressed
    KeyRelease             /**/, // Occurs when a key is released
    KeyActivate            /**/, // Occurs when a control is activated through a key
    KeySelect              /**/, // Occurs when a control is selected through a key, a selected control may has child control to determine more detailed selection, and activate the last selected control.
    KeyWant                /**/, // Occurs when the host requests the special keys that the control want to receive
    ImeCompStart           /**/, // Occurs when the IME starts composition
    ImeOpenCand            /**/, // Occurs when the IME opens composition window
    ImeReconv              /**/, // Occurs when the IME requests to do reconversion
    ImeReconvConf          /**/, // Occurs when the IME confirms the reconversion
    ImeInputChar           /**/, // Occurs when the IME inputs a character
    PopupShow              /**/, // Occurs when a popup window is opened
    PopupHide              /**/, // Occurs when a popup window is hide
    FocusGet               /**/, // Occurs when the host requests the control that having focus
    FocusSet               /**/, // Occurs when the host wants to change the focus control
    CanGetFocus            /**/, // Occurs when the host requests whether a control can get focus
    CanGetIme              /**/, // Occurs when the host requests whether a control can open IME
    ChangeFocus            /**/, // Occurs when the focus control change
    ChangedFocus           /**/, // Occurs when the focus contorl is changed, this is use to inform the host
    ChangeParent           /**/, // Occurs when a control's parent is changed
    ChangePosition         /**/, // Occurs when a control's position is changed
    ChangeSize             /**/, // Occurs when a control's size is changing
    ChangeOwner            /**/, // Occurs when a control's owner is changed
    ChangedSize            /**/, // Occurs when a control's size is changed
    ChangeDpi              /**/, // Occurs when the DPI is changed
    ChangeIsVisual         /**/, // Occurs when the IsVisual property is override
    ChangeSetting          /**/, // Occurs when the system settings is changed
    RequestTimer           /**/, // Occurs when the timer needs to be reset, this might occurs when the hardware power configuration is changed, e.g. the timer counter is broken or the timer frequence is changed
    RequestPause           /**/, // Occurs when a control requests to pause the application logic, this might occurs when a window is moving or resizing.
    Timer                  /**/, // Occurs when a timer is tick
    KeyTipGetCount         /**/, // Gets key tip count
    KeyTipGet              /**/, // Gets key tip
    NcHitTest              /**/, // Hit-test non-client area
    ShowSysMenu            /**/, // Hit-test non-client area
    MinMaxInfo             /**/, // Get min/max info
    RibbonShrinkHint       /**/, // Notifies the optimized ribbon shrink mode
    UpdateState            /**/, // Update states
    SetTypedPainter        /**/, // Set typed painter

    // Reverse messagess (from control to native container/window)
    Rev = 0x20000000,
    RevGetSysParam         /**/, // Gets system parameters
    RevPopupHide           /**/, // Notifies the container (window) to close
    RevSysMenu             /**/, // Notifies the container (window) to initialize the sysmenu
    RevSysCommand          /**/, // Notifies the container (window) to execute a syscommand
    RevUpdateFrame         /**/, // Notifies the container (window) to update frame
    RevMoveWindow          /**/, // Starts move window
    RevMoveWindowEnd       /**/, // move window stopped (not reverse)

    // User messages
    User0 = 0x40000000,
}

export interface IDragContext {
    GetBehavior(): DropBehavior;
    GetPosition(): Vec2;
    GetData(): IShellData;

    SetDropTip(image: DragDropImage, s: string): void;
    SetDropBehavior(n: DropBehavior): void;
}

export interface IControl extends IControlExtension {
    SetVisible(b: boolean): IControl;
    GetVisible(): boolean;

    SetEnable(b: boolean): IControl;
    GetEnable(): boolean;

    GetRect(): Rect;
    GetRectClient(): Rect;

    GetParent(): IControl;

    SetFocusEnable(b: boolean): IControl;
    GetFocusEnable(): boolean;
    GetFocus(): IControl;
    SetFocus(): IControl;

    SetKeyTip(tip: string, nIndex?: number): IControl;
    GetKeyTip(nIndex: number): string;

    SetToolTip(tip: string): IControl;
    GetToolTip(pt: Vec2): string;

    SetStyle(nStyle: number): IControl;
    GetStyle(): number;

    SetTextColor(vColor: Vec4): IControl;
    GetTextColor(): Vec4;

    SetOpacity(f: number): IControl;
    GetOpacity(): number;

    SetRotation(f: number): IControl;
    GetRotation(): number;
    HasRotation(): boolean;

    SetTabStop(b: boolean): IControl;
    GetTabStop(): boolean;

    MapRect(rc: Rect, bClient: boolean): Rect;
    Redraw(): IControl;

    SetDropEnable(b: boolean): IControl;
    GetDropEnable(): boolean;

    OnDragEnter(fn: (sender: IDragContext) => void): IControl;
    OnDragMove(fn: (sender: IDragContext) => void): IControl;
    OnDragLeave(fn: (sender: IDragContext) => void): IControl;
    OnDragDrop(fn: (sender: IDragContext) => void): IControl;
    OnDragEnd(fn: (sender: IDragContext) => void): IControl;

    ListenEvent();
    OnMessagePost(
        fn: (sender: IControl, nMsg: ControlMessage) => void
    ): IControl;
}
