import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "../Control/UiWindow";
import { IconCache, DpiSize } from "../UiCommon";
import { Vec2 } from "../../Math/Vector";

export enum RibbonGalleryItemFlag {
    None /**/ = 0x0000,
    Icon /**/ = 0x0001,
    Text /**/ = 0x0002,
    Group /**/ = 0x0004,
    Tooltip /**/ = 0x0010,
}

export enum RibbonGalleryMenuFlag {
    None /**/ = 0x0000,
    Icon /**/ = 0x0001,
    Id /**/ = 0x0002,
    Text /**/ = 0x0004,
    State /**/ = 0x0008,
}

export enum RibbonGalleryMenuState {
    Enabled /**/ = 0x00,
    Grayed /**/ = 0x01,
}

export enum RibbonGalleryViewMode {
    IconOnly1Line,
    IconOnly2Line,
    IconOnly3Line,
    IconText1Line,
    IconText2Line,
    IconText3Line,
}

export class RibbonGalleryItem {
    Flag: RibbonGalleryItemFlag = RibbonGalleryItemFlag.None;
    Index: number = 0;
    Icon: IconCache = 0;
    Text: string = "";
    Tooltip: string = "";
    Group: number = 0;
}

export class RibbonGalleryMenu {
    Flag: RibbonGalleryMenuFlag = RibbonGalleryMenuFlag.None;
    Index: number = 0;
    Id: number = 0;
    Icon: IconCache = 0;
    State: RibbonGalleryMenuState = RibbonGalleryMenuState.Enabled;
    Text: string = "";
}

export interface IRibbonGallery extends IControl {
    new (window: Window, key?: string | number): IRibbonGallery;

    ItemInsert(pItem: RibbonGalleryItem): number;
    ItemRemove(nIndex: number): boolean;
    ItemClear(): RibbonGallery;
    ItemSelect(nIndex: number): RibbonGallery;
    ItemSet(pItem: RibbonGalleryItem): boolean;
    ItemGet(nIndex: number): RibbonGalleryItem;
    ItemGetCount(): number;
    ItemGetSelection(): number;

    GroupInsert(s: string, nInsertBefore: number): number;
    GroupRemove(nIndex: number): boolean;
    GroupClear(): RibbonGallery;
    GroupSet(nIndex: number, s: string): string;
    GroupGet(nIndex: number): string;
    GroupGetCount(): number;

    MenuInsert(pItem: RibbonGalleryMenu): number;
    MenuRemove(nIndex: number): boolean;
    MenuClear(): RibbonGallery;
    MenuSet(pItem: RibbonGalleryMenu): boolean;
    MenuGet(nIndex: number): RibbonGalleryMenu;
    MenuSetEnable(nId: number, b: boolean): RibbonGallery;
    MenuGetEnable(nId: number): boolean;
    MenuGetCount(): number;

    ViewSetMode(nViewMode: RibbonGalleryViewMode): RibbonGallery;
    ViewGetMode(): RibbonGalleryViewMode;

    ViewSetItemWidth(nWidth: DpiSize): RibbonGallery;
    ViewGetItemWidth(): DpiSize;

    ViewSetDefaultItemCountPerLine(nCount: number): RibbonGallery;
    ViewGetDefaultItemCountPerLine(): number;

    ViewSetItemCountPerLineRange(vRange: Vec2): RibbonGallery;
    ViewGetItemCountPerLineRange(): Vec2;

    ViewSetWidthWeight(nWeight: number): RibbonGallery;
    ViewGetWidthWeight(): number;

    OnSelect(fn: (sender: RibbonGallery) => void): RibbonGallery;
    OnPreview(
        fn: (sender: RibbonGallery, nIndex: number) => void
    ): RibbonGallery;
    OnDrop(fn: (sender: RibbonGallery) => void): RibbonGallery;
    OnMenuClick(
        fn: (sender: RibbonGallery, nId: number) => void
    ): RibbonGallery;
}

export class RibbonGallery extends (AveLib.UiRibbonGallery as IRibbonGallery) {
    ViewGetItemCountPerLineRange(): Vec2 {
        return Vec2.FromNative(super.ViewGetItemCountPerLineRange());
    }
}
