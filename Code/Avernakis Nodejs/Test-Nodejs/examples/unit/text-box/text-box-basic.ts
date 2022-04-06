import { Window, TextBox } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const textBox = new TextBox(window);
	textBox.OnChange((sender, reason) => {
		console.log(reason);
		console.log(sender.GetText());
	});

	const container = getControlDemoContainer(window);
	container.ControlAdd(textBox).SetGrid(1, 1);
	window.SetContent(container);
}
