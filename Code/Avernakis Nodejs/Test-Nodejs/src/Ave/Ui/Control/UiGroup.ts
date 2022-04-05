import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { IVisual } from "../UiVisual";
import { Window } from "./UiWindow";
import { Vec2 } from "../../Math/Vector";

export interface IGroup extends IControl {
    new (window: Window, key?: string | number): IGroup;

    SetText(s: string): Group;
    GetText(): string;

    SetHeader(c: IControl): IControl;
    GetHeader(): IControl;

    SetContent(c: IControl): IControl;
    GetContent(): IControl;

    GetContentSize(): Vec2;
}

export class Group extends (AveLib.UiGroup as IGroup) {
    private m_Header: IControl;
    private m_Content: IVisual;

    SetHeader(c: IControl) {
        this.m_Header = c;
        return super.SetHeader(c);
    }

    SetContent(c: IControl) {
        this.m_Content = c;
        return super.SetContent(c);
    }

    GetContentSize(): Vec2 {
        return Vec2.FromNative(super.GetContentSize());
    }
}
