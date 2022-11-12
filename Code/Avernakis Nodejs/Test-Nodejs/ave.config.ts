import { IPackConfig } from "ave-pack";

const config: IPackConfig = {
	build: {
		projectRoot: __dirname,
		target: "node14-win-x64",
		input: "./build/examples/app/index.js",
		output: "./bin/ave-app.exe",
		// debug: true,
		edit: false,
	},
	resource: {
		icon: "./examples/assets/ave.ico",
		productVersion: "0.0.1",
		productName: "Ave Demo App",
		fileVersion: "0.0.1",
		companyName: "QberSoft",
		fileDescription: "The Demo App of Ave",
		LegalCopyright: `© ${new Date().getFullYear()} Ave Copyright.`,
		manifest: "./node-manifest.xml",
	},
};

export default config;
