import { Window, Picture, ResourceSource } from "../../../src";
import { AppPath } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const picture = new Picture(window);
    const source = ResourceSource.FromFilePath(
        AppPath.AppPath + "_Debug\\AppRes\\Icon\\Clock#6.png"
    );
    picture.SetPicture(source);

    const container = getControlDemoContainer(window, 1, 300, 300);
    container.ControlAdd(picture).SetGrid(1, 1);
    window.SetContent(container);
}
