import { Rect } from "../UiCommon";
import { IControl } from "../UiControl";
import { IVisual } from "../UiVisual";
import { MenuItem } from "./UiMenu";

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

	SetCaptionVisible(b: boolean): IWindowFrame;
	GetCaptionVisible(): boolean;

	SysMenuReset(): void;
	SysMenuAppend(mi: MenuItem): boolean;
}
