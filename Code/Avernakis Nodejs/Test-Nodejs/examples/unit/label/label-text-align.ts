import { Window, Label, Vec4, AlignType } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const container = getControlDemoContainer(window, 5);
	const lightBlue = new Vec4(0, 146, 255, 255 * 0.75);

	{
		const label = new Label(window);
		label.SetText("Label");
		label.SetAlignHorz(AlignType.Near);
		label.SetBackColor(lightBlue);

		container.ControlAdd(label).SetGrid(1, 3);
	}

	{
		const label = new Label(window);
		label.SetText("Label");
		label.SetAlignHorz(AlignType.Center);
		label.SetBackColor(lightBlue);

		container.ControlAdd(label).SetGrid(3, 3);
	}

	{
		const label = new Label(window);
		label.SetText("Label");
		label.SetAlignHorz(AlignType.Far);
		label.SetBackColor(lightBlue);

		container.ControlAdd(label).SetGrid(5, 3);
	}

	window.SetContent(container);
}
