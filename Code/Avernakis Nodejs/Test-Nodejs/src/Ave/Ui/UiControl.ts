import { Vec2, Vec4 } from "../Math/Vector";
import { AlignType, CursorType, DpiSize_2, InputModifier, InputType, KbKey, PointerButton, PointerType, Rect } from "./UiCommon";
import { IControlExtension } from "../AveLib";
import { FileFindItem } from "../Io/IoCommon";
import { IAveStream } from "../Io/IoStream";
import { IPainter } from "./UiPainter";
import { Byo2Font } from "../Byo2/Byo2Font";

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

export class MessageKey {
	Key: KbKey;
	Modifier: InputModifier;
}

export class MessagePointerMouse {
	LinePerWheel: number;
	Wheel: number;
}

export class MessagePointerTouch {
	Pressure: number; // [0, 1]
	Orientation: number; // [0, 1]
	Contact: Rect;
}

export class MessagePointerPen {
	Pressure: number; // [0, 1]
	Twist: number; // [0, 1]
	Tilt: Vec2; // [-1, 1]
}

export class MessagePointer {
	static FromNative(mp: MessagePointer): MessagePointer {
		mp.Touch.Contact = Rect.FromNative(mp.Touch.Contact);
		mp.Pen.Tilt = Vec2.FromNative(mp.Pen.Tilt);
		mp.Position = Vec2.FromNative(mp.Position);
		return mp;
	}
	// Common
	Id: number;
	Type: PointerType;
	Position: Vec2;
	Modifier: InputModifier;
	Button: PointerButton;
	Count: number;

	// Specified types by Type
	Mouse: MessagePointerMouse;
	Touch: MessagePointerTouch;
	Pen: MessagePointerPen;
}

export interface IDragContext {
	GetModifier(): InputModifier;
	GetPosition(): Vec2;

	SetDropTip(image: DragDropImage, s: string): void;
	SetDropBehavior(n: DropBehavior): void;

	HasVirtualFile(): boolean;
	HasFile(): boolean;

	VirtualFileGetCount(): number;
	VirtualFileGetInfo(nIndex: number): FileFindItem;
	VirtualFileOpen(nIndex: number): IAveStream;

	FileGetCount(): number;
	FileGet(): string[];
}

export enum PopupAlign {
    Auto,
    Left,
    Right,
};

export class PopupParam {
    // Excluded rect in control space which popup another control, the popuped control will avoid this area
    Exclude: Rect = Rect.Empty;

    // Horizontal alignemnt, if the PC has pen input and current system is set to right-handed, the popuped control will display at left side of the origin point
    Align: PopupAlign = PopupAlign.Auto;

    // Vertical alignment
    VerticalAlign: AlignType = AlignType.Near;

    // Whether to restrict the whole popuped control to the monitor that origin point belongs to
    ClipMonitor: boolean = true;

    // Whether to use screen space instead of popuper control's client space
    ScreenSpace: boolean = false;

    // How many clicked can be catched that cause the popup window close, catched click will be sent to the target control that clicked.
    // If this is 0, the user clicked a button on the main window, the popuped window will close but the button will not be clicked, this clicking is wasted and just use to close the popuped window
    CatchClosingClick: number = 0;

    constructor(rcExclue: Rect = Rect.Empty, align: PopupAlign = PopupAlign.Auto, valign: AlignType = AlignType.Near) {
        this.Exclude = rcExclue;
        this.Align = align;
        this.VerticalAlign = valign;
    }
}

// prettier-ignore
export interface IControl extends IControlExtension {
    SetVisible(b: boolean): IControl;
    GetVisible(): boolean;

    SetEnable(b: boolean): IControl;
    GetEnable(): boolean;

    GetRect(): Rect;
    GetRectClient(): Rect;

    SetIdealSize(vSize: DpiSize_2): IControl;
    GetIdealSize(): DpiSize_2;
    
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

    SetFont(pFont: Byo2Font): IControl;

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

    GetLastInputType(): InputType;
    GetLastPointerType(): PointerType;
    GetLastMessageTime(): number;
    IsVisual(): boolean;

    SetDropEnable(b: boolean): IControl;
    GetDropEnable(): boolean;

    ShowPopup(pPopup: IControl, vPos: Vec2, param: PopupParam): Promise<boolean>;
    HidePopup(); // Hide the popup window the control belongs to, NOT the control that called ShowPoup

    OnKeyPress  /**/(fn: (sender: IControl, mk: MessageKey) => void): IControl;
    OnKeyRelease/**/(fn: (sender: IControl, mk: MessageKey) => void): IControl;

    OnPointerEnter    /**/(fn: (sender: IControl, mp: MessagePointer) => void): IControl;
    OnPointerLeave    /**/(fn: (sender: IControl, mp: MessagePointer) => void): IControl;
    OnPointerPress    /**/(fn: (sender: IControl, mp: MessagePointer) => void): IControl;
    OnPointerRelease  /**/(fn: (sender: IControl, mp: MessagePointer) => void): IControl;
    OnPointerClickNdc /**/(fn: (sender: IControl, mp: MessagePointer) => void): IControl;
    OnPointerMove     /**/(fn: (sender: IControl, mp: MessagePointer) => void): IControl;
    OnPointerVWheel   /**/(fn: (sender: IControl, mp: MessagePointer) => void): IControl;
    OnPointerHWheel   /**/(fn: (sender: IControl, mp: MessagePointer) => void): IControl;
    OnPointerHover    /**/(fn: (sender: IControl, mp: MessagePointer) => void): IControl;
    OnPointerLost     /**/(fn: (sender: IControl, mp: MessagePointer) => void): IControl;
    OnPointerCursor   /**/(fn: (sender: IControl, mp: MessagePointer) => CursorType): IControl;
    
    OnDragEnter /**/(fn: (sender: IControl, dc: IDragContext) => void): IControl;
    OnDragMove  /**/(fn: (sender: IControl, dc: IDragContext) => void): IControl;
    OnDragLeave /**/(fn: (sender: IControl, dc: IDragContext) => void): IControl;
    OnDragDrop  /**/(fn: (sender: IControl, dc: IDragContext) => void): IControl;
    OnDragEnd   /**/(fn: (sender: IControl, dc: IDragContext) => void): IControl;

    OnChangeFocus(fn: (sender: IControl, bFocus: boolean) => void): IControl;
    OnChangeSize(fn: (sender: IControl, vSize: Vec2) => void): IControl;
    OnPaintPost(fn: (sender: IControl, painter: IPainter, rc: Rect) => void): IControl;
}
