import { Window, TextBox } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const container = getControlDemoContainer(window, 3);

	{
		// by default, IME(input method) is disabled
		const textBox = new TextBox(window);
		console.log(textBox.GetIme()); // expect false
		container.ControlAdd(textBox).SetGrid(1, 1);
	}

	{
		const textBox = new TextBox(window);
		textBox.SetIme(true);
		container.ControlAdd(textBox).SetGrid(3, 1);
	}

	window.SetContent(container);
}
