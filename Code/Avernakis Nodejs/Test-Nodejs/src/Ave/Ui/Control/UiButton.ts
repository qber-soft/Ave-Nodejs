import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { ButtonType, ButtonStyle, AlignType, VisualTextLayout } from "../UiCommon";
import { IVisual } from "../UiVisual";
import { Window } from "./UiWindow";

export interface IButton extends IControl {
	new (window: Window, key?: string | number): IButton;

	SetText(s: string): Button;
	GetText(): string;

	SetButtonType(n: ButtonType): Button;
	GetButtonType(): ButtonType;

	SetButtonStyle(n: ButtonStyle): Button;
	GetButtonStyle(): ButtonStyle;

	SetDrop(c: IControl): IControl;
	GetDrop(): IControl;

	SetAlignHorz(n: AlignType): Button;
	GetAlignHorz(): AlignType;

	SetVisualTextLayout(n: VisualTextLayout): Button;
	GetVisualTextLayout(): VisualTextLayout;

	SetVisual(v: IVisual): IVisual;
	GetVisual(): IVisual;

	OnClick(fn: (sender: Button) => void): Button;
	OnDrop(fn: (sender: Button) => void): Button;
}

export class Button extends (AveLib.UiButton as IButton) {
	private m_Drop: IControl;
	private m_Visual: IVisual;

	SetDrop(c: IControl) {
		this.m_Drop = c;
		return super.SetDrop(c);
	}

	SetVisual(v: IVisual) {
		this.m_Visual = v;
		return super.SetVisual(v);
	}
}
