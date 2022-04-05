import { Vec2, Vec4 } from "../Math/Vector";
import {
    CursorType,
    InputModifier,
    KbKey,
    PointerButton,
    PointerType,
    Rect,
} from "./UiCommon";
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
    GetBehavior(): DropBehavior;
    GetPosition(): Vec2;
    GetData(): IShellData;

    SetDropTip(image: DragDropImage, s: string): void;
    SetDropBehavior(n: DropBehavior): void;
}

// prettier-ignore
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

    OnDragEnter /**/(fn: (sender: IDragContext) => void): IControl;
    OnDragMove  /**/(fn: (sender: IDragContext) => void): IControl;
    OnDragLeave /**/(fn: (sender: IDragContext) => void): IControl;
    OnDragDrop  /**/(fn: (sender: IDragContext) => void): IControl;
    OnDragEnd   /**/(fn: (sender: IDragContext) => void): IControl;
    
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
}
