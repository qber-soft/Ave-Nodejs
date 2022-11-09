import { IPackConfig } from "ave-pack";

const config: IPackConfig = {
	build: {
		projectRoot: __dirname,
		target: "node14-win-x64",
		input: "./build/src/index.js",
		output: "./bin/ave-app.exe",
	},
	resource: {
		icon: "./assets/ave.ico",
		productVersion: "0.0.1",
		productName: "Ave Template App",
		fileVersion: "0.0.1",
		companyName: "QberSoft",
		fileDescription: "The Template App of Ave",
		LegalCopyright: `© ${new Date().getFullYear()} Ave Copyright.`,
	},
};

export default config;
