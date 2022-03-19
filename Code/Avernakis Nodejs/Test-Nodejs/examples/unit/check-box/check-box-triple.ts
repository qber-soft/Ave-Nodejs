import { Window, CheckBox, CheckBoxStyle } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const container = getControlDemoContainer(window, 3);

    {
        const checkBox = new CheckBox(window);
        checkBox.SetText("Check all");
        checkBox.SetTriple(true);

        container.ControlAdd(checkBox).SetGrid(1, 1);
    }

    {
        const checkBox = new CheckBox(window);
        checkBox.SetText("Check all");
        checkBox.SetTriple(true);
        checkBox.SetCheckBoxStyle(CheckBoxStyle.Pushing);

        container.ControlAdd(checkBox).SetGrid(3, 1);
    }

    window.SetContent(container);
}
