import { AveLib } from "../AveLib";

export interface IPixelMatchConfig {
	threshold: number;
	includeAA: boolean;
	alpha: number;
}

export interface IImageProcessor {
	PixelMatch(a: ArrayBuffer, b: ArrayBuffer, diff: ArrayBuffer, width: number, height: number, config: IPixelMatchConfig): boolean;
}

const processor: IImageProcessor = {
	PixelMatch(...args) {
		return AveLib.AvePixelMatch(...args);
	},
};

export function AveGetImageProcessor(): IImageProcessor {
	return processor;
}
