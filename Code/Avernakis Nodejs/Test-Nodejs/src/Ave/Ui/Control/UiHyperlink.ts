import { AveLib } from "../../AveLib";
import { AlignType } from "../UiCommon";
import { Vec4 } from "../../Math/Vector";
import { IVisual } from "../UiVisual";
import { Window } from "../Control/UiWindow";

export enum HyperlinkUnderline {
    Always,
    Active,
    None,
}

export interface IHyperlink extends IVisual {
    new (window: Window, key?: string | number): IHyperlink;

    SetText(s: string): Hyperlink;
    GetText(): string;
    GetTextValid(): boolean;

    SetAlignHorz(n: AlignType): Hyperlink;
    GetAlignHorz(): AlignType;

    SetAlignVert(n: AlignType): Hyperlink;
    GetAlignVert(): AlignType;

    SetBackColor(vColor: Vec4): Hyperlink;
    GetBackColor(): Vec4;

    SetWrappable(b: boolean): Hyperlink;
    GetWrappable(): boolean;

    SetUnderline(b: HyperlinkUnderline): Hyperlink;
    GetUnderline(): HyperlinkUnderline;

    OnClick(fn: (sender: Hyperlink, nId: number) => void): Hyperlink;
}

export class Hyperlink extends (AveLib.UiHyperlink as IHyperlink) {}
