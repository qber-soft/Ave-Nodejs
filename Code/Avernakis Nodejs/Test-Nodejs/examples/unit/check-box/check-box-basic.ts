import { Window, CheckBox, CheckValue } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const checkBox = new CheckBox(window);
	checkBox.SetText("Apple");
	checkBox.OnCheck((sender: CheckBox) => {
		const checkValue = sender.GetValue();
		console.log(`check value: ${checkValue}(${CheckValue[checkValue]})`);
	});

	const container = getControlDemoContainer(window);
	container.ControlAdd(checkBox).SetGrid(1, 1);
	window.SetContent(container);
}
