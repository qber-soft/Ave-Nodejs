import { AveLib } from "../../AveLib";
import { IVisual } from "../UiVisual";
import { Window } from "../Control/UiWindow";
import { StretchMode, ResourceSource } from "../UiCommon";

export interface IPicture extends IVisual {
    new (window: Window): IPicture;

    SetStretchMode(nMode: StretchMode): Picture;
    GetStretchMode(): StretchMode;

    SetPicture(rs: ResourceSource): Picture;
}

export class Picture extends (AveLib.UiPicture as IPicture) {}
