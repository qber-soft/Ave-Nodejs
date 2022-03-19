import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { DpiSize, StringKey } from "../UiCommon";
import { Window } from "./UiWindow";

export enum ComboBoxMode {
    DropDown,
    DropDownEdit,
    ListEdit,
}

export interface IComboBox extends IControl {
    new (window: Window, key?: StringKey): IComboBox;

    Append(s: string): ComboBox;
    Insert(s: string, nInsertBefore: number): ComboBox;
    Remove(nIndex: number): boolean;
    Clear(): ComboBox;
    Select(nIndex: number): ComboBox;
    Sort(bAsc: boolean, bCaseInsensitive: boolean): ComboBox;
    Find(
        s: string,
        nIndexStart: number,
        bExact: boolean,
        bCaseInsensitive: boolean
    ): number;
    Set(nIndex: number, s: string): boolean;
    Get(nIndex: number): string;
    GetCount(): number;
    GetSelection(): number;

    SetCount(nCount: number): ComboBox;

    SetMode(nMode: ComboBoxMode): ComboBox;
    GetMode(): ComboBoxMode;

    SetDropHeight(n: DpiSize): ComboBox;
    GetDropHeight(): DpiSize;

    SetFindExact(b: boolean): ComboBox;
    GetFindExact(): boolean;

    SetFindCaseInsensitive(b: boolean): ComboBox;
    GetFindCaseInsensitive(): boolean;

    SetBorder(b: boolean): ComboBox;
    GetBorder(): boolean;

    OnSelectionChange(fn: (sender: ComboBox) => void): ComboBox;
}

export class ComboBox extends (AveLib.UiComboBox as IComboBox) {
    Append(...s: string[]) {
        s.forEach((e) => super.Append(e));
        return this;
    }
}
