import { Window, CheckBox, Vec4 } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const checkBox = new CheckBox(window);
	checkBox.SetText("Apple");

	const lightBlue = new Vec4(0, 146, 255, 255 * 0.75);
	checkBox.SetTextColor(lightBlue);

	const container = getControlDemoContainer(window);
	container.ControlAdd(checkBox).SetGrid(1, 1);
	window.SetContent(container);
}
