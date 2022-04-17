import { ResourceSource } from "../Io";
import { ImageMetadata } from "./ImgCommon";
import { AveImage } from "./ImgImage";

export enum ImageContainerType {
	AVE = 0,
	BMP = 1,
	JPG = 2,
	PNG = 3,
	DDS = 4,
	TGA = 5,
	TIF = 6,
	GIF = 7,
}

export interface IImageCodecExtension {
	OpenFile(file: string): AveImage;
	OpenArrayBuffer(buffer: ArrayBuffer): AveImage;
	OpenResource(nId: number): AveImage;

	GetMetadataFile(file: string): AveImage;
	GetMetadataArrayBuffer(buffer: ArrayBuffer): AveImage;
	GetMetadataResource(nId: number): AveImage;
}

export interface IImageCodec extends IImageCodecExtension {
	Open(res: ResourceSource): AveImage;
	GetMetadata(res: ResourceSource): ImageMetadata;

	SaveFile(file: string, pImage: AveImage, nType: ImageContainerType): boolean;
	SaveArrayBuffer(pImage: AveImage, nType: ImageContainerType): ArrayBuffer;
}
