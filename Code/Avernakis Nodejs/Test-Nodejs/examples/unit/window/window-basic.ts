import { App, WindowCreation, WindowFlag, Window } from "../../../src";

export function run() {
	const app = new App();
	globalThis.app = app;

	const cpWindow = new WindowCreation();
	cpWindow.Title = "Window";
	cpWindow.Flag |= WindowFlag.Layered;

	const window = new Window(cpWindow);
	globalThis._window = window;

	window.OnCreateContent((sender) => {
		return true;
	});

	if (!window.CreateWindow()) process.exit(-1);

	window.SetVisible(true);
	window.Activate();
}
