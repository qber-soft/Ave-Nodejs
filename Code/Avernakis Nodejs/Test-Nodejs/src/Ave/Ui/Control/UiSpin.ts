import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";

export interface ISpin extends IControl {
	new (window: Window): ISpin;

	OnClick(fn: (sender: Spin, nDelta: number) => void): Spin;
	OnSpinStart(fn: (sender: Spin) => void): Spin;
	OnSpinEnd(fn: (sender: Spin, bCanceled: boolean) => void): Spin;
	OnSpin(fn: (sender: Spin, nDelta: number) => void): Spin;
}

export class Spin extends (AveLib.UiSpin as ISpin) {}
