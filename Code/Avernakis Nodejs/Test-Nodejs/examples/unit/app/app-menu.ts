import { App, WindowCreation, WindowFlag, CultureId, Grid, Window, ToolBar, StringKey, ToolBarItem, ToolBarItemType, Menu, MenuItem, MenuType, Button, DpiSize } from "../../../src";
import * as path from "path";

interface ILang {
	// ave built-in language key
	AppTitle: string;

	// user defined key
	SwitchLang: string;

	[key: string]: string;
}

interface Ii18n {
	t(key: keyof ILang): string;
	switch(id: CultureId): void;
	lang: Partial<Record<CultureId, ILang>>;
}

export function run() {
	const app = new App();

	const iconDataMap = {
		WindowIcon: [path.resolve(__dirname, "./Ave#2.png")],
	};
	const resMap = app.CreateResourceMap(app, [16], iconDataMap);

	const i18n: Ii18n = {
		t(key: keyof ILang) {
			return app.LangGetString(key);
		},
		switch(this: Ii18n, id: CultureId) {
			app.LangSetDefaultString(id, this.lang[id]);
			app.LangSetCurrent(id);
		},
		lang: {
			[CultureId.en_us]: {
				AppTitle: "My App",
				SwitchLang: "Switch Lang",

				WdMainAppbar0: "FILE",
				WdMainAppbar1: "EDIT",
				WdMainAppbar2: "VIEW",
				WdMainAppbar3: "HELP",

				WdMainFile0: "New File",
				WdMainFile1: "Open File",
				WdMainFile2: "Save File",
				WdMainFile3: "Save File As",

				WdMainEdit0: "Undo",
				WdMainEdit1: "Redo",
				WdMainEdit2: "Cut",
				WdMainEdit3: "Copy",

				WdMainHelp0: "Help",
				WdMainHelp1: "About",
			},
			[CultureId.zh_cn]: {
				AppTitle: "我的应用",
				SwitchLang: "切换语言",

				WdMainAppbar0: "文件",
				WdMainAppbar1: "编辑",
				WdMainAppbar2: "视图",
				WdMainAppbar3: "帮助",

				WdMainFile0: "新建文件",
				WdMainFile1: "打开文件",
				WdMainFile2: "保存文件",
				WdMainFile3: "另存为",

				WdMainEdit0: "撤销",
				WdMainEdit1: "重做",
				WdMainEdit2: "剪切",
				WdMainEdit3: "复制",

				WdMainHelp0: "帮助",
				WdMainHelp1: "关于",
			},
		},
	};

	globalThis.app = app;

	const cpWindow = new WindowCreation();
	cpWindow.Flag |= WindowFlag.Layered;

	const window = new Window(cpWindow);
	globalThis._window = window;

	window.OnCreateContent((sender) => {
		//
		window.SetIcon(resMap.WindowIcon);

		//
		let lang = CultureId.en_us;
		i18n.switch(lang);

		const button = new Button(window);
		button.SetText(i18n.t("SwitchLang"));

		button.OnClick((sender) => {
			if (lang === CultureId.en_us) {
				lang = CultureId.zh_cn;
			} else if (lang === CultureId.zh_cn) {
				lang = CultureId.en_us;
			}
			i18n.switch(lang);
			button.SetText(i18n.t("SwitchLang"));
		});

		const container = getControlDemoContainer(window);
		container.ControlAdd(button).SetGrid(1, 1);

		const toolbarLeft = createToolbar(window);
		window.GetFrame().SetToolBarLeft(toolbarLeft);
		window.SetContent(container);
		return true;
	});

	if (!window.CreateWindow()) process.exit(-1);

	window.SetVisible(true);
	window.Activate();
}

function getControlDemoContainer(window: Window, count = 1, width = 120, height = 32) {
	const container = new Grid(window);
	container.ColAddSlice(1);
	container.ColAddDpx(...Array.from<number>({ length: count }).fill(width));
	container.ColAddSlice(1);

	container.RowAddSlice(1);
	container.RowAddDpx(...Array.from<number>({ length: count }).fill(height));
	container.RowAddSlice(1);
	return container;
}

function createToolbar(sender: Window) {
	const toolbar = new ToolBar(sender);
	toolbar.SetBackground(false);
	toolbar.ToolInsert(new ToolBarItem(1, ToolBarItemType.Menu, 0, DpiSize.FromPixelScaled(50), "File", "File Tooltip"), -1);

	const menuFile = new Menu(sender);
	menuFile.InsertItem(new MenuItem(1, MenuType.Text, 0, "", "", ""));
	// menuFile.InsertItem(new MenuItem(2, MenuType.Text, 0, "", "", ""));
	// menuFile.InsertItem(new MenuItem(3, MenuType.Text, 0, "", "", ""));
	// menuFile.InsertItem(new MenuItem(4, MenuType.Text, 0, "", "", ""));
	// toolbar.DropSetById(1, menuFile);

	//
	menuFile.OnClick((sender, nId) => {
		console.log(`click file menu, Id: ${nId}, Text: ${menuFile.GetById(nId).Text}`);
	});

	const menuEdit = new Menu(sender, new StringKey("WdMainEdit", 0, 7));
	menuEdit.InsertItem(new MenuItem(1, MenuType.Text, 0, "", "", ""));
	menuEdit.InsertItem(new MenuItem(2, MenuType.Text, 0, "", "", ""));
	menuEdit.InsertItem(new MenuItem(3, MenuType.Text, 0, "", "", ""));
	menuEdit.InsertItem(new MenuItem(4, MenuType.Text, 0, "", "", ""));
	// toolbar.DropSetById(2, menuEdit);

	const menuView = new Menu(sender);
	for (let i = 0; i < 16; ++i) menuView.InsertItem(new MenuItem(i + 1, MenuType.Text, 0, `View Item ${i}`));
	menuView.InsertItem(new MenuItem(0, MenuType.Separator));
	const menuViewSub = menuView.InsertSubMenu(new MenuItem(100, MenuType.Text, 0, "Sub Menu"));
	for (let i = 0; i < 16; ++i) menuViewSub.InsertItem(new MenuItem(200 + i, MenuType.Text, 0, `Sub Item ${i}`));
	toolbar.DropSetById(1, menuView);

	//
	menuView.OnClick((sender, nId) => {
		console.log(`click view menu, Id: ${nId}, Text: ${menuView.GetById(nId).Text}`);
	});

	// TODO: OnClick doesn't work
	menuViewSub.OnClick((sender, nId) => {
		console.log(`click sub view menu Id ${nId}`);
	});

	const menuHelp = new Menu(sender, new StringKey("WdMainHelp", 0, 2));
	menuHelp.InsertItem(new MenuItem(1, MenuType.Text, 0, "", "", ""));
	menuHelp.InsertItem(new MenuItem(2, MenuType.Text, 0, "", "", ""));
	// toolbar.DropSetById(4, menuHelp);
	return toolbar;
}
