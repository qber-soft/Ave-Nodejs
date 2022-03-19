import { Window, Button } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const button = new Button(window);
    button.SetText("Button");
    button.OnClick((sender) => {
        const commonUi = window.GetCommonUi();
        const label = "Please input:";
        const placeHolder = "input here";
        const title = "Title";
        const value = "default input";
        const fallback = "input cancelled";
        const result = commonUi.Input(
            fallback,
            label,
            value,
            placeHolder,
            title
        );
        console.log(`input result: "${result}"`);
    });

    const container = getControlDemoContainer(window);
    container.ControlAdd(button).SetGrid(1, 1);
    window.SetContent(container);
}
