type DerivedVecType<N> = N extends 2 ? Vec2 : N extends 3 ? Vec3 : N extends 4 ? Vec4 : Vec;
type FixedLengthArray<T, N extends number = number> = N extends 1 ? [T] : N extends 2 ? [T, T] : N extends 3 ? [T, T, T] : N extends 4 ? [T, T, T, T] : N extends 5 ? [T, T, T, T, T] : number[];

class Vec<Dimension extends number = number, DataType extends number[] = FixedLengthArray<number, Dimension>, VecType extends Vec = DerivedVecType<Dimension>> {
	protected _v: DataType;
	constructor(data: DataType) {
		this._v = [...data] as DataType;
	}
	get v() {
		return [...this._v] as DataType;
	}
	set v(data: DataType) {
		this._v = [...data] as DataType;
	}

	Add(value: Vec | number): VecType {
		return Reflect.construct(
			this.constructor,
			this.v.map((each, index) => (value instanceof Vec ? each + value.v[index] : each + value))
		);
	}
	Sub(value: Vec | number): VecType {
		return Reflect.construct(
			this.constructor,
			this.v.map((each, index) => (value instanceof Vec ? each - value.v[index] : each - value))
		);
	}
	Mul(value: Vec | number): VecType {
		return Reflect.construct(
			this.constructor,
			this.v.map((each, index) => (value instanceof Vec ? each * value.v[index] : each * value))
		);
	}
	Div(value: Vec | number): VecType {
		return Reflect.construct(
			this.constructor,
			this.v.map((each, index) => (value instanceof Vec ? each / value.v[index] : each / value))
		);
	}

	Neg(): VecType {
		return Reflect.construct(
			this.constructor,
			this.v.map((each) => -each)
		);
	}
	Equal(value: Vec) {
		return value.v.every((each, index) => each === this.v[index]);
	}

	Dot(value: Vec) {
		return this.v.reduce((prev, curr, index) => prev + curr * value.v[index], 0);
	}
	Length() {
		return Math.sqrt(this.Dot(this));
	}
	LengthSq() {
		return this.Dot(this);
	}
	Normalize(): VecType {
		return Reflect.construct(this.constructor, this.v).Mul(1.0 / this.Length());
	}

	Clone(): VecType {
		return Reflect.construct(this.constructor, this.v);
	}
}

export class Vec2 extends Vec<2> {
	constructor(x: number = 0, y: number = 0) {
		super([x, y]);
	}

	static FromNative(vec: Vec2) {
		return new Vec2(vec.x, vec.y);
	}

	get x() {
		return this._v[0];
	}
	get y() {
		return this._v[1];
	}
	get r() {
		return this._v[0];
	}
	get g() {
		return this._v[1];
	}
	set x(r: number) {
		this._v[0] = r;
	}
	set y(r: number) {
		this._v[1] = r;
	}
	set r(r: number) {
		this._v[0] = r;
	}
	set g(r: number) {
		this._v[1] = r;
	}

	Cross(r: Vec2) {
		return this.x * r.y - this.y * r.x;
	}
	Reflect(r: Vec2) {
		return this.Sub(r.Mul(this.Dot(r) * 2));
	}

	static get Zero() {
		return new Vec2(0, 0);
	}
	static get One() {
		return new Vec2(1, 1);
	}
	static get NegOne() {
		return new Vec2(-1, -1);
	}
	static get UnitX() {
		return new Vec2(1, 0);
	}
	static get UnitY() {
		return new Vec2(0, 1);
	}
	static get NegUnitX() {
		return new Vec2(-1, 0);
	}
	static get NegUnitY() {
		return new Vec2(0, -1);
	}
}

export class Vec3 extends Vec<3> {
	constructor(x: number = 0, y: number = 0, z: number = 0) {
		super([x, y, z]);
	}

	static FromNative(vec: Vec3) {
		return new Vec3(vec.x, vec.y, vec.z);
	}

	get x() {
		return this._v[0];
	}
	get y() {
		return this._v[1];
	}
	get z() {
		return this._v[2];
	}
	get r() {
		return this._v[0];
	}
	get g() {
		return this._v[1];
	}
	get b() {
		return this._v[2];
	}
	set x(r: number) {
		this._v[0] = r;
	}
	set y(r: number) {
		this._v[1] = r;
	}
	set z(r: number) {
		this._v[2] = r;
	}
	set r(r: number) {
		this._v[0] = r;
	}
	set g(r: number) {
		this._v[1] = r;
	}
	set b(r: number) {
		this._v[2] = r;
	}

	get xy() {
		return new Vec2(this._v[0], this._v[1]);
	}
	get rg() {
		return new Vec2(this._v[0], this._v[1]);
	}
	get xz() {
		return new Vec2(this._v[0], this._v[2]);
	}

	get rb() {
		return new Vec2(this._v[0], this._v[2]);
	}
	get yz() {
		return new Vec2(this._v[1], this._v[2]);
	}
	get gb() {
		return new Vec2(this._v[1], this._v[2]);
	}

	set xy(r: Vec2) {
		this._v[0] = r.x;
		this._v[1] = r.y;
	}
	set xz(r: Vec2) {
		this._v[0] = r.x;
		this._v[2] = r.y;
	}
	set yz(r: Vec2) {
		this._v[1] = r.x;
		this._v[2] = r.y;
	}

	set rg(r: Vec2) {
		this._v[0] = r.x;
		this._v[1] = r.y;
	}
	set rb(r: Vec2) {
		this._v[0] = r.x;
		this._v[2] = r.y;
	}
	set gb(r: Vec2) {
		this._v[1] = r.x;
		this._v[2] = r.y;
	}

	Cross(r: Vec3) {
		return new Vec3(this.y * r.z - this.z * r.y, this.z * this.x - this.x * r.z, this.x * r.y - this.y * r.x);
	}
	Reflect(r: Vec3) {
		return this.Sub(r.Mul(this.Dot(r) * 2));
	}

	static get Zero() {
		return new Vec3(0, 0, 0);
	}
	static get One() {
		return new Vec3(1, 1, 1);
	}
	static get NegOne() {
		return new Vec3(-1, -1, -1);
	}
	static get UnitX() {
		return new Vec3(1, 0, 0);
	}
	static get UnitY() {
		return new Vec3(0, 1, 0);
	}
	static get UnitZ() {
		return new Vec3(0, 0, 1);
	}
	static get NegUnitX() {
		return new Vec3(-1, 0, 0);
	}
	static get NegUnitY() {
		return new Vec3(0, -1, 0);
	}
	static get NegUnitZ() {
		return new Vec3(0, 0, -1);
	}
}

export class Vec4 extends Vec<4> {
	constructor(x: number = 0, y: number = 0, z: number = 0, w: number = 0) {
		super([x, y, z, w]);
	}

	static FromNative(vec: Vec4) {
		return new Vec4(vec.x, vec.y, vec.z, vec.w);
	}

	get x() {
		return this._v[0];
	}
	get y() {
		return this._v[1];
	}
	get z() {
		return this._v[2];
	}
	get w() {
		return this._v[3];
	}
	get r() {
		return this._v[0];
	}
	get g() {
		return this._v[1];
	}
	get b() {
		return this._v[2];
	}
	get a() {
		return this._v[3];
	}
	set x(r: number) {
		this._v[0] = r;
	}
	set y(r: number) {
		this._v[1] = r;
	}
	set z(r: number) {
		this._v[2] = r;
	}
	set w(r: number) {
		this._v[3] = r;
	}
	set r(r: number) {
		this._v[0] = r;
	}
	set g(r: number) {
		this._v[1] = r;
	}
	set b(r: number) {
		this._v[2] = r;
	}
	set a(r: number) {
		this._v[3] = r;
	}

	get xy() {
		return new Vec2(this._v[0], this._v[1]);
	}
	get xz() {
		return new Vec2(this._v[0], this._v[2]);
	}
	get xw() {
		return new Vec2(this._v[0], this._v[3]);
	}
	get yz() {
		return new Vec2(this._v[1], this._v[2]);
	}
	get yw() {
		return new Vec2(this._v[1], this._v[3]);
	}
	get zw() {
		return new Vec2(this._v[2], this._v[3]);
	}

	get rg() {
		return new Vec2(this._v[0], this._v[1]);
	}
	get rb() {
		return new Vec2(this._v[0], this._v[2]);
	}
	get ra() {
		return new Vec2(this._v[0], this._v[3]);
	}
	get gb() {
		return new Vec2(this._v[1], this._v[2]);
	}
	get ga() {
		return new Vec2(this._v[1], this._v[3]);
	}
	get ba() {
		return new Vec2(this._v[2], this._v[3]);
	}

	get xyz() {
		return new Vec3(this._v[0], this._v[1], this._v[2]);
	}
	get xyw() {
		return new Vec3(this._v[0], this._v[1], this._v[3]);
	}
	get xzw() {
		return new Vec3(this._v[0], this._v[2], this._v[3]);
	}
	get yzw() {
		return new Vec3(this._v[1], this._v[2], this._v[3]);
	}

	get rgb() {
		return new Vec3(this._v[0], this._v[1], this._v[2]);
	}
	get rga() {
		return new Vec3(this._v[0], this._v[1], this._v[3]);
	}
	get rba() {
		return new Vec3(this._v[0], this._v[2], this._v[3]);
	}
	get gba() {
		return new Vec3(this._v[1], this._v[2], this._v[3]);
	}

	set xy(r: Vec2) {
		this._v[0] = r.x;
		this._v[1] = r.y;
	}
	set xz(r: Vec2) {
		this._v[0] = r.x;
		this._v[2] = r.y;
	}
	set xw(r: Vec2) {
		this._v[0] = r.x;
		this._v[3] = r.y;
	}
	set yz(r: Vec2) {
		this._v[1] = r.x;
		this._v[2] = r.y;
	}
	set yw(r: Vec2) {
		this._v[1] = r.x;
		this._v[3] = r.y;
	}
	set zw(r: Vec2) {
		this._v[2] = r.x;
		this._v[3] = r.y;
	}

	set rg(r: Vec2) {
		this._v[0] = r.x;
		this._v[1] = r.y;
	}
	set rb(r: Vec2) {
		this._v[0] = r.x;
		this._v[2] = r.y;
	}
	set ra(r: Vec2) {
		this._v[0] = r.x;
		this._v[3] = r.y;
	}
	set gb(r: Vec2) {
		this._v[1] = r.x;
		this._v[2] = r.y;
	}
	set ga(r: Vec2) {
		this._v[1] = r.x;
		this._v[3] = r.y;
	}
	set ba(r: Vec2) {
		this._v[2] = r.x;
		this._v[3] = r.y;
	}

	set xyz(r: Vec3) {
		this._v[0] = r.x;
		this._v[1] = r.y;
		this._v[2] = r.z;
	}
	set xyw(r: Vec3) {
		this._v[0] = r.x;
		this._v[1] = r.y;
		this._v[3] = r.z;
	}
	set xzw(r: Vec3) {
		this._v[0] = r.x;
		this._v[2] = r.y;
		this._v[3] = r.z;
	}
	set yzw(r: Vec3) {
		this._v[1] = r.x;
		this._v[2] = r.y;
		this._v[3] = r.z;
	}

	set rgb(r: Vec3) {
		this._v[0] = r.x;
		this._v[1] = r.y;
		this._v[2] = r.z;
	}
	set rga(r: Vec3) {
		this._v[0] = r.x;
		this._v[1] = r.y;
		this._v[3] = r.z;
	}
	set rba(r: Vec3) {
		this._v[0] = r.x;
		this._v[2] = r.y;
		this._v[3] = r.z;
	}
	set gba(r: Vec3) {
		this._v[1] = r.x;
		this._v[2] = r.y;
		this._v[3] = r.z;
	}

	static get Zero() {
		return new Vec4(0, 0, 0, 0);
	}
	static get One() {
		return new Vec4(1, 1, 1, 1);
	}
	static get NegOne() {
		return new Vec4(-1, -1, -1, -1);
	}
	static get UnitX() {
		return new Vec4(1, 0, 0, 0);
	}
	static get UnitY() {
		return new Vec4(0, 1, 0, 0);
	}
	static get UnitZ() {
		return new Vec4(0, 0, 1, 0);
	}
	static get UnitW() {
		return new Vec4(0, 0, 0, 1);
	}
	static get NegUnitX() {
		return new Vec4(-1, 0, 0, 0);
	}
	static get NegUnitY() {
		return new Vec4(0, -1, 0, 0);
	}
	static get NegUnitZ() {
		return new Vec4(0, 0, -1, 0);
	}
	static get NegUnitW() {
		return new Vec4(0, 0, 0, -1);
	}
}
