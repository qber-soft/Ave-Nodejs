import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { WindowLike } from "../Control/UiWindow";

export interface IRibbonApp extends IControl {
	new (window: WindowLike, key?: string | number): IRibbonApp;

	SetText(s: string): RibbonApp;
	GetText(): string;

	OnClick(fn: (sender: RibbonApp) => void): RibbonApp;
}

export class RibbonApp extends (AveLib.UiRibbonApp as IRibbonApp) {}
