import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";
import { Vec2, Vec4 } from "../../Math/Vector";
import { IVisual } from "../UiVisual";

export interface IKnob extends IControl {
    new (window: Window, key?: string | number): IKnob;

    SetText(s: string): Knob;
    GetText(): string;

    ValueSetRange(v: Vec2): Knob;
    ValueGetRange(): Vec2;

    ValueSetDefault(f: number): Knob;
    ValueGetDefault(): number;

    ValueSet(f: number): Knob;
    ValueGet(): number;

    StepSetUnlimited(f: number): Knob;
    StepGetUnlimited(): number;

    ValueSetCycle(b: boolean): Knob;
    ValueGetCycle(): boolean;

    StepSetLarge(f: number): Knob;
    StepGetLarge(): number;

    StepSetSmall(f: number): Knob;
    StepGetSmall(): number;

    ValueSetSplit(f: number): Knob;
    ValueGetSplit(): number;

    ValueSetTick(t: number[]): Knob;
    ValueGetTick(): number[];

    RingSetColor(v: Vec4): Knob;
    RingGetColor(): Vec4;

    RingSetDefaultColor(v: Vec4): Knob;
    RingGetDefaultColor(): Vec4;

    RingSetTickColor(v: Vec4): Knob;
    RingGetTickColor(): Vec4;

    RingSetVisual(v: IVisual): IVisual;
    RingGetVisual(): IVisual;

    OnChange(fn: (sender: Knob) => void): Knob;
    OnRotateBegin(fn: (sender: Knob) => void): Knob;
    OnRotateEnd(fn: (sender: Knob, bCanceled: boolean) => void): Knob;
}

export class Knob extends (AveLib.UiKnob as IKnob) {
    private m_RingVisual: IVisual;

    RingSetVisual(v: IVisual) {
        this.m_RingVisual = v;
        return super.RingSetVisual(v);
    }

    ValueGetRange(): Vec2 {
        return Vec2.FromNative(super.ValueGetRange());
    }

    RingGetColor(): Vec4 {
        return Vec4.FromNative(super.RingGetColor());
    }

    RingGetDefaultColor(): Vec4 {
        return Vec4.FromNative(super.RingGetDefaultColor());
    }

    RingGetTickColor(): Vec4 {
        return Vec4.FromNative(super.RingGetTickColor());
    }
}
