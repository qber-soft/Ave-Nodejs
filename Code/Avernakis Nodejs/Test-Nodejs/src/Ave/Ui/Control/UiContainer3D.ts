import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";
import { Camera } from "../../Math/Camera";
import { DpiSize_2 } from "../UiCommon";
import { Vec3 } from "../../Math/Vector";
import { Quat } from "../../Math/Quaternion";
import { Mat44 } from "../../Math/Matrix";
import { PixFormat } from "../../Common";

export class Container3DMesh {
    Position: ArrayBuffer; // use Float32Array; [p0.x, p0.y, p0.z, p1.x, p1.y, p1.z, ...]
    Texcoord: ArrayBuffer; // use Float32Array; [t0.x, t0.y, t1.x, t1.y, ...]
    Index: ArrayBuffer; // use Uint16Array; [i0, i1, i2, i3, i4, i5, ...]
}

export class Container3DData {
    Geometry: Container3DMesh = new Container3DMesh();
    Render: Container3DMesh = new Container3DMesh();
}

export interface IContainer3DObject {
    SetData(d: Container3DData): boolean;
}

export interface IContainer3DControl<T extends IControl = IControl> {
    GetControl(): T;

    SetSize(v: DpiSize_2): IContainer3DControl;
    GetSize(): DpiSize_2;

    SetCustomObject(o: IContainer3DObject): IContainer3DObject;
    GetCustomObject(): IContainer3DObject;

    SetPosition(v: Vec3): IContainer3DControl;
    SetRotation(q: Quat): IContainer3DControl;
    SetScaling(v: Vec3): IContainer3DControl;

    Translate(v: Vec3): IContainer3DControl;
    Rotate(q: Quat): IContainer3DControl;
    Scale(v: Vec3): IContainer3DControl;
    Transform(m: Mat44): IContainer3DControl;

    GetPosition(): Vec3;
    GetRotation(): Quat;
    GetScaling(): Vec3;
    GetTransform(): Mat44;
    GetTransformT(): Mat44;
}

export interface IContainer3D extends IControl {
    new (window: Window): IContainer3D;

    ControlAdd(c: IControl): any;
    ControlRemove(c: IControl): IControl;
    ControlRemoveAll(): Container3D;

    GetContainerControl<T extends IControl>(c: T): IContainer3DControl<T>;

    SetContent2D(c: IControl): IControl;
    GetContent2D(): IControl;

    SetDepthFormat(nFormat: PixFormat): Container3D;
    GetDepthFormat(): Container3D;

    GetCamera(): Camera;

    CreateCustom3DObject(): IContainer3DObject;
}

export class Container3D extends (AveLib.UiContainer3D as IContainer3D) {
    private m_Child: Set<IControl>;
    private m_Content2D: IControl;

    constructor(window: Window) {
        super(window);
        this.m_Child = new Set();
    }

    ControlAdd<T extends IControl>(c: T) {
        this.m_Child.add(c);
        super.ControlAdd(c);

        const control = super.GetContainerControl(c);

        const OriginalGetPosition = control.GetPosition.bind(control);
        control.GetPosition = (): Vec3 =>
            Vec3.FromNative(OriginalGetPosition());

        const OriginalGetScaling = control.GetScaling.bind(control);
        control.GetScaling = (): Vec3 => Vec3.FromNative(OriginalGetScaling());

        return control;
    }

    ControlRemove(c: IControl) {
        this.m_Child.delete(c);
        return super.ControlRemove(c);
    }

    ControlRemoveAll() {
        this.m_Child.clear();
        return super.ControlRemoveAll();
    }

    SetContent2D(c: IControl) {
        this.m_Content2D = c;
        return super.SetContent2D(c);
    }
}
