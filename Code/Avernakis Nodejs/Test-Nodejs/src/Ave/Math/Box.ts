import { Vec3 } from "./Vector";

export class Box {
	Min: Vec3 = new Vec3();
	Max: Vec3 = new Vec3();

	constructor(min: Vec3, max: Vec3) {
		this.Min = min;
		this.Max = max;
	}

	get Center() {
		return this.Max.Add(this.Min).Mul(0.5);
	}
	get Extend() {
		return this.Max.Sub(this.Min).Mul(0.5);
	}

	static get Empty() {
		return new Box(Vec3.Zero, Vec3.Zero);
	}
}
