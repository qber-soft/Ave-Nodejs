import { Vec4 } from "../Ave";
import { AveMath } from "../Math";

export enum ImageDimension {
	Unknown,
	Texture1D,
	Texture2D,
	Texture3D,
}

export enum ImageMetadataFlag {
	None = 0,
	Cube = 0x1,
	Premultiplied = 0x2,
	MultiFrame = 0x4,
	MultiMetadata = 0x8,
}

export class ImageMetadata {
	Width: number;
	Height: number;
	DepthOrArraySize: number;
	MipLevel: number;
	Format: PixFormat;
	Dimension: ImageDimension = ImageDimension.Texture2D;
	Flag: ImageMetadataFlag = ImageMetadataFlag.None;

	constructor(width: number = 0, height: number = 0, depthOrArraySize: number = 1, mipLevel: number = 1, format: PixFormat = PixFormat.UNKNOWN, dimension: ImageDimension = ImageDimension.Texture2D, flag: ImageMetadataFlag = ImageMetadataFlag.None) {
		this.Width = width;
		this.Height = height;
		this.DepthOrArraySize = depthOrArraySize;
		this.MipLevel = mipLevel;
		this.Format = format;
		this.Dimension = dimension;
		this.Flag = flag;
	}

	get IsCube() {
		return 0 != (ImageMetadataFlag.Cube & this.Flag);
	}

	get IsPremultiplied() {
		return 0 != (ImageMetadataFlag.Premultiplied & this.Flag);
	}

	get IsMultiFrame() {
		return 0 != (ImageMetadataFlag.MultiFrame & this.Flag);
	}

	get IsMultiMetadata() {
		return 0 != (ImageMetadataFlag.MultiMetadata & this.Flag);
	}

	ComputeSubresourceCount() {
		if (ImageDimension.Texture3D != this.Dimension)
			return this.DepthOrArraySize * this.MipLevel;
		else
			return this.MipLevel;
	}

	ComputeSubresourceIndex(mipIndex: number, arrayIndex: number) {
		if (mipIndex >= this.MipLevel)
			return -1;
		if (ImageDimension.Texture3D != this.Dimension) {
			if (arrayIndex >= this.DepthOrArraySize)
				return -1;
		} else {
			if (0 != arrayIndex)
				return -1;
		}
		return arrayIndex * this.MipLevel + mipIndex;
	}

	static FromNative(md: ImageMetadata) {
		return new ImageMetadata(md.Width, md.Height, md.DepthOrArraySize, md.MipLevel, md.Format, md.Dimension, md.Flag);
	}
}

export class AnimationInfo {
	FrameCount: number;
	RepeatCount: number;
}

export class AnimationFrame {
	DelaySecond: number;
}

// prettier-ignore
export enum BlendType {
	Zero             /**/ = 1,
	One              /**/ = 2,
	Src_Color        /**/ = 3,
	Inv_Src_Color    /**/ = 4,
	Src_Alpha        /**/ = 5,
	Inv_Src_Alpha    /**/ = 6,
	Dest_Alpha       /**/ = 7,
	Inv_Dest_Alpha   /**/ = 8,
	Dest_Color       /**/ = 9,
	Inv_Dest_Color   /**/ = 10,
	Src_Alpha_Sat    /**/ = 11,
	Blend_Factor     /**/ = 14,
	Inv_Blend_Factor /**/ = 15,
};

// prettier-ignore
export enum BlendOp {
	Add          /**/ = 1,
	Subtract     /**/ = 2,
	Rev_Subtract /**/ = 3,
	Min          /**/ = 4,
	Max          /**/ = 5,
};

export enum ColorWriteFlag {
	None = 0,
	Red = 1,
	Green = 2,
	Blue = 4,
	Alpha = 8,
	All = Red | Green | Blue | Alpha,
}

export class BlendOption {
	Src: BlendType = BlendType.Src_Alpha;
	Dest: BlendType = BlendType.Inv_Src_Alpha;
	Op: BlendOp = BlendOp.Add;
	AlphaSrc: BlendType = BlendType.Src_Alpha;
	AlphaDest: BlendType = BlendType.Inv_Src_Alpha;
	AlphaOp: BlendOp = BlendOp.Add;
	WriteMask: ColorWriteFlag = ColorWriteFlag.All;
	BlendFactor: Vec4 = Vec4.Zero;
}

export class ImageBox {
	Left: number = 0;
	Top: number = 0;
	Front: number = 0;
	Right: number = 0;
	Bottom: number = 0;
	Back: number = 0;

	static Full() {
		return new ImageBox();
	}
}

export enum ImageRotateType {
	Rotate0,
	Rotate90,
	Rotate180,
	Rotate270,
}

export enum ImageChannel {
	Red,
	Green,
	Blue,
	Alpha,
	Luminance,
}

export enum ImageFilterType {
	Point,
	Linear,
	Cubic,
	Box,
	Triangle,
}

// prettier-ignore
export class ImageData {
	Width: number;
	Height: number;
	Depth: number;
	Format: PixFormat;
	RowPitch: number;
	SlicePitch: number;
	Data: ArrayBuffer;
	View: DataView;

	private m_Get: (x, y, z) => Vec4;
	private m_Set: (x, y, z, v) => void;

	static FromNative(d: ImageData) {
		const data = new ImageData();
		data.Width = d.Width;
		data.Height = d.Height;
		data.Depth = d.Depth;
		data.Format = d.Format;
		data.RowPitch = d.RowPitch;
		data.SlicePitch = d.SlicePitch;
		data.Data = d.Data;
		data.View = new DataView(data.Data);

		data.m_Get = data[`G_${PixFormat[data.Format]}`] ?? data.G_Empty;
		data.m_Set = data[`S_${PixFormat[data.Format]}`] ?? data.S_Empty;
		return data;
	}

	GetPixel(x: number = 0, y: number = 0, z: number = 0): Vec4 {
		return this.m_Get(x, y, z);
	}

	SetPixel(x: number = 0, y: number = 0, z: number = 0, v: Vec4) {
		return this.m_Set(x, y, z, v);
	}

	private G_R32_4(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 16; return new Vec4(this.View.getFloat32(o), this.View.getFloat32(o + 4), this.View.getFloat32(o + 8), this.View.getFloat32(o + 12)); }
	private G_U32_4(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 16; return new Vec4(this.View.getUint32(o), this.View.getUint32(o + 4), this.View.getUint32(o + 8), this.View.getUint32(o + 12)); }
	private G_S32_4(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 16; return new Vec4(this.View.getInt32(o), this.View.getInt32(o + 4), this.View.getInt32(o + 8), this.View.getInt32(o + 12)); }
	private G_R32_3(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 12; return new Vec4(this.View.getFloat32(o), this.View.getFloat32(o + 4), this.View.getFloat32(o + 8), 0); }
	private G_U32_3(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 12; return new Vec4(this.View.getUint32(o), this.View.getUint32(o + 4), this.View.getUint32(o + 8), 0); }
	private G_S32_3(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 12; return new Vec4(this.View.getInt32(o), this.View.getInt32(o + 4), this.View.getInt32(o + 8), 0); }
	private G_R32_2(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; return new Vec4(this.View.getFloat32(o), this.View.getFloat32(o + 4), 0, 0); }
	private G_U32_2(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; return new Vec4(this.View.getUint32(o), this.View.getUint32(o + 4), 0, 0); }
	private G_S32_2(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; return new Vec4(this.View.getInt32(o), this.View.getInt32(o + 4), 0, 0); }

	private G_R16_4(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; return new Vec4(AveMath.ReadR16(this.View, o), AveMath.ReadR16(this.View, o + 2), AveMath.ReadR16(this.View, o + 4), AveMath.ReadR16(this.View, o + 6)); }
	private G_U16_4(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; return new Vec4(this.View.getUint16(o), this.View.getUint16(o + 2), this.View.getUint16(o + 4), this.View.getUint16(o + 6)); }
	private G_S16_4(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; return new Vec4(this.View.getInt16(o), this.View.getInt16(o + 2), this.View.getInt16(o + 4), this.View.getInt16(o + 6)); }
	private G_R16_2(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 4; return new Vec4(AveMath.ReadR16(this.View, o), AveMath.ReadR16(this.View, o + 2), 0, 0); }
	private G_U16_2(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 4; return new Vec4(this.View.getUint16(o), this.View.getUint16(o + 2), 0, 0); }
	private G_S16_2(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 4; return new Vec4(this.View.getInt16(o), this.View.getInt16(o + 2), 0, 0); }

	private G_U10_3_U2(x, y, z) { const d = this.View.getUint32(z * this.SlicePitch + y * this.RowPitch + x * 4); return new Vec4(0x3ff & d, 0x3ff & (d >> 10), 0x3ff & (d >> 20), 0x3 & (d >> 30)); }

	private G_U8_4(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 4; return new Vec4(this.View.getUint8(o), this.View.getUint8(o + 1), this.View.getUint8(o + 2), this.View.getUint8(o + 3)); }
	private G_S8_4(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 4; return new Vec4(this.View.getInt8(o), this.View.getInt8(o + 1), this.View.getInt8(o + 2), this.View.getInt8(o + 3)); }
	private G_U8_2(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 2; return new Vec4(this.View.getUint8(o), this.View.getUint8(o + 1), 0, 0); }
	private G_S8_2(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 2; return new Vec4(this.View.getInt8(o), this.View.getInt8(o + 1), 0, 0); }

	private G_U4_4(x, y, z) { const d = this.View.getUint16(z * this.SlicePitch + y * this.RowPitch + x * 2); return new Vec4(0xf & d, 0xf & (d >> 4), 0xf & (d >> 8), 0xf & (d >> 12)); }

	private G_Empty(x, y, z) { return Vec4.Zero; }
	

	private S_R32_4(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 16; this.View.setFloat32(o, v.r); this.View.setFloat32(o + 4, v.g); this.View.setFloat32(o + 8, v.b); this.View.setFloat32(o + 12, v.a); }
	private S_U32_4(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 16; this.View.setUint32(o, v.r); this.View.setUint32(o + 4, v.g); this.View.setUint32(o + 8, v.b); this.View.setUint32(o + 12, v.a); }
	private S_S32_4(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 16; this.View.setInt32(o, v.r); this.View.setInt32(o + 4, v.g); this.View.setInt32(o + 8, v.b); this.View.setInt32(o + 12, v.a); }
	private S_R32_3(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 12; this.View.setFloat32(o, v.r); this.View.setFloat32(o + 4, v.g); this.View.setFloat32(o + 8, v.b); }
	private S_U32_3(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 12; this.View.setUint32(o, v.r); this.View.setUint32(o + 4, v.g); this.View.setUint32(o + 8, v.b); }
	private S_S32_3(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 12; this.View.setInt32(o, v.r); this.View.setInt32(o + 4, v.g); this.View.setInt32(o + 8, v.b); }
	private S_R32_2(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; this.View.setFloat32(o, v.r); this.View.setFloat32(o + 4, v.g); }
	private S_U32_2(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; this.View.setUint32(o, v.r); this.View.setUint32(o + 4, v.g); }
	private S_S32_2(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; this.View.setInt32(o, v.r); this.View.setInt32(o + 4, v.g); }

	private S_R16_4(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; AveMath.WriteR16(this.View, o, v.r); AveMath.WriteR16(this.View, o + 2, v.g); AveMath.WriteR16(this.View, o + 4, v.z); AveMath.WriteR16(this.View, o + 6, v.a); }
	private S_U16_4(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; this.View.setUint16(o, v.r); this.View.setUint16(o + 2, v.g); this.View.setUint16(o + 4, v.b); this.View.setUint16(o + 6, v.a); }
	private S_S16_4(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; this.View.setInt16(o, v.r); this.View.setInt16(o + 2, v.g); this.View.setInt16(o + 4, v.b); this.View.setInt16(o + 6, v.a); }
	private S_R16_2(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 4; AveMath.WriteR16(this.View, o, v.r); AveMath.WriteR16(this.View, o + 2, v.g); }
	private S_U16_2(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 4; this.View.setUint16(o, v.r); this.View.setUint16(o + 2, v.g); }
	private S_S16_2(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 4; this.View.setInt16(o, v.r); this.View.setInt16(o + 2, v.g); }

	private S_U10_3_U2(x, y, z, v) { const d = (0x3ff & v.r) | (0x3ff & v.g) << 10 | (0x3ff & v.b) << 20 | (0x3 & v.a) << 30; this.View.setUint32(z * this.SlicePitch + y * this.RowPitch + x * 4, d); }

	private S_U8_4(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 4; this.View.setUint8(o, v.r); this.View.setUint8(o + 4, v.g); this.View.setUint8(o + 8, v.b); this.View.setUint8(o + 12, v.a); }
	private S_S8_4(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 4; this.View.setInt8(o, v.r); this.View.setInt8(o + 4, v.g); this.View.setInt8(o + 8, v.b); this.View.setInt8(o + 12, v.a); }
	private S_U8_2(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 2; this.View.setUint8(o, v.r); this.View.setUint8(o + 4, v.g); }
	private S_S8_2(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 2; this.View.setInt8(o, v.r); this.View.setInt8(o + 4, v.g); }

	private S_U4_4(x, y, z, v) { const d = (0xf & v.r) | (0xf & v.g) << 4 | (0xf & v.b) << 8 | (0xf & v.a) << 12; this.View.setUint16(z * this.SlicePitch + y * this.RowPitch + x * 2, d); }

	private S_Empty(x, y, z, v) {}


	private G_R32G32B32A32_FLOAT          /**/(x, y, z) { return this.G_R32_4(x, y, z); }
	private G_R32G32B32A32_UINT           /**/(x, y, z) { return this.G_U32_4(x, y, z); }
	private G_R32G32B32A32_SINT           /**/(x, y, z) { return this.G_S32_4(x, y, z); }
	private G_R32G32B32_FLOAT             /**/(x, y, z) { return this.G_R32_3(x, y, z); }
	private G_R32G32B32_UINT              /**/(x, y, z) { return this.G_U32_3(x, y, z); }
	private G_R32G32B32_SINT              /**/(x, y, z) { return this.G_S32_3(x, y, z); }
	private G_R16G16B16A16_FLOAT          /**/(x, y, z) { return this.G_R16_4(x, y, z); }
	private G_R16G16B16A16_UNORM          /**/(x, y, z) { return this.G_U16_4(x, y, z).Div(65535); }
	private G_R16G16B16A16_UINT           /**/(x, y, z) { return this.G_U16_4(x, y, z); }
	private G_R16G16B16A16_SNORM          /**/(x, y, z) { return this.G_S16_4(x, y, z).Div(32768); }
	private G_R16G16B16A16_SINT           /**/(x, y, z) { return this.G_S16_4(x, y, z); }
	private G_R32G32_FLOAT                /**/(x, y, z) { return this.G_R32_2(x, y, z); }
	private G_R32G32_UINT                 /**/(x, y, z) { return this.G_U32_2(x, y, z); }
	private G_R32G32_SINT                 /**/(x, y, z) { return this.G_S32_2(x, y, z); }
	private G_D32_FLOAT_S8X24_UINT        /**/(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; return new Vec4(this.View.getFloat32(o), this.View.getUint8(o + 4), 0, 0); }
	private G_R32_FLOAT_X8X24_TYPELESS    /**/(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; return new Vec4(this.View.getFloat32(o), 0, 0, 0); }
	private G_X32_TYPELESS_G8X24_UINT     /**/(x, y, z) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; return new Vec4(0, this.View.getUint8(o + 4), 0, 0); }
	private G_R10G10B10A2_UNORM           /**/(x, y, z) { return this.G_U10_3_U2(x, y, z).Div(new Vec4(1023, 1023, 1023, 3)); }
	private G_R10G10B10A2_UINT            /**/(x, y, z) { return this.G_U10_3_U2(x, y, z); }
	//private G_R11G11B10_FLOAT             /**/(x, y, z) { return Vec4.Zero; } // TODO: Implement R11 and R10
	private G_R8G8B8A8_UNORM              /**/(x, y, z) { return this.G_U8_4(x, y, z).Div(255); }
	private G_R8G8B8A8_UNORM_SRGB         /**/(x, y, z) { return this.G_U8_4(x, y, z).Div(255); }
	private G_R8G8B8A8_UINT               /**/(x, y, z) { return this.G_U8_4(x, y, z); }
	private G_R8G8B8A8_SNORM              /**/(x, y, z) { return this.G_S8_4(x, y, z).Div(128); }
	private G_R8G8B8A8_SINT               /**/(x, y, z) { return this.G_S8_4(x, y, z); }
	private G_R16G16_FLOAT                /**/(x, y, z) { return this.G_R16_2(x, y, z); }
	private G_R16G16_UNORM                /**/(x, y, z) { return this.G_U16_2(x, y, z).Div(65535); }
	private G_R16G16_UINT                 /**/(x, y, z) { return this.G_U16_2(x, y, z); }
	private G_R16G16_SNORM                /**/(x, y, z) { return this.G_S16_4(x, y, z).Div(32768); }
	private G_R16G16_SINT                 /**/(x, y, z) { return this.G_S16_4(x, y, z); }
	private G_D32_FLOAT                   /**/(x, y, z) { return this.View.getFloat32(z * this.SlicePitch + y * this.RowPitch + x * 4); }
	private G_R32_FLOAT                   /**/(x, y, z) { return this.View.getFloat32(z * this.SlicePitch + y * this.RowPitch + x * 4); }
	private G_R32_UINT                    /**/(x, y, z) { return this.View.getUint32(z * this.SlicePitch + y * this.RowPitch + x * 4); }
	private G_R32_SINT                    /**/(x, y, z) { return this.View.getInt32(z * this.SlicePitch + y * this.RowPitch + x * 4); }
	private G_D24_UNORM_S8_UINT           /**/(x, y, z) { const d = this.View.getUint32(z * this.SlicePitch + y * this.RowPitch + x * 4); return new Vec4((0xffffff & d) / 16777215, 0xff & (d >> 24), 0, 0); }
	private G_R24_UNORM_X8_TYPELESS       /**/(x, y, z) { const d = this.View.getUint32(z * this.SlicePitch + y * this.RowPitch + x * 4); return new Vec4((0xffffff & d) / 16777215, 0, 0, 0); }
	private G_X24_TYPELESS_G8_UINT        /**/(x, y, z) { const d = this.View.getUint32(z * this.SlicePitch + y * this.RowPitch + x * 4); return new Vec4(0, 0xff & (d >> 24), 0, 0); }
	private G_R8G8_UNORM                  /**/(x, y, z) { return this.G_U8_2(x, y, z).Div(255); }
	private G_R8G8_UINT                   /**/(x, y, z) { return this.G_U8_2(x, y, z); }
	private G_R8G8_SNORM                  /**/(x, y, z) { return this.G_S8_2(x, y, z).Div(128); }
	private G_R8G8_SINT                   /**/(x, y, z) { return this.G_S8_2(x, y, z); }
	private G_R16_FLOAT                   /**/(x, y, z) { return new Vec4(AveMath.ReadR16(this.View, z * this.SlicePitch + y * this.RowPitch + x * 2), 0, 0, 0); }
	private G_D16_UNORM                   /**/(x, y, z) { return new Vec4(this.View.getUint16(z * this.SlicePitch + y * this.RowPitch + x * 2) / 65535, 0, 0, 0); }
	private G_R16_UNORM                   /**/(x, y, z) { return new Vec4(this.View.getUint16(z * this.SlicePitch + y * this.RowPitch + x * 2) / 65535, 0, 0, 0); }
	private G_R16_UINT                    /**/(x, y, z) { return new Vec4(this.View.getUint16(z * this.SlicePitch + y * this.RowPitch + x * 2), 0, 0, 0); }
	private G_R16_SNORM                   /**/(x, y, z) { return new Vec4(this.View.getInt16(z * this.SlicePitch + y * this.RowPitch + x * 2) / 32768, 0, 0, 0); }
	private G_R16_SINT                    /**/(x, y, z) { return new Vec4(this.View.getInt16(z * this.SlicePitch + y * this.RowPitch + x * 2), 0, 0, 0); }
	private G_R8_UNORM                    /**/(x, y, z) { return new Vec4(this.View.getUint8(z * this.SlicePitch + y * this.RowPitch + x) / 255, 0, 0, 0); }
	private G_R8_UINT                     /**/(x, y, z) { return new Vec4(this.View.getUint8(z * this.SlicePitch + y * this.RowPitch + x), 0, 0, 0); }
	private G_R8_SNORM                    /**/(x, y, z) { return new Vec4(this.View.getInt8(z * this.SlicePitch + y * this.RowPitch + x) / 128, 0, 0, 0); }
	private G_R8_SINT                     /**/(x, y, z) { return new Vec4(this.View.getInt8(z * this.SlicePitch + y * this.RowPitch + x), 0, 0, 0); }
	private G_A8_UNORM                    /**/(x, y, z) { return new Vec4(this.View.getUint8(z * this.SlicePitch + y * this.RowPitch + x) / 255, 0, 0, 0); }
	private G_R1_UNORM                    /**/(x, y, z) { return new Vec4(1 & this.View.getUint8(z * this.SlicePitch + y * this.RowPitch + (x >> 3)) >> (7 & x), 0, 0, 0); }
	//private G_R9G9B9E5_SHAREDEXP          /**/(x, y, z) { return Vec4.Zero; } // TODO: Implement R9G9B9E5_SHAREDEXP

	// Don't support these format because GetPixel can't read two pixels
	//private G_R8G8_B8G8_UNORM             /**/(x, y, z) { return Vec4.Zero; }
	//private G_G8R8_G8B8_UNORM             /**/(x, y, z) { return Vec4.Zero; }

	// BC formats need to be uncompressed first to read pixels
	//private G_BC1_UNORM                   /**/(x, y, z) { return Vec4.Zero; }
	//private G_BC1_UNORM_SRGB              /**/(x, y, z) { return Vec4.Zero; }
	//private G_BC2_UNORM                   /**/(x, y, z) { return Vec4.Zero; }
	//private G_BC2_UNORM_SRGB              /**/(x, y, z) { return Vec4.Zero; }
	//private G_BC3_UNORM                   /**/(x, y, z) { return Vec4.Zero; }
	//private G_BC3_UNORM_SRGB              /**/(x, y, z) { return Vec4.Zero; }
	//private G_BC4_UNORM                   /**/(x, y, z) { return Vec4.Zero; }
	//private G_BC4_SNORM                   /**/(x, y, z) { return Vec4.Zero; }
	//private G_BC5_UNORM                   /**/(x, y, z) { return Vec4.Zero; }
	//private G_BC5_SNORM                   /**/(x, y, z) { return Vec4.Zero; }
	//private G_BC6H_UF16                   /**/(x, y, z) { return Vec4.Zero; }
	//private G_BC6H_SF16                   /**/(x, y, z) { return Vec4.Zero; }
	//private G_BC7_UNORM                   /**/(x, y, z) { return Vec4.Zero; }
	//private G_BC7_UNORM_SRGB              /**/(x, y, z) { return Vec4.Zero; }

	private G_B5G6R5_UNORM                /**/(x, y, z) { const d = this.View.getUint32(z * this.SlicePitch + y * this.RowPitch + x * 2); return new Vec4((0x1f & (d >> 11)) / 31, (0x3f & (d >> 5)) / 63, (0x1f & d) / 31, 0); }
	private G_B5G5R5A1_UNORM              /**/(x, y, z) { const d = this.View.getUint32(z * this.SlicePitch + y * this.RowPitch + x * 2); return new Vec4((0x1f & (d >> 10)) / 31, (0x1f & (d >> 5)) / 31, (0x1f & d) / 31, 1 & (d >> 15)); }
	private G_B8G8R8A8_UNORM              /**/(x, y, z) { const d = this.G_U8_4(x, y, z).Div(255); return new Vec4(d.b, d.g, d.r, d.a); }
	private G_B8G8R8X8_UNORM              /**/(x, y, z) { const d = this.G_U8_4(x, y, z).Div(255); return new Vec4(d.b, d.g, d.r, 1); }
	// private G_R10G10B10_XR_BIAS_A2_UNORM  /**/(x, y, z) { return Vec4.Zero; } // TODO: Implement R10G10B10_XR_BIAS_A2_UNORM
	private G_B8G8R8A8_UNORM_SRGB         /**/(x, y, z) { const d = this.G_U8_4(x, y, z).Div(255); return new Vec4(d.b, d.g, d.r, d.a); }
	private G_B8G8R8X8_UNORM_SRGB         /**/(x, y, z) { const d = this.G_U8_4(x, y, z).Div(255); return new Vec4(d.b, d.g, d.r, 1); }

	private G_P8                          /**/(x, y, z) { return new Vec4(this.View.getUint8(z * this.SlicePitch + y * this.RowPitch + x) / 255, 0, 0, 0); }
	private G_A8P8                        /**/(x, y, z) { return this.G_U8_2(x, y, z).Div(255); }
	private G_B4G4R4A4_UNORM              /**/(x, y, z) { const d = this.G_U4_4(x, y, z).Div(15); return new Vec4(d.b, d.g, d.r, d.a); }


	private S_R32G32B32A32_FLOAT          /**/(x, y, z, v) { this.S_R32_4(x, y, z, v); }
	private S_R32G32B32A32_UINT           /**/(x, y, z, v) { this.S_U32_4(x, y, z, v); }
	private S_R32G32B32A32_SINT           /**/(x, y, z, v) { this.S_S32_4(x, y, z, v); }
	private S_R32G32B32_FLOAT             /**/(x, y, z, v) { this.S_R32_3(x, y, z, v); }
	private S_R32G32B32_UINT              /**/(x, y, z, v) { this.S_U32_3(x, y, z, v); }
	private S_R32G32B32_SINT              /**/(x, y, z, v) { this.S_S32_3(x, y, z, v); }
	private S_R16G16B16A16_FLOAT          /**/(x, y, z, v) { this.S_R16_4(x, y, z, v); }
	private S_R16G16B16A16_UNORM          /**/(x, y, z, v) { this.S_U16_4(x, y, z, v.Mul(65535)); }
	private S_R16G16B16A16_UINT           /**/(x, y, z, v) { this.S_U16_4(x, y, z, v); }
	private S_R16G16B16A16_SNORM          /**/(x, y, z, v) { this.S_S16_4(x, y, z, v.Mul(32768)); }
	private S_R16G16B16A16_SINT           /**/(x, y, z, v) { this.S_S16_4(x, y, z, v); }
	private S_R32G32_FLOAT                /**/(x, y, z, v) { this.S_R32_2(x, y, z, v); }
	private S_R32G32_UINT                 /**/(x, y, z, v) { this.S_U32_2(x, y, z, v); }
	private S_R32G32_SINT                 /**/(x, y, z, v) { this.S_S32_2(x, y, z, v); }
	private S_D32_FLOAT_S8X24_UINT        /**/(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; this.View.setFloat32(o, v.r); this.View.setUint8(o + 4, v.g); }
	private S_R32_FLOAT_X8X24_TYPELESS    /**/(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; this.View.setFloat32(o, v.r); }
	private S_X32_TYPELESS_G8X24_UINT     /**/(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + x * 8; this.View.setUint8(o + 4, v.g); }
	private S_R10G10B10A2_UNORM           /**/(x, y, z, v) { this.S_U10_3_U2(x, y, z, v.Mul(new Vec4(1023, 1023, 1023, 3))); }
	private S_R10G10B10A2_UINT            /**/(x, y, z, v) { this.S_U10_3_U2(x, y, z, v); }
	//private S_R11G11B10_FLOAT             /**/(x, y, z, v) {} // TODO: Implement R11 and R10
	private S_R8G8B8A8_UNORM              /**/(x, y, z, v) { this.S_U8_4(x, y, z, v.Mul(255)); }
	private S_R8G8B8A8_UNORM_SRGB         /**/(x, y, z, v) { this.S_U8_4(x, y, z, v.Mul(255)); }
	private S_R8G8B8A8_UINT               /**/(x, y, z, v) { this.S_U8_4(x, y, z, v); }
	private S_R8G8B8A8_SNORM              /**/(x, y, z, v) { this.S_S8_4(x, y, z, v.Mul(128)); }
	private S_R8G8B8A8_SINT               /**/(x, y, z, v) { this.S_S8_4(x, y, z, v); }
	private S_R16G16_FLOAT                /**/(x, y, z, v) { this.S_R16_2(x, y, z, v); }
	private S_R16G16_UNORM                /**/(x, y, z, v) { this.S_U16_2(x, y, z, v.Mul(65535)); }
	private S_R16G16_UINT                 /**/(x, y, z, v) { this.S_U16_2(x, y, z, v); }
	private S_R16G16_SNORM                /**/(x, y, z, v) { this.S_S16_4(x, y, z, v.Mul(32768)); }
	private S_R16G16_SINT                 /**/(x, y, z, v) { this.S_S16_4(x, y, z, v); }
	private S_D32_FLOAT                   /**/(x, y, z, v) { this.View.setFloat32(z * this.SlicePitch + y * this.RowPitch + x * 4, v.r); }
	private S_R32_FLOAT                   /**/(x, y, z, v) { this.View.setFloat32(z * this.SlicePitch + y * this.RowPitch + x * 4, v.r); }
	private S_R32_UINT                    /**/(x, y, z, v) { this.View.setUint32(z * this.SlicePitch + y * this.RowPitch + x * 4, v.r); }
	private S_R32_SINT                    /**/(x, y, z, v) { this.View.setInt32(z * this.SlicePitch + y * this.RowPitch + x * 4, v.r); }
	private S_D24_UNORM_S8_UINT           /**/(x, y, z, v) { const d = (0xffffff & (16777215 * v.r)) | (0xff & v.g) << 24; this.View.setUint32(z * this.SlicePitch + y * this.RowPitch + x * 4, d); }
	private S_R24_UNORM_X8_TYPELESS       /**/(x, y, z, v) { const d = 0xffffff & (16777215 * v.r); this.View.setUint32(z * this.SlicePitch + y * this.RowPitch + x * 4, d); }
	private S_X24_TYPELESS_G8_UINT        /**/(x, y, z, v) { const d = (0xff & v.g) << 24; this.View.setUint32(z * this.SlicePitch + y * this.RowPitch + x * 4, d); }
	private S_R8G8_UNORM                  /**/(x, y, z, v) { this.S_U8_2(x, y, z, v.Mul(255)); }
	private S_R8G8_UINT                   /**/(x, y, z, v) { this.S_U8_2(x, y, z, v); }
	private S_R8G8_SNORM                  /**/(x, y, z, v) { this.S_S8_2(x, y, z, v.Mul(255)); }
	private S_R8G8_SINT                   /**/(x, y, z, v) { this.S_S8_2(x, y, z, v); }
	private S_R16_FLOAT                   /**/(x, y, z, v) { AveMath.WriteR16(this.View, z * this.SlicePitch + y * this.RowPitch + x * 2, v.r); }
	private S_D16_UNORM                   /**/(x, y, z, v) { this.View.setUint16(z * this.SlicePitch + y * this.RowPitch + x * 2, v.r * 65535); }
	private S_R16_UNORM                   /**/(x, y, z, v) { this.View.setUint16(z * this.SlicePitch + y * this.RowPitch + x * 2, v.r * 65535); }
	private S_R16_UINT                    /**/(x, y, z, v) { this.View.setUint16(z * this.SlicePitch + y * this.RowPitch + x * 2, v.r); }
	private S_R16_SNORM                   /**/(x, y, z, v) { this.View.setInt16(z * this.SlicePitch + y * this.RowPitch + x * 2, v.r * 32768); }
	private S_R16_SINT                    /**/(x, y, z, v) { this.View.setInt16(z * this.SlicePitch + y * this.RowPitch + x * 2, v.r); }
	private S_R8_UNORM                    /**/(x, y, z, v) { this.View.setUint8(z * this.SlicePitch + y * this.RowPitch + x, v.r * 255); }
	private S_R8_UINT                     /**/(x, y, z, v) { this.View.setUint8(z * this.SlicePitch + y * this.RowPitch + x, v.r); }
	private S_R8_SNORM                    /**/(x, y, z, v) { this.View.setInt8(z * this.SlicePitch + y * this.RowPitch + x, v.r * 128); }
	private S_R8_SINT                     /**/(x, y, z, v) { this.View.setInt8(z * this.SlicePitch + y * this.RowPitch + x, v.r); }
	private S_A8_UNORM                    /**/(x, y, z, v) { this.View.setUint8(z * this.SlicePitch + y * this.RowPitch + x, v.r * 255); }
	private S_R1_UNORM                    /**/(x, y, z, v) { const o = z * this.SlicePitch + y * this.RowPitch + (x >> 3); this.View.setUint8(o, this.View.getUint8(o) & ~(1 << (7 & x)) | (v.r ? 1 : 0) << (7 & x)); }
	//private S_R9G9B9E5_SHAREDEXP          /**/(x, y, z, v) {} // TODO: Implement R9G9B9E5_SHAREDEXP

	private S_B5G6R5_UNORM                /**/(x, y, z, v) { const d = (0x1f & (v.b * 31)) | (0x3f & (v.g * 63)) << 5 | (0x1f & (v.r * 31)) << 11; this.View.setUint32(z * this.SlicePitch + y * this.RowPitch + x * 2, d); }
	private S_B5G5R5A1_UNORM              /**/(x, y, z, v) { const d = (0x1f & (v.b * 31)) | (0x1f & (v.g * 31)) << 5 | (0x1f & (v.r * 31)) << 10 | (0x1 & v.r) << 15; this.View.setUint32(z * this.SlicePitch + y * this.RowPitch + x * 2, d); }
	private S_B8G8R8A8_UNORM              /**/(x, y, z, v) { const d = new Vec4(v.b, v.g, v.r, v.a); this.S_U8_4(x, y, z, v.Mul(255)); }
	private S_B8G8R8X8_UNORM              /**/(x, y, z, v) { const d = new Vec4(v.b, v.g, v.r, 1); this.S_U8_4(x, y, z, v.Mul(255)); }
	// private S_R10G10B10_XR_BIAS_A2_UNORM  /**/(x, y, z, v) {} // TODO: Implement R10G10B10_XR_BIAS_A2_UNORM
	private S_B8G8R8A8_UNORM_SRGB         /**/(x, y, z, v) { const d = new Vec4(v.b, v.g, v.r, v.a); this.S_U8_4(x, y, z, v.Mul(255)); }
	private S_B8G8R8X8_UNORM_SRGB         /**/(x, y, z, v) { const d = new Vec4(v.b, v.g, v.r, 1); this.S_U8_4(x, y, z, v.Mul(255)); }

	private S_P8                          /**/(x, y, z, v) { this.View.setUint8(z * this.SlicePitch + y * this.RowPitch + x, v.r * 255); }
	private S_A8P8                        /**/(x, y, z, v) { this.S_U8_2(x, y, z, v.Mul(255)); }
	private S_B4G4R4A4_UNORM              /**/(x, y, z, v) { const d = new Vec4(v.b, v.g, v.r, v.a); this.S_U4_4(x, y, z, v.Mul(15)); }
}

// prettier-ignore
export enum PixFormat {
	UNKNOWN	                    /**/ = 0,
	R32G32B32A32_TYPELESS       /**/ = 1,
	R32G32B32A32_FLOAT          /**/ = 2,
	R32G32B32A32_UINT           /**/ = 3,
	R32G32B32A32_SINT           /**/ = 4,
	R32G32B32_TYPELESS          /**/ = 5,
	R32G32B32_FLOAT             /**/ = 6,
	R32G32B32_UINT              /**/ = 7,
	R32G32B32_SINT              /**/ = 8,
	R16G16B16A16_TYPELESS       /**/ = 9,
	R16G16B16A16_FLOAT          /**/ = 10,
	R16G16B16A16_UNORM          /**/ = 11,
	R16G16B16A16_UINT           /**/ = 12,
	R16G16B16A16_SNORM          /**/ = 13,
	R16G16B16A16_SINT           /**/ = 14,
	R32G32_TYPELESS             /**/ = 15,
	R32G32_FLOAT                /**/ = 16,
	R32G32_UINT                 /**/ = 17,
	R32G32_SINT                 /**/ = 18,
	R32G8X24_TYPELESS           /**/ = 19,
	D32_FLOAT_S8X24_UINT        /**/ = 20,
	R32_FLOAT_X8X24_TYPELESS    /**/ = 21,
	X32_TYPELESS_G8X24_UINT     /**/ = 22,
	R10G10B10A2_TYPELESS        /**/ = 23,
	R10G10B10A2_UNORM           /**/ = 24,
	R10G10B10A2_UINT            /**/ = 25,
	R11G11B10_FLOAT             /**/ = 26,
	R8G8B8A8_TYPELESS           /**/ = 27,
	R8G8B8A8_UNORM              /**/ = 28,
	R8G8B8A8_UNORM_SRGB         /**/ = 29,
	R8G8B8A8_UINT               /**/ = 30,
	R8G8B8A8_SNORM              /**/ = 31,
	R8G8B8A8_SINT               /**/ = 32,
	R16G16_TYPELESS             /**/ = 33,
	R16G16_FLOAT                /**/ = 34,
	R16G16_UNORM                /**/ = 35,
	R16G16_UINT                 /**/ = 36,
	R16G16_SNORM                /**/ = 37,
	R16G16_SINT                 /**/ = 38,
	R32_TYPELESS                /**/ = 39,
	D32_FLOAT                   /**/ = 40,
	R32_FLOAT                   /**/ = 41,
	R32_UINT                    /**/ = 42,
	R32_SINT                    /**/ = 43,
	R24G8_TYPELESS              /**/ = 44,
	D24_UNORM_S8_UINT           /**/ = 45,
	R24_UNORM_X8_TYPELESS       /**/ = 46,
	X24_TYPELESS_G8_UINT        /**/ = 47,
	R8G8_TYPELESS               /**/ = 48,
	R8G8_UNORM                  /**/ = 49,
	R8G8_UINT                   /**/ = 50,
	R8G8_SNORM                  /**/ = 51,
	R8G8_SINT                   /**/ = 52,
	R16_TYPELESS                /**/ = 53,
	R16_FLOAT                   /**/ = 54,
	D16_UNORM                   /**/ = 55,
	R16_UNORM                   /**/ = 56,
	R16_UINT                    /**/ = 57,
	R16_SNORM                   /**/ = 58,
	R16_SINT                    /**/ = 59,
	R8_TYPELESS                 /**/ = 60,
	R8_UNORM                    /**/ = 61,
	R8_UINT                     /**/ = 62,
	R8_SNORM                    /**/ = 63,
	R8_SINT                     /**/ = 64,
	A8_UNORM                    /**/ = 65,
	R1_UNORM                    /**/ = 66,
	R9G9B9E5_SHAREDEXP          /**/ = 67,
	R8G8_B8G8_UNORM             /**/ = 68,
	G8R8_G8B8_UNORM             /**/ = 69,
	BC1_TYPELESS                /**/ = 70,
	BC1_UNORM                   /**/ = 71,
	BC1_UNORM_SRGB              /**/ = 72,
	BC2_TYPELESS                /**/ = 73,
	BC2_UNORM                   /**/ = 74,
	BC2_UNORM_SRGB              /**/ = 75,
	BC3_TYPELESS                /**/ = 76,
	BC3_UNORM                   /**/ = 77,
	BC3_UNORM_SRGB              /**/ = 78,
	BC4_TYPELESS                /**/ = 79,
	BC4_UNORM                   /**/ = 80,
	BC4_SNORM                   /**/ = 81,
	BC5_TYPELESS                /**/ = 82,
	BC5_UNORM                   /**/ = 83,
	BC5_SNORM                   /**/ = 84,
	B5G6R5_UNORM                /**/ = 85,
	B5G5R5A1_UNORM              /**/ = 86,
	B8G8R8A8_UNORM              /**/ = 87,
	B8G8R8X8_UNORM              /**/ = 88,
	R10G10B10_XR_BIAS_A2_UNORM  /**/ = 89,
	B8G8R8A8_TYPELESS           /**/ = 90,
	B8G8R8A8_UNORM_SRGB         /**/ = 91,
	B8G8R8X8_TYPELESS           /**/ = 92,
	B8G8R8X8_UNORM_SRGB         /**/ = 93,
	BC6H_TYPELESS               /**/ = 94,
	BC6H_UF16                   /**/ = 95,
	BC6H_SF16                   /**/ = 96,
	BC7_TYPELESS                /**/ = 97,
	BC7_UNORM                   /**/ = 98,
	BC7_UNORM_SRGB              /**/ = 99,
	AYUV                        /**/ = 100,
	Y410                        /**/ = 101,
	Y416                        /**/ = 102,
	NV12                        /**/ = 103,
	P010                        /**/ = 104,
	P016                        /**/ = 105,
	_420_OPAQUE                 /**/ = 106,
	YUY2                        /**/ = 107,
	Y210                        /**/ = 108,
	Y216                        /**/ = 109,
	NV11                        /**/ = 110,
	AI44                        /**/ = 111,
	IA44                        /**/ = 112,
	P8                          /**/ = 113,
	A8P8                        /**/ = 114,
	B4G4R4A4_UNORM              /**/ = 115,

	// Xbox
	R10G10B10_7E3_A2_FLOAT      /**/ = 116,
	R10G10B10_6E4_A2_FLOAT      /**/ = 117,
	D16_UNORM_S8_UINT           /**/ = 118,
	R16_UNORM_X8_TYPELESS       /**/ = 119,
	X16_TYPELESS_G8_UINT        /**/ = 120,

	// Windows 10
	P208                        /**/ = 130,
	V208                        /**/ = 131,
	V408                        /**/ = 132,

	// Xbox
	R10G10B10_SNORM_A2_UNORM    /**/ = 189,
	R4G4_UNORM                  /**/ = 190,

	// ----------------------------------------------------------------------------------------------------
	// Other

	// Imagination Technologies PowerVR (Apple iPhone, Apple iPad, SAMSUMG I9000/P3100...)
	PVRTC2_RGB                  /**/ = 0x70000000,
	PVRTC2_RGBA                 /**/ = 0x70000001,
	PVRTC4_RGB                  /**/ = 0x70000002,
	PVRTC4_RGBA                 /**/ = 0x70000003,

	// OpenGL ES Standard ( All deviccs )
	ETC1                        /**/ = 0x70100000,

	// Qualcomm Adreno (HTC G10/G14..., mi1, mi2...)
	ATITC_RGB                   /**/ = 0x70200000,
	ATITC_RGBA                  /**/ = 0x70200001,
	ATITC_PRGBA                 /**/ = 0x70200002,
}
