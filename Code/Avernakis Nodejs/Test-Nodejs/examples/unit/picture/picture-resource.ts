import { Window, Picture } from "../../../src";
import { getControlDemoContainer } from "../utility";
import { ResId } from "../ResId";
import { ResourceSource } from "../../../src/Ave/Io/IoCommon";

export function main(window: Window) {
	const picture = new Picture(window);
	const source = ResourceSource.FromResource(ResId.Icon_Clock_png);
	picture.SetPicture(source);

	const container = getControlDemoContainer(window, 1, 300, 300);
	container.ControlAdd(picture).SetGrid(1, 1);
	window.SetContent(container);
}
