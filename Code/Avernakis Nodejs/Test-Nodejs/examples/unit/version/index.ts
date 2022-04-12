import { Window, Grid, Vec4, AveGetSDKVersion } from "../../../src";

export function main(window: Window) {
	const grid = new Grid(window);
	const lightBlue = new Vec4(0, 146, 255, 255 * 0.75);
	grid.SetBackColor(lightBlue);

	//
	const version = AveGetSDKVersion();
	console.log(`ave sdk version: ${JSON.stringify(version.VersionString, null, 4)}, is private: ${version.IsPrivateVersion}`);
	window.SetContent(grid);
}
