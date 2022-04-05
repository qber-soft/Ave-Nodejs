import { Window } from "../Ave";
import { AveLib } from "../AveLib";

// prettier-ignore
export enum Byo2FontFlag {
    Normal    /**/ = 0x0000,
    Bold      /**/ = 0x0001,
    Italic    /**/ = 0x0002,
    Underline /**/ = 0x0004,
    StrikeOut /**/ = 0x0008,
}

export class Byo2FontCreation {
    // FontName[:File][/FontName2[:File2][...]]
    // Example1: Meiryo UI/Microsoft YaHei UI
    // Example2: Noto Sans Mono CJK JP Regular:c:\NotoSansMonoCJKjp-Regular.otf/Segoe UI
    // Example3: Noto Sans Mono CJK JP Regular:\usr\local\NotoSansMonoCJKjp-Regular.otf
    Name: string;
    Size: number = 9;
    Flag: Byo2FontFlag = Byo2FontFlag.Normal;
}

export enum Byo2ReadingDirection {
    LeftToRight,
    RightToLeft,
    TopToBottom,
    BottomToTop,
};

export enum Byo2FlowDirection {
    TopToBottom,
    BottomToTop,
    LeftToRight,
    RightToLeft,
};

export interface IByo2Font {
    new(window: Window, cp: Byo2FontCreation): IByo2Font;

    GetAscent(): number;
    GetDescent(): number;
    GetHeight(): number;
    GetWidth(): number;
    GetLeadingExternal(): number;
    GetLeadingInternal(): number;
    SetReadingDirection(n: Byo2ReadingDirection): void;
    GetReadingDirection(): Byo2ReadingDirection;
    SetFlowDirection(n: Byo2FlowDirection): void;
    GetFlowDirection(): Byo2FlowDirection;

    Measure(s: string): number[];
}

export class Byo2Font extends (AveLib.Byo2Font as IByo2Font) { }
