import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";

export enum TrackBarOrientation {
    Auto,
    Horizontal,
    Vertical,
}

export interface ITrackBar extends IControl {
    new (window: Window, key?: string | number): ITrackBar;

    SetOrientation(nOrient: TrackBarOrientation): TrackBar;
    GetOrientation(): TrackBarOrientation;
    GetOrientationActually(): TrackBarOrientation;

    SetMinimum(nValue: number): TrackBar;
    GetMinimum(): number;

    SetMaximum(nValue: number): TrackBar;
    GetMaximum(): number;

    SetValue(nValue: number): TrackBar;
    SetValueForce(nValue: number): TrackBar;
    GetValue(): number;

    SetPage(nValue: number): TrackBar;
    GetPage(): number;

    OnThumbChange(fn: (sender: TrackBar) => void): TrackBar;
    OnThumbRelease(fn: (sender: TrackBar) => void): TrackBar;
    OnPageChange(fn: (sender: TrackBar) => void): TrackBar;
}

export class TrackBar extends (AveLib.UiTrackBar as ITrackBar) {}
