// All date in comment is in M/d/yyyy format

export enum DayOfWeek {
	Sunday,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
}

export enum TimeDatePart {
	Year,
	DayOfYear,
	Month,
	Day,
}

// This class in C++: 1 Tick == 100 ns
// Because of number type in js is actually double (which contains 1 sign bit, 53 exponent bits and 10 mantissa bits), the max safe integer is (1<<53)-1
// 9007199254740991 (max safe int) / 315569520000 (seconds of 10000 years) is 28542.678
// The maximum tick for 1 second is 28542.
// So here 1 Tick == 0.1 ms == 0.0001 second == 100000 ns
export class TimePoint {
	Tick: number = 0;

	static get TickPerMillisecond() {
		return 10;
	}
	static get TickPerSecond() {
		return 10000;
	}
	static get TickPerMinute() {
		return TimePoint.TickPerSecond * 60;
	}
	static get TickPerHour() {
		return TimePoint.TickPerMinute * 60;
	}
	static get TickPerDay() {
		return TimePoint.TickPerHour * 24;
	}
	static get TickPerWeek() {
		return TimePoint.TickPerDay * 7;
	}

	static get MsPerSecond() {
		return 1000;
	}
	static get MsPerMinute() {
		return TimePoint.MsPerSecond * 60;
	}
	static get MsPerHour() {
		return TimePoint.MsPerMinute * 60;
	}
	static get MsPerDay() {
		return TimePoint.MsPerHour * 24;
	}

	static get DayPerYear() {
		return 365;
	} // non-leap year
	static get DayPer4Year() {
		return TimePoint.DayPerYear * 4 + 1;
	}
	static get DayPer100Year() {
		return TimePoint.DayPer4Year * 25 - 1;
	}
	static get DayPer400Year() {
		return TimePoint.DayPer100Year * 4 + 1;
	}

	static get DayTo1601() {
		return TimePoint.DayPer400Year * 4;
	} // days from 1/1/0001 to 12/31/1600
	static get DayTo1899_30() {
		return TimePoint.DayPer400Year * 4 + TimePoint.DayPer100Year * 3 - 367;
	} // days from 1/1/0001 to 12/30/1899
	static get DayTo10000() {
		return TimePoint.DayPer400Year * 25 - 366;
	} // days from 1/1/0001 to 12/31/9999

	static get TickMin() {
		return 0;
	}
	static get TickMax() {
		return TimePoint.DayTo10000 * TimePoint.TickPerDay - 1;
	}

	static get FileTimeOffset() {
		return TimePoint.DayTo1601 * TimePoint.TickPerDay;
	}
	static get OATimeOffset() {
		return TimePoint.DayTo1899_30 * TimePoint.TickPerDay;
	}
	static get OAMinTick() {
		return (TimePoint.DayPer100Year - TimePoint.DayPerYear) * TimePoint.TickPerDay;
	} // 1/1/0100

	static get Day365() {
		return [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
	}
	static get Day366() {
		return [0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
	}
	static get DayTotal365() {
		return [0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365];
	}
	static get DayTotal366() {
		return [0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366];
	}

	static IsLeapYear(nYear: number) {
		return (!(3 & nYear) && 0 != nYear % 100) || 0 == nYear % 400;
	}

	static Day(nYear: number) {
		return TimePoint.IsLeapYear(nYear) ? TimePoint.Day366 : TimePoint.Day365;
	}
	static DayTotal(nYear: number) {
		return TimePoint.IsLeapYear(nYear) ? TimePoint.DayTotal366 : TimePoint.DayTotal365;
	}

	// nMonth in [0, 12)
	static DayInMonth0(nYear: number, nMonth: number) {
		return TimePoint.Day(nYear)[nMonth + 1];
	}

	// nMonth in [1, 12]
	static DayInMonth1(nYear: number, nMonth: number) {
		return TimePoint.Day(nYear)[nMonth];
	}

	// Only valid after 10/15/1582, other dates use DayOfWeek property
	static CalculateWeek(nYear: number, nMonth: number, nDay: number): DayOfWeek {
		if (nMonth < 3) {
			nMonth += 12;
			--nYear;
		}
		return (nDay + 1 + 2 * nMonth + (3 * (nMonth + 1)) / 5 + nYear + (nYear >> 2) - nYear / 100 + nYear / 400) % 7;
	}

	static FromTick(n: number) {
		const ret = new TimePoint();
		ret.Tick = n;
		return ret;
	}

	static FromFileTime(n: number) {
		const ret = new TimePoint();
		ret.FileTime = n;
		return ret;
	}

	static FromOATime(n: number) {
		const ret = new TimePoint();
		ret.OATime = n;
		return ret;
	}

	constructor(nYear?: number, nMonth: number = 1, nDay: number = 1, nHour: number = 0, nMinute: number = 0, nSecond: number = 0, nMillisecond: number = 0) {
		if (nYear) this.Set(nYear, nMonth, nDay, nHour, nMinute, nSecond, nMillisecond);
	}

	Set(nYear: number, nMonth: number = 1, nDay: number = 1, nHour: number = 0, nMinute: number = 0, nSecond: number = 0, nMillisecond: number = 0) {
		if (nYear >= 1 && nYear <= 9999 && nMonth >= 1 && nMonth <= 12 && nDay >= 1 && nDay <= TimePoint.DayInMonth1(nYear, nMonth)) {
			const y = nYear - 1;
			this.Tick = (y * 365 + Math.floor(y / 4) - Math.floor(y / 100) + Math.floor(y / 400) + TimePoint.DayTotal(nYear)[nMonth - 1] + nDay - 1) * TimePoint.TickPerDay + nHour * TimePoint.TickPerHour + nMinute * TimePoint.TickPerMinute + nSecond * TimePoint.TickPerSecond + nMillisecond * TimePoint.TickPerMillisecond;
		}
		return this;
	}

	GetDatePart(nPart: TimeDatePart) {
		let d = Math.floor(this.Tick / TimePoint.TickPerDay);
		let y400 = Math.floor(d / TimePoint.DayPer400Year);
		d -= y400 * TimePoint.DayPer400Year;
		let y100 = Math.floor(d / TimePoint.DayPer100Year);
		if (4 == y100) y100 = 3;
		d -= y100 * TimePoint.DayPer100Year;
		let y4 = Math.floor(d / TimePoint.DayPer4Year);
		d -= y4 * TimePoint.DayPer4Year;
		let y1 = Math.floor(d / TimePoint.DayPerYear);
		if (4 == y1) y1 = 3;
		if (TimeDatePart.Year == nPart) return y400 * 400 + y100 * 100 + y4 * 4 + y1 + 1;

		d -= y1 * TimePoint.DayPerYear;
		if (TimeDatePart.DayOfYear == nPart) return d + 1;

		const bLeap = 3 == y1 && (24 != y4 || 3 == y100);
		const days = bLeap ? TimePoint.DayTotal366 : TimePoint.DayTotal365;
		let m = (d >> 5) + 1;
		for (; d >= days[m]; ++m);
		if (TimeDatePart.Month == nPart) return m;

		return d - days[m - 1] + 1;
	}

	AddTick(n: number) {
		const nNew = Math.floor(this.Tick + n);
		if (nNew >= TimePoint.TickMin && nNew <= TimePoint.TickMax) this.Tick = nNew;
		return this;
	}

	AddWeek(f: number) {
		return this.AddTick(f * TimePoint.TickPerWeek);
	}
	AddDay(f: number) {
		return this.AddTick(f * TimePoint.TickPerDay);
	}
	AddHour(f: number) {
		return this.AddTick(f * TimePoint.TickPerHour);
	}
	AddMinute(f: number) {
		return this.AddTick(f * TimePoint.TickPerMinute);
	}
	AddSecond(f: number) {
		return this.AddTick(f * TimePoint.TickPerSecond);
	}
	AddMillisecond(f: number) {
		return this.AddTick(f * TimePoint.TickPerMillisecond);
	}

	AddMonth(n: number) {
		n = Math.floor(n);
		let t = this.Tick;
		let y = this.Year;
		let m = this.Month;
		let d = this.Day;
		let i = m - 1 + n;
		if (i >= 0) {
			m = (i % 12) + 1;
			y = y + i / 12;
		} else {
			m = 12 + ((i + 1) % 12);
			y = y + (i - 11) / 12;
		}
		if (y < 1 || y > 9999) return this;
		let nDays = TimePoint.DayInMonth1(y, m);
		if (d > nDays) d = nDays;
		this.Set(y, m, d);
		this.Tick += t % TimePoint.TickPerDay;
		return this;
	}
	AddYear(n: number) {
		return this.AddMonth(Math.floor(n) * 12);
	}

	get Year() {
		return this.GetDatePart(TimeDatePart.Year);
	}
	get Month() {
		return this.GetDatePart(TimeDatePart.Month);
	}
	get Day() {
		return this.GetDatePart(TimeDatePart.Day);
	}
	get DayOfYear() {
		return this.GetDatePart(TimeDatePart.DayOfYear);
	}
	get DayOfWeek(): DayOfWeek {
		return (this.Tick / TimePoint.TickPerDay + 1) % 7;
	}
	get Hour() {
		return (this.Tick / TimePoint.TickPerHour) % 24;
	}
	get Minute() {
		return (this.Tick / TimePoint.TickPerMinute) % 60;
	}
	get Second() {
		return (this.Tick / TimePoint.TickPerSecond) % 60;
	}
	get Millisecond() {
		return (this.Tick / TimePoint.TickPerMillisecond) % 1000;
	}

	// Window FILETIME/U64
	set FileTime(nTime: number) {
		this.Tick = nTime + TimePoint.FileTimeOffset;
	}
	get FileTime() {
		if (this.Tick >= TimePoint.FileTimeOffset) return this.Tick - TimePoint.FileTimeOffset;
		else return 0;
	}

	// Window OLE Automation Time/R64
	set OATime(f: number) {
		if (f < -657435 || f > 2958466) return;
		let nMs = Math.floor(f * TimePoint.MsPerDay + (f >= 0 ? 0.5 : -0.5));
		if (nMs < 0) nMs -= (nMs % TimePoint.MsPerDay) * 2;
		nMs += TimePoint.OATimeOffset / TimePoint.TickPerMillisecond;
		this.Tick = nMs * TimePoint.TickPerMillisecond;
	}
	get OATime() {
		let t = this.Tick + 0.0;
		if (0 == t) return 0;
		if (t < TimePoint.TickPerDay) t += TimePoint.DayTo1899_30;
		if (t < TimePoint.OAMinTick) return 0;
		let nMs = (t - TimePoint.OATimeOffset) / TimePoint.TickPerMillisecond;
		if (nMs < 0) {
			let nFrac = nMs % TimePoint.MsPerDay;
			if (0 != nFrac) nMs -= nFrac + TimePoint.MsPerDay;
		}
		return nMs / TimePoint.MsPerDay;
	}
}
