import { Vec2 } from "../../Math";
import { Rect } from "../UiCommon";
import { IControl } from "../UiControl";
import { IVisual } from "../UiVisual";
import { MenuItem } from "./UiMenu";

export enum WindowFramePart {
	BorderL,
	BorderT,
	BorderR,
	BorderB,
	CornerLT,
	CornerRT,
	CornerLB,
	CornerRB,
	Caption,
	Client,
	Minimum,
	Maximum,
	Close,
	SysMenu,
}

export interface IWindowFrame {
	SetIcon(n: IVisual): IVisual;
	GetIcon(): IVisual;

	SetToolBarLeft(c: IControl): IControl;
	GetToolBarLeft(): IControl;

	SetToolBarRight(c: IControl): IControl;
	GetToolBarRight(): IControl;

	GetCaptionRect(): Rect;
	GetIconRect(): Rect;
	GetTextRect(): Rect;
	GetNonBorderRect(): Rect;

	SetBorderVisible(b: boolean): IWindowFrame;
	GetBorderVisible(): boolean;

	SetBorderOpacity(f: number): IWindowFrame;
	GetBorderOpacity(): number;

	SetCaptionVisible(b: boolean): IWindowFrame;
	GetCaptionVisible(): boolean;

	SysMenuReset(): void;
	SysMenuAppend(mi: MenuItem): boolean;

	OnNcHitTest(fn: (sender: IWindowFrame, vPos: Vec2, nPart: WindowFramePart) => WindowFramePart): IWindowFrame;
	OnNcHitTestResult(fn: (sender: IWindowFrame, nPart: WindowFramePart) => void): IWindowFrame;
	OnSysMenuPopup(fn: (sender: IWindowFrame) => void): IWindowFrame;
	OnSysMenuClick(fn: (sender: IWindowFrame, nId: number) => void): IWindowFrame;
	OnMaximumClick(fn: (sender: IWindowFrame) => void): IWindowFrame;
}
