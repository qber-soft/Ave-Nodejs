import { Window, Calendar } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const calendar = new Calendar(window);
	calendar.OnChange((sender) => {
		const timePoint = sender.GetDate();
		console.log(`Date: ${timePoint.Year}-${timePoint.Month}-${timePoint.Day}`);
	});

	const container = getControlDemoContainer(window, 1, 500, 500);
	container.ControlAdd(calendar).SetGrid(1, 1);
	window.SetContent(container);
}
