import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { WindowLike } from "./UiWindow";
import { Vec2 } from "../../Math/Vector";
import { Hotkey } from "../UiCommon";

export enum TextBoxLimitMode {
	Char, // A UTF-16 char
	Cluster, // A real completed char, for example, for '𪚥', it has two UTF-16 chars and 1 cluster
}

export enum TextBoxKeyInput {
	None /**/ = 0x00000,
	AllowSingleKey /**/ = 0x00001,
	AllowCtrl /**/ = 0x00002,
	AllowShift /**/ = 0x00004,
	AllowMenu /**/ = 0x00008,
	AllowSys /**/ = 0x00010,
	AllowCtrlShift /**/ = 0x00020,
	AllowCtrlMenu /**/ = 0x00040,
	AllowCtrlSys /**/ = 0x00080,
	AllowShiftMenu /**/ = 0x00100,
	AllowShiftSys /**/ = 0x00200,
	AllowMenuSys /**/ = 0x00400,
	AllowCtrlShiftMenu /**/ = 0x00800,
	AllowCtrlShiftSys /**/ = 0x01000,
	AllowCtrlMenuSys /**/ = 0x02000,
	AllowShiftMenuSys /**/ = 0x04000,
	AllowCtrlShiftMenuSys /**/ = 0x08000,
	AllowSingleModifier /**/ = 0x10000,
	AllowAll /**/ = 0x0ffff,
	AllowLocal /**/ = 0x0096f,
}

export enum TextBoxChangeReason {
	Input,
	UpDown,
	Reset,
	Spin,
	SpinCommit,
	SpinCancel,
}

export interface ITextBox extends IControl {
	new (window: WindowLike, key?: string | number): ITextBox;

	SetText(s: string): TextBox;
	GetText(): string;

	SetCue(s: string): TextBox;
	GetCue(): string;

	SetLimit(s: number): TextBox;
	GetLimit(): number;

	SetLimitMode(s: TextBoxLimitMode): TextBox;
	GetLimitMode(): TextBoxLimitMode;

	SetNumeric(s: number): TextBox;
	GetNumeric(): number;

	SetRange(fMin: number, fMax: number): TextBox;
	GetRange(): Vec2;

	SetStep(f: number): TextBox;
	GetStep(): number;

	SetDefault(f: number): TextBox;
	GetDefault(): number;

	SetValue(f: number): TextBox;
	GetValue(): number;

	SetInvalid(s: string): TextBox;
	GetInvalid(): string;

	SetValid(s: string): TextBox;
	GetValid(): string;

	SetReadOnly(s: boolean): TextBox;
	GetReadOnly(): boolean;

	SetPassword(s: string): TextBox; // Only use first char, don't support characters require UTF-16 surrogates
	GetPassword(): string;

	SetIme(n: boolean): TextBox;
	GetIme(): boolean;

	SetRememberCaret(n: boolean): TextBox;
	GetRememberCaret(): boolean;

	SetHideSelection(n: boolean): TextBox;
	GetHideSelection(): boolean;

	SetBorder(n: boolean): TextBox;
	GetBorder(): boolean;

	SetForceCue(n: boolean): TextBox;
	GetForceCue(): boolean;

	SetKeyInputMode(n: TextBoxKeyInput): TextBox;
	GetKeyInputMode(): TextBoxKeyInput;

	SetKey(n: Hotkey): TextBox;
	GetKey(): Hotkey;

	SelectionSet(nStart: number, nEnd: number): TextBox;
	SelectionGet(): Vec2;
	SelectionGetText(): string;
	SelectionReplace(s: string): TextBox;

	GetCaretPos(): Vec2;

	OnChange(fn: (sender: TextBox, nReason: TextBoxChangeReason) => void): TextBox;
	OnSpinStart(fn: (sender: TextBox) => void): TextBox;
	OnSpinEnd(fn: (sender: TextBox, bCanceled: boolean) => void): TextBox;
	OnSpin(fn: (sender: TextBox) => void): TextBox;
}

export class TextBox extends (AveLib.UiTextBox as ITextBox) {
	SelectionGet(): Vec2 {
		return Vec2.FromNative(super.SelectionGet());
	}

	GetRange(): Vec2 {
		return Vec2.FromNative(super.GetRange());
	}

	GetCaretPos(): Vec2 {
		return Vec2.FromNative(super.GetCaretPos());
	}
}
