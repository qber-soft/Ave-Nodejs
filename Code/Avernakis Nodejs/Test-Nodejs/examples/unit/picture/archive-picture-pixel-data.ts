import { Window, Picture, Byo2Image, Byo2ImageCreation, Byo2ImageDataType, Rect, Button, ResourceSource, PixFormat } from "../../../src";
import { getControlDemoContainer } from "../utility";
import * as fs from "fs";
import * as path from "path";

export function main(window: Window) {
	const imgcp = new Byo2ImageCreation();
	imgcp.DataType = Byo2ImageDataType.Raw;
	imgcp.Width = 128;
	imgcp.Height = 128;
	imgcp.Format = PixFormat.R8G8B8A8_UNORM;
	const imgdata = new Uint8Array(imgcp.Width * imgcp.Height * 4);
	for (let y = 0; y < imgcp.Height; ++y) {
		for (let x = 0; x < imgcp.Width; ++x) {
			const i = (y * imgcp.Width + x) * 4;
			imgdata[i] = 255;
			imgdata[i + 1] = 0;
			imgdata[i + 2] = 0;
			imgdata[i + 3] = (255 * x) / imgcp.Width;
		}
	}
	imgcp.Data = ResourceSource.FromArrayBuffer(imgdata.buffer, imgcp.Width * 4, imgcp.Width * imgcp.Height * 4);
	//imgcp.Data = ResourceSource.Empty;

	const buffer = fs.readFileSync(path.resolve(__dirname, "./Clock#6.png"));
	const source = ResourceSource.FromBuffer(buffer);
	const picture1 = new Picture(window);
	picture1.SetPicture(source);

	const picture2 = new Picture(window);
	const img = new Byo2Image(window, imgcp);
	picture2.SetImage(img);

	const btn = new Button(window);
	btn.SetText("Change Pixels");
	btn.OnClick((sender) => {
		for (let y = 0; y < imgcp.Height; ++y) {
			for (let x = 0; x < imgcp.Width; ++x) {
				const i = (y * imgcp.Width + x) * 4;
				imgdata[i + 1] = (255 * y) / imgcp.Height;
			}
		}
		img.Upload(Rect.Empty, imgcp.Data.InMemory);
	});

	const container = getControlDemoContainer(window, 2, 300, 300);
	container.ControlAdd(picture1).SetGrid(1, 1);
	container.ControlAdd(picture2).SetGrid(1, 1);
	container.ControlAdd(btn).SetGrid(2, 1);
	window.SetContent(container);
}
