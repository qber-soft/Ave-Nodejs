import { AveLib } from "../../AveLib";
import { ThemeImage } from "./UiTheme";

export interface IThemePredefined {
    SetStyle(theme: ThemeImage, nStyle: number): void;
}

export type ThemePredefined = IThemePredefined;

export interface IThemePredefined_Dark extends ThemePredefined {
    new (): IThemePredefined_Dark;
}

export class ThemePredefined_Dark extends (AveLib.UiThemePredefined_Dark as IThemePredefined_Dark) {}
