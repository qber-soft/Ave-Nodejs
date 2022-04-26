import { Window, Picture, ResourceSource, App, Byo2ImageCreation, Byo2ImageDataType, Byo2Image } from "../../../src";
import { getControlDemoContainer } from "../utility";
import * as fs from "fs";
import * as path from "path";

export function main(window: Window, { app }: { app: App }) {
	//
	const codec = app.GetImageCodec();
	const buffer = fs.readFileSync(path.resolve(__dirname, "./Paste#6.png"));
	const source = ResourceSource.FromBuffer(buffer);
	const aveImage = codec.Open(source);

	//
	const imgcp = new Byo2ImageCreation();
	imgcp.DataType = Byo2ImageDataType.Raw;

	const imgData = aveImage.GetImage(0, 0, 0);
	imgcp.Data = ResourceSource.FromArrayBuffer(imgData.Data, imgData.RowPitch, imgData.SlicePitch);
	imgcp.Width = imgData.Width;
	imgcp.Height = imgData.Height;
	imgcp.Format = imgData.Format;
	const byo2 = new Byo2Image(window, imgcp);

	//
	const picture = new Picture(window);
	picture.SetImage(byo2);

	const container = getControlDemoContainer(window, 1, 300, 300);
	container.ControlAdd(picture).SetGrid(1, 1);
	window.SetContent(container);
}
