import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";
import { Vec2 } from "../../Math/Vector";

export enum PagerAdjustment {
    None,
    FitWidth,
    FitHeight,
}

export interface IPager extends IControl {
    new (window: Window): IPager;

    SetContent(pControl: IControl): IControl;
    GetContent(): IControl;

    SetContentSize(vSize: Vec2): Pager;
    GetContentSize(): Vec2;
    GetRealContentSize(): Vec2;

    SetAdjustment(nAdjust: PagerAdjustment): Pager;
    GetAdjustment(): PagerAdjustment;

    SetAutoHideScroll(b: boolean): Pager;
    GetAutoHideScroll(): boolean;

    SetPointerScroll(b: boolean): Pager;
    GetPointerScroll(): boolean;
}

export class Pager extends (AveLib.UiPager as IPager) {
    private m_Content: IControl;

    SetContent(pControl: IControl) {
        this.m_Content = pControl;
        return super.SetContent(pControl);
    }
}
