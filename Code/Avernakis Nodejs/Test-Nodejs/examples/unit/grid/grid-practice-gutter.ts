import { Window, Grid, Vec4, DpiMargin, DpiSize } from "../../../src";

const Color = {
	White: new Vec4(255, 255, 255, 255),
	DarkBlue: new Vec4(0, 146, 255, 255),
	LightBlue: new Vec4(0, 146, 255, 255 * 0.75),
};

function createGrid(color: Vec4, window: Window) {
	return new Grid(window).SetBackColor(color);
}

export function main(window: Window) {
	const grid = new Grid(window);

	// 添加24列
	grid.ColAddSlice(...Array.from<number>({ length: 24 }).fill(1));

	// 添加3行，中间固定高度的用来画例子
	grid.RowAddSlice(1);
	grid.RowAddDpx(50);
	grid.RowAddSlice(1);

	const gutter = 50; // dpx
	const margin = new DpiMargin(DpiSize.FromPixelScaled(gutter / 2), DpiSize.FromPixelScaled(0), DpiSize.FromPixelScaled(gutter / 2), DpiSize.FromPixelScaled(0));

	grid.ControlAdd(createGrid(Color.LightBlue, window)).SetGrid(0, 1, 6, 1).SetMargin(margin);
	grid.ControlAdd(createGrid(Color.DarkBlue, window)).SetGrid(6, 1, 6, 1).SetMargin(margin);
	grid.ControlAdd(createGrid(Color.LightBlue, window)).SetGrid(12, 1, 6, 1).SetMargin(margin);
	grid.ControlAdd(createGrid(Color.DarkBlue, window)).SetGrid(18, 1, 6, 1).SetMargin(margin);

	window.SetContent(grid);
}
