import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { WindowLike } from "./UiWindow";
import { TimePoint } from "../../TimePoint";
import { CultureId, CultureInfoDateTime } from "../../Culture";

export interface IDatePicker extends IControl {
	new (window: WindowLike): IDatePicker;

	SetRange(tpFrom: TimePoint, tpTo: TimePoint): DatePicker;
	GetRange(): TimePoint[];

	SetDate(n: TimePoint): DatePicker;
	GetDate(): TimePoint;

	SetDateMark(c: TimePoint): DatePicker;
	GetDateMark(): TimePoint;

	SetCultureId(n: CultureId): DatePicker;
	GetCultureId(): CultureId;

	SetFormat(n: CultureInfoDateTime): DatePicker;
	GetFormat(): CultureInfoDateTime;

	SetBorder(b: boolean): DatePicker;
	GetBorder(): boolean;

	Drop(): DatePicker;

	OnChange(fn: (sender: DatePicker) => void): DatePicker;
}

export class DatePicker extends (AveLib.UiDatePicker as IDatePicker) {
	GetDate() {
		return TimePoint.FromTick(super.GetDate().Tick);
	}

	GetDateMark() {
		return TimePoint.FromTick(super.GetDateMark().Tick);
	}
}
