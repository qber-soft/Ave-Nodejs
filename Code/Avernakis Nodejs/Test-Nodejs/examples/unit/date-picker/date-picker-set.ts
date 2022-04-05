import { Window, DatePicker } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const datePicker = new DatePicker(window);
	datePicker.OnChange((sender) => {
		const timePoint = sender.GetDate();
		console.log(`Date: ${timePoint.Year}-${timePoint.Month}-${timePoint.Day}`);
		datePicker.SetDate(timePoint);
		datePicker.SetDateMark(timePoint);
	});

	const container = getControlDemoContainer(window);
	container.ControlAdd(datePicker).SetGrid(1, 1);
	window.SetContent(container);
}
