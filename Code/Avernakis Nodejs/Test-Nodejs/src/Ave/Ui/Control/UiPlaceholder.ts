import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { WindowLike } from "./UiWindow";

export interface IPlaceholder extends IControl {
	new (window: WindowLike): IPlaceholder;
}

export class Placeholder extends (AveLib.UiPlaceholder as IPlaceholder) {}
