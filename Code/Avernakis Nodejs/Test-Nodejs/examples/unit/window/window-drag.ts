import { WindowFramePart, App, WindowCreation, WindowFlag, Window, Grid, Vec4, DockMode } from "../../../src";

export function run() {
	const app = new App();
	globalThis.app = app;

	const cpWindow = new WindowCreation();
	cpWindow.Title = "Window";
	cpWindow.Flag |= WindowFlag.Layered;

	const window = new Window(cpWindow);
	globalThis._window = window;

	window.OnCreateContent((sender) => {
		sender.SetBackground(false);
		const frame = sender.GetFrame();
		frame.SetCaptionVisible(false);
		frame.OnNcHitTest((sender, pos, part) => {
			if (part == WindowFramePart.Client) return WindowFramePart.Caption;
			return part;
		});

		const grid = new Grid(sender);
		{
			const gridChild = new Grid(sender);
			grid.ControlAdd(gridChild).SetDock(DockMode.Fill);
			const color = new Vec4(100, 149, 237, 255);
			gridChild.SetBackColor(color);
			gridChild.SetOpacity(0.5);
		}
		window.SetContent(grid);
		return true;
	});

	if (!window.CreateWindow()) process.exit(-1);

	window.SetVisible(true);
	window.Activate();
}
