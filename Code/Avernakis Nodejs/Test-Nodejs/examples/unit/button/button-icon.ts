import { Window, Button, IconSource, VisualTextLayout } from "../../../src";
import { ResId } from "../ResId";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const button = new Button(window);
    button.SetText("Open");
    button.SetVisualTextLayout(VisualTextLayout.HorzVisualText);
    button.SetVisual(
        window.CreateManagedIcon(new IconSource(ResId.Icon_FileOpen_png, 16))
    );

    const container = getControlDemoContainer(window);
    container.ControlAdd(button).SetGrid(1, 1);
    window.SetContent(container);
}
