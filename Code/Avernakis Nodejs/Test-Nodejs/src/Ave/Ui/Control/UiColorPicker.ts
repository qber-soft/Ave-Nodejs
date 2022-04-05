import { AveLib } from "../../AveLib";
import { Vec3 } from "../../Math/Vector";
import { IControl } from "../UiControl";
import { Window } from "./UiWindow";

export enum ColorPickerType {
    Cube,
    HsvWheel,
}

export enum ColorPickerCubePrimary {
    RgbR,
    RgbG,
    RgbB,
    HsvH,
    HsvS,
    HsvV,
}

export interface IColorPicker extends IControl {
    new (window: Window): IColorPicker;

    SetPickerType(nType: ColorPickerType): ColorPicker;
    GetPickerType(): ColorPickerType;

    SetCubePrimary(n: ColorPickerCubePrimary): ColorPicker;
    GetCubePrimary(): ColorPickerCubePrimary;

    SetColor(v: Vec3): ColorPicker;
    GetColor(): Vec3;

    OnChange(fn: (sender: ColorPicker) => void): ColorPicker;
}

export class ColorPicker extends (AveLib.UiColorPicker as IColorPicker) {
    GetColor(): Vec3 {
        return Vec3.FromNative(super.GetColor());
    }
}
