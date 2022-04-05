import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";

export enum ScrollOrientation {
	Auto,
	Horizontal,
	Vertical,
}

export interface IScrollBar extends IControl {
	new (window: Window): IScrollBar;

	SetOrientation(n: ScrollOrientation): ScrollBar;
	GetOrientation(): ScrollOrientation;
	GetOrientationActually(): ScrollOrientation;

	SetShrink(b: boolean): ScrollBar;
	GetShrink(): boolean;

	SetArrowVisible(b: boolean): ScrollBar;
	GetArrowVisible(): boolean;

	SetDynamicPage(b: boolean): ScrollBar;
	GetDynamicPage(): boolean;

	SetMinimumExtend(b: boolean): ScrollBar;
	GetMinimumExtend(): boolean;

	SetMaximumExtend(b: boolean): ScrollBar;
	GetMaximumExtend(): boolean;

	SetMinimum(n: number): ScrollBar;
	GetMinimum(): number;
	GetMinimumVirtual(): number;

	SetMaximum(n: number): ScrollBar;
	GetMaximum(): number;
	GetMaximumVirtual(): number;

	SetValue(n: number): ScrollBar;
	SetValueForce(n: number): ScrollBar;
	GetValue(): number;
	GetValueFinal(): number;
	GetValuePercent(): number; // [0, 1]
	GetValuePercentFinal(): number; // [0, 1]

	SetPage(n: number): ScrollBar;
	GetPage(): number;

	SetStep(n: number): ScrollBar;
	GetStep(): number;

	Scroll(): ScrollBar;

	OnScroll(fn: (sender: ScrollBar, bIsThumbScroll: boolean) => void): ScrollBar;
	OnScrolling(fn: (sender: ScrollBar) => void): ScrollBar;
	OnPageChange(fn: (sender: ScrollBar, fPagePercent: number) => void): ScrollBar;
}

export class ScrollBar extends (AveLib.UiScrollBar as IScrollBar) {
	GetMaximumValue() {
		return this.GetMaximumVirtual() + 1 - this.GetPage();
	}

	ScrollPrevious() {
		this.SetValue(this.GetValue() - 1);
		return this;
	}

	ScrollNext() {
		this.SetValue(this.GetValue() + 1);
		return this;
	}

	ScrollPreviousPage() {
		this.SetValue(this.GetValue() - this.GetPage());
		return this;
	}

	ScrollNextPage() {
		this.SetValue(this.GetValue() + this.GetPage());
		return this;
	}
}
