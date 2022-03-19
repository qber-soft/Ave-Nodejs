import { AveLib } from "../AveLib";
import { CultureId } from "../Culture";
import { Window } from "./Control/UiWindow";

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
    new (): IApp;

    //----------------------------------------------------------------------------------------------------
    // Resource related

    // Add an indexed package resource file
    ResAddPackageIndex(sIndex: string, sRoot: string): boolean;

    // Add a packaged resource file
    ResAddPackage(sFile: string): boolean;

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
    // Events
    OnExit(fn: (nExitCode: number) => void): void;
    OnLanguageChange(fn: () => void): void;
}

export class App extends (AveLib.UiApp as IApp) {}
