import { Window, Grid, Vec4 } from "../../../src";

export function main(window: Window) {
	const container = new Grid(window);
	container.ColAddSlice(1, 1, 1, 1, 1);
	container.RowAddSlice(1, 1, 1, 1, 1);

	const gridA = new Grid(window);
	const aColor = new Vec4(0, 146, 255, 255 * 0.25);
	gridA.SetBackColor(aColor);
	container.ControlAdd(gridA).SetGrid(1, 1, 1, 1);

	const gridB = new Grid(window);
	const bColor = new Vec4(0, 146, 255, 255);
	gridB.SetBackColor(bColor);
	gridB.SetOpacity(0.25);
	container.ControlAdd(gridB).SetGrid(3, 1, 1, 1);

	window.SetContent(container);
}
