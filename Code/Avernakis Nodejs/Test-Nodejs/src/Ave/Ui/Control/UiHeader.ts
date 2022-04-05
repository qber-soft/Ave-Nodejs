import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";
import { DpiSize, Rect, StringKey } from "../UiCommon";

export enum HeaderItemFlag {
    None /**/ = 0x0000,
    Format /**/ = 0x0001,
    Width /**/ = 0x0002,
    Text /**/ = 0x0004,
    Context /**/ = 0x0008,
}

export enum HeaderItemFormat {
    Left /**/ = 0x0000,
    Right /**/ = 0x0001,
    Center /**/ = 0x0002,
    DropDown /**/ = 0x0010,
    Filter /**/ = 0x0020,
    Check /**/ = 0x0040,
    Checked /**/ = 0x0080,
    Fixed /**/ = 0x0100,
}

export class HeaderItem {
    Flag: HeaderItemFlag = HeaderItemFlag.None;
    Format: HeaderItemFormat = HeaderItemFormat.Left;
    Width: DpiSize = DpiSize.FromPixel(0);
    MinWidth: DpiSize = DpiSize.FromPixel(0);
    Text: string = "";
    Context: number = 0;

    constructor(
        nFormat?: HeaderItemFormat,
        text?: string,
        nWidth?: DpiSize,
        nMinWidth?: DpiSize
    ) {
        if (undefined == nFormat) return;
        this.Flag = HeaderItemFlag.Format;
        this.Format = nFormat;
        if (text) {
            this.Flag |= HeaderItemFlag.Text;
            this.Text = text;
        }
        if (undefined == nMinWidth) nMinWidth = nWidth;
        if (undefined != nWidth && undefined != nMinWidth) {
            this.Flag |= HeaderItemFlag.Width;
            this.Width = nWidth;
            this.MinWidth = nMinWidth;
        }
    }
}

export enum HeaderItemSort {
    Asc,
    Desc,
    Auto,
}

export interface IHeader extends Omit<IControl, "GetRect"> {
    new (window: Window, key?: StringKey): IHeader;

    Add(item: HeaderItem): Header;
    Insert(nInsertBefore: number, item: HeaderItem): boolean;
    GetCount(): number;
    Get(nIndex: number): HeaderItem;
    GetRect(nIndex: number): Rect;
    Set(nInsertBefore: number, item: HeaderItem): boolean;
    Remove(nIndex: number): boolean;
    RemoveAll(): Header;

    ItemSetDownDrop(nIndex: number, b: boolean): Header;
    ItemGetDownDrop(nIndex: number): boolean;
    ItemSetFilter(nIndex: number, b: boolean): Header;
    ItemGetFilter(nIndex: number): boolean;
    ItemSetCheckValue(nIndex: number, b: boolean): Header;
    ItemGetCheckValue(nIndex: number): boolean;

    SetOrder(order: number[]): Header;
    GetOrder(): Array<number>;

    SetSort(
        nIndex: number,
        nOrder: HeaderItemSort,
        nDefault: HeaderItemSort
    ): Header;

    GetSortIndex(): number;
    GetSortOrder(): HeaderItemSort;

    SetDrag(b: boolean): Header;
    GetDrag(): boolean;

    SetButton(b: boolean): Header;
    GetButton(): boolean;

    SetCheckMode(b: boolean): Header;
    GetCheckMode(): boolean;

    SetCheckValue(b: boolean): Header;
    GetCheckValue(): boolean;

    OnClick(/**/ fn: (sender: Header, nIndex: number) => void): Header;
    OnAdjustWidth(
        /**/ fn: (sender: Header, nIndex: number, bAdjusting: boolean) => void
    ): Header;
    OnOrder(
        /**/ fn: (sender: Header, nNewIndex: number, nOldIndex: number) => void
    ): Header;
    OnDropDown(/**/ fn: (sender: Header, nIndex: number) => void): Header;
    OnCheckItem(/**/ fn: (sender: Header, nIndex: number) => void): Header;
    OnCheckHeader(/**/ fn: (sender: Header) => void): Header;
}

export class Header extends (AveLib.UiHeader as IHeader) {
    GetRect(nIndex: number): Rect {
        return Rect.FromNative(super.GetRect(nIndex));
    }
}
