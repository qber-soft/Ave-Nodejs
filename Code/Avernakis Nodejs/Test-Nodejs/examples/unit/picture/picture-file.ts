import { Window, Picture, ResourceSource, AppPath } from "../../../src";
import { getControlDemoContainer } from "../utility";
import * as fs from "fs";
import * as path from "path";

export function main(window: Window) {
    const picture = new Picture(window);
    const source = ResourceSource.FromFilePath(path.resolve(__dirname, "./Clock#6.png"));
    picture.SetPicture(source);

    const container = getControlDemoContainer(window, 1, 300, 300);
    container.ControlAdd(picture).SetGrid(1, 1);
    window.SetContent(container);
}
