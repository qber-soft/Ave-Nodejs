import { AveLib } from "../../AveLib";
import { IVisual } from "../UiVisual";
import { WindowLike } from "../Control/UiWindow";
import { StretchMode } from "../UiCommon";
import { Byo2Image } from "../../Ave";
import { ResourceSource } from "../../Io/IoCommon";
import { DrawImageFilter } from "../UiPainter";
import { AnimationInfo, AveImage } from "../../Image";

export interface IPicture extends IVisual {
	new(window: WindowLike): IPicture;

	SetStretchMode(nMode: StretchMode): Picture;
	GetStretchMode(): StretchMode;

	SetImageFilter(nFilter: DrawImageFilter): Picture;
	GetImageFilter(): DrawImageFilter;

	SetPicture(rs: ResourceSource): Picture;
	SetImageData(img: AveImage): Picture;
	SetImage(img: Byo2Image): Picture;

	GetAnimationInfo(): AnimationInfo;
	GetDuration(): number;

	Play(): Picture;
	Stop(): Picture;
	IsPlaying(): boolean;

	SetPlayPosition(fTime: number): Picture;
	GetPlayPosition(): number;

	SetPlayFrame(nFrame: number): Picture;
	GetPlayFrame(): number;
}

export class Picture extends (AveLib.UiPicture as IPicture) { }
