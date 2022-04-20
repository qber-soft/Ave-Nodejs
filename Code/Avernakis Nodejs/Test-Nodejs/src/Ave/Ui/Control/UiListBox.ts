import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { WindowLike } from "./UiWindow";
import { Rect } from "../UiCommon";
import { Vec2 } from "../../Math";

export enum ListBoxSelectionMode {
	Single,
	Multiple,
}

export enum ListBoxItemFlag {
	None = 0x0,
	Visual = 0x1,
}

export class ListBoxItemVirtual {
	Misc: ListBoxItemFlag;
	String: string;
}

export interface IListBox extends IControl {
	new (window: WindowLike): IListBox;

	Append(text: string): ListBox;
	Insert(text: string, nInsertBefore: number): ListBox;
	Remove(nIndex: number): boolean;
	Clear(): ListBox;
	Select(nIndex: number): ListBox;
	SetSelect(nIndex: number, bSelect: boolean): ListBox;
	SetSelectRange(nStart: number, nTo: number, bSelect: boolean): ListBox; // [nStart, nTo], NOT [nStart, nTo)
	Sort(bAsc: boolean, bCaseInsensitive: boolean): ListBox;
	Find(text: string, nStartIndex: number, bExact: boolean, bCaseInsensitive: boolean): number;
	Swap(nIndex0: number, nIndex1: number): boolean;
	Set(nIndex: number, text: string): boolean;
	Get(nIndex: number): string;
	GetCount(): number;
	GetSelection(): number;
	IsSelected(nIndex: number): boolean;
	GetNextSelection(nIndex: number): number;

	Ensure(nIndex: number): ListBox;
	SetTopIndex(nIndex: number): ListBox;
	GetTopIndex(): number;
	ItemIsVisible(nIndex: number): boolean;
	ItemGetRect(nIndex: number): Rect;
	ItemHitTest(vPos: Vec2): number;

	SetCount(nCount: number): ListBox;
	SetVirtual(fn: (sender: ListBox, nIndex: number) => ListBoxItemVirtual): ListBox;

	SetSelectionMode(nSelMode: ListBoxSelectionMode): ListBox;
	GetSelectionMode(): ListBoxSelectionMode;

	OnSelectionChange(fn: (sender: ListBox) => void): ListBox;
	OnSelectionEnd(fn: (sender: ListBox) => void): ListBox;
	OnDoubleClick(fn: (sender: ListBox, nIndex: number) => void): ListBox;
	OnRightClick(fn: (sender: ListBox, nIndex: number) => void): ListBox;
}

export class ListBox extends (AveLib.UiListBox as IListBox) {
	ItemGetRect(nIndex: number): Rect {
		return Rect.FromNative(super.ItemGetRect(nIndex));
	}
}
