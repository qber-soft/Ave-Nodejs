import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { WindowLike } from "./UiWindow";
import { Vec2 } from "../../Math/Vector";
import { AlignType } from "../UiCommon";

export enum PagerAdjustment {
	None,
	FitWidth,
	FitHeight,
}

export interface IPager extends IControl {
	new (window: WindowLike): IPager;

	SetContent(pControl: IControl): IControl;
	GetContent(): IControl;

	SetContentSize(vSize: Vec2): Pager;
	GetContentSize(): Vec2;
	GetRealContentSize(): Vec2;

	SetContentHorizontalAlign(nType: AlignType): Pager;
	GetContentHorizontalAlign(): AlignType;

	SetContentVerticalAlign(nType: AlignType): Pager;
	GetContentVerticalAlign(): AlignType;

	SetAdjustment(nAdjust: PagerAdjustment): Pager;
	GetAdjustment(): PagerAdjustment;

	SetAutoHideScroll(b: boolean): Pager;
	GetAutoHideScroll(): boolean;

	SetPointerScroll(b: boolean): Pager;
	GetPointerScroll(): boolean;

	SetScrollPosition(vPos: Vec2, bScroll: boolean): Pager;
	GetScrollPosition(): Vec2;
	GetScrollSize(): Vec2;
	GetScrollMax(): Vec2;
}

export class Pager extends (AveLib.UiPager as IPager) {
	private m_Content: IControl;

	SetContent(pControl: IControl) {
		this.m_Content = pControl;
		return super.SetContent(pControl);
	}

	GetContentSize(): Vec2 {
		return Vec2.FromNative(super.GetContentSize());
	}

	GetRealContentSize(): Vec2 {
		return Vec2.FromNative(super.GetRealContentSize());
	}

	GetScrollPosition(): Vec2 {
		return Vec2.FromNative(super.GetScrollPosition());
	}

	GetScrollSize(): Vec2 {
		return Vec2.FromNative(super.GetScrollSize());
	}

	GetScrollMax(): Vec2 {
		return Vec2.FromNative(super.GetScrollMax());
	}
}
