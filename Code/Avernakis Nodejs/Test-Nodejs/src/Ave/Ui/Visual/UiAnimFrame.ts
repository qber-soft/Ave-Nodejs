import { AveLib } from "../../AveLib";
import { IControl } from "../UiControl";
import { ResourceSource, StretchMode } from "../UiCommon";
import { Vec2 } from "../../Math/Vector";
import { Window } from "../Control/UiWindow";

export class AnimFrameInfo {
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

export class AnimFrame extends (AveLib.UiAnimFrame as IAnimFrame) {}
