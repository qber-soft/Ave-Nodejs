import { AveLib } from "../AveLib";
import { Codepage, CultureId, CultureInfo } from "../Culture";
import { IResourceProvider, ResourceSource } from "../Io";
import { Window } from "./Control/UiWindow";
import * as fs from "fs";
import { AveImage, IImageCodec, ImageMetadata } from "../Image";

// You can use your own language files but you also need to apply the text for each control too when the user change the language
// AveUI does support apply language for many standard controls so you can take this advantage for convenient
export enum AppLanguageFileType {
	// ini file style string table with string key, this is the default
	Text,

	// compiled string table with number key (unsigned 32-bit int, except 0)
	// Also this is a close-source language file, normal users are hard to add new languages
	// This is mainly for making games, binary files is way much faster to read than text files
	Binary,
}

export type AppLanguageItem = {
	Path: string; // Language full file path, maybe '' if this is an internal language
	Cid: CultureId;
	NameEnglish: string; // Language name in English
	NameNative: string; // Language name in the language itself
};

export interface IApp {
	new(): IApp;

	//----------------------------------------------------------------------------------------------------
	// Resource related

	// Add an indexed package resource file
	ResAddPackageIndex(sIndex: string, sRoot: string): boolean;

	// Add a packaged resource file
	ResAddPackage(sFile: string): boolean;

	// Add a packaged resource file data
	ResAddPackageData(data: ArrayBuffer): boolean;

	// Add a resource provider, IResourceProvider is not supported yet
	ResAddResourceProvider(p: (nId: number) => ArrayBuffer | IResourceProvider): void;

	// Set the supported icon sizes
	ResSetIconSizeList(n: number[]): App;

	//----------------------------------------------------------------------------------------------------
	// Multilingual related

	// Set the lanaguage file type to use
	LangSetType(n: AppLanguageFileType): App;

	// Set a folder and file extension to search the language files
	LangSetFileRoot(sFolder: string, sExtensionWithoutDot: string): App;

	// Set the default language table (also means embed language)
	// cid: Which CultureId the default language is
	// v: pass an object like { 'key1': 'string1', 'key2': 'string2', ... }
	LangSetDefaultString(cid: CultureId, v: any): App;

	// Search the language files, this method will be called once so you don't have to call this in normal situation
	LangRefresh(): App;

	// Get all searched languages
	LangGet(): Array<AppLanguageItem>;

	// Create a menu that user can change the language or export the current language
	LangCreateMenu(window: Window, bIncludeExportMenuItem: boolean): any; // TODO: change any to Menu

	// Show a file save dialog to let user pick a file to export the current language (only support AppLanguageFileType.Text)
	LangExport(window: Window): void;

	// Change language, this will cause all controls under AveUI's management to change language
	// This will rise events of IApp.OnLanguageChange and IWindow.OnLanguageChange on all existing windows
	LangSetCurrent(n: CultureId): App;
	LangGetCurrent(): CultureId;

	// Get a localized string from current language table
	LangGetString(key: string | number): string;

	// Get the whole localized string table
	LangGetStringTable(): any;

	//----------------------------------------------------------------------------------------------------
	// Multilingual related
	GetSystemAcp(): Codepage;
	GetSystemCultureId(): CultureId;
	GetCultureInfo(cid: CultureId): CultureInfo;

	//----------------------------------------------------------------------------------------------------
	// Image
	GetImageCodec(): IImageCodec;

	//----------------------------------------------------------------------------------------------------
	// Events
	OnExit(fn: (nExitCode: number) => void): void;
	OnLanguageChange(fn: () => void): void;
}

export class App extends (AveLib.UiApp as IApp) {
	GetImageCodec(): IImageCodec {
		const codec = super.GetImageCodec();

		const OriginalOpen = codec.Open.bind(codec);
		codec.Open = (...args) => AveImage.FromNative(OriginalOpen(...args));

		const OriginalGetMetadata = codec.GetMetadata.bind(codec);
		codec.GetMetadata = (...args) => ImageMetadata.FromNative(OriginalGetMetadata(...args));

		// extension
		codec.OpenFile = (file: string) => codec.Open(ResourceSource.FromFilePath(file));
		codec.OpenArrayBuffer = (ab: ArrayBuffer) => codec.Open(ResourceSource.FromArrayBuffer(ab));
		codec.OpenResource = (id: number) => codec.Open(ResourceSource.FromResource(id));

		codec.GetMetadataFile = (file: string) => codec.GetMetadata(ResourceSource.FromFilePath(file));
		codec.GetMetadataArrayBuffer = (ab: ArrayBuffer) => codec.GetMetadata(ResourceSource.FromArrayBuffer(ab));
		codec.GetMetadataResource = (id: number) => codec.GetMetadata(ResourceSource.FromResource(id));

		return codec;
	}

	CreateResourceMap<IconDataMap extends Record<string, string[]>, Name extends string = keyof IconDataMap & string>(app: App, sizeList: number[], iconDataMap: IconDataMap): Record<Name, number> {
		const map = {} as Record<Name, number>;
		const provider: Record<number, string> = {};

		if (sizeList.length < 1 || sizeList.length > 1024) throw new Error("Invalid sizeList length.");
		if (sizeList[0] <= 0) throw new Error("Invalid sizeList data.");
		for (let i = 1; i < sizeList.length; ++i) if (sizeList[i] <= sizeList[i - 1]) throw new Error("Invalid sizeList data.");

		let subIdCount = sizeList.length;
		if (subIdCount & (subIdCount - 1)) {
			subIdCount |= subIdCount >> 1;
			subIdCount |= subIdCount >> 2;
			subIdCount |= subIdCount >> 4;
			subIdCount |= subIdCount >> 8;
			subIdCount |= subIdCount >> 16;
			++subIdCount;
		}
		const baseId = subIdCount;

		Object.keys(iconDataMap).forEach((name, iconIndex) => {
			const dataList = iconDataMap[name];
			if (sizeList.length != dataList.length) throw new Error("Length of each item in iconDataMap must equals to sizeList's.");
			const primaryId = baseId + iconIndex * subIdCount;
			map[name] = primaryId;
			dataList.forEach((filepath, dataIndex) => (provider[primaryId + dataIndex] = filepath));
		});

		app.ResSetIconSizeList(sizeList);
		app.ResAddResourceProvider((id) => ResourceSource.ToArrayBuffer(fs.readFileSync(provider[id])));

		return map;
	}
}
