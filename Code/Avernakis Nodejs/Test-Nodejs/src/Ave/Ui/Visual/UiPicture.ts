import { AveLib } from "../../AveLib";
import { IVisual } from "../UiVisual";
import { WindowLike } from "../Control/UiWindow";
import { StretchMode } from "../UiCommon";
import { Byo2Image } from "../../Ave";
import { ResourceSource } from "../../Io/IoCommon";

export interface IPicture extends IVisual {
	new (window: WindowLike): IPicture;

	SetStretchMode(nMode: StretchMode): Picture;
	GetStretchMode(): StretchMode;

	SetPicture(rs: ResourceSource): Picture;

	SetImage(img: Byo2Image): void;
}

export class Picture extends (AveLib.UiPicture as IPicture) {}
