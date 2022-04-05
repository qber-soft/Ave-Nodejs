import { Window, Button, ButtonStyle } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const container = getControlDemoContainer(window, 3);

	{
		const button = new Button(window);
		button.SetText("Button");
		button.SetButtonStyle(ButtonStyle.Command);
		container.ControlAdd(button).SetGrid(1, 1);
	}

	{
		const button = new Button(window);
		button.SetText("Button");
		button.SetButtonStyle(ButtonStyle.Push);
		container.ControlAdd(button).SetGrid(3, 1);
	}

	window.SetContent(container);
}
