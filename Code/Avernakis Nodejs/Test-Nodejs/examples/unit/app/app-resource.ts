import { App, WindowCreation, WindowFlag, Window, Button, VisualTextLayout, IconSource, ResourceSource } from "../../../src";
import { getControlDemoContainer } from "../utility";
import * as fs from "fs";
import * as path from "path";

export function run() {
	const app = new App();

	app.ResSetIconSizeList([16]);
	const iconDataMap = {
		Open: [fs.readFileSync(path.resolve(__dirname, "./FileOpen#0.png"))],
	};
	const resMap = createResourceMap(app, iconDataMap);

	globalThis.app = app;

	const cpWindow = new WindowCreation();
	cpWindow.Title = "Window";
	cpWindow.Flag |= WindowFlag.Layered;

	const window = new Window(cpWindow);
	globalThis._window = window;

	window.OnCreateContent((sender) => {
		const button = new Button(window);
		button.SetText("Open");
		button.SetVisualTextLayout(VisualTextLayout.HorzVisualText);
		const iconSource = new IconSource(resMap.get("Open"), 16);
		const icon = window.CreateManagedIcon(iconSource);
		button.SetVisual(icon);

		const container = getControlDemoContainer(window);
		container.ControlAdd(button).SetGrid(1, 1);
		window.SetContent(container);
		return true;
	});

	if (!window.CreateWindow()) process.exit(-1);

	window.SetVisible(true);
	window.Activate();
}

class ResourceMap<Name extends string = string> {
	private map: Record<Name, number>;

	constructor(map: Record<Name, number>) {
		this.map = map;
	}

	get(name: Name): number {
		return this.map[name];
	}
}

function createResourceMap<IconDataMap extends Record<string, Buffer[]>, Name extends string = keyof IconDataMap & string>(app: App, iconDataMap: IconDataMap): ResourceMap<Name> {
	const map: Record<string, number> = {};
	const provider: Record<number, Buffer> = {};

	const baseId = 0x10;
	const deltaId = 0x10;

	Object.keys(iconDataMap).forEach((name, iconIndex) => {
		const dataList = iconDataMap[name];
		dataList.forEach((buffer, dataIndex) => {
			const id = baseId + iconIndex * deltaId + dataIndex;
			if (dataIndex === 0) {
				map[name] = id;
			}
			provider[id] = buffer;
		});
	});

	app.ResAddResourceProvider((id) => ResourceSource.ToArrayBuffer(provider[id]));

	const resMap = new ResourceMap(map);
	return resMap;
}
