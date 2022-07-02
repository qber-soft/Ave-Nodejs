import { Window, Button, ThemeFileImage, ResourceSource } from "../../../src";
import { getControlDemoContainer, IThemeManager } from "../utility";
import * as fs from "fs";
import * as path from "path";

export function main(window: Window, themeManager: IThemeManager) {
	const button = new Button(window);
	button.SetText("Toggling Themes");

	let isDark = false;
	button.OnClick((sender) => {
		if (!isDark) {
			const themePath = path.resolve(__dirname, "./HyperEmerald.ave-theme-image");
			const themeBuffer = fs.readFileSync(themePath);
			const themeGeek = new ThemeFileImage();
			if (themeGeek.Open(ResourceSource.FromBuffer(themeBuffer))) {
				themeGeek.SetTheme(themeManager.theme, 0);
			} else {
				console.log("open image file failed");
			}
		} else {
			themeManager.theme.ResetTheme();
		}
		isDark = !isDark;
	});

	const container = getControlDemoContainer(window);
	container.ControlAdd(button).SetGrid(1, 1);
	window.SetContent(container);
}
