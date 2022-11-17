import { Window, Picture, ResourceSource, App, Byo2ImageCreation, Byo2ImageDataType, Byo2Image, ImageContainerType } from "../../../src";
import { getControlDemoContainer } from "../utility";
import * as fs from "fs";
import * as path from "path";

export function main(window: Window, { app }: { app: App }) {
	//
	const codec = app.GetImageCodec();
	const buffer = fs.readFileSync(path.resolve(__dirname, "./Paste#6.png"));
	const source = ResourceSource.FromBuffer(buffer);
	const aveImage = codec.Open(source);

	const picture = new Picture(window);
	{
		const arrayBuffer = codec.SaveArrayBuffer(aveImage, ImageContainerType.PNG);
		const source = ResourceSource.FromBuffer(Buffer.from(arrayBuffer));
		picture.SetPicture(source);
	}

	const container = getControlDemoContainer(window, 1, 300, 300);
	container.ControlAdd(picture).SetGrid(1, 1);
	window.SetContent(container);
}
