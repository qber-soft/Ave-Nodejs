import { AveLib } from "../../AveLib";
import { AlignType } from "../UiCommon";
import { Vec4 } from "../../Math/Vector";
import { IVisual } from "../UiVisual";
import { WindowLike } from "../Control/UiWindow";

export interface ILabel extends IVisual {
	new (window: WindowLike, key?: string | number): ILabel;

	SetText(s: string): Label;
	GetText(): string;

	SetAlignHorz(n: AlignType): Label;
	GetAlignHorz(): AlignType;

	SetAlignVert(n: AlignType): Label;
	GetAlignVert(): AlignType;

	SetBackColor(vColor: Vec4): Label;
	GetBackColor(): Vec4;

	SetWrappable(b: boolean): Label;
	GetWrappable(): boolean;
}

export class Label extends (AveLib.UiLabel as ILabel) {
	GetBackColor(): Vec4 {
		return Vec4.FromNative(super.GetBackColor());
	}
}
