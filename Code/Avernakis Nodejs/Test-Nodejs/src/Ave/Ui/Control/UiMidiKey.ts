import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";
import { Vec2, Vec4 } from "../../Math/Vector";
import {
    DpiSize_2,
    DpiSize,
    IconCache,
    DpiMargin,
    Rect,
    InputModifier,
} from "../UiCommon";

export type NoteIndex = number;
export type NoteRange = Vec2;

export class NoteIndexUtil {
    static C(nOctave: number) {
        return 12 * nOctave;
    }
    static D(nOctave: number) {
        return 12 * nOctave + 2;
    }
    static E(nOctave: number) {
        return 12 * nOctave + 4;
    }
    static F(nOctave: number) {
        return 12 * nOctave + 5;
    }
    static G(nOctave: number) {
        return 12 * nOctave + 7;
    }
    static A(nOctave: number) {
        return 12 * nOctave + 9;
    }
    static B(nOctave: number) {
        return 12 * nOctave + 11;
    }

    static Cx(nOctave: number) {
        return 12 * nOctave + 1;
    }
    static Dx(nOctave: number) {
        return 12 * nOctave + 3;
    }
    static Fx(nOctave: number) {
        return 12 * nOctave + 6;
    }
    static Gx(nOctave: number) {
        return 12 * nOctave + 8;
    }
    static Ax(nOctave: number) {
        return 12 * nOctave + 10;
    }

    static Db(nOctave: number) {
        return 12 * nOctave + 1;
    }
    static Eb(nOctave: number) {
        return 12 * nOctave + 3;
    }
    static Gb(nOctave: number) {
        return 12 * nOctave + 6;
    }
    static Ab(nOctave: number) {
        return 12 * nOctave + 8;
    }
    static Bb(nOctave: number) {
        return 12 * nOctave + 10;
    }

    private static get __WhiteArray() {
        return [
            true,
            false,
            true,
            false,
            true,
            true,
            false,
            true,
            false,
            true,
            false,
            true,
        ];
    }
    static IsWhiteKey(n: NoteIndex) {
        return NoteIndexUtil.__WhiteArray[n % 12];
    }

    private static get __WhiteCountArray() {
        return [1, 1, 2, 2, 3, 4, 5, 5, 6, 6, 7, 7];
    }
    static CountWhiteKey(v: NoteRange) {
        return (
            Math.max(0, Math.floor(v.y / 12) - Math.floor(v.x / 12) - 1) * 7 +
            8 -
            NoteIndexUtil.__WhiteCountArray[v.x % 12] +
            NoteIndexUtil.__WhiteCountArray[v.y % 12]
        );
    }

    private static get __KeyNameSharpArray() {
        return [
            "C",
            "C#",
            "D",
            "D#",
            "E",
            "F",
            "F#",
            "G",
            "G#",
            "A",
            "A#",
            "B",
        ];
    }
    static GetKeyNameSharp(n: NoteIndex) {
        return NoteIndexUtil.__KeyNameSharpArray[n % 12];
    }

    private static get __KeyNameFlatArray() {
        return [
            "C",
            "Db",
            "D",
            "Eb",
            "E",
            "F",
            "Gb",
            "G",
            "Ab",
            "A",
            "Bb",
            "B",
        ];
    }
    static GetKeyNameFlat(n: NoteIndex) {
        return NoteIndexUtil.__KeyNameSharpArray[n % 12];
    }

    static GetOctave(n: NoteIndex) {
        return Math.floor(n / 12);
    }
    static GetKey(n: NoteIndex) {
        return n % 12;
    }
    static FromKeyOctave(nKey: number, nOctave: number): NoteIndex {
        return 12 * nOctave + nKey;
    }

    private static get __FromName_note() {
        return [9, 11, 0, 2, 4, 5, 7];
    }
    private static get __FromName_type() {
        return [3, 2, 1, 3, 2, 1, 3];
    }
    private static get __A() {
        return "A".charCodeAt(0);
    }
    private static get __G() {
        return "g".charCodeAt(0);
    }
    private static get __a() {
        return "a".charCodeAt(0);
    }
    private static get __g() {
        return "g".charCodeAt(0);
    }
    static FromName(s: string): NoteIndex {
        if (s.length < 2 || s.length > 4) return -1;
        let n: NoteIndex = -1;
        let i: number = 0;
        let index: number = 0;
        const s0 = s.charCodeAt(i++);
        if (s0 >= NoteIndexUtil.__A && s0 <= NoteIndexUtil.__G) {
            index = s0 - NoteIndexUtil.__A;
            n = NoteIndexUtil.__FromName_note[index];
        } else if (s0 >= NoteIndexUtil.__a && s0 <= NoteIndexUtil.__g) {
            index = s0 - NoteIndexUtil.__a;
            n = NoteIndexUtil.__FromName_note[index];
        } else return -1;
        const s1 = s[i];
        if (s1 == "#") {
            if (1 & NoteIndexUtil.__FromName_type[index]) ++n;
            else return -1;
            ++i;
        } else if (s1 == "b") {
            if (2 & NoteIndexUtil.__FromName_type[index]) --n;
            else return -1;
            ++i;
        }
        if (i >= s.length) return -1;
        n += 12 * parseInt(s.substr(i));
        return n;
    }

    static get Invalid(): NoteIndex {
        return -1;
    } // Invalid NoteIndex
    static get C5(): NoteIndex {
        return 60;
    } // C5 is the middle C
    static get A5(): NoteIndex {
        return 60;
    } // A5 is 440Hz (tuning standard)

    static get Key88Range /**/(): NoteRange {
        return new Vec2(NoteIndexUtil.A(1), NoteIndexUtil.C(9));
    } // 88-key midi keyboard range
    static get Key76Range /**/(): NoteRange {
        return new Vec2(NoteIndexUtil.E(2), NoteIndexUtil.G(8));
    } // 76-key midi keyboard range
    static get Key61Range /**/(): NoteRange {
        return new Vec2(NoteIndexUtil.C(3), NoteIndexUtil.C(8));
    } // 61-key midi keyboard range
    static get Key54Range /**/(): NoteRange {
        return new Vec2(NoteIndexUtil.C(3), NoteIndexUtil.F(7));
    } // 54-key midi keyboard range
    static get Key49Range /**/(): NoteRange {
        return new Vec2(NoteIndexUtil.C(3), NoteIndexUtil.C(7));
    } // 49-key midi keyboard range
    static get Key37Range1 /**/(): NoteRange {
        return new Vec2(NoteIndexUtil.F(3), NoteIndexUtil.F(6));
    } // 37-key midi keyboard range type 1
    static get Key37Range2 /**/(): NoteRange {
        return new Vec2(NoteIndexUtil.C(4), NoteIndexUtil.C(7));
    } // 37-key midi keyboard range type 2
    static get Key36Range1 /**/(): NoteRange {
        return new Vec2(NoteIndexUtil.F(3), NoteIndexUtil.E(6));
    } // 36-key midi keyboard range type 1
    static get Key36Range2 /**/(): NoteRange {
        return new Vec2(NoteIndexUtil.C(4), NoteIndexUtil.B(6));
    } // 36-key midi keyboard range type 2
    static get Key32Range1 /**/(): NoteRange {
        return new Vec2(NoteIndexUtil.F(3), NoteIndexUtil.C(6));
    } // 32-key midi keyboard range type 1
    static get Key32Range2 /**/(): NoteRange {
        return new Vec2(NoteIndexUtil.C(4), NoteIndexUtil.G(6));
    } // 32-key midi keyboard range type 2
    static get Key25Range /**/(): NoteRange {
        return new Vec2(NoteIndexUtil.C(4), NoteIndexUtil.C(6));
    } // 25-key midi keyboard range
}

export class MidiKeyItem {
    Id: number;
    Note: NoteIndex;
    Velocity: number; // normalized
}

export interface IMidiKey extends IControl {
    new (window: Window): IMidiKey;

    SetRange(v: NoteRange): MidiKey; // range [v.x, v.y]
    GetRange(): NoteRange;

    SetMiddleOctave(nOctave: number): MidiKey;
    GetMiddleOctave(): number;

    SetUniformWidth(b: boolean): MidiKey;
    GetUniformWidth(): boolean;

    SetPerfectWidth(b: boolean): MidiKey;
    GetPerfectWidth(): boolean;

    SetWhiteWidthLimit(v: DpiSize_2): MidiKey; // range [v.x, v.y]
    GetWhiteWidthLimit(): DpiSize_2;

    SetWhiteWidth(nPixelWidth: DpiSize): MidiKey;
    GetWhiteWidth(): DpiSize;

    SetBlackSize(vPercentage: Vec2): MidiKey;
    GetBlackSize(): Vec2;

    SetOctaveLabel(b: boolean): MidiKey;
    GetOctaveLabel(): boolean;

    SetMultiplePress(b: boolean): MidiKey;
    GetMultiplePress(): boolean;

    GetOctaveKeyWidth(): number[]; // length is 12 for 12 keys in one octave

    MarkClear(): MidiKey;
    MarkSetLabel(nNote: NoteIndex, s: string): MidiKey;
    MarkGetLabel(nNote: NoteIndex): string;
    MarkSetLabelColor(nNote: NoteIndex, vColor: Vec4): MidiKey;
    MarkGetLabelColor(nNote: NoteIndex): Vec4;
    MarkSetColor(nNote: NoteIndex, vColor: Vec4): MidiKey;
    MarkGetColor(nNote: NoteIndex): Vec4;
    MarkSetIcon(nNote: NoteIndex, nIcon: IconCache): MidiKey;
    MarkGetIcon(nNote: NoteIndex): IconCache;

    MarkbarSetHeight(nHeight: DpiSize): MidiKey;
    MarkbarGetHeight(): DpiSize;
    MarkbarSetMargin(margin: DpiMargin): MidiKey;
    MarkbarGetMargin(): DpiMargin;
    MarkbarSetColor(nNote: NoteIndex, vColor: Vec4): MidiKey;
    MarkbarGetColor(nNote: NoteIndex): Vec4;
    MarkbarSetColorHeight(nNote: NoteIndex, f: number): MidiKey; // f in [0, 1]
    MarkbarGetColorHeight(nNote: NoteIndex): number;
    MarkbarSetIcon(nNote: NoteIndex, nIcon: IconCache): MidiKey;
    MarkbarGetIcon(nNote: NoteIndex): IconCache;

    RangeClear(): MidiKey;
    RangeAdd(vRange: NoteRange, vColor: Vec4): MidiKey;

    KeyHitTest(pt: Vec2): number;
    KeyGetRect(nKey: NoteIndex): Rect;
    KeySetPress(nKey: NoteIndex, bPress: boolean): MidiKey;
    KeyGetPress(nKey: NoteIndex): boolean;
    KeyClearPress(): MidiKey;

    OnClick(
        fn: (
            sender: MidiKey,
            key: MidiKeyItem,
            bIsFirstPress: boolean,
            nModifier: InputModifier
        ) => void
    ): MidiKey;
    OnDrop(
        fn: (
            sender: MidiKey,
            key: MidiKeyItem,
            bIsLastRelease: boolean,
            nModifier: InputModifier
        ) => void
    ): MidiKey;
}

export class MidiKey extends (AveLib.UiMidiKey as IMidiKey) {
    KeyGetRect(nKey: NoteIndex): Rect {
        return Rect.FromNative(super.KeyGetRect(nKey));
    }

    GetBlackSize(): Vec2 {
        return Vec2.FromNative(super.GetBlackSize());
    }

    MarkGetLabelColor(nNote: NoteIndex): Vec4 {
        return Vec4.FromNative(super.MarkGetLabelColor(nNote));
    }

    MarkGetColor(nNote: NoteIndex): Vec4 {
        return Vec4.FromNative(super.MarkGetColor(nNote));
    }

    MarkbarGetColor(nNote: NoteIndex): Vec4 {
        return Vec4.FromNative(super.MarkbarGetColor(nNote));
    }
}
