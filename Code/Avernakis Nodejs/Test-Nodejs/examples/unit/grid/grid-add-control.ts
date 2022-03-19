import { Window, Grid, Vec4 } from "../../../src";

export function main(window: Window) {
    const container = new Grid(window);
    container.ColAddSlice(1, 1, 1);
    container.RowAddSlice(1, 1, 1);

    const center = new Grid(window);
    const lightBlue = new Vec4(0, 146, 255, 255 * 0.75);
    center.SetBackColor(lightBlue);

    container.ControlAdd(center).SetGrid(1, 1, 1, 1);
    window.SetContent(container);
}
