import { Window, Label, Vec4, Grid } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const label = new Label(window);
    label.SetText("Label");

    const backgroundGrid = new Grid(window);
    const lightBlue = new Vec4(0, 146, 255, 255 * 0.75);
    backgroundGrid.SetBackColor(lightBlue).ColAddSlice(1).RowAddSlice(1);
    backgroundGrid.ControlAdd(label).SetGrid(0, 0);

    const container = getControlDemoContainer(window);
    container.ControlAdd(backgroundGrid).SetGrid(1, 1);
    window.SetContent(container);
}
