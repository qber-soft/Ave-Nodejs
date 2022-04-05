import { Window, Knob, Vec4 } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const knob = new Knob(window);
	knob.SetText("volume");
	const lightBlue = new Vec4(0, 146, 255, 255 * 0.75);
	knob.RingSetColor(lightBlue);
	knob.OnChange((sender) => {
		console.log(`value: ${sender.ValueGet()}`);
	});

	const container = getControlDemoContainer(window, 1, 80, 80);
	container.ControlAdd(knob).SetGrid(1, 1);
	window.SetContent(container);
}
