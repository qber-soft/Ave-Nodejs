import { IControl } from "../UiControl";
import { AveLib, ExtendControlInstance } from "../../AveLib";
import { Window } from "./UiWindow";
import { IconCache, DpiSize, StringKey, DpiSize_2 } from "../UiCommon";

export enum MenuFlag {
	None /**/ = 0x00,
	State /**/ = 0x01,
	Type /**/ = 0x02,
	Text /**/ = 0x04,
	TextSub /**/ = 0x08,
	Key /**/ = 0x10,
	Icon /**/ = 0x20,
	Context /**/ = 0x40,
	Size /**/ = 0x80,
}

export enum MenuType {
	Text,
	Section,
	Separator,
	Content,
}

export enum MenuState {
	Enabled /**/ = 0x00,
	Disabled /**/ = 0x01,
	Checked /**/ = 0x02,
	Radio /**/ = 0x04,
	Default /**/ = 0x08,
	Break /**/ = 0x10,
	NoClose /**/ = 0x20, // Left Click or Keyboard
	NoClose2 /**/ = 0x40, // Right Click
	NoClose3 /**/ = 0x80, // Middle Click
}

export class MenuItem {
	Flag: MenuFlag = MenuFlag.None;
	State: MenuState = MenuState.Enabled;
	Type: MenuType = MenuType.Text;
	Index: number = -1;
	Id: number = 0;
	Icon: IconCache = 0;
	Text: string = "";
	TextSub: string = "";
	Key: string = "";
	Size: DpiSize_2 = new DpiSize_2(DpiSize.FromPixel(0), DpiSize.FromPixel(0));

	constructor(id: number = 0, type: MenuType = MenuType.Text, icon: IconCache = 0, text: string = "", textSub: string = "", key: string = "") {
		this.Id = id;
		this.Type = type;
		this.Icon = icon;
		this.Text = text;
		this.TextSub = textSub;
		this.Key = key;
	}
}

export interface IMenu extends IControl {
	new (window: Window, key?: StringKey): IMenu;

	InsertItem(pItem: MenuItem): number;
	InsertSubMenu(pItem: MenuItem): Menu;
	RemoveById(nId: number): boolean;
	RemoveByIndex(nIndex: number): boolean;
	SetById(pItem: MenuItem): boolean;
	SetByIndex(pItem: MenuItem): boolean;
	GetById(nId: number): MenuItem;
	GetByIndex(nIndex: number): MenuItem;
	GetSubMenuById(nId: number): Menu;
	GetSubMenuByIndex(nIndex: number): Menu;
	Clear(): Menu;
	GetCount(): number;
	SetItemHeight(nHeight: DpiSize): Menu;
	GetItemHeight(): DpiSize;
	SetCheckById(nId: number, b: boolean): number; // return Index
	GetCheckById(nId: number): boolean;
	SetRadioId(nId: number): number; // return Index
	GetRadioId(): number;
	SetGroupRadioId(nIdStart: number, nIdEnd: number, nId: number): number; // return Index, range in [nIdStart, nIdEnd)
	GetGroupRadioId(nIdStart: number, nIdEnd: number): number; // range in [nIdStart, nIdEnd)
	SetContentById(nId: number, pControl: IControl): IControl;
	SetContentByIndex(nIndex: number, pControl: IControl): IControl;
	GetContentById(nId: number): IControl;
	GetContentByIndex(nIndex: number): IControl;

	OnClick(fn: (sender: Menu, nId: number) => void): Menu;
	OnRightClick(fn: (sender: Menu, nId: number) => void): Menu;
	OnMiddleClick(fn: (sender: Menu, nId: number) => void): Menu;
	OnShow(fn: (sender: Menu) => void): Menu;
	OnHide(fn: (sender: Menu) => void): Menu;
}

export class Menu extends (AveLib.UiMenu as IMenu) {
	private m_Content: Set<IControl> = new Set();

	RemoveById(nId: number) {
		this.m_Content.delete(this.GetContentById(nId));
		return super.RemoveById(nId);
	}

	RemoveByIndex(nIndex: number) {
		this.m_Content.delete(this.GetContentByIndex(nIndex));
		return super.RemoveByIndex(nIndex);
	}

	Clear() {
		this.m_Content.clear();
		return super.Clear();
	}

	SetContentById(nId: number, pControl: IControl) {
		const t = super.SetContentById(nId, pControl);
		if (t) this.m_Content.delete(t);
		if (pControl) this.m_Content.add(pControl);
		return t;
	}

	SetContentByIndex(nIndex: number, pControl: IControl) {
		const t = super.SetContentByIndex(nIndex, pControl);
		if (t) this.m_Content.delete(t);
		if (pControl) this.m_Content.add(pControl);
		return t;
	}

	InsertSubMenu(pItem: MenuItem): Menu {
		const menu = super.InsertSubMenu(pItem);
		ExtendControlInstance(menu);
		return menu;
	}
}
