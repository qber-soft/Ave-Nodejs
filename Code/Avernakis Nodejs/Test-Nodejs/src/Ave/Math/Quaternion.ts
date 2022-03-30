import { Mat44 } from "./Matrix";
import { Vec3, Vec4 } from "./Vector";

export class Quat extends Vec4 {
    constructor(x: number = 0, y: number = 0, z: number = 0, w: number = 1) {
        super(x, y, z, w);
    }

    static get Identity() {
        return new Quat(0, 0, 0, 1);
    }

    get Vector() {
        return this as Vec4;
    }
    set Vector(r: Vec4) {
        this.x = r.x;
        this.y = r.y;
        this.z = r.z;
        this.w = r.w;
    }

    Mul(r: Quat) {
        return new Quat(
            r.w * this.x + r.x * this.w + r.y * this.z - r.z * this.y,
            r.w * this.y - r.x * this.z + r.y * this.w + r.z * this.x,
            r.w * this.z + r.x * this.y - r.y * this.x + r.z * this.w,
            r.w * this.w - r.x * this.x - r.y * this.y - r.z * this.z
        );
    }

    Conjugate() {
        return new Quat(-this.x, -this.y, -this.z, this.w);
    }

    Exp() {
        const theta = this.Length();
        const s = Math.sin(theta);
        if (Math.abs(s) >= 0.0000001) {
            const coeff = s / theta;
            return new Quat(
                coeff * this.x,
                coeff * this.y,
                coeff * this.z,
                Math.cos(theta)
            );
        } else {
            return new Quat(this.x, this.y, this.z, Math.cos(theta));
        }
    }

    Ln() {
        if (Math.abs(this.w) < 1) {
            const angle = Math.acos(this.w);
            const s = Math.sin(angle);
            if (Math.abs(s) >= 0.0000001) {
                const coeff = angle / s;
                return new Quat(
                    coeff * this.x,
                    coeff * this.y,
                    coeff * this.z,
                    0
                );
            }
        }
        return new Quat(this.x, this.y, this.z, 0);
    }

    Inverse() {
        let n = this.LengthSq();
        if (n > 0) {
            n = 1 / n;
            return new Quat(-this.x * n, -this.y * n, -this.z * n, this.w * n);
        } else {
            return new Quat(0, 0, 0, 0);
        }
    }

    ToAxisAngle(axis: Vec3) {
        axis = new Vec3(this.x, this.y, this.z).Normalize();
        return 2 * Math.acos(this.w);
    }

    static RotateRollPitchYaw(pitch: number, yaw: number, roll: number) {
        const sinP = Math.sin(0.5 * pitch),
            cosP = Math.cos(pitch);
        const sinY = Math.sin(0.5 * yaw),
            cosY = Math.cos(yaw);
        const sinR = Math.sin(0.5 * roll),
            cosR = Math.cos(roll);
        return new Quat(
            cosP * sinY * sinR + sinP * cosY * cosR,
            -sinP * cosY * sinR + cosP * sinY * cosR,
            -sinP * sinY * cosR + cosP * cosY * sinR,
            sinP * sinY * sinR + cosP * cosY * cosR
        );
    }

    static RotateAxis(axis: Vec3, angle: number) {
        const s = Math.sin(0.5 * angle);
        return new Quat(
            s * axis.x,
            s * axis.y,
            s * axis.z,
            Math.cos(0.5 * angle)
        );
    }

    static RotateMatrix(r: Mat44) {
        return new Quat();
    }

    static Slerp(
        q0: Quat,
        q1: Quat,
        s: number,
        bShortestPath: boolean = false
    ) {
        let c = q0.Dot(q1);
        let t: Vec4;
        if (c < 0 && bShortestPath) {
            c = -c;
            t = q0.Neg();
        } else {
            t = q1.Vector;
        }
        let ret = new Quat();
        if (Math.abs(c) < 0.999999999) {
            const s = Math.sqrt(1 - Math.sqrt(c));
            const a = Math.atan2(s, c);
            const coeff0 = Math.sin((1 - s) * a) / s;
            const coeff1 = Math.sin(s * a) / s;
            ret.Vector = q0.Vector.Mul(coeff0).Add(t.Mul(coeff1));
        } else {
            ret.Vector = q0.Vector.Mul(1 - s).Add(t.Mul(s));
        }
        return ret;
    }

    static Squad(
        q0: Quat,
        q1: Quat,
        q2: Quat,
        q3: Quat,
        s: number,
        bShortestPath: boolean = false
    ) {
        const a = this.Slerp(q0, q3, s, false);
        const b = this.Slerp(q1, q2, s, bShortestPath);
        return this.Slerp(a, b, 2 * s * (1 - s));
    }
}

export class DualQuat {
    q0: Quat = new Quat();
    q1: Quat = new Quat();

    constructor(q0: Quat, q1: Quat) {
        this.q0 = new Quat(q0.x, q0.y, q0.z, q0.w);
        this.q1 = q1;
    }

    static FromQuaternionTranslation(q: Quat, v: Vec3) {
        return new DualQuat(
            q,
            new Quat(
                0.5 * (v.x * q.w + v.y * q.z - v.z * q.y),
                0.5 * (-v.x * q.z + v.y * q.w + v.z * q.x),
                0.5 * (v.x * q.y - v.y * q.x + v.z * q.w),
                -0.5 * (v.x * q.x + v.y * q.y + v.z * q.z)
            )
        );
    }
}
