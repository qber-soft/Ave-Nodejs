import { Window, Picture, ResourceSource, Byo2Image, Byo2ImageCreation, Byo2ImageDataType, PixFormat, Rect, InMemoryData, Button } from "../../../src";
import { AppPath } from "../../../src";
import { getControlDemoContainer } from "../utility";
import { ResId } from "../ResId";

export function main(window: Window) {
    const picture = new Picture(window);
    const source = ResourceSource.FromResource(ResId.Icon_Clock_png);
    picture.SetPicture(source);

    const container = getControlDemoContainer(window, 1, 300, 300);
    container.ControlAdd(picture).SetGrid(1, 1);
    window.SetContent(container);
}
