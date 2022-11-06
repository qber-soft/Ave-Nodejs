import { TimePoint } from "../src";

describe("TimePoint", () => {
	test("from js date time", () => {
		const now = 1667709843452;
		const time = TimePoint.FromJsDateTime(now);

		const date = new Date(now); // Sun Nov 06 2022 12:44:03 GMT+0800 (China Standard Time)
		expect(time.Year).toEqual(date.getFullYear());
		expect(time.Month).toEqual(date.getMonth());
		expect(time.Day).toEqual(date.getDay());
	});
});
