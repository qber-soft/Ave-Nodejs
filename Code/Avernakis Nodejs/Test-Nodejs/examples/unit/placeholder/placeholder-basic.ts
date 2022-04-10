import { Window, Placeholder, Vec4 } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const placeholder = new Placeholder(window);
	placeholder.OnPaintPost((sender, painter, rect) => {
		painter.SetPenColor(new Vec4(255, 0, 0, 255));
		painter.DrawRectangle(0, 0, rect.w, rect.h);
	});
	const container = getControlDemoContainer(window, 1, 500, 500);
	container.ControlAdd(placeholder).SetGrid(1, 1);
	window.SetContent(container);
}
