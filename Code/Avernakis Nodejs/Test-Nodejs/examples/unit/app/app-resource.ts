import { App, WindowCreation, WindowFlag, Window, Button, VisualTextLayout, IconSource, ResourceSource } from "../../../src";
import { getControlDemoContainer } from "../utility";
import * as path from "path";

export function run() {
	const app = new App();

	const iconDataMap = {
		Open: [path.resolve(__dirname, "./FileOpen#0.png")],
	};
	const resMap = app.CreateResourceMap(app, [16], iconDataMap);

	globalThis.app = app;

	const cpWindow = new WindowCreation();
	cpWindow.Title = "Window";
	cpWindow.Flag |= WindowFlag.Layered;

	const window = new Window(cpWindow);
	globalThis._window = window;

	window.OnCreateContent((sender) => {
		const button = new Button(window);
		button.SetText("Open");
		button.SetVisualTextLayout(VisualTextLayout.HorzVisualText);
		const iconSource = new IconSource(resMap.Open, 16);
		const icon = window.CreateManagedIcon(iconSource);
		button.SetVisual(icon);

		const container = getControlDemoContainer(window);
		container.ControlAdd(button).SetGrid(1, 1);
		window.SetContent(container);
		return true;
	});

	if (!window.CreateWindow()) process.exit(-1);

	window.SetVisible(true);
	window.Activate();
}
