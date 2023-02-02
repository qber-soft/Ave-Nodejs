import { Plane } from "./Plane";
import { DualQuat, Quat } from "./Quaternion";
import { Vec2, Vec3, Vec4 } from "./Vector";

export class Mat32 {
	_11: number = 1;
	_12: number = 0;
	_21: number = 0;
	_22: number = 1;
	_31: number = 0;
	_32: number = 0;

	constructor(a: Mat32 | Vec2 | number = 1, b: Vec2 | number = 0, c: Vec2 | number = 0, _22: number = 1, _31: number = 0, _32: number = 0) {
		if (a instanceof Mat32) {
			this._11 = a._11;
			this._12 = a._12;
			this._21 = a._21;
			this._22 = a._22;
			this._31 = a._31;
			this._32 = a._32;
		} else if (a instanceof Vec2 && b instanceof Vec2 && c instanceof Vec2) {
			this._11 = a.x;
			this._12 = a.y;
			this._21 = b.x;
			this._22 = b.y;
			this._31 = c.x;
			this._32 = c.y;
		} else if (typeof a == "number" && typeof b == "number" && typeof c == "number") {
			this._11 = a;
			this._12 = b;
			this._21 = c;
			this._22 = _22;
			this._31 = _31;
			this._32 = _32;
		}
	}

	static FromNative(m: Mat32) {
		return new Mat32(m._11, m._12, m._21, m._22, m._31, m._32);
	}

	static get Identity() {
		return new Mat32();
	}

	static Translation(x: number = 0, y: number = 0) {
		return new Mat32(1, 0, 0, 1, x, y);
	}

	static Scaling(x: number = 1, y: number = 1, cx: number = 0, cy: number = 0) {
		return new Mat32(x, 0, 0, y, cx - x * cx, cy - y * cy);
	}

	static Rotation(f: number, cx: number = 0, cy: number = 0) {
		const s = Math.sin(f),
			c = Math.cos(f);
		return new Mat32(c, s, -s, c, cx - cx * c + cy * s, cy - cx * s - cy * c);
	}

	static Skew(x: number = 0, y: number = 0, cx: number = 0, cy: number = 0) {
		const tx = Math.tan(x),
			ty = Math.tan(y);
		return new Mat32(1, ty, tx, 1, -tx * cy, -ty * cx);
	}

	Equal(r: Mat32) {
		return this._11 == r._11 && this._12 == r._12 && this._21 == r._21 && this._22 == r._22 && this._31 == r._31 && this._32 == r._32;
	}

	Mul(r: Mat32) {
		return new Mat32(this._11 * r._11 + this._12 * r._21, this._11 * r._12 + this._12 * r._22, this._21 * r._11 + this._22 * r._21, this._21 * r._12 + this._22 * r._22, this._31 * r._11 + this._32 * r._21 + r._31, this._31 * r._12 + this._32 * r._22 + r._32);
	}
}

export class Mat43 {
	_11: number = 1;
	_12: number = 0;
	_13: number = 0;
	_21: number = 0;
	_22: number = 1;
	_23: number = 0;
	_31: number = 0;
	_32: number = 0;
	_33: number = 1;
	_41: number = 0;
	_42: number = 0;
	_43: number = 0;

	static get Identity() {
		return new Mat43();
	}
}

export class Mat34 {
	_11: number = 1;
	_12: number = 0;
	_13: number = 0;
	_14: number = 0;
	_21: number = 0;
	_22: number = 1;
	_23: number = 0;
	_24: number = 0;
	_31: number = 0;
	_32: number = 0;
	_33: number = 1;
	_34: number = 0;

	static get Identity() {
		return new Mat34();
	}
}

export class Mat44 {
	_11: number = 1;
	_12: number = 0;
	_13: number = 0;
	_14: number = 0;
	_21: number = 0;
	_22: number = 1;
	_23: number = 0;
	_24: number = 0;
	_31: number = 0;
	_32: number = 0;
	_33: number = 1;
	_34: number = 0;
	_41: number = 0;
	_42: number = 0;
	_43: number = 0;
	_44: number = 1;

	static get Identity() {
		return new Mat44();
	}

	constructor(a: Mat44 | Vec4 | number = 1, b: Vec4 | number = 0, c: Vec4 | number = 0, d: Vec4 | number = 0, _21: number = 0, _22: number = 1, _23: number = 0, _24: number = 0, _31: number = 0, _32: number = 0, _33: number = 1, _34: number = 0, _41: number = 0, _42: number = 0, _43: number = 0, _44: number = 1) {
		if (a instanceof Mat44) {
			this._11 = a._11;
			this._12 = a._12;
			this._13 = a._13;
			this._14 = a._14;
			this._21 = a._21;
			this._22 = a._22;
			this._23 = a._23;
			this._24 = a._24;
			this._31 = a._31;
			this._32 = a._32;
			this._33 = a._33;
			this._34 = a._34;
			this._41 = a._41;
			this._42 = a._42;
			this._43 = a._43;
			this._44 = a._44;
		} else if (a instanceof Vec4 && b instanceof Vec4 && c instanceof Vec4 && d instanceof Vec4) {
			this._11 = a.x;
			this._12 = a.y;
			this._13 = a.z;
			this._14 = a.w;
			this._21 = b.x;
			this._22 = b.y;
			this._23 = b.z;
			this._24 = b.w;
			this._31 = c.x;
			this._32 = c.y;
			this._33 = c.z;
			this._34 = c.w;
			this._41 = d.x;
			this._42 = d.y;
			this._43 = d.z;
			this._44 = d.w;
		} else if (typeof a == "number" && typeof b == "number" && typeof c == "number" && typeof d == "number") {
			this._11 = a;
			this._12 = b;
			this._13 = c;
			this._14 = d;
			this._21 = _21;
			this._22 = _22;
			this._23 = _23;
			this._24 = _24;
			this._31 = _31;
			this._32 = _32;
			this._33 = _33;
			this._34 = _34;
			this._41 = _41;
			this._42 = _42;
			this._43 = _43;
			this._44 = _44;
		}
	}

	get r(): Vec4[] {
		return [new Vec4(this._11, this._12, this._13, this._14), new Vec4(this._21, this._22, this._23, this._24), new Vec4(this._31, this._32, this._33, this._34), new Vec4(this._41, this._42, this._43, this._44)];
	}

	set r(v: Vec4[]) {
		this._11 = v[0].x;
		this._12 = v[0].y;
		this._13 = v[0].z;
		this._14 = v[0].w;
		this._21 = v[1].x;
		this._22 = v[1].y;
		this._23 = v[1].z;
		this._24 = v[1].w;
		this._31 = v[2].x;
		this._32 = v[2].y;
		this._33 = v[2].z;
		this._34 = v[2].w;
		this._41 = v[3].x;
		this._42 = v[3].y;
		this._43 = v[3].z;
		this._44 = v[3].w;
	}

	get d(): number[] {
		return [this._11, this._12, this._13, this._14, this._21, this._22, this._23, this._24, this._31, this._32, this._33, this._34, this._41, this._42, this._43, this._44];
	}

	set d(r: number[]) {
		this._11 = r[0];
		this._12 = r[1];
		this._13 = r[2];
		this._14 = r[3];
		this._21 = r[4];
		this._22 = r[5];
		this._23 = r[6];
		this._24 = r[7];
		this._31 = r[8];
		this._32 = r[9];
		this._33 = r[10];
		this._34 = r[11];
		this._41 = r[12];
		this._42 = r[13];
		this._43 = r[14];
		this._44 = r[15];
	}

	get r0() {
		return new Vec4(this._11, this._12, this._13, this._14);
	}
	get r1() {
		return new Vec4(this._21, this._22, this._23, this._24);
	}
	get r2() {
		return new Vec4(this._31, this._32, this._33, this._34);
	}
	get r3() {
		return new Vec4(this._41, this._42, this._43, this._44);
	}

	set r0(v: Vec4) {
		this._11 = v.x;
		this._12 = v.y;
		this._13 = v.z;
		this._14 = v.w;
	}
	set r1(v: Vec4) {
		this._21 = v.x;
		this._22 = v.y;
		this._23 = v.z;
		this._24 = v.w;
	}
	set r2(v: Vec4) {
		this._31 = v.x;
		this._32 = v.y;
		this._33 = v.z;
		this._34 = v.w;
	}
	set r3(v: Vec4) {
		this._41 = v.x;
		this._42 = v.y;
		this._43 = v.z;
		this._44 = v.w;
	}

	Equal(r: Mat44) {
		return this._11 == r._11 && this._12 == r._12 && this._13 == r._13 && this._14 == r._14 && this._21 == r._21 && this._22 == r._22 && this._23 == r._23 && this._24 == r._24 && this._31 == r._31 && this._32 == r._32 && this._33 == r._33 && this._34 == r._34 && this._41 == r._41 && this._42 == r._42 && this._43 == r._43 && this._44 == r._44;
	}

	Mul(r: Mat44) {
		return new Mat44(this._11 * r._11 + this._12 * r._21 + this._13 * r._31 + this._14 * r._41, this._11 * r._12 + this._12 * r._22 + this._13 * r._32 + this._14 * r._42, this._11 * r._13 + this._12 * r._23 + this._13 * r._33 + this._14 * r._43, this._11 * r._14 + this._12 * r._24 + this._13 * r._34 + this._14 * r._44, this._21 * r._11 + this._22 * r._21 + this._23 * r._31 + this._24 * r._41, this._21 * r._12 + this._22 * r._22 + this._23 * r._32 + this._24 * r._42, this._21 * r._13 + this._22 * r._23 + this._23 * r._33 + this._24 * r._43, this._21 * r._14 + this._22 * r._24 + this._23 * r._34 + this._24 * r._44, this._31 * r._11 + this._32 * r._21 + this._33 * r._31 + this._34 * r._41, this._31 * r._12 + this._32 * r._22 + this._33 * r._32 + this._34 * r._42, this._31 * r._13 + this._32 * r._23 + this._33 * r._33 + this._34 * r._43, this._31 * r._14 + this._32 * r._24 + this._33 * r._34 + this._34 * r._44, this._41 * r._11 + this._42 * r._21 + this._43 * r._31 + this._44 * r._41, this._41 * r._12 + this._42 * r._22 + this._43 * r._32 + this._44 * r._42, this._41 * r._13 + this._42 * r._23 + this._43 * r._33 + this._44 * r._43, this._41 * r._14 + this._42 * r._24 + this._43 * r._34 + this._44 * r._44);
	}

	Inverse() {
		const m00 = this._11,
			m01 = this._12,
			m02 = this._13,
			m03 = this._14;
		const m10 = this._21,
			m11 = this._22,
			m12 = this._23,
			m13 = this._24;
		const m20 = this._31,
			m21 = this._32,
			m22 = this._33,
			m23 = this._34;
		const m30 = this._41,
			m31 = this._42,
			m32 = this._43,
			m33 = this._44;

		let v0 = m20 * m31 - m21 * m30;
		let v1 = m20 * m32 - m22 * m30;
		let v2 = m20 * m33 - m23 * m30;
		let v3 = m21 * m32 - m22 * m31;
		let v4 = m21 * m33 - m23 * m31;
		let v5 = m22 * m33 - m23 * m32;

		const t00 = +(v5 * m11 - v4 * m12 + v3 * m13);
		const t10 = -(v5 * m10 - v2 * m12 + v1 * m13);
		const t20 = +(v4 * m10 - v2 * m11 + v0 * m13);
		const t30 = -(v3 * m10 - v1 * m11 + v0 * m12);

		const invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

		const d00 = t00 * invDet;
		const d10 = t10 * invDet;
		const d20 = t20 * invDet;
		const d30 = t30 * invDet;

		const d01 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		const d11 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		const d21 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		const d31 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		v0 = m10 * m31 - m11 * m30;
		v1 = m10 * m32 - m12 * m30;
		v2 = m10 * m33 - m13 * m30;
		v3 = m11 * m32 - m12 * m31;
		v4 = m11 * m33 - m13 * m31;
		v5 = m12 * m33 - m13 * m32;

		const d02 = +(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		const d12 = -(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		const d22 = +(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		const d32 = -(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		v0 = m21 * m10 - m20 * m11;
		v1 = m22 * m10 - m20 * m12;
		v2 = m23 * m10 - m20 * m13;
		v3 = m22 * m11 - m21 * m12;
		v4 = m23 * m11 - m21 * m13;
		v5 = m23 * m12 - m22 * m13;

		const d03 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		const d13 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		const d23 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		const d33 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		return new Mat44(d00, d01, d02, d03, d10, d11, d12, d13, d20, d21, d22, d23, d30, d31, d32, d33);
	}

	Determinant() {
		return this._11 * (this._22 * (this._33 * this._44 - this._43 * this._34) - this._23 * (this._32 * this._44 - this._42 * this._34) + this._24 * (this._32 * this._43 - this._42 * this._33)) - this._12 * (this._21 * (this._33 * this._44 - this._43 * this._34) - this._23 * (this._31 * this._44 - this._41 * this._34) + this._24 * (this._31 * this._43 - this._41 * this._33)) + this._13 * (this._21 * (this._32 * this._44 - this._42 * this._34) - this._22 * (this._31 * this._44 - this._41 * this._34) + this._24 * (this._31 * this._42 - this._41 * this._32)) - this._14 * (this._21 * (this._32 * this._43 - this._42 * this._33) - this._22 * (this._31 * this._43 - this._41 * this._33) + this._23 * (this._31 * this._42 - this._41 * this._32));
	}

	Transpose() {
		return new Mat44(this._11, this._21, this._31, this._41, this._12, this._22, this._32, this._42, this._13, this._23, this._33, this._43, this._14, this._24, this._34, this._44);
	}

	private __Decompose(x: number, y: number, z: number) {
		let a, b, c;
		if (x < y) {
			if (y < z) {
				a = 2;
				b = 1;
				c = 0;
			} else {
				a = 1;
				if (x < z) {
					b = 2;
					c = 0;
				} else {
					b = 0;
					c = 2;
				}
			}
		} else {
			if (x < z) {
				a = 2;
				b = 0;
				c = 1;
			} else {
				a = 0;
				if (y < z) {
					b = 2;
					c = 1;
				} else {
					b = 1;
					c = 2;
				}
			}
		}
		return [a, b, c];
	}

	Decompose(vTranslation: Vec3, vScaling: Vec3, q: Quat): boolean {
		const decEpsilon = 0.0001;
		const canonicalBasis: Vec3[] = [new Vec3(1, 0, 0), new Vec3(0, 1, 0), new Vec3(0, 0, 1)];

		vTranslation = this.r3.xyz;

		let t = new Mat44(this);
		t._41 = this._42 = this._43 = 0;
		this._44 = 1;
		vScaling = new Vec3(t.r0.Length(), t.r1.Length(), t.r2.Length());

		let [a, b, c] = this.__Decompose(vScaling.x, vScaling.y, vScaling.z);
		if (vScaling.v[a] < decEpsilon) {
			t.r[a].x = canonicalBasis[a].x;
		}
		t.r[a].xyz = t.r[a].xyz.Normalize();

		if (vScaling.v[b] < decEpsilon) {
			const [aa, bb, cc] = this.__Decompose(Math.abs(t[a].x), Math.abs(t[a].y), Math.abs(t[a].z));
			t[b].xyz = t.r[a].xyz.Cross(canonicalBasis[cc]);
		}
		t.r[b].xyz = t.r[b].xyz.Normalize();

		if (vScaling.v[c] < decEpsilon) {
			t.r[c].xyz = t.r[a].xyz.Cross(t.r[b].xyz);
		}
		t.r[c].xyz = t.r[c].xyz.Normalize();

		let fDet = t.Determinant();
		if (fDet < 0) {
			vScaling.v[a] = -vScaling.v[a];
			t.r[a] = t.r[a].Neg();
			fDet = -fDet;
		}

		fDet -= 1;
		fDet *= fDet;

		if (decEpsilon < fDet) return false;

		q = Quat.RotateMatrix(t);
		return true;
	}

	static Translation(x: number, y: number, z: number) {
		return new Mat44(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1);
	}

	static Scaling(x: number, y: number, z: number) {
		return new Mat44(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1);
	}

	static RotateX(f: number) {
		const s = Math.sin(f),
			c = Math.cos(f);
		return new Mat44(1, 0, 0, 0, 0, c, s, 0, 0, -s, c, 0, 0, 0, 0, 1);
	}

	static RotateY(f: number) {
		const s = Math.sin(f),
			c = Math.cos(f);
		return new Mat44(c, 0, -s, 0, 0, 1, 0, 0, s, 0, c, 0, 0, 0, 0, 1);
	}

	static RotateZ(f: number) {
		const s = Math.sin(f),
			c = Math.cos(f);
		return new Mat44(c, s, 0, 0, -s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	}

	static RotateNormal(vNormal: Vec3, f: number) {
		const s = Math.sin(f),
			c = Math.cos(f);
		const d = 1 - c;
		return new Mat44(d * vNormal.x * vNormal.x + c, s * vNormal.z + d * vNormal.x * vNormal.y, d * vNormal.z * vNormal.x - s * vNormal.y, 0, d * vNormal.x * vNormal.y - s * vNormal.z, d * vNormal.y * vNormal.y + c, s * vNormal.x + d * vNormal.y * vNormal.z, 0, s * vNormal.y + d * vNormal.z * vNormal.x, d * vNormal.y * vNormal.z - s * vNormal.x, d * vNormal.z * vNormal.z + c, 0, 0, 0, 0, 1);
	}

	static RotationQuaternion(q: Quat) {
		return new Mat44(1 - q.y * (q.y + q.y) - q.z * (q.z + q.z), q.x * (q.y + q.y) + q.w * (q.z + q.z), q.x * (q.z + q.z) - q.w * (q.y + q.y), 0, q.x * (q.y + q.y) - q.w * (q.z + q.z), 1 - q.x * (q.x + q.x) - q.z * (q.z + q.z), q.y * (q.z + q.z) + q.w * (q.x + q.x), 0, q.x * (q.z + q.z) + q.w * (q.y + q.y), q.y * (q.z + q.z) - q.w * (q.x + q.x), 1 - q.x * (q.x + q.x) - q.y * (q.y + q.y), 0, 0, 0, 0, 1);
	}

	static RotationDualQuaternion(dq: DualQuat) {
		const q0 = dq.q0;
		const q1 = dq.q1;

		let ret = new Mat44();
		ret._11 = q0.w * q0.w + q0.x * q0.x - q0.y * q0.y - q0.z * q0.z;
		ret._21 = 2 * q0.x * q0.y - 2 * q0.w * q0.z;
		ret._31 = 2 * q0.x * q0.z + 2 * q0.w * q0.y;
		ret._12 = 2 * q0.x * q0.y + 2 * q0.w * q0.z;
		ret._22 = q0.w * q0.w + q0.y * q0.y - q0.x * q0.x - q0.z * q0.z;
		ret._32 = 2 * q0.y * q0.z - 2 * q0.w * q0.x;
		ret._13 = 2 * q0.x * q0.z - 2 * q0.w * q0.y;
		ret._23 = 2 * q0.y * q0.z + 2 * q0.w * q0.x;
		ret._33 = q0.w * q0.w + q0.z * q0.z - q0.x * q0.x - q0.y * q0.y;

		ret._41 = -2 * q1.w * q0.x + 2 * q1.x * q0.w - 2 * q1.y * q0.z + 2 * q1.z * q0.y;
		ret._42 = -2 * q1.w * q0.y + 2 * q1.x * q0.z + 2 * q1.y * q0.w - 2 * q1.z * q0.x;
		ret._43 = -2 * q1.w * q0.z - 2 * q1.x * q0.y + 2 * q1.y * q0.x + 2 * q1.z * q0.w;
		ret.r3.xyz = ret.r3.xyz.Div(q0.Dot(q0));

		ret._14 = 0;
		ret._24 = 0;
		ret._34 = 0;
		ret._44 = 1;

		return ret;
	}

	static LookToLH(vEye: Vec3, vDir: Vec3, vUp: Vec3) {
		let ret = new Mat44();
		const vEyeNeg = vEye.Neg();
		ret.r2.xyz = vDir.Normalize();
		ret.r0.xyz = vUp.Cross(ret.r2.xyz);
		ret.r2.xyz = ret.r2.xyz.Normalize();
		ret.r1.xyz = ret.r2.xyz.Cross(ret.r0.xyz);
		ret._14 = ret.r0.xyz.Dot(vEyeNeg);
		ret._24 = ret.r1.xyz.Dot(vEyeNeg);
		ret._34 = ret.r2.xyz.Dot(vEyeNeg);
		ret._41 = ret._42 = ret._43 = 0;
		ret._44 = 1;
		return ret.Transpose();
	}

	static LookAtLH(vEye: Vec3, vFocus: Vec3, vUp: Vec3) {
		return this.LookToLH(vEye, vFocus.Sub(vEye), vUp);
	}

	static LookToRH(vEye: Vec3, vDir: Vec3, vUp: Vec3) {
		return this.LookToLH(vEye, vDir.Neg(), vUp);
	}

	static LookAtRH(vEye: Vec3, vFocus: Vec3, vUp: Vec3) {
		return this.LookToRH(vEye, vFocus.Sub(vEye), vUp);
	}

	static OrthographicLH(fViewWidth: number, fViewHeight: number, fNearZ: number, fFarZ: number) {
		const fRange = 1 / (fFarZ - fNearZ);
		return new Mat44(2 / fViewWidth, 0, 0, 0, 0, 2 / fViewHeight, 0, 0, 0, 0, fRange, 0, 0, 0, -fRange * fNearZ, 1);
	}

	static OrthographicRH(fViewWidth: number, fViewHeight: number, fNearZ: number, fFarZ: number) {
		const fRange = 1 / (fNearZ - fFarZ);
		return new Mat44(2 / fViewWidth, 0, 0, 0, 0, 2 / fViewHeight, 0, 0, 0, 0, fRange, 0, 0, 0, fRange * fNearZ, 1);
	}

	static OrthographicOffCenterLH(fViewLeft: number, fViewRight: number, fViewBottom: number, fViewTop: number, fNearZ: number, fFarZ: number) {
		const ReciprocalWidth = 1 / (fViewRight - fViewLeft);
		const ReciprocalHeight = 1 / (fViewTop - fViewBottom);
		const fRange = 1 / (fFarZ - fNearZ);
		return new Mat44(ReciprocalWidth + ReciprocalWidth, 0, 0, 0, 0, ReciprocalHeight + ReciprocalHeight, 0, 0, 0, 0, fRange, 0, -(fViewLeft + fViewRight) * ReciprocalWidth, -(fViewTop + fViewBottom) * ReciprocalHeight, -fRange * fNearZ, 1);
	}

	static OrthographicOffCenterRH(fViewLeft: number, fViewRight: number, fViewBottom: number, fViewTop: number, fNearZ: number, fFarZ: number) {
		const ReciprocalWidth = 1 / (fViewRight - fViewLeft);
		const ReciprocalHeight = 1 / (fViewTop - fViewBottom);
		const fRange = 1 / (fNearZ - fFarZ);
		return new Mat44(ReciprocalWidth + ReciprocalWidth, 0, 0, 0, 0, ReciprocalHeight + ReciprocalHeight, 0, 0, 0, 0, fRange, 0, -(fViewLeft + fViewRight) * ReciprocalWidth, -(fViewTop + fViewBottom) * ReciprocalHeight, fRange * fNearZ, 1);
	}

	static PerspectiveFovLH(fFovY: number, fAspectHByW: number, fNearZ: number, fFarZ: number) {
		const s = Math.sin(0.5 * fFovY),
			c = Math.cos(0.5 * fFovY);
		const Height = c / s;
		const Width = Height / fAspectHByW;
		const fRange = fFarZ / (fFarZ - fNearZ);
		return new Mat44(Width, 0, 0, 0, 0, Height, 0, 0, 0, 0, fRange, 1, 0, 0, -fRange * fNearZ, 0);
	}

	static PerspectiveFovRH(fFovY: number, fAspectHByW: number, fNearZ: number, fFarZ: number) {
		const s = Math.sin(0.5 * fFovY),
			c = Math.cos(0.5 * fFovY);
		const Height = c / s;
		const Width = Height / fAspectHByW;
		const fRange = fFarZ / (fNearZ - fFarZ);
		return new Mat44(Width, 0, 0, 0, 0, Height, 0, 0, 0, 0, fRange, 1, 0, 0, fRange * fNearZ, 0);
	}

	static PerspectiveLH(fViewWidth: number, fViewHeight: number, fNearZ: number, fFarZ: number) {
		const TwoNearZ = fNearZ + fNearZ;
		const fRange = fFarZ / (fFarZ - fNearZ);
		return new Mat44(TwoNearZ / fViewWidth, 0, 0, 0, 0, TwoNearZ / fViewHeight, 0, 0, 0, 0, fRange, 1, 0, 0, -fRange * fNearZ, 0);
	}

	static PerspectiveRH(fViewWidth: number, fViewHeight: number, fNearZ: number, fFarZ: number) {
		const TwoNearZ = fNearZ + fNearZ;
		const fRange = fFarZ / (fNearZ - fFarZ);
		return new Mat44(TwoNearZ / fViewWidth, 0, 0, 0, 0, TwoNearZ / fViewHeight, 0, 0, 0, 0, fRange, 1, 0, 0, fRange * fNearZ, 0);
	}

	static PerspectiveOffCenterLH(fViewLeft: number, fViewRight: number, fViewBottom: number, fViewTop: number, fNearZ: number, fFarZ: number) {
		const TwoNearZ = fNearZ + fNearZ;
		const ReciprocalWidth = 1 / (fViewRight - fViewLeft);
		const ReciprocalHeight = 1 / (fViewTop - fViewBottom);
		const fRange = fFarZ / (fFarZ - fNearZ);
		return new Mat44(TwoNearZ * ReciprocalWidth, 0, 0, 0, 0, TwoNearZ * ReciprocalHeight, 0, 0, -(fViewLeft + fViewRight) * ReciprocalWidth, -(fViewTop + fViewBottom) * ReciprocalHeight, fRange, 1, 0, 0, -fRange * fNearZ, 0);
	}

	static PerspectiveOffCenterRH(fViewLeft: number, fViewRight: number, fViewBottom: number, fViewTop: number, fNearZ: number, fFarZ: number) {
		const TwoNearZ = fNearZ + fNearZ;
		const ReciprocalWidth = 1 / (fViewRight - fViewLeft);
		const ReciprocalHeight = 1 / (fViewTop - fViewBottom);
		const fRange = fFarZ / (fNearZ - fFarZ);
		return new Mat44(TwoNearZ * ReciprocalWidth, 0, 0, 0, 0, TwoNearZ * ReciprocalHeight, 0, 0, (fViewLeft + fViewRight) * ReciprocalWidth, (fViewTop + fViewBottom) * ReciprocalHeight, fRange, -1, 0, 0, fRange * fNearZ, 0);
	}

	static Reflect(vPlane: Plane) {
		const P = vPlane.Normalize();
		const S = P.Mul(new Vec4(-2, -2, -2, 0));
		let ret = new Mat44();
		ret.r0 = S.Mul(P.x);
		ret.r1 = S.Mul(P.y);
		ret.r2 = S.Mul(P.z);
		ret.r3 = S.Mul(P.w);
		ret._11 += 1;
		ret._22 += 1;
		ret._33 += 1;
		ret._44 += 1;
		return ret;
	}

	static Shadow(vPlane: Plane, vLight: Vec3) {
		let P = vPlane.Normalize();
		const fDot = P.xyz.Dot(vLight);
		P.Vector = P.Neg();
		let ret = new Mat44();
		ret.r0.xyz = vLight.Mul(P.x);
		ret.r1.xyz = vLight.Mul(P.y);
		ret.r2.xyz = vLight.Mul(P.z);
		ret.r3.xyz = vLight.Mul(P.w);
		ret.r0.x += fDot;
		ret.r1.y += fDot;
		ret.r2.z += fDot;
		ret.r3.w += fDot;
		return ret;
	}
}
