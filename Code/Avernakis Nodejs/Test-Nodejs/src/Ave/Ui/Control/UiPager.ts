import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";
import { Vec2 } from "../../Math/Vector";
import { AlignType } from "../UiCommon";

export enum PagerAdjustment {
    None,
    FitWidth,
    FitHeight,
}

export interface IPager extends IControl {
    new(window: Window): IPager;

    SetContent(pControl: IControl): IControl;
    GetContent(): IControl;

    SetContentSize(vSize: Vec2): Pager;
    GetContentSize(): Vec2;
    GetRealContentSize(): Vec2;

    SetContentHorizontalAlign(nType: AlignType): Pager;
    GetContentHorizontalAlign(): AlignType;

    SetContentVerticalAlign(nType: AlignType): Pager;
    GetContentVerticalAlign(): AlignType;

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

    GetContentSize(): Vec2 {
        return Vec2.FromNative(super.GetContentSize());
    }

    GetRealContentSize(): Vec2 {
        return Vec2.FromNative(super.GetRealContentSize());
    }
}
