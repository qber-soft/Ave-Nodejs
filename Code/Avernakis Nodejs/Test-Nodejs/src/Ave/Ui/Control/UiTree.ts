import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";
import { IconCache, Rect, ExpandAction, DpiSize } from "../UiCommon";
import { Vec2 } from "../../Math/Vector";

export type TreeItemHandle = number;

export enum TreeItemFlag {
	None /**/ = 0x0000,
	Text /**/ = 0x0001,
	Icon /**/ = 0x0004,
	Blank /**/ = 0x0008,
}

export class TreeGenericHandle {
	private constructor() {}

	static get Root(): TreeItemHandle {
		return 0;
	}
	static get First(): TreeItemHandle {
		return 0xffffffff;
	}
	static get Last(): TreeItemHandle {
		return 0xfffffffe;
	}
	static get Sort(): TreeItemHandle {
		return 0xfffffffd;
	}
}

export class TreeItem {
	Flag: TreeItemFlag = TreeItemFlag.None;
	Icon: IconCache = 0;
	Text: string = "";
	Item: TreeItemHandle = 0;
	Blank: boolean = false;
}

export class TreeInsert {
	Parent: TreeItemHandle = 0;
	After: TreeItemHandle = 0;
	Item: TreeItem = new TreeItem();
}

export enum TreeItemPart {
	Item,
	Glyph,
	Icon,
	Text,
}

export enum TreeItemPlace {
	Item,
	Above,
	Below,
}

export enum TreeSelectionMode {
	Single,
	Multiple,
}

export enum TreeNextItem {
	Child,
	Parent,
	Next,
	Previous,
	DisplayNext,
	DisplayPrevious,
}

export class TreeHitTestResult {
	Item: TreeItemHandle;
	Part: TreeItemPart;
	Place: TreeItemPlace;
	PlaceAb: TreeItemPlace;
}

export class TreeEdit {
	Text: string;
	CanEdit: boolean;
}

export class TreeEditFinish {
	Text: string;
	Canceled: boolean;
}

export interface ITree extends IControl {
	new (window: Window): ITree;

	ItemInsert(pInsert: TreeInsert): TreeItemHandle;
	ItemRemove(pItem: TreeItemHandle): boolean;
	ItemClear(): Tree;
	ItemSelect(pItem: TreeItemHandle): Tree;
	ItemSetSelected(pItem: TreeItemHandle, bSelect: boolean): Tree;
	ItemSort(pItem: TreeItemHandle, bSortChild: boolean): Tree;
	ItemSet(pItem: TreeItem): boolean;
	ItemGet(pItem: TreeItemHandle): TreeItem;
	ItemGetNext(pItem: TreeItemHandle, nNext: TreeNextItem): TreeItemHandle;
	ItemGetCountPerPage(bIncludePartial: boolean): number;
	ItemGetSelectionCount(): number;
	ItemGetSelection(): TreeItemHandle;
	ItemGetSelected(pItem: TreeItemHandle): boolean;
	ItemGetSelectionAll(): TreeItemHandle[];
	ItemEnsure(pItem: TreeItemHandle): Tree;
	ItemGetTop(): TreeItemHandle;
	ItemGetTopIndex(): number;
	ItemSetTopIndex(nIndex: number): Tree;
	ItemIsVisible(pItem: TreeItemHandle): boolean;
	ItemGetRect(pItem: TreeItemHandle, nPart: TreeItemPart): Rect;
	ItemHitTest(pt: Vec2): TreeHitTestResult;
	ItemExpand(pItem: TreeItemHandle, nExpand: ExpandAction, bIncludeChild: boolean): Tree;
	ItemIsExpanded(pItem: TreeItemHandle): boolean;
	ItemEdit(pItem: TreeItemHandle): boolean;
	ItemIsEdit(): boolean;
	ItemEditFinish(bCancel: boolean): Tree;
	ItemSetHighlight(pItem: TreeItemHandle, nPlace: TreeItemPlace): Tree;

	SetAutoEdit(bAutoEdit: boolean): Tree;
	GetAutoEdit(): boolean;

	SetAutoScrollOnHover(b: boolean): Tree;
	GetAutoScrollOnHover(): boolean;

	SetNodeLine(b: boolean): Tree;
	GetNodeLine(): boolean;

	SetNodeLineHighlight(b: boolean): Tree;
	GetNodeLineHighlight(): boolean;

	SetSingleClickExpand(b: boolean): Tree;
	GetSingleClickExpand(): boolean;

	SetSelectionMode(nSelMode: TreeSelectionMode): Tree;
	GetSelectionMode(): TreeSelectionMode;

	SetIndentWidth(nWidth: DpiSize): Tree;
	GetIndentWidth(): DpiSize;

	SetScrollPosition(pt: Vec2, bScroll: boolean): Tree;
	GetScrollPosition(): Vec2;
	GetScrollSize(): Vec2;
	GetScrollMax(): Vec2;

	OnSelectionChange(fn: (sender: Tree) => void): Tree;
	OnDoubleClick(fn: (sender: Tree, pItem: TreeItemHandle) => void): Tree;
	OnRightClick(fn: (sender: Tree, pItem: TreeItemHandle) => void): Tree;
	OnEditBegin(fn: (sender: Tree, pItem: TreeItemHandle, pEidt: TreeEdit) => void): Tree;
	OnEditEnd(fn: (sender: Tree, pItem: TreeItemHandle, pEidt: TreeEdit) => void): Tree;
	OnEditFinish(fn: (sender: Tree, pItem: TreeItemHandle, pEidt: TreeEditFinish) => void): Tree;
	OnDragBegin(fn: (sender: Tree) => boolean): Tree;
}

export class Tree extends (AveLib.UiTree as ITree) {
	ItemGetRect(pItem: TreeItemHandle, nPart: TreeItemPart): Rect {
		return Rect.FromNative(super.ItemGetRect(pItem, nPart));
	}

	GetScrollPosition(): Vec2 {
		return Vec2.FromNative(super.GetScrollPosition());
	}
	
	GetScrollSize(): Vec2 {
		return Vec2.FromNative(super.GetScrollSize());
	}
	
	GetScrollMax(): Vec2 {
		return Vec2.FromNative(super.GetScrollMax());
	}
}
