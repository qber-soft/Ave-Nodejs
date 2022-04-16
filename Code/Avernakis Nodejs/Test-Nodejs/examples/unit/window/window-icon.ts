import { App, WindowCreation, WindowFlag, Window } from "../../../src";
import * as path from "path";

export function run() {
	const app = new App();
	globalThis.app = app;

	const iconDataMap = {
		WindowIcon: [path.resolve(__dirname, "./assets/Ave#0.png"), path.resolve(__dirname, "./assets/Ave#1.png"), path.resolve(__dirname, "./assets/Ave#2.png")],
	};
	const resMap = app.CreateResourceMap(app, [16, 24, 32], iconDataMap);

	const cpWindow = new WindowCreation();
	cpWindow.Title = "Avernakis";
	cpWindow.Flag |= WindowFlag.Layered;

	const window = new Window(cpWindow);
	globalThis._window = window;

	window.OnCreateContent((window) => {
		window.SetIcon(resMap.WindowIcon);
		return true;
	});

	if (!window.CreateWindow()) process.exit(-1);

	window.SetVisible(true);
	window.Activate();
}
