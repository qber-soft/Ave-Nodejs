import { Window, Button, Vec4 } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const button = new Button(window);
	button.SetText("Button");
	button.OnClick(async (sender) => {
		const commonUi = window.GetCommonUi();
		const result = await commonUi.PickColor(new Vec4(255, 255, 255, 255), false);
		console.log(result);
		sender.SetTextColor(result);
	});

	const container = getControlDemoContainer(window);
	container.ControlAdd(button).SetGrid(1, 1);
	window.SetContent(container);
}
