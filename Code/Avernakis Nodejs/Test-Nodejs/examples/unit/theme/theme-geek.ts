import { Window, Button, ThemeFileImage, ResourceSource } from "../../../src";
import { getControlDemoContainer, IAppContext } from "../utility";
import * as fs from "fs";
import * as path from "path";

export function main(window: Window, appContext: IAppContext) {
	const button = new Button(window);
	button.SetText("Toggling Themes");

	let isDark = false;
	button.OnClick((sender) => {
		if (!isDark) {
			const themePath = path.resolve(__dirname, "./HyperEmerald.ave-theme-image");
			const themeBuffer = fs.readFileSync(themePath);
			const themeGeek = new ThemeFileImage();
			if (themeGeek.Open(ResourceSource.FromBuffer(themeBuffer))) {
				themeGeek.SetTheme(appContext.theme, 0);
			} else {
				console.log("open image file failed");
			}
		} else {
			appContext.theme.ResetTheme();
		}
		isDark = !isDark;
	});

	const container = getControlDemoContainer(window);
	container.ControlAdd(button).SetGrid(1, 1);
	window.SetContent(container);
}
