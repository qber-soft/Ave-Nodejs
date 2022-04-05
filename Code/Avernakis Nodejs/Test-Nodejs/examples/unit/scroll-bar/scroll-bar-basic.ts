import { Window, ScrollBar } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const scrollBar = new ScrollBar(window);
	scrollBar.SetMinimum(0).SetMaximum(100).SetValue(50).SetShrink(false);
	scrollBar.OnScrolling((sender: ScrollBar) => {
		console.log(sender.GetValue());
	});

	const container = getControlDemoContainer(window, 2, 120, 16);
	container.ControlAdd(scrollBar).SetGrid(1, 1, 2, 1);
	window.SetContent(container);
}
