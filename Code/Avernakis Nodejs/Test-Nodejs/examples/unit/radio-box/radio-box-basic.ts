import { Window, RadioBox } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const radioBoxA = new RadioBox(window);
	radioBoxA.SetText("Option A");

	const radioBoxB = new RadioBox(window);
	radioBoxB.SetText("Option B");

	const handleCheck: Parameters<typeof RadioBox.OnCheck>[0] = (sender) => {
		console.log(`${sender.GetText()} onCheck`);
	};
	radioBoxA.OnCheck(handleCheck);
	radioBoxB.OnCheck(handleCheck);

	const container = getControlDemoContainer(window, 2);
	container.ControlAdd(radioBoxA).SetGrid(1, 1);
	container.ControlAdd(radioBoxB).SetGrid(2, 1);
	window.SetContent(container);
}
