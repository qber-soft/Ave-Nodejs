import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { WindowLike } from "./UiWindow";
import { TimePoint } from "../../TimePoint";
import { CultureId, CultureInfoDateTime } from "../../Culture";

export enum CalendarRangeLevel {
	Month,
	Year,
	Decade,
	Century,
	Millenary,
}

export interface ICalendar extends IControl {
	new (window: WindowLike): ICalendar;

	SetRange(tpFrom: TimePoint, tpTo: TimePoint): Calendar;
	GetRange(): TimePoint[];

	SetRangeLevel(n: CalendarRangeLevel): Calendar;
	GetRangeLevel(): CalendarRangeLevel;

	SetDate(n: TimePoint): Calendar;
	GetDate(): TimePoint;

	SetDateMark(c: TimePoint): Calendar;
	GetDateMark(): TimePoint;

	SetCultureId(n: CultureId): Calendar;
	GetCultureId(): CultureId;

	SetFormat(n: CultureInfoDateTime): Calendar;
	GetFormat(): CultureInfoDateTime;

	OnChange(fn: (sender: Calendar) => void): Calendar;
}

export class Calendar extends (AveLib.UiCalendar as ICalendar) {
	GetDate() {
		return TimePoint.FromTick(super.GetDate().Tick);
	}

	GetDateMark() {
		return TimePoint.FromTick(super.GetDateMark().Tick);
	}
}
