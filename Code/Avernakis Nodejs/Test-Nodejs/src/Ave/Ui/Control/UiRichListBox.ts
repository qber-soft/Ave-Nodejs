import { IControl } from "../UiControl";
import { AveLib, ExtendControlInstance } from "../../AveLib";
import { Window } from "./UiWindow";
import { DpiSize, DpiSize_2, IconCache, Rect } from "../UiCommon";
import { Vec2 } from "../../Math/Vector";
import { Header } from "./UiHeader";

export enum RichListBoxSelectionMode {
    Single,
    Multiple,
}

export enum RichListBoxViewMode {
    Detail,
    Tile,
    Icon,
    List,
}

export enum RichListBoxItemPlace {
    Item,
    Above,
    Below,
}

export enum RichListBoxItemCheck {
    None,
    Selection,
    Standalone,
}

export enum RichListBoxItemFlag {
    None /**/ = 0x0000,
    Text /**/ = 0x0001,
    Indent /**/ = 0x0002,
    GroupId /**/ = 0x0004,
    Context /**/ = 0x0008,
    Icon /**/ = 0x0010,
    Misc /**/ = 0x0020,
}

export enum RichListBoxItemMisc {
    None /**/ = 0x0000, // Draw a tree glyph
    HasChild /**/ = 0x0001, // Draw a tree glyph
    Expanded /**/ = 0x0002, // Draw an expanded tree glyph
    NoChild /**/ = 0x0004, // The item has no glyph (no glyph indent)
    PlaceHolder /**/ = 0x0008,
    Checked /**/ = 0x0010, // Only valid in RichListBoxItemCheck::Standalone mode
    CheckHidden /**/ = 0x0020, // Only valid in RichListBoxItemCheck::Standalone mode
    SingleLine /**/ = 0x0100, // Single line text, only for tile mode
}

export class RichListBoxItem {
    Flag: RichListBoxItemFlag = RichListBoxItemFlag.None;
    Index: number = 0;
    IndexSub: number = 0;
    Icon: IconCache = 0;
    Text: string = "";
    Indent: number = 0;
    GroupId: number = 0;
    Misc: RichListBoxItemMisc = RichListBoxItemMisc.None;
    Context: number = 0;
}

export class RichListBoxHitTestResult {
    Index: number;
    SubIndex: number;
    Place: RichListBoxItemPlace;
    PlaceAb: RichListBoxItemPlace;
}

export class RichListBoxItemVirtual {
    Icon: IconCache = 0;
    Indent: number = 0;
    Misc: RichListBoxItemMisc = RichListBoxItemMisc.None;
    String: string = "";
}

export interface IRichListBox extends IControl {
    new (window: Window): IRichListBox;

    ItemInsert(item: RichListBoxItem, bReserveSelection: boolean): number;
    ItemRemove(nIndex: number, bReserveSelection: boolean): boolean;
    ItemClear(): RichListBox;
    ItemSelect(nIndex: number): RichListBox;
    ItemSetSelect(nIndex: number, bSelect: boolean): RichListBox;
    ItemSetSelectRange(
        nStart: number,
        nEnd: number,
        bSelect: boolean
    ): RichListBox; // in the range [nStart, nEnd], not [nStart, nEnd)
    ItemSort(
        nSubItem: number,
        bAsc: boolean,
        bCaseInsensitive: boolean
    ): RichListBox;
    ItemFind(
        szString: string,
        nIndex: number,
        bExact: boolean,
        bCaseInsensitive: boolean
    ): number;
    ItemSet(item: RichListBoxItem): boolean;
    ItemGet(
        nFlag: RichListBoxItemFlag,
        nIndex: number,
        nSubIndex: number
    ): RichListBoxItem;
    ItemGetCount(): number;
    ItemGetCountPerPage(bIncludePartial: boolean): number;
    ItemGetSelectionCount(): number;
    ItemGetSelection(): number;
    ItemIsSelected(nIndex: number): boolean;
    ItemGetNextSelection(nIndex: number): number;
    ItemEnsure(nIndex: number): RichListBox;
    ItemGetTopIndex(): number;
    ItemIsVisible(nIndex: number): boolean;
    ItemGetRect(nIndex: number): Rect;
    ItemHitTest(
        pt: Vec2,
        bMustOnContent: boolean,
        bIncludePlaceholder: boolean
    ): RichListBoxHitTestResult;
    ItemSetCount(nCount: number): RichListBox;
    ItemSetHighlight(nIndex: number, nPlace: RichListBoxItemPlace): RichListBox;
    ItemSetMinimumHeight(nHeight: DpiSize): RichListBox;
    ItemGetMinimumHeight(): DpiSize;

    SetVirtual(
        fn: (
            sender: RichListBox,
            nIndex: number,
            nSubIndex: number
        ) => RichListBoxItemVirtual
    ): RichListBox;

    GetHeader(): Header;
    SetHeaderAutoWidth(b: boolean): RichListBox;
    GetHeaderAutoWidth(): boolean;

    SetScrollPosition(vPos: Vec2): RichListBox;
    GetScrollPosition(): Vec2;

    SetSelectionMode(nSelMode: RichListBoxSelectionMode): RichListBox;
    GetSelectionMode(): RichListBoxSelectionMode;

    SetViewMode(nViewMode: RichListBoxViewMode): RichListBox;
    GetViewMode(): RichListBoxViewMode;

    SetTileSize(vSize: DpiSize_2): RichListBox;
    GetTileSize(): DpiSize_2;
    SetTileColumnPriority(order: number[]): RichListBox;
    GetTileColumnPriority(): Array<number>;

    SetItemSpace(vSize: DpiSize_2): RichListBox;
    GetItemSpace(): DpiSize_2;

    SetTreeStyle(b: boolean): RichListBox;
    GetTreeStyle(): boolean;

    SetItemCheck(nSelMode: RichListBoxItemCheck): RichListBox;
    GetItemCheck(): RichListBoxItemCheck;

    SetIconSize(nMode: RichListBoxViewMode, vSize: DpiSize): RichListBox;
    GetIconSize(nMode: RichListBoxViewMode): DpiSize;

    SetIconNameColumn(nColumn: number): RichListBox;
    GetIconNameColumn(): number;

    SetListItemWidth(nColumn: DpiSize): RichListBox;
    GetListItemWidth(): DpiSize;

    GetListRect(): Rect;

    OnSelectionChange(/**/ fn: (sender: RichListBox) => void): RichListBox;
    OnSelectionEnd(/**/ fn: (sender: RichListBox) => void): RichListBox;
    OnDoubleClick(
        /**/ fn: (sender: RichListBox, nIndex: number) => void
    ): RichListBox;
    OnRightClick(
        /**/ fn: (sender: RichListBox, nIndex: number) => void
    ): RichListBox;
    OnDragBegin(/**/ fn: (sender: RichListBox) => void): RichListBox;
    OnGlyphClick(
        /**/ fn: (sender: RichListBox, nIndex: number) => void
    ): RichListBox;
    OnItemCheck(
        /**/ fn: (sender: RichListBox, nIndex: number) => void
    ): RichListBox;
}

export class RichListBox extends (AveLib.UiRichListBox as IRichListBox) {
    ItemGetRect(nIndex: number): Rect {
        return Rect.FromNative(super.ItemGetRect(nIndex));
    }

    GetListRect(): Rect {
        return Rect.FromNative(super.GetListRect());
    }

    GetScrollPosition(): Vec2 {
        return Vec2.FromNative(super.GetScrollPosition());
    }

    GetHeader(): Header {
        const header = super.GetHeader();
        ExtendControlInstance(header as any as IControl);
        return header;
    }
}
