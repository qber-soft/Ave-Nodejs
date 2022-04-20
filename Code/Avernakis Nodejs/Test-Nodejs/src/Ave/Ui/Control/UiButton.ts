import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { ButtonType, ButtonStyle, AlignType, VisualTextLayout, CustomDrawStage, Rect, Std5State } from "../UiCommon";
import { IVisual } from "../UiVisual";
import { WindowLike } from "./UiWindow";
import { DrawTextFlag, IPainter, PainterState } from "../UiPainter";
import { Vec4 } from "../../Math";

export enum ButtonCustomDrawBehavior {
	DoDefault = 0x0,
	Skip = 0x1,

	NewTextColor = 0x10,
	NewRect = 0x20,
	NewFormat = 0x40,
}

export class ButtonCustomDrawResult {
	Behavior: ButtonCustomDrawBehavior = ButtonCustomDrawBehavior.DoDefault;
	NewTextColor: Vec4 = Vec4.Zero;
	NewRect: Rect = Rect.Empty;
	NewFormat: DrawTextFlag = 0;
}

export enum ButtonCustomDrawPart {
	Button,
	ButtonMain,
	ButtonSecondary,
	ButtonDrop,
	Text,
}

export class ButtonCustomDraw {
	Painter: IPainter;
	Part: ButtonCustomDrawPart;
	Stage: CustomDrawStage;
	RectButton: Rect;
	Rect: Rect;
	Text: string;
	TextFlag: DrawTextFlag;
	State: PainterState<Std5State>;

	static FromNative(r: ButtonCustomDraw) {
		const ret = new ButtonCustomDraw();
		ret.Painter = r.Painter;
		ret.Part = r.Part;
		ret.Stage = r.Stage;
		ret.Rect = Rect.FromNative(r.Rect);
		ret.RectButton = Rect.FromNative(r.RectButton);
		ret.Text = r.Text;
		ret.TextFlag = r.TextFlag;
		ret.State = PainterState.FromNative<Std5State>(r.State);
		return ret;
	}
}

export interface IButton extends IControl {
	new(window: WindowLike, key?: string | number): IButton;

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
	OnCustomDraw(fn: (sender: Button, cdp: ButtonCustomDraw) => ButtonCustomDrawResult): Button;
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

	OnCustomDraw(fn: (sender: Button, cdp: ButtonCustomDraw) => ButtonCustomDrawResult): Button {
		if (fn)
			return super.OnCustomDraw((sender, cdp) => fn(sender, ButtonCustomDraw.FromNative(cdp)));
		else
			return super.OnCustomDraw(null);
	}

}
