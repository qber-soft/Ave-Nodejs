import { Byo2Image, Mat32, Vec2, Vec4 } from "../Ave";
import { Byo2FlowDirection, Byo2Font, Byo2ReadingDirection } from "../Byo2/Byo2Font";
import { AveMath } from "../Math";
import { Rect } from "./UiCommon";

export enum FillMode {
	Color,
	Brush,
	Image,
}

// prettier-ignore
export enum DrawTextFlag {
	Top         /**/ = 0x00000000,
	Left        /**/ = 0x00000000,
	Center      /**/ = 0x00000001,
	Right       /**/ = 0x00000002,
	VCenter     /**/ = 0x00000004,
	Bottom      /**/ = 0x00000008,
	SingleLine  /**/ = 0x00000020,
	NoClip      /**/ = 0x00000100,
	CalcRect    /**/ = 0x00000400,
	EllipsePath /**/ = 0x00004000,
	EllipseEnd  /**/ = 0x00008000,
	EllipseWord /**/ = 0x00040000,
	UpdateRect  /**/ = 0x10000000,
}

// prettier-ignore
export enum DrawImageFlag {
	SourceRect  /**/ = 0x00000001,
	SourceAlpha /**/ = 0x00000002,
	Filter      /**/ = 0x00000004,
	TargetSize  /**/ = 0x00000008,
	SourceRect2 /**/ = 0x00000010,
	Address     /**/ = 0x00000100,
	Address2    /**/ = 0x00000200,
	Transform   /**/ = 0x00000400,
	Transform2  /**/ = 0x00000800,
}

export enum DrawImageFilter {
	Point = 0,
	Linear = 1,
}

export enum DrawImageAddress {
	Clamp = 0,
	Wrap = 1,
}

export class DrawImageParam {
	SourceRect: Rect = Rect.Empty;
	TargetSize: Vec2 = Vec2.Zero;
	SourceAlpha: number = 1;
	SourceRect2: Rect = Rect.Empty;
	Filter: DrawImageFilter = DrawImageFilter.Linear;
	Address: DrawImageAddress = DrawImageAddress.Clamp;
	Address2: DrawImageAddress = DrawImageAddress.Clamp;
	Transform: Mat32 = Mat32.Identity;
	Transform2: Mat32 = Mat32.Identity;
}

export class PainterState<T extends number = number> {
	private m_Time: number = -Number.MAX_VALUE;
	private m_Speed: number = 1;
	private m_Ratio: number = 0;

	private m_OldState: T;
	private m_NewState: T;

	constructor(nState?: T) {
		if (nState) {
			this.m_OldState = nState;
			this.m_NewState = nState;
			this.m_Ratio = 1;
		}
	}

	Set(nNewState: T, fTime: number, fSpeed: number = 1): number {
		if (nNewState != this.m_NewState) {
			this.m_OldState = this.m_NewState;
			this.m_NewState = nNewState;
			this.m_Time = fTime;
			this.m_Speed = fSpeed;
			this.m_Ratio = 0;
			return 1;
		}
		return 0;
	}

	SetStable(nNewState: T, fTime: number, fSpeed: number = 1): number {
		if (nNewState != this.m_NewState) {
			this.m_OldState = this.CurrentStateSmoothEnd;
			this.m_NewState = nNewState;
			this.m_Time = fTime;
			this.m_Speed = fSpeed;
			this.m_Ratio = 0;
			return 1;
		}
		return 0;
	}

	SetForce(nNewState: T) {
		this.m_OldState = nNewState;
		this.m_NewState = nNewState;
		this.m_Time = -Number.MAX_VALUE;
		this.m_Ratio = 1;
	}

	get IsStable() {
		return this.m_Ratio >= 1;
	}

	get Ratio() {
		return this.m_Ratio;
	}

	get RatioSmoothEnd() {
		return Math.sin((Math.PI * 0.5 - 0.000001) * this.m_Ratio);
	}

	get RatioSmoothStartEnd() {
		const f = Math.sin((Math.PI * 0.5 - 0.000001) * this.m_Ratio);
		return f * f;
	}

	get OldState() {
		return this.m_OldState;
	}

	get NewState() {
		return this.m_NewState;
	}

	get CurrentState() {
		return AveMath.Lerp(this.m_OldState, this.m_NewState, this.m_Ratio);
	}

	get CurrentStateSmoothEnd() {
		return AveMath.Lerp(this.m_OldState, this.m_NewState, this.RatioSmoothEnd);
	}

	static FromNative<T extends number>(r: PainterState<T>) {
		const ret = new PainterState<T>();
		ret.m_Time = r.m_Time;
		ret.m_Speed = r.m_Speed;
		ret.m_Ratio = r.m_Ratio;
		ret.m_OldState = r.m_OldState;
		ret.m_NewState = r.m_NewState;
		return ret;
	}
}

export class PainterViewport {
	Offset: Vec2 = Vec2.Zero;
	Opacity: number = 1;
	Transform: Mat32 = Mat32.Identity;
}

// prettier-ignore
export interface IPainter {
	GetTime(): number;
	IsStable(): boolean;

	// The painter is stable on initial, passing any unstable state to this method will cause the painter to unstable state so it will schedule the next frame rendering
	// Return true if the currently updated state is stable
	UpdateState<T extends number>(state: PainterState<T>): boolean;

	TypedSetStyle(nStyle: number): void;
	TypedSetOpacity(f: number): void;
	TypedSetFont(pFont: Byo2Font): void;
	TypedSetTextColor(vColor: Vec4): void;
	TypedClearTextColor(): void;
	TypedSetHintColor(vColor: Vec4): void;

	GetFontStandard(): Byo2Font;

	DrawAnimation(): void;

	PushViewport(rc: Rect, vOffset: Vec2, fOpacity: number): void;
	PushViewport2(rc: Rect, vp: PainterViewport): void;
	PopViewport(): void;
	GetViewportRect(): Rect;

	SetPenFillMode(n: FillMode): void;
	GetPenFillMode(): FillMode;
	SetPenColor(vColor: Vec4): void;
	SetPenImage(pImage: Byo2Image): void;
	SetPenWidth(f: number): void;

	SetFillFillMode(n: FillMode): void;
	GetFillFillMode(): FillMode;
	SetFillColor(vColor: Vec4): void;
	SetFillImage(pImage: Byo2Image): void;

	SetTextFillMode(n: FillMode): void;
	GetTextFillMode(): FillMode;
	SetTextColor(vColor: Vec4): void;
	SetTextImage(pImage: Byo2Image): void;
	SetTextReadingDirection(n: Byo2ReadingDirection): void;
	GetTextReadingDirection(): Byo2ReadingDirection;
	SetTextFlowDirection(n: Byo2FlowDirection): void;
	GetTextFlowDirection(): Byo2FlowDirection;

	SetWorld(m: Mat32): void;

	DrawLine(x0: number, y0: number, x1: number, y1: number): void;

	DrawRectangle(x: number, y: number, w: number, h: number): void;
	FillRectangle(x: number, y: number, w: number, h: number): void;

	DrawRoundedRectangle(x: number, y: number, w: number, h: number, rx: number, ry: number): void;
	FillRoundedRectangle(x: number, y: number, w: number, h: number, rx: number, ry: number): void;

	DrawEllipse(x: number, y: number, w: number, h: number): void;
	FillEllipse(x: number, y: number, w: number, h: number): void;

	// r0 and r1: 0 at top, sweep in CW direction, r1 must greater than r0 and (r1-r0) must in the range (0, 2π]
	DrawArc(x: number, y: number, w: number, h: number, r0: number, r1: number): void;
	FillPie(x: number, y: number, w: number, h: number, r0: number, r1: number): void;

	FillImageMask(rcFill: Rect, pMask: Byo2Image, rcMask: Rect): void;

	DrawImage(pImage: Byo2Image, vPos: Vec2): void;
	DrawImageEx(pImage: Byo2Image, vPos: Vec2, nFlag: DrawImageFlag, dip: DrawImageParam): void;
	DrawImageMask(pImage: Byo2Image, vPos: Vec2, pMask: Byo2Image): void;
	DrawImageMaskEx(pImage: Byo2Image, vPos: Vec2, pMask: Byo2Image, nFlag: DrawImageFlag, dip: DrawImageParam): void;
	DrawImageLerp(pImage0: Byo2Image, pImage1: Byo2Image, vPos: Vec2, fLerp: number): void;
	DrawImageLerpEx(pImage0: Byo2Image, pImage1: Byo2Image, vPos: Vec2, fLerp: number, nFlag: DrawImageFlag, dip: DrawImageParam): void;

	DrawString(pFont: Byo2Font, rc: Rect, s: string, nFlag: DrawTextFlag, nCharCount: number): Rect;
}
