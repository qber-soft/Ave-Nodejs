import {
    Window,
    MessageIcon,
    MessageButton,
    Button,
    MessageResult,
} from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const button = new Button(window);
    button.SetText("Button");
    button.OnClick((sender) => {
        const commonUi = window.GetCommonUi();
        const result = commonUi.Message(
            "Message",
            "This is a message",
            MessageIcon.Infomation,
            MessageButton.YesNo,
            "Title"
        );
        console.log(`message result: ${result}(${MessageResult[result]})`);
    });

    const container = getControlDemoContainer(window);
    container.ControlAdd(button).SetGrid(1, 1);
    window.SetContent(container);
}
