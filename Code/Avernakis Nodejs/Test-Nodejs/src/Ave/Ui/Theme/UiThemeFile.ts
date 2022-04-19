import { AveLib } from "../../AveLib";
import { ResourceSource } from "../../Io";
import { Theme, ThemeImage, ThemeType } from "./UiTheme";

export interface IThemeFile {
	GetThemeType(): ThemeType;

	Open(res: ResourceSource): boolean;

	SetTheme(theme: Theme, nTargetStyle: number): boolean;
}

export type ThemeFile = IThemeFile;

export interface IThemeFileImage extends ThemeFile {
	new(): IThemeFileImage;

	CreateTheme(): ThemeImage;
}

export class ThemeFileImage extends (AveLib.UiThemeFileImage as IThemeFileImage) { }
