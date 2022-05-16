import { App, WindowCreation, WindowFlag, Window, CultureId, Button, Grid } from "../../../src";

interface ILang {
	// ave built-in language key
	AppTitle: string;

	// user defined key
	SwitchLang: string;
}

interface Ii18n {
	t(key: keyof ILang): string;
	switch(id: CultureId): void;
	lang: Partial<Record<CultureId, ILang>>;
}

export function run() {
	const app = new App();

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
			},
			[CultureId.zh_cn]: {
				AppTitle: "我的应用",
				SwitchLang: "切换语言",
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
		let lang = CultureId.en_us;
		i18n.switch(lang);

		//
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
