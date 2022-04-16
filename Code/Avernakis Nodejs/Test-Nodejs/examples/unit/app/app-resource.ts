import { App, WindowCreation, WindowFlag, Window, Button, VisualTextLayout, IconSource, ResourceSource } from "../../../src";
import { getControlDemoContainer } from "../utility";
import * as fs from "fs";
import * as path from "path";

export function run() {
	const app = new App();
	app.ResSetIconSizeList([16]);

	const openFileIcon = fs.readFileSync(path.resolve(__dirname, "./FileOpen#0.png"));
	app.ResAddResourceProvider((id) => {
		switch (id) {
			case 0x10:
				return ResourceSource.ToArrayBuffer(openFileIcon);
		}
	});

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
		const id = 0x10;
		const iconSource = new IconSource(id, 16);
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
