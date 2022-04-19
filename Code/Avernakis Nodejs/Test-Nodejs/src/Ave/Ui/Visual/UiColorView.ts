import { AveLib } from "../../AveLib";
import { IVisual } from "../UiVisual";
import { WindowLike } from "../Control/UiWindow";
import { Vec4 } from "../../Math/Vector";
import { DpiSize } from "../UiCommon";

export interface IColorView extends IVisual {
	new (window: WindowLike): IColorView;

	SetSolidColor(vColor: Vec4): ColorView;
	GetSolidColor(): Vec4;

	SetBackColor1(vColor: Vec4): ColorView;
	GetBackColor1(): Vec4;

	SetBackColor2(vColor: Vec4): ColorView;
	GetBackColor2(): Vec4;

	SetBackBlockSize(nSize: DpiSize): ColorView;
	GetBackBlockSize(): DpiSize;
}

export class ColorView extends (AveLib.UiColorView as IColorView) {
	GetSolidColor(): Vec4 {
		return Vec4.FromNative(super.GetSolidColor());
	}

	GetBackColor1(): Vec4 {
		return Vec4.FromNative(super.GetBackColor1());
	}

	GetBackColor2(): Vec4 {
		return Vec4.FromNative(super.GetBackColor2());
	}
}
