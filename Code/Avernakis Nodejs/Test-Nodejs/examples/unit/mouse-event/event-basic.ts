import { Window, Button, MessagePointer, Vec2 } from "../../../src";
import { getControlDemoContainer } from "../utility";

function formatMessagePointer(m: MessagePointer) {
	return `pos: (${m.Position.x}, ${m.Position.y})`;
}

export function main(window: Window) {
	const button = new Button(window);
	let entered = false;
	let pos = Vec2.Zero;

	const updateButton = () => button.SetText(`${entered ? `at ${pos.x}, ${pos.y}` : "out"}`);
	updateButton();

	//
	button.OnPointerEnter((sender, mp) => {
		entered = true;
		updateButton();
	});
	button.OnPointerLeave((sender, mp) => {
		entered = false;
		updateButton();
	});

	//
	button.OnPointerPress((sender, mp) => {
		console.log(`on press: ${formatMessagePointer(mp)}`);
	});
	button.OnPointerRelease((sender, mp) => {
		console.log(`on release: ${formatMessagePointer(mp)}`);
	});

	//
	button.OnPointerMove((sender, mp) => {
		pos = mp.Position;
		updateButton();
	});

	button.OnPointerHover((sender, mp) => {
		console.log("on hover");
	});

	const container = getControlDemoContainer(window);
	container.ControlAdd(button).SetGrid(1, 1);
	window.SetContent(container);
}
