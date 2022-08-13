import { Window, Button, ThemePredefined_Dark } from "../../../src";
import { getControlDemoContainer, IAppContext } from "../utility";

export function main(window: Window, appContext: IAppContext) {
	const button = new Button(window);
	button.SetText("Toggling Themes");

	let isDark = false;
	button.OnClick((sender) => {
		if (!isDark) {
			const themeDark = new ThemePredefined_Dark();
			themeDark.SetStyle(appContext.theme, 0);
		} else {
			appContext.theme.ResetTheme();
		}
		isDark = !isDark;
	});

	const container = getControlDemoContainer(window);
	container.ControlAdd(button).SetGrid(1, 1);
	window.SetContent(container);
}
