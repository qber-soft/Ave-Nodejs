import { Window, ComboBox } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const comboBox = new ComboBox(window);
    comboBox.Append("a", "b", "c");
    comboBox.Select(0);
    comboBox.OnSelectionChange((comboBox: ComboBox) => {
        console.log(`current index: ${comboBox.GetSelection()}`);
    });

    const container = getControlDemoContainer(window);
    container.ControlAdd(comboBox).SetGrid(1, 1);
    window.SetContent(container);
}
