import { AveLib } from "../../AveLib";
import { IControl } from "../UiControl";
import { Vec2 } from "../../Math/Vector";
import { Window } from "../Control/UiWindow";
import { ResourceSource } from "../../Io/IoCommon";
import { StretchMode } from "../UiCommon";

export class AnimFrameInfo {
	static FromNative(info: AnimFrameInfo) {
		info.SizePerFrame = Vec2.FromNative(info.SizePerFrame);
		return info;
	}
	SizePerFrame: Vec2;
	FramePerRow: number;
	FrameCount: number;
	FrameRate: number;
}

export interface IAnimFrame extends IControl {
	new (window: Window): IAnimFrame;

	SetStretchMode(n: StretchMode): AnimFrame;
	GetStretchMode(): StretchMode;

	SetFrameInfo(info: AnimFrameInfo): AnimFrame;
	GetFrameInfo(): AnimFrameInfo;

	SetPicture(p: ResourceSource): AnimFrame;

	Play(): AnimFrame;
	Stop(): AnimFrame;

	SetPlayPosition(nFrameIndex: number): AnimFrame;
	GetPlayPosition(): number;

	IsPlaying(): boolean;
}

export class AnimFrame extends (AveLib.UiAnimFrame as IAnimFrame) {
	GetFrameInfo(): AnimFrameInfo {
		return AnimFrameInfo.FromNative(super.GetFrameInfo());
	}
}
