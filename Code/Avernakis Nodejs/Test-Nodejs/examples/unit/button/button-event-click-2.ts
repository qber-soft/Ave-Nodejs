import { Window, Button } from "../../../src";
import { getControlDemoContainer } from "../utility";

// expect: only print "on click 2" once
export function main(window: Window) {
	const button = new Button(window);
	button.SetText("Button");

	button.OnClick((sender) => {
		console.log("on click 1");
	});

	button.OnClick((sender) => {
		console.log("on click 2");
	});

	const container = getControlDemoContainer(window);
	container.ControlAdd(button).SetGrid(1, 1);
	window.SetContent(container);
}
