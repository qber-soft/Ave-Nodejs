import { AveLib } from "../AveLib";
import { Box } from "./Box";
import { Frustum } from "./Frustum";
import { Mat34, Mat44 } from "./Matrix";
import { Quat } from "./Quaternion";
import { Vec3, Vec4 } from "./Vector";

export enum ProjectionType {
    Perspective, // Default
    Orthographic,
    Customization,
}

export interface ICamera {
    new (): ICamera;

    // ----------------------------------------------------------------------------------------------------
    // Common
    CopyFrom(r: ICamera): void;

    SetProjectionType(r: ProjectionType): void;
    GetProjectionType(): ProjectionType;

    SetPosition(v: Vec3): void;
    GetPosition(): Vec3;

    SetRotation(v: Quat): void;
    GetRotation(): Quat;

    // ----------------------------------------------------------------------------------------------------
    // Perspective & Orthographic

    SetZNear(f: number): void;
    GetZNear(): number;

    SetZFar(f: number): void;
    GetZFar(): number;

    SetDirection(v: Vec3): void;
    GetDirection(): Vec3;

    SetTarget(v: Vec3): void;

    Roll(f: number): void;
    Yaw(f: number): void;
    Pitch(f: number): void;
    RotateAngle(v: Vec3, f: number): void;

    // ----------------------------------------------------------------------------------------------------
    // Perspective

    SetFovY(f: number): void;
    GetFovY(): number;

    SetAspect(f: number): void;
    GetAspect(): number;

    GetFrustum(): Frustum;

    // ----------------------------------------------------------------------------------------------------
    // Orthographic

    SetOrthoRange(vLRBT: Vec4): void; // x=left, y=right, z=bottom, w=top
    GetOrthoRange(): Vec4;

    GetOrthoBox(): Box;

    // ----------------------------------------------------------------------------------------------------
    // Customization

    SetCustomProjection(mProj: Mat44): void;

    // ----------------------------------------------------------------------------------------------------
    // Get methods
    GetViewUp(): Vec3;
    GetViewRight(): Vec3;
    GetView(): Mat44;
    GetView33(): Mat34;
    GetView33_4(): Mat44;
    GetViewT(): Mat44;
    GetViewT33(): Mat34;
    GetViewT33_4(): Mat44;
    GetProjection(): Mat44;
    GetProjectionT(): Mat44;
    GetViewProjection(): Mat44;
    GetViewProjectionT(): Mat44;
}

export class Camera extends (AveLib.CoCamera as ICamera) {
    GetPosition(): Vec3 {
        return Vec3.FromNative(super.GetPosition());
    }

    GetDirection(): Vec3 {
        return Vec3.FromNative(super.GetDirection());
    }

    GetOrthoRange(): Vec4 {
        return Vec4.FromNative(super.GetOrthoRange());
    }

    GetViewUp(): Vec3 {
        return Vec3.FromNative(super.GetViewUp());
    }

    GetViewRight(): Vec3 {
        return Vec3.FromNative(super.GetViewRight());
    }
}
