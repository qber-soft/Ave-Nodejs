import { KbKey, Window } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	// hk: hot key
	const hkW = window.HotkeyRegister(KbKey.W, 0);
	const hkS = window.HotkeyRegister(KbKey.S, 0);
	const hkA = window.HotkeyRegister(KbKey.A, 0);
	const hkD = window.HotkeyRegister(KbKey.D, 0);

	window.OnWindowHotkey((sender, nId, key, n) => {
		switch (nId) {
			case hkW:
				console.log("press w");
				break;
			case hkS:
				console.log("press s");
				break;
			case hkA:
				console.log("press a");
				break;
			case hkD:
				console.log("press d");
				break;
		}
	});

	const container = getControlDemoContainer(window);
	window.SetContent(container);
}
