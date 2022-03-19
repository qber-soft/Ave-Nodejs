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
}
