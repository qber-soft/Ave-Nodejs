import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { CheckValue } from "../UiCommon";
import { Window } from "./UiWindow";

export enum CheckBoxStyle {
    Checking,
    Pushing,
}

export interface ICheckBox extends IControl {
    new (window: Window, key?: string | number): ICheckBox;

    SetText(s: string): CheckBox;
    GetText(): string;

    SetValue(v: CheckValue): CheckBox;
    GetValue(): CheckValue;
    GetNextValue(): CheckValue;

    SetTriple(b: boolean): CheckBox;
    GetTriple(): boolean;

    SetCheckBoxStyle(n: CheckBoxStyle): CheckBox;
    GetCheckBoxStyle(): CheckBoxStyle;

    OnCheck(fn: (sender: CheckBox) => void): CheckBox;
    OnChecking(fn: (sender: CheckBox) => boolean): CheckBox;
}

export class CheckBox extends (AveLib.UiCheckBox as ICheckBox) {}
