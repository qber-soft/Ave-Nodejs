import { Window, Button, ControlMessage } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const button = new Button(window);
    button.SetText("Button");

    button.ListenEvent();
    button.OnPointerEnter((sender) => {
        console.log("-----on enter");
    });
    button.OnPointerLeave((sender) => {
        console.log("on leave");
    });
    // button.OnMessagePost((sender, nMsg) => {
    //     if (nMsg === ControlMessage.PointerEnter) {
    //         console.log(`-----${ControlMessage[nMsg]}(${nMsg})`);
    //     } else if (nMsg === ControlMessage.PointerLeave) {
    //         console.log(`${ControlMessage[nMsg]}(${nMsg})`);
    //     }
    // });

    const container = getControlDemoContainer(window);
    container.ControlAdd(button).SetGrid(1, 1);
    window.SetContent(container);
}
