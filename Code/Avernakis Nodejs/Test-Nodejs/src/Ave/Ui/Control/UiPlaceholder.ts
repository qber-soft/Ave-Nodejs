import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";

export interface IPlaceholder extends IControl {
    new (window: Window): IPlaceholder;
}

export class Placeholder extends (AveLib.UiPlaceholder as IPlaceholder) {}
