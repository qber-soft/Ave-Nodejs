import { AveLib } from "../AveLib";
import { AveImage } from "../Image";
import { FileFindItem, IAveStream } from "../Io";

export interface IClipboardVirtualFile {
	GetCount(): number;
	GetInfo(nIndex: number): FileFindItem;
	Open(nIndex: number): IAveStream;
}

export interface IClipboardCopy {
	Commit(): boolean;

	SetText(text: string): void;
	SetImage(img: AveImage): void;
	SetFile(file: string[]): void;
	AddFile(file: string): void;
	AddFiles(file: string[]): void;
}

export interface IClipboard {
	SetText(text: string): boolean;
	GetText(): string;
	HasText(): boolean;

	SetImage(img: AveImage): boolean;
	GetImage(): AveImage;
	HasImage(): boolean;

	SetFile(file: string[]): boolean;
	GetFile(): string[];
	HasFile(): boolean;

	GetVirtualFile(): IClipboardVirtualFile;
	HasVirtualFile(): boolean;

	// Start copy a multi-form clipboard data
	StartCopy(): IClipboardCopy;
}

export function AveGetClipboard(): IClipboard {
	const clipboard = AveLib.AveGetClipboard() as IClipboard;

	const OriginalGetImage = clipboard.GetImage.bind(clipboard);
	clipboard.GetImage = () => AveImage.FromNative(OriginalGetImage());

	return clipboard;
}
