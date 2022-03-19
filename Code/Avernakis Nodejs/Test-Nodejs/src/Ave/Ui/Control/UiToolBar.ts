import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";
import { CrossDirection, IconCache, DpiSize, StringKey } from "../UiCommon";
import { Vec2 } from "../../Math/Vector";

export enum ToolBarItemFlag {
    None /**/ = 0x0000,
    Id /**/ = 0x0001,
    Type /**/ = 0x0002,
    Icon /**/ = 0x0004,
    Text /**/ = 0x0010,
    Tooltip /**/ = 0x0020,
    Width /**/ = 0x0040,
}

export enum ToolBarItemType {
    Button,
    ButtonDrop,
    ButtonSplit,
    Splitter,
    Content,
    Text,
    Menu,
}

export class ToolBarItem {
    Flag: ToolBarItemFlag = ToolBarItemFlag.None;
    Id: number = 0;
    Type: ToolBarItemType = ToolBarItemType.Button;
    Icon: IconCache = 0;
    Width: DpiSize = DpiSize.FromPixel(0);
    Text: string = "";
    Tooltip: string = "";

    constructor(
        id: number = 0,
        type: ToolBarItemType = ToolBarItemType.Button,
        icon: IconCache = 0,
        width: DpiSize = DpiSize.FromPixel(0),
        text: string = "",
        tooltip: string = ""
    ) {
        this.Id = id;
        this.Type = type;
        this.Icon = icon;
        this.Width = width;
        this.Text = text;
        this.Tooltip = tooltip;
    }
}

export interface IToolBar extends IControl {
    new (window: Window, key?: StringKey): IToolBar;

    ToolInsert(item: ToolBarItem, nIndexBefore: number): boolean;
    ToolRemove(nIndex: number): boolean;
    ToolRemoveAll(): ToolBar;
    ToolGet(nIndex: number): ToolBarItem;
    ToolSet(nIndex: number, item: ToolBarItem): boolean;
    ToolGetById(nId: number): ToolBarItem;
    ToolSetById(nId: number, item: ToolBarItem): boolean;
    ToolGetCount(): number;

    ToolSetEnable(nId: number, bEnable: boolean): ToolBar;
    ToolGetEnable(nId: number): boolean;

    ToolSetVisible(nId: number, bVisible: boolean): ToolBar;
    ToolGetVisible(nId: number): boolean;

    ToolSetCheck(nId: number, bCheck: boolean): ToolBar;
    ToolGetCheck(nId: number): boolean;

    ToolHitTest(
        pt: Vec2,
        bIncludeInvisible: boolean,
        bIncludeDisabled: boolean
    ): number;

    ContentSet(nIndex: number, pControl: IControl): IControl;
    ContentGet(nIndex: number): IControl;
    ContentSetById(nId: number, pControl: IControl): IControl;
    ContentGetById(nId: number): IControl;

    DropSet(nIndex: number, pControl: IControl): IControl;
    DropGet(nIndex: number): IControl;
    DropSetById(nId: number, pControl: IControl): IControl;
    DropGetById(nId: number): IControl;

    SetBackground(b: boolean): ToolBar;
    GetBackground(): boolean;

    SetIconTextDirection(nDir: CrossDirection): ToolBar;
    GetIconTextDirection(): CrossDirection;

    OnClick(fn: (sender: ToolBar, nId: number) => void): ToolBar;
    OnDrop(fn: (sender: ToolBar, nId: number) => void): ToolBar;
}

export class ToolBar extends (AveLib.UiToolBar as IToolBar) {
    private m_Content: Set<IControl> = new Set();
    private m_Drop: Set<IControl> = new Set();

    ToolRemove(nIndex: number) {
        this.m_Content.delete(this.ContentGet(nIndex));
        this.m_Drop.delete(this.DropGet(nIndex));
        return super.ToolRemove(nIndex);
    }

    ToolRemoveAll() {
        this.m_Content.clear();
        this.m_Drop.clear();
        return super.ToolRemoveAll();
    }

    ContentSet(nIndex: number, pControl: IControl) {
        const t = super.ContentSet(nIndex, pControl);
        if (t) this.m_Content.delete(t);
        if (pControl) this.m_Content.add(pControl);
        return t;
    }

    ContentSetById(nId: number, pControl: IControl) {
        const t = super.ContentSetById(nId, pControl);
        if (t) this.m_Content.delete(t);
        if (pControl) this.m_Content.add(pControl);
        return t;
    }

    DropSet(nIndex: number, pControl: IControl) {
        const t = super.DropSet(nIndex, pControl);
        if (t) this.m_Drop.delete(t);
        if (pControl) this.m_Drop.add(pControl);
        return t;
    }

    DropSetById(nId: number, pControl: IControl) {
        const t = super.DropSetById(nId, pControl);
        if (t) this.m_Drop.delete(t);
        if (pControl) this.m_Drop.add(pControl);
        return t;
    }
}
