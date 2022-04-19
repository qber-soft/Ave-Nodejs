import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { WindowLike } from "./UiWindow";

export interface IListBox extends IControl {
	new (window: WindowLike): IListBox;

	Append(text: string): ListBox;
	OnSelectionEnd(fn: (sender: ListBox) => void): ListBox;
	GetSelection(): number;
}

export class ListBox extends (AveLib.UiListBox as IListBox) {}
