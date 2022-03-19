import { Window, Button } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const button = new Button(window);
    button.SetText("Button");
    button.OnClick((sender) => {
        sender.SetText("Button Clicked");
    });

    const container = getControlDemoContainer(window);
    container.ControlAdd(button).SetGrid(1, 1);
    window.SetContent(container);
}
