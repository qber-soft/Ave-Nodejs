import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";
import { DpiSize, AlignType, IconCache, Rect, StringKey } from "../UiCommon";
import { Vec2, Vec4 } from "../../Math/Vector";

export interface IStatusBar extends IControl {
    new (window: Window, key?: StringKey): IStatusBar;

    SetPart(vPartWidth: DpiSize[]): StatusBar;
    GetPart(): DpiSize[];
    SetWidth(nIndex: number, nWidth: DpiSize): StatusBar;
    GetWidth(nIndex: number): DpiSize;
    GetWidthReal(nIndex: number): number;
    SetMaxWidth(nIndex: number, nWidth: DpiSize): StatusBar;
    GetMaxWidth(nIndex: number): DpiSize;
    SetReducePriority(nIndex: number, nPriority: number): StatusBar;
    GetReducePriority(nIndex: number): number;
    SetText(nIndex: number, s: string): StatusBar;
    GetText(nIndex: number): string;
    SetPartToolTip(nIndex: number, s: string): StatusBar;
    SetAlign(nIndex: number, nType: AlignType): StatusBar;
    GetAlign(nIndex: number): AlignType;
    SetIcon(nIndex: number, nIcon: IconCache): StatusBar;
    GetIcon(nIndex: number): IconCache;
    SetClickable(nIndex: number, bClickable: boolean): StatusBar;
    GetClickable(nIndex: number): boolean;
    SetContent(nIndex: number, pControl: IControl): IControl;
    GetContent(nIndex: number): IControl;
    SetContentMargin(nIndex: number, nMargin: number): StatusBar;
    GetContentMargin(nIndex: number): number;
    HitTest(pt: Vec2, bIncludeUnclickable: boolean): number;
    GetItemRect(nIndex: number): Rect;

    SetBackground(b: boolean): StatusBar;
    GetBackground(): boolean;

    SetBackColor(vColor: Vec4): StatusBar;
    GetBackColor(): Vec4;

    OnClick(fn: (sender: StatusBar, nIndex: number) => void): StatusBar;
}

export class StatusBar extends (AveLib.UiStatusBar as IStatusBar) {
    private m_Content: Array<IControl>;
    SetPart(vPartWidth: DpiSize[]) {
        this.m_Content = null;
        if (vPartWidth.length > 0)
            this.m_Content = new Array(vPartWidth.length);
        return super.SetPart(vPartWidth);
    }

    SetContent(nIndex: number, pControl: IControl) {
        if (this.m_Content && nIndex < this.m_Content.length)
            this.m_Content[nIndex] = pControl;
        return super.SetContent(nIndex, pControl);
    }

    GetItemRect(nIndex: number): Rect {
        return Rect.FromNative(super.GetItemRect(nIndex));
    }
}
