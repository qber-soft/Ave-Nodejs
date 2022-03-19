import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "../Control/UiWindow";
import { IconCache, Rect, DpiSize } from "../UiCommon";

export interface IRibbonBackstage extends IControl {
    new (window: Window, key?: string | number): IRibbonBackstage;

    SetText(s: string): RibbonBackstage;
    GetText(): string;

    SetCount(nCount: number): RibbonBackstage;
    GetCount(): number;
    Add(): RibbonBackstage;
    Select(nIndex: number): RibbonBackstage;
    GetSelection(): number;
    GetHighlight(): number;

    SetText(nIndex: number, s: string): RibbonBackstage;
    GetText(nIndex: number): string;
    SetIcon(nIndex: number, nIcon: IconCache): RibbonBackstage;
    GetIcon(nIndex: number): IconCache;
    SetContent(nIndex: number, pControl: IControl): IControl;
    GetContent(nIndex: number): IControl;
    SetItemEnable(nIndex: number, b: boolean): RibbonBackstage;
    GetItemEnable(nIndex: number): boolean;
    GetItemRect(nIndex: number): Rect;

    SetBannerWidth(nWidth: DpiSize): RibbonBackstage;
    GetBannerWidth(): DpiSize;

    SetTextVisible(b: boolean): RibbonBackstage;
    GetTextVisible(): boolean;

    ClearHighlight(): RibbonBackstage;

    OnSelect(
        fn: (sender: RibbonBackstage, nIndex: number) => void
    ): RibbonBackstage;
    OnHighlight(
        fn: (sender: RibbonBackstage, nIndex: number) => void
    ): RibbonBackstage;
}

export class RibbonBackstage extends (AveLib.UiRibbonBackstage as IRibbonBackstage) {
    private m_Content: Array<IControl> = [];

    SetCount(nCount: number) {
        while (this.m_Content.length > nCount) this.m_Content.pop();
        return super.SetCount(nCount);
    }

    SetContent(nIndex: number, pControl: IControl) {
        if (nIndex < this.GetCount()) {
            while (nIndex < this.m_Content.length)
                this.m_Content.push(null as IControl);
            this.m_Content[nIndex] = pControl;
        }
        return super.SetContent(nIndex, pControl);
    }
}
