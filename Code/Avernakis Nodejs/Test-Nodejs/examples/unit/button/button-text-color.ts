import { Window, Button, Vec4 } from "../../../src/Ave/Ave";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const button = new Button(window);
	button.SetText("Button");

	const lightBlue = new Vec4(0, 146, 255, 255 * 0.75);
	button.SetTextColor(lightBlue);

	const container = getControlDemoContainer(window);
	container.ControlAdd(button).SetGrid(1, 1);
	window.SetContent(container);
}
