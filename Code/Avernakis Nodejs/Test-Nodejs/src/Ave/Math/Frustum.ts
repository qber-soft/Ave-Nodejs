import { Quat } from "./Quaternion";
import { Vec3 } from "./Vector";

export class Frustum {
	Origin: Vec3 = new Vec3();
	Orient: Quat = new Quat();
	SlopeL: number = 0;
	SlopeR: number = 0;
	SlopeT: number = 0;
	SlopeB: number = 0;
	Near: number = 0;
	Far: number = 0;
}
