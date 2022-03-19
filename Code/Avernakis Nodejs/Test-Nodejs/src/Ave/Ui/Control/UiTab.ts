import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";
import {
    AxisDirection,
    ExpandAction,
    IconCache,
    Rect,
    DpiSize,
    DpiSize_2,
    StringKey,
} from "../UiCommon";
import { Vec4, Vec2 } from "../../Math/Vector";

export enum TabOverflow {
    Reduce,
    ScrollButton,
    ScrollBar,
    MultipleLine,
}

export enum TabSort {
    Unsorted,
    Alphabet,
    Logical,
}

export enum TabUngroupedPosition {
    Last,
    AfterPinned,
}

export enum TabButtonDisplay {
    Hidden,
    Pointing, // This is the worst way to display buttons that may cause many accident clicks. And this is bad for touch inputs.
    Selected,
    Always,
}

export enum TabObjectType {
    Tab,
    Group,
}

export enum TabItemMisc {
    None /**/ = 0x0000,
    Disabled /**/ = 0x0001,
    Pinned /**/ = 0x0002,
}

export class TabItem {
    Id: number = 0;
    Order: number = 0;
    Icon: IconCache = 0;
    Text: string = "";
    StackGroup: string = "";
    StackText: string = "";
    GroupId: number = 0;
    Misc: TabItemMisc = TabItemMisc.None;
    ButtonMask: number = 0;
    Color: Vec4 = new Vec4();
}

export class TabGroup {
    Id: number = 0;
    OrderNormal: number = 0;
    OrderPinned: number = 0;
    Icon: IconCache = 0;
    Text: string = "";
    ButtonMask: number = 0;
    Color: Vec4 = new Vec4();
}

export interface ITab extends IControl {
    new (window: Window, key?: StringKey): ITab;

    TabInsert(pTab: TabItem): boolean;
    TabGetAll(): number[];
    TabGet(nId: number): TabItem;
    TabSet(pTab: TabItem): boolean;
    TabRemove(nId: number): boolean;
    TabClear(): Tab;

    TabSelect(nId: number): boolean;
    TabGetSelection(): number;
    TabSetSelected(nId: number, bSelect: boolean): Tab;
    TabGetSelected(nId: number): boolean;
    TabGetSelectionCount(): number;
    TabGetAllSelection(): number[];
    TabSetMultipleSelection(b: boolean): Tab;
    TabGetMultipleSelection(): boolean;

    TabGetRect(nId: number, bReal: boolean): Rect;
    TabGetHeaderRect(): Rect;

    TabSetDirection(nDir: AxisDirection): Tab;
    TabGetDirection(): AxisDirection;

    TabSetVertical(b: boolean): Tab;
    TabGetVertical(): boolean;

    TabSetOverflow(nOverflow: TabOverflow): Tab;
    TabGetOverflow(): TabOverflow;

    TabSetSort(nSort: TabSort): Tab;
    TabGetSort(): TabSort;

    TabSetHeaderSize(nSize: DpiSize): Tab;
    TabGetHeaderSize(): DpiSize;

    TabSetMaxHeaderSize(nSize: DpiSize): Tab;
    TabGetMaxHeaderSize(): DpiSize;

    TabSetUngroupedPosition(nPos: TabUngroupedPosition): Tab;
    TabGetUngroupedPosition(): TabUngroupedPosition;
    TabSetUngroupedName(s: string): Tab;
    TabGetUngroupedName(): String;

    TabSetReorderable(b: boolean): Tab;
    TabGetReorderable(): boolean;
    TabSetRegroup(b: boolean): Tab;
    TabGetRegroup(): boolean;

    GroupInsert(pGroup: TabGroup): boolean;
    GroupGetAll(): number[];
    GroupGet(nId: number): TabGroup;
    GroupSet(pGroup: TabGroup): boolean;
    GroupRemove(nId: number): boolean;
    GroupClear(): Tab;
    GroupExpand(nId: number, bPinned: boolean, nAction: ExpandAction): Tab;
    GroupIsExpanded(nId: number, bPinned: boolean): boolean;

    GroupSetGlyphVisible(b: boolean): Tab;
    GroupGetGlyphVisible(): boolean;

    ButtonClear(): Tab;
    ButtonSetIcon(nIndex: number, nIcon: IconCache): Tab;
    ButtonGetIcon(nIndex: number): IconCache;
    ButtonSetDisplay(nIndex: number, nDisplay: TabButtonDisplay): Tab;
    ButtonGetDisplay(nIndex: number): TabButtonDisplay;
    ButtonSetName(nIndex: number, s: string): Tab;
    ButtonGetName(nIndex: number): string;

    HeaderSetNearSize(vSize: DpiSize_2): Tab;
    HeaderGetNearSize(): DpiSize_2;
    HeaderSetNearContent(pControl: IControl): IControl;
    HeaderGetNearContent(): IControl;
    HeaderSetFarSize(vSize: DpiSize_2): Tab;
    HeaderGetFarSize(): DpiSize_2;
    HeaderSetFarContent(pControl: IControl): IControl;
    HeaderGetFarContent(): IControl;

    SetSimpleTab(b: boolean): Tab;
    GetSimpleTab(): boolean;
    SetSimpleColor(vColor: Vec4): Tab;
    GetSimpleColor(): Vec4;

    ContentSet(nId: number, pControl: IControl): IControl;
    ContentGet(nId: number): IControl;
    ContentGetRect(): Rect;

    ContentSetMargin(b: boolean): Tab;
    ContentGetMargin(): boolean;

    StopReordering(bCancel: boolean): Tab;

    SetTabKeyTip(sKeyTip: string, nId: number): Tab;
    GetTabKeyTip(nId: number): string;

    OnSelectionChange(fn: (sender: Tab) => void): Tab;
    OnDoubleClick(
        fn: (sender: Tab, nId: number, nType: TabObjectType) => void
    ): Tab;
    OnRightClickOnMiddleClick(
        fn: (sender: Tab, nId: number, nType: TabObjectType) => void
    ): Tab;
    OnMiddleClick(
        fn: (sender: Tab, nId: number, nType: TabObjectType) => void
    ): Tab;
    OnDrag(
        fn: (
            sender: Tab,
            nId: number,
            nType: TabObjectType,
            vDragStartPosition: Vec2
        ) => void
    ): Tab;
    OnButtonClick(
        fn: (
            sender: Tab,
            nId: number,
            nType: TabObjectType,
            nButtonIndex: number
        ) => void
    ): Tab;
}

export class Tab extends (AveLib.UiTab as ITab) {
    private m_HeaderNearContent: IControl;
    private m_HeaderFarContent: IControl;
    private m_Content: Map<number, IControl> = new Map();

    HeaderSetNearContent(pControl: IControl) {
        this.m_HeaderNearContent = pControl;
        return super.HeaderSetNearContent(pControl);
    }

    HeaderSetFarContent(pControl: IControl) {
        this.m_HeaderFarContent = pControl;
        return super.HeaderSetFarContent(pControl);
    }

    TabRemove(nId: number) {
        this.m_Content.delete(nId);
        return super.TabRemove(nId);
    }

    TabClear() {
        this.m_Content.clear();
        return super.TabClear();
    }

    ContentSet(nId: number, pControl: IControl) {
        if (pControl) this.m_Content[nId] = pControl;
        else this.m_Content.delete(nId);
        return super.ContentSet(nId, pControl);
    }
}
