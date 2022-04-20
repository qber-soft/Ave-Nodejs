import { FontDescription, WindowLike } from "../Ave";
import { AveLib } from "../AveLib";

export enum Byo2ReadingDirection {
	LeftToRight,
	RightToLeft,
	TopToBottom,
	BottomToTop,
}

export enum Byo2FlowDirection {
	TopToBottom,
	BottomToTop,
	LeftToRight,
	RightToLeft,
}

export interface IByo2Font {
	new (window: WindowLike, cp: FontDescription): IByo2Font;

	GetAscent(): number;
	GetDescent(): number;
	GetHeight(): number;
	GetWidth(): number;
	GetLeadingExternal(): number;
	GetLeadingInternal(): number;
	SetReadingDirection(n: Byo2ReadingDirection): void;
	GetReadingDirection(): Byo2ReadingDirection;
	SetFlowDirection(n: Byo2FlowDirection): void;
	GetFlowDirection(): Byo2FlowDirection;

	Measure(s: string): number[];
}

export class Byo2Font extends (AveLib.Byo2Font as IByo2Font) {}
