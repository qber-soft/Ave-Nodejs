import { Window, Button, AveGetClipboard } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const clipboard = AveGetClipboard();

	const button = new Button(window);
	button.SetText("Inspect Clipboard");
	button.OnClick((sender) => {
		if (clipboard.HasImage()) {
			const aveImage = clipboard.GetImage();
			const imageData = aveImage.GetImage(0, 0, 0);
			console.log(`image found! width: ${imageData.Width} height: ${imageData.Height}`);
		} else if (clipboard.HasFile()) {
			const [file] = clipboard.GetFile();
			console.log(`file found! path: ${file}`);
		} else {
			console.log(`nothing found in clipboard`);
		}
	});

	const container = getControlDemoContainer(window);
	container.ControlAdd(button).SetGrid(1, 1);
	window.SetContent(container);
}
