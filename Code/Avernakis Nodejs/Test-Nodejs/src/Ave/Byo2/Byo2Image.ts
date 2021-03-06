import { Rect } from "../Ave";
import { AveLib } from "../AveLib";
import { PixFormat } from "../Image";
import { InMemoryData, ResourceSource } from "../Io/IoCommon";
import { WindowLike } from "../Ui/Control/UiWindow";

export enum Byo2ImageDataType {
	Coded,
	Raw,
}

export class Byo2ImageCreation {
	DataType: Byo2ImageDataType = Byo2ImageDataType.Coded;
	Data: ResourceSource = null;
	Width: number = 0;
	Height: number = 0;
	Format: PixFormat = PixFormat.UNKNOWN;
}

export interface IByo2Image {
	new (window: WindowLike, cp: Byo2ImageCreation): IByo2Image;

	GetWidth(): number;
	GetHeight(): number;
	Upload(rc: Rect, data: InMemoryData): void;
}

export class Byo2Image extends (AveLib.Byo2Image as IByo2Image) {}
