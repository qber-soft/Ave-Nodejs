import { Window, Picture, Byo2Image, Byo2ImageCreation, Byo2ImageDataType, PixFormat, Rect, ResourceSource } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	// imgcp: image creation param
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
			imgdata[i + 3] = 255;
		}
	}
	imgcp.Data = ResourceSource.FromBuffer(Buffer.from(imgdata));

	const picture = new Picture(window);
	const img = new Byo2Image(window, imgcp);
	picture.SetImage(img);

	const container = getControlDemoContainer(window, 1, 128, 128);
	container.ControlAdd(picture).SetGrid(1, 1);
	window.SetContent(container);
}
