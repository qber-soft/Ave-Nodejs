import { Window, Hyperlink } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const hyperLink = new Hyperlink(window);
	hyperLink.SetText(`<https://github.com/>`);
	hyperLink.OnClick((sender, id) => {
		console.log("hyper link clicked");
	});

	const container = getControlDemoContainer(window);
	container.ControlAdd(hyperLink).SetGrid(1, 1);
	window.SetContent(container);
}
