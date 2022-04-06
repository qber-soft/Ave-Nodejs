import { Window, Grid, Vec4, DpiSize, DpiSize_2 } from "../../../src";

export function main(window: Window) {
	const container = new Grid(window);
	container.ColAddSlice(1, 1, 1);
	container.RowAddSlice(1, 1, 1);

	const center = new Grid(window);
	const lightBlue = new Vec4(0, 146, 255, 255 * 0.75);
	center.SetBackColor(lightBlue);

	const gridControl = container.ControlAdd(center);
	const pos = {
		x: DpiSize.FromPixelScaled(100),
		y: DpiSize.FromPixelScaled(50),
	};
	gridControl.SetPos(pos.x, pos.y);
	const size = new DpiSize_2(DpiSize.FromPixelScaled(200), DpiSize.FromPixelScaled(100));
	gridControl.SetSize(size);
	window.SetContent(container);
}
