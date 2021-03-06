import { AveLib } from "../../AveLib";
import { DpiSize, FontDescription } from "../UiCommon";

export enum ThemeType {
	Unknown = 0,
	ImageBased = 1,
}

export interface ITheme {
	ResetTheme(): void;

	SetFont(font: FontDescription): void;

	AnimationSetDuration(nMillisecond: number): void; // [0, 10000]
	AnimationGetDuration(): number;
	AnimationSetFps(nFps: number): void; // [8, 240]
	AnimationGetFps(): number;

	InfectionSet(option: UiThemeInfection): void;
	InfectionGet(): UiThemeInfection;
}

export type Theme = ITheme;

export class UiThemeInfection {
	m_InfectionSpread: boolean = false;
	m_InfectionRadius: DpiSize = DpiSize.FromPixel(0);
	m_InfectionOpacity: number = 0.75;
	m_InfectionActiveRatio: number = 0.75;

	static FromNative(raw: UiThemeInfection) {
		const infection = new UiThemeInfection();
		infection.m_InfectionSpread = raw.m_InfectionSpread;
		infection.m_InfectionRadius = raw.m_InfectionRadius;
		infection.m_InfectionOpacity = raw.m_InfectionOpacity;
		infection.m_InfectionActiveRatio = raw.m_InfectionActiveRatio;
		return infection;
	}
}

export interface IThemeImage extends Theme {
	new (): IThemeImage;
}

export class ThemeImage extends (AveLib.UiThemeImage as IThemeImage) {}
