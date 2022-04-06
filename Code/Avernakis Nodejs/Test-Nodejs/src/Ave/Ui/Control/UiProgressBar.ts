import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";
import { ProgressBarState } from "../UiCommon";

export interface IProgressBar extends IControl {
	new (window: Window): IProgressBar;

	SetState(n: ProgressBarState): ProgressBar;
	GetState(): ProgressBarState;

	SetMaximum(n: number): ProgressBar;
	GetMaximum(): number;

	SetValue(n: number): ProgressBar;
	GetValue(): number;

	SetStep(n: number): ProgressBar;
	GetStep(): number;
	Step(): ProgressBar;

	SetAnimation(b: boolean): ProgressBar;
	GetAnimation(): boolean;
}

export class ProgressBar extends (AveLib.UiProgressBar as IProgressBar) {}
