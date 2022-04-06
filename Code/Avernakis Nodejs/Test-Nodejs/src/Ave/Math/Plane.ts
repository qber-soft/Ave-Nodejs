import { Vec3, Vec4 } from "./Vector";

export class Plane extends Vec4 {
	get Vector() {
		return this as Vec4;
	}
	set Vector(r: Vec4) {
		this.x = r.x;
		this.y = r.y;
		this.z = r.z;
		this.w = r.w;
	}

	Normalize(): Plane {
		const l = 1 / this.xyz.Length();
		return new Plane(this.x * l, this.y * l, this.z * l, this.w * l);
	}

	static FromPointNormal(vPoint: Vec3, vNormal: Vec3) {
		return new Plane(vNormal.x, vNormal.y, vNormal.z, -vPoint.Dot(vNormal));
	}

	static FromPoints(v0: Vec3, v1: Vec3, v2: Vec3) {
		let n = v0.Sub(v1).Cross(v0.Sub(v2)).Normalize();
		return new Plane(n.x, n.y, n.z, -n.Dot(v0));
	}
}

export class Plane6 {
	protected p: Plane[] = [new Plane(), new Plane(), new Plane(), new Plane(), new Plane(), new Plane()];

	get p0() {
		return this.p[0];
	}
	get p1() {
		return this.p[1];
	}
	get p2() {
		return this.p[2];
	}
	get p3() {
		return this.p[3];
	}
	get p4() {
		return this.p[4];
	}
	get p5() {
		return this.p[5];
	}

	set p0(v: Plane) {
		this.p[0] = v;
	}
	set p1(v: Plane) {
		this.p[1] = v;
	}
	set p2(v: Plane) {
		this.p[2] = v;
	}
	set p3(v: Plane) {
		this.p[3] = v;
	}
	set p4(v: Plane) {
		this.p[4] = v;
	}
	set p5(v: Plane) {
		this.p[5] = v;
	}
}
