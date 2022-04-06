import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";

export interface IRadioBox extends IControl {
	new (window: Window, key?: string | number): IRadioBox;

	SetText(s: string): RadioBox;
	GetText(): string;

	SetValue(s: boolean): RadioBox;
	GetValue(): boolean;

	SetGroup(s: number): RadioBox;
	GetGroup(): number;

	OnCheck(fn: (sender: RadioBox) => void): RadioBox;
	OnChecking(fn: (sender: RadioBox, bCanChangeValue: boolean) => boolean): RadioBox; // return bCanChangeValue to execute the default behavior, return false to reject the value change
}

export class RadioBox extends (AveLib.UiRadioBox as IRadioBox) {}
