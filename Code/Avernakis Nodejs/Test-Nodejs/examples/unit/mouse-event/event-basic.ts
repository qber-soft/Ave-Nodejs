import { Window, Button, ControlMessage } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const button = new Button(window);
    button.SetText("Button");
    button.OnMessagePost((sender, nMsg) => {
        if (
            nMsg !== ControlMessage.Paint &&
            nMsg !== ControlMessage.PointerCursor &&
            nMsg !== ControlMessage.PointerMove
        ) {
            console.log(`on message post: ${ControlMessage[nMsg]}(${nMsg})`);
        }
    });

    const container = getControlDemoContainer(window);
    container.ControlAdd(button).SetGrid(1, 1);
    window.SetContent(container);
}
