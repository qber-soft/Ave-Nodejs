import { TimePoint } from "../src";

describe("TimePoint", () => {
	test("from js date time", () => {
		const now = 1667709843452; // Sun Nov 06 2022 12:44:03 GMT+0800 (China Standard Time)
		const time = TimePoint.FromJsDateTime(now);

		expect(time.Year).toEqual(2022);
		expect(time.Month).toEqual(11);
		expect(time.Day).toEqual(6);
	});
});
