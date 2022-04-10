import { Window, Placeholder, Vec4, FontDescription, Byo2Font, Rect, DrawTextFlag, IPainter, IPlaceholder } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const button = new Button(window, "Primary Button");
	const container = getControlDemoContainer(window, 1, 120, 32);
	container.ControlAdd(button.control).SetGrid(1, 1);
	window.SetContent(container);
}

interface IButtonStyle {
	border: {
		radius: number;
	};
	color: Vec4;
	backgroundColor: Vec4;
	font: {
		size: number;
		family: string[];
	};
}

class Button {
	text: string;
	placeholder: Placeholder;
	font: Byo2Font;
	style: IButtonStyle;
	colors: { normal: Vec4; active: Vec4; hover: Vec4 };
	isEntered: boolean;
	isPressed: boolean;

	constructor(window: Window, text: string) {
		this.text = text;
		this.placeholder = new Placeholder(window);
		this.placeholder.OnPaintPost(this.onPaint.bind(this));
		this.placeholder.OnPointerEnter(this.onEnter.bind(this));
		this.placeholder.OnPointerLeave(this.onLeave.bind(this));
		this.placeholder.OnPointerPress(this.onPress.bind(this));
		this.placeholder.OnPointerRelease(this.onRelease.bind(this));

		this.colors = {
			normal: new Vec4(24, 144, 255, 255),
			hover: new Vec4(64, 169, 255, 255),
			active: new Vec4(9, 109, 217, 255),
		};

		this.isEntered = false;
		this.isPressed = false;

		this.style = {
			border: {
				radius: 3,
			},
			color: new Vec4(255, 255, 255, 255),
			backgroundColor: this.colors.normal,
			font: {
				size: 9,
				family: ["Segoe UI", "Microsoft YaHei UI", "Meiryo UI", "SimSun-ExtB"],
			},
		};

		const fontDesc = new FontDescription();
		fontDesc.Name = this.style.font.family;
		fontDesc.Size = this.style.font.size;
		const font = new Byo2Font(window, fontDesc);
		this.font = font;
	}

	onEnter() {
		this.isEntered = true;
		this.style.backgroundColor = this.colors.hover;
		this.placeholder.Redraw();
	}

	onPress() {
		this.isPressed = true;
		this.style.backgroundColor = this.colors.active;
		this.placeholder.Redraw();
	}

	onRelease() {
		this.isPressed = false;
		this.style.backgroundColor = this.colors.normal;
		this.placeholder.Redraw();
	}

	onLeave() {
		this.isEntered = false;
		if (!this.isPressed) {
			this.style.backgroundColor = this.colors.normal;
		}
		this.placeholder.Redraw();
	}

	onPaint(sender: IPlaceholder, painter: IPainter, rect: Rect) {
		const { border, color, backgroundColor } = this.style;
		painter.SetFillColor(backgroundColor);
		painter.FillRoundedRectangle(rect.x, rect.y, rect.w, rect.h, border.radius, border.radius);
		painter.SetTextColor(color);
		painter.DrawString(this.font, rect, this.text, DrawTextFlag.Center | DrawTextFlag.VCenter, this.text.length);
	}

	get control() {
		return this.placeholder;
	}
}
