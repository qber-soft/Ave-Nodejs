import { Window, Grid, Vec4 } from "../../../src";

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

	// 中间固定高度的用来画例子
	// 50dpx: 画例子
	// 25dpx：间隙
	grid.RowAddSlice(1);
	grid.RowAddDpx(50, 25, 50, 25, 50);
	grid.RowAddSlice(1);

	{
		const span = 8;
		const offset1 = 0;
		const offset2 = offset1 + span + 8;
		grid.ControlAdd(createGrid(Color.DarkBlue, window)).SetGrid(offset1, 1, span, 1);
		grid.ControlAdd(createGrid(Color.DarkBlue, window)).SetGrid(offset2, 1, span, 1);
	}

	{
		const span = 6;
		const offset1 = 6;
		const offset2 = offset1 + span + 6;
		grid.ControlAdd(createGrid(Color.DarkBlue, window)).SetGrid(offset1, 3, span, 1);
		grid.ControlAdd(createGrid(Color.DarkBlue, window)).SetGrid(offset2, 3, span, 1);
	}

	{
		const span = 12;
		const offset = 6;
		grid.ControlAdd(createGrid(Color.DarkBlue, window)).SetGrid(offset, 5, span, 1);
	}

	window.SetContent(grid);
}
