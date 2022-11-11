﻿//const log = require('why-is-node-running') // should be your first require

//import { run } from "./Examples/window";
//run();

import * as fs from "fs";
import * as path from "path";

import { App, CultureId, AppPath, ResourceSource } from "../../src";
import { DefaultString } from "./DefaultString";

import { WindowMain } from "./UI/WindowMain";

// Use portable mode
AppPath.InitializeSavePath(true);

class MyApp {
	private m_App: App;
	private m_Window: WindowMain;

	Run() {
		this.m_App = new App();

		// All path passes to Ave must use backslash(\) to split folders on all platforms (including macOS, linux and all other systems!!) For example: \usr\local\bin\....

		// Config resources
		if (fs.existsSync(AppPath.AppPath + "_Debug\\AppRes.index")) {
			// debug mode
			this.m_App.ResAddPackageIndex(AppPath.AppPath + "_Debug\\AppRes.index", AppPath.AppPath + "_Debug\\AppRes");
		} else if (fs.existsSync(AppPath.AppPath + "Data\\AppRes.bin")) {
			// release mode
			this.m_App.ResAddPackage(AppPath.AppPath + "Data\\AppRes.bin");
		} else {
			// pack
			const exePath = process.cwd();
			this.m_App.ResAddPackage(exePath + "\\Data\\AppRes.bin");

			// const data = fs.readFileSync(path.resolve(__dirname, "/Data/AppRes.bin"));
			// const source = ResourceSource.FromBuffer(data);
			// this.m_App.ResAddPackageData(source.InMemory.Data);
		}

		this.m_App.ResSetIconSizeList([16, 24, 32, 48, 64, 96, 128]);

		// Config localized strings
		this.m_App.LangSetFileRoot(AppPath.AppPath + "Language", "ini");
		this.m_App.LangSetDefaultString(CultureId.en_us, DefaultString);
		this.m_App.LangSetCurrent(CultureId.en_us);

		this.m_Window = new WindowMain();
		this.m_Window.CreateAndShow();

		return this;
	}
}

(global as any).app = new MyApp().Run();
