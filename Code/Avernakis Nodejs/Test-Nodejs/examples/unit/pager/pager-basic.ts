import { Window, Picture, ResourceSource, Pager, AlignType } from "../../../src";
import { getControlDemoContainer } from "../utility";
import * as fs from "fs";
import * as path from "path";

export function main(window: Window) {
	const pager = new Pager(window);
	pager.SetContentHorizontalAlign(AlignType.Center);
	pager.SetContentVerticalAlign(AlignType.Center);

	const picture = new Picture(window);
	const buffer = fs.readFileSync(path.resolve(__dirname, "./wallpaper.png"));
	const source = ResourceSource.FromBuffer(buffer);
	picture.SetPicture(source);
	pager.SetContent(picture);

	const container = getControlDemoContainer(window, 1, 300, 300);
	container.ControlAdd(pager).SetGrid(1, 1);
	window.SetContent(container);
}
