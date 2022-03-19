import { Window, CheckBox, CheckBoxStyle } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const container = getControlDemoContainer(window, 3);

    {
        const checkBox = new CheckBox(window);
        checkBox.SetText("Apple");
        checkBox.SetCheckBoxStyle(CheckBoxStyle.Checking);

        container.ControlAdd(checkBox).SetGrid(1, 1);
    }

    {
        const checkBox = new CheckBox(window);
        checkBox.SetText("Apple");
        checkBox.SetCheckBoxStyle(CheckBoxStyle.Pushing);

        container.ControlAdd(checkBox).SetGrid(3, 1);
    }

    window.SetContent(container);
}
