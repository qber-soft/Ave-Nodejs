import { Window, TrackBar } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const trackBar = new TrackBar(window);
    trackBar.OnThumbRelease((sender) => {
        console.log(`on thumb release, current value: ${sender.GetValue()}`);
    });

    const container = getControlDemoContainer(window, 1, 500, 25);
    container.ControlAdd(trackBar).SetGrid(1, 1);
    window.SetContent(container);
}
