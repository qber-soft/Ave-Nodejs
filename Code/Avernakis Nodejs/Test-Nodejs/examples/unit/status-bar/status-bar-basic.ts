import { Window, StatusBar, DpiSize, Grid } from "../../../src";

export function main(window: Window) {
	const statusBar = new StatusBar(window);

	// 状态栏分为3部分：100、100、其余
	statusBar.SetPart([DpiSize.FromPixelScaled(100), DpiSize.FromPixelScaled(100), DpiSize.FromSlice(1)]);

	statusBar.SetText(0, "feature/status-bar").SetClickable(0, true);

	statusBar.SetText(1, "Git Graph").SetClickable(1, true);

	//
	statusBar.OnClick((sender, index) => {
		console.log(`index: ${index}`);
	});

	//
	const container = getControlDemoContainer(window);
	container.ControlAdd(statusBar).SetGrid(0, 1);
	window.SetContent(container);
}

export function getControlDemoContainer(window: Window) {
	const container = new Grid(window);
	container.ColAddSlice(1);

	container.RowAddSlice(1);
	container.RowAddDpx(32);
	return container;
}
