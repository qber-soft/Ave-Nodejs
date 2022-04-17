export class AveMath {
	private constructor() { }

	static ReadR16(dv: DataView, nByteOffset: number): number {
		const f = dv.getUint16(nByteOffset);
		let Mantissa = 0x3ff & f;
		let Exponent;
		if ((f & 0x7C00) != 0) {
			Exponent = (f >> 10) & 0x1f;
		}
		else if (Mantissa != 0) {
			Exponent = 1;
			do {
				Exponent--;
				Mantissa <<= 1;
			} while ((Mantissa & 0x0400) == 0);
			Mantissa &= 0x03ff;
		}
		else {
			Exponent = -112;
		}
		const Result = ((f & 0x8000) << 16) | ((Exponent + 112) << 23) | (Mantissa << 13);
		const buf = new Uint8Array(4);
		const data = new DataView(buf);
		data.setUint32(0, Result);
		return data.getFloat32(0);
	}

	static WriteR16(dv: DataView, nByteOffset: number, f: number) {

	}
}
