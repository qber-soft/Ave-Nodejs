import { AveLib } from "../AveLib";
import { Vec4 } from "../Math";
import { AnimationFrame, AnimationInfo, BlendOption, ImageBox, ImageData, ImageChannel, ImageDimension, ImageFilterType, ImageMetadata, ImageRotateType, PixFormat } from "./ImgCommon";

export interface IAveImage {
	new (): IAveImage;

	CreateFromMeta(md: ImageMetadata): boolean;
	CreateFromMetaArray(md: ImageMetadata[]): boolean;
	Create1D(nFormat: PixFormat, nLength: number, nArrayCount: number, nMipLevel: number): boolean;
	Create2D(nFormat: PixFormat, nWidth: number, nHeight: number, nArrayCount: number, nMipLevel: number): boolean;
	Create3D(nFormat: PixFormat, nWidth: number, nHeight: number, nDepth: number, nMipLevel: number): boolean;
	CreateCube(nFormat: PixFormat, nLength: number, nArrayCount: number, nMipLevel: number): boolean;

	CreateFromImage(nDimension: ImageDimension, pImage: ImageData): boolean;
	CreateFromImages(nDimension: ImageDimension, pImage: ImageData[], bIsCube: boolean): boolean;
	CreateCheckerGrid(nFormat: PixFormat, nDimension: ImageDimension, nImageSize: number, nGridSize: number, vColor0: Vec4, vColor1: Vec4): boolean;

	GetMetadataCount(): number;
	GetMetadata(nIndex: number): ImageMetadata;

	// Find the smallest image which >= desired size.
	// If there is no such an image, the image with largest area will be returned.
	// Use 0 to ignore the specified dimension.
	GetIndexBySize2(nDesiredWidth: number, nDesiredHeight: number, nDesiredDepth: number);
	
	// Find the smallest squre/cube image which >= desired size.
	// If there is no such an image or no squer/cube image, 0 will be returned.
	// Usually this is use to find an icon with the best size
	GetIndexBySize(nDesiredSize: number);

	GetAnimationInfo(): AnimationInfo;
	SetAnimationInfo(ai: AnimationInfo): void;
	GetFrameInfo(): AnimationFrame[];
	SetFrameInfo(pFrame: AnimationFrame[]): boolean;

	GetImageCount(): number;
	GetImage(nMipIndex: number, nArrayIndex: number, nImageIndex: number): ImageData;

	Clone(): AveImage;

	Blend(nSubresource: number, x: number, y: number, z: number, pImage: ImageData, pBlendOption: BlendOption, pSrcBox: ImageBox, nDestIndex: number): boolean;
	CopyFrom(nSubresource: number, x: number, y: number, z: number, pImage: ImageData, pSrcBox: ImageBox, nDestIndex: number): boolean;
	CopyTo(pTarget: ImageData, x: number, y: number, z: number, nSrcSubresource: number, pSrcBox: ImageBox, nSrcIndex: number): ImageData;
	PremultiplyAlpha(): boolean;
	DetectAlpha(): boolean;

	// These methods use all mip-levels and output same levels of mips
	FlipRotate(flipX: boolean, flipY: boolean, flipZ: boolean, rotateZ: ImageRotateType, rotateX: ImageRotateType, rotateY: ImageRotateType): AveImage;
	Convert(nFormat: PixFormat, fAlphaRef: number): AveImage;
	ComputeNormal(nFormat: PixFormat, nChannel: ImageChannel, fAmplitude: number): AveImage;

	// These methods use the most detail mip-level and output with 1 mip-level
	Resize(nWidth: number, nHeight: number, nFilter: ImageFilterType): AveImage;

	// These methods use the most detail mip-level and output with specified mip levels
	GenerateMipMaps(nLevelCount: number, nFilter: ImageFilterType, bIndependent3DSlice: boolean): AveImage;
}

export class AveImage extends (AveLib.ImgImage as IAveImage) {
	static FromNative(aveImage: AveImage) {
		const OriginalGetImage = aveImage.GetImage.bind(aveImage);
		aveImage.GetImage = (...args) => ImageData.FromNative(OriginalGetImage(...args));

		const OriginalCopyTo = aveImage.CopyTo.bind(aveImage);
		aveImage.CopyTo = (...args) => ImageData.FromNative(OriginalCopyTo(...args));
		return aveImage;
	}
}
