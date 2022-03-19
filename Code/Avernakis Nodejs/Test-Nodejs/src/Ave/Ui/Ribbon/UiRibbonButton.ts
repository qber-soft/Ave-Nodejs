import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "../Control/UiWindow";
import { ButtonType } from "../UiCommon";
import { IVisual } from "../UiVisual";

export interface IRibbonButton extends IControl {
    new (window: Window, key?: string | number): IRibbonButton;

    SetText(s: string): RibbonButton;
    GetText(): string;

    SetSmall(b: boolean): RibbonButton;
    GetSmall(): boolean;

    SetCheck(b: boolean): RibbonButton;
    GetCheck(): boolean;

    SetButtonType(n: ButtonType): RibbonButton;
    GetButtonType(): ButtonType;

    SetDrop(c: IControl): IControl;
    GetDrop(): IControl;

    SetBigVisual(v: IVisual): IVisual;
    GetBigVisual(): IVisual;

    SetSmallVisual(v: IVisual): IVisual;
    GetSmallVisual(): IVisual;

    OnClick(fn: (sender: RibbonButton) => void): RibbonButton;
    OnDrop(fn: (sender: RibbonButton) => void): RibbonButton;
}

export class RibbonButton extends (AveLib.UiRibbonButton as IRibbonButton) {
    private m_Drop: IControl;
    private m_BigVisual: IVisual;
    private m_SmallVisual: IVisual;

    SetDrop(c: IControl) {
        this.m_Drop = c;
        return super.SetDrop(c);
    }

    SetBigVisual(v: IVisual) {
        this.m_BigVisual = v;
        return super.SetBigVisual(v);
    }

    SetSmallVisual(v: IVisual) {
        this.m_SmallVisual = v;
        return super.SetSmallVisual(v);
    }
}
