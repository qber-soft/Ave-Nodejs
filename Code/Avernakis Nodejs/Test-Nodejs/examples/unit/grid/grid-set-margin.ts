import { Window, Grid, Vec4, DpiMargin, DpiSize } from "../../../src";

export function main(window: Window) {
    const container = new Grid(window);
    container.ColAddSlice(1, 1, 1);
    container.RowAddSlice(1, 1, 1);

    const center = new Grid(window);
    const lightBlue = new Vec4(0, 146, 255, 255 * 0.75);
    center.SetBackColor(lightBlue);

    //
    const margin = new DpiMargin(
        DpiSize.FromPixelScaled(100), // margin left
        DpiSize.FromPixelScaled(50), // margin top
        DpiSize.FromPixelScaled(0), // margin right
        DpiSize.FromPixelScaled(0)
    ); // margin bottom

    const gridControl = container.ControlAdd(center);
    gridControl.SetGrid(0, 0, 1, 1);
    gridControl.SetMargin(margin);

    window.SetContent(container);
}
