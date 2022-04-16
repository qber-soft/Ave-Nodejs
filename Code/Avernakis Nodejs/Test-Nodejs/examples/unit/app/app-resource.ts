import { App, WindowCreation, WindowFlag, Window, Button, VisualTextLayout, IconSource, ResourceSource } from "../../../src";
import { getControlDemoContainer } from "../utility";
import * as fs from "fs";
import * as path from "path";

export function run() {
	const app = new App();

	const iconDataMap = {
		Open: [path.resolve(__dirname, "./FileOpen#0.png")],
	};
	const resMap = createResourceMap(app, [16], iconDataMap);

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

function createResourceMap<IconDataMap extends Record<string, string[]>, Name extends string = keyof IconDataMap & string>(app: App, sizeList: number[], iconDataMap: IconDataMap): ResourceMap<Name> {
	const map: Record<string, number> = {};
	const provider: Record<number, string> = {};

	const subIdCount = sizeList.length;
	const baseId = subIdCount;

	if (sizeList.length < 1 || sizeList.length > 1024)
		throw new Error("Invalid sizeList length.");
	if (sizeList[0] <= 0)
		throw new Error("Invalid sizeList data.");
	for (let i = 1; i < sizeList.length; ++i)
		if (sizeList[i] <= sizeList[i - 1])
			throw new Error("Invalid sizeList data.");
			
	Object.keys(iconDataMap).forEach((name, iconIndex) => {
		const dataList = iconDataMap[name];
		if (sizeList.length != dataList.length)
			throw new Error("Length of each item in iconDataMap must equals to sizeList's.");
		const primaryId = baseId + iconIndex * subIdCount;
		map[name] = primaryId;
		dataList.forEach((filepath, dataIndex) => provider[primaryId + dataIndex] = filepath);
	});

	app.ResSetIconSizeList(sizeList);
	app.ResAddResourceProvider((id) => ResourceSource.ToArrayBuffer(fs.readFileSync(provider[id])));

	const resMap = new ResourceMap(map);
	return resMap;
}
