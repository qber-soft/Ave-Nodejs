import { App, WindowCreation, WindowFlag, Window, Grid, ThemeImage, ThemePredefined_Dark, AppPath, CultureId } from "../../src";
import * as fs from "fs";
import { DefaultString } from "./DefaultString";

export interface IAppContext {
	theme: ThemeImage;
	app: App;
}

export function run(main: Function) {
	const app = new App();
	globalThis.app = app;

	// Config resources
	if (fs.existsSync(AppPath.AppPath + "_Debug\\AppRes.index")) {
		// debug mode
		app.ResAddPackageIndex(AppPath.AppPath + "_Debug\\AppRes.index", AppPath.AppPath + "_Debug\\AppRes");
	} else {
		// release mode
		app.ResAddPackage(AppPath.AppPath + "Data\\AppRes.bin");
	}

	// Config localized strings
	globalThis.app.LangSetFileRoot(AppPath.AppPath + "Language", "ini");
	globalThis.app.LangSetDefaultString(CultureId.en_us, DefaultString);

	//
	const cpWindow = new WindowCreation();
	cpWindow.Title = "Window";
	cpWindow.Flag |= WindowFlag.Layered;

	const theme = new ThemeImage();
	if (!theme) process.exit(-1);

	cpWindow.Theme = theme;
	globalThis.theme = theme;

	const window = new Window(cpWindow);
	globalThis._window = window;

	window.OnCreateContent((sender) => {
		main(window, { theme, app });
		return true;
	});

	if (!window.CreateWindow()) process.exit(-1);

	window.SetVisible(true);
	window.Activate();
}

export function getControlDemoContainer(window: Window, count = 1, width = 120, height = 32) {
	const container = new Grid(window);
	container.ColAddSlice(1);
	container.ColAddDpx(...Array.from<number>({ length: count }).fill(width));
	container.ColAddSlice(1);

	container.RowAddSlice(1);
	container.RowAddDpx(...Array.from<number>({ length: count }).fill(height));
	container.RowAddSlice(1);
	return container;
}
