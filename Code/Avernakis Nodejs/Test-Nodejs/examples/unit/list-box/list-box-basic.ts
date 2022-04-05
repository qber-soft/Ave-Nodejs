import { Window, ListBox } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const listBox = new ListBox(window);
	listBox.Append("a");
	listBox.Append("b");
	listBox.Append("c");
	listBox.OnSelectionEnd((sender) => {
		console.log(sender.GetSelection());
	});

	const container = getControlDemoContainer(window, 1, 200, 300);
	container.ControlAdd(listBox).SetGrid(1, 1);
	window.SetContent(container);
}
