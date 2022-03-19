import { Window, Label, Vec4 } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const label = new Label(window);
    label.SetText("Label");
    const lightBlue = new Vec4(0, 146, 255, 255 * 0.75);
    label.SetBackColor(lightBlue);

    const container = getControlDemoContainer(window);
    container.ControlAdd(label).SetGrid(1, 1);
    window.SetContent(container);
}
