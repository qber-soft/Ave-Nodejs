import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { WindowLike } from "./UiWindow";
import { AlignType, CursorType, DpiSize, ExpandAction, IconCache, InputModifier, KbKey } from "../UiCommon";
import { Byo2Font, Byo2Image } from "../../Byo2";
import { Vec4 } from "../../Math";
import { StringLineEnding } from "../../Common";

// prettier-ignore
export enum CodeEditorCommand {
	//                              Default key binding
	ClipCut                /**/, // Ctrl+X, Cut selected text or current line if there is no selection
	ClipCopy               /**/, // Ctrl+C, Copy selected text or current line if there is no selection
	ClipPaste              /**/, // Ctrl+V
	ClipPasteHistory       /**/, // Ctrl+Shift+V
	ClipLineCut            /**/, //
	ClipLineCopy           /**/, //
	OpUndo                 /**/, // Ctrl+Z
	OpRedo                 /**/, // Ctrl+Y
	ViewZoomIn             /**/, // Ctrl+Shift+,
	ViewZoomOut            /**/, // Ctrl+Shift+.
	ScrollLinePrev         /**/, // *(Variety) Ctrl+Up   | Ctrl+Right
	ScrollLineNext         /**/, // *(Variety) Ctrl+Down | Ctrl+Left
	ScrollPagePrev         /**/, // Ctrl+Alt+PageUp
	ScrollPageNext         /**/, // Ctrl+Alt+PageDown
	ScrollDocStart         /**/, // Ctrl+Alt+Home
	ScrollDocEnd           /**/, // Ctrl+Alt+End
	ScrollToCaret          /**/, // Ctrl+Alt+Backspace
	EditDelete             /**/, // Delete
	EditDeleteBack         /**/, // Backspace
	EditDeleteWord         /**/, // Ctrl+Delete
	EditDeleteWordBack     /**/, // Ctrl+Backspace
	EditDeleteLine         /**/, //
	EditLinePrev           /**/, // *(Variety) Alt+Up   | Alt+Right
	EditLineNext           /**/, // *(Variety) Alt+Down | Alt+Left
	EditLineDuplicate      /**/, //
	EditLineNew            /**/, // Enter
	EditLineNewBefore      /**/, // Ctrl+Enter
	EditLineNewAfter       /**/, // Ctrl+Shift+Enter
	EditCaseLower          /**/, // Ctrl+U
	EditCaseUpper          /**/, // Ctrl+Shift+U
	EditTab                /**/, // Tab
	EditTabBack            /**/, // Shift+Tab
	EditCancel             /**/, // Escape
	EditToggleOverlap      /**/, // Insert
	EditShowSense          /**/, // Ctrl+Space & Ctrl+J
	EditShowInfo           /**/, // Ctrl+Shift+Space
	SelectWord             /**/, // Ctrl+W
	SelectLine             /**/, //
	SelectPara             /**/, //
	SelectAll              /**/, // Ctrl+A
	SelectColumnUp         /**/, // Alt+Shift+Up
	SelectColumnDown       /**/, // Alt+Shift+Down
	SelectColumnLeft       /**/, // Alt+Shift+Left
	SelectColumnRight      /**/, // Alt+Shift+Right
	CaretClusterPrev       /**/, // *(Variety) Left             | Up
	CaretClusterPrevExtend /**/, // *(Variety) Shift+Left       | Shift+Up
	CaretClusterNext       /**/, // *(Variety) Right            | Down
	CaretClusterNextExtend /**/, // *(Variety) Shift+Right      | Shift+Down
	CaretWordPrev          /**/, // *(Variety) Ctrl+Left        | Ctrl+Up
	CaretWordPrevExtend    /**/, // *(Variety) Ctrl+Shift+Left  | Ctrl+Shift+Up
	CaretWordNext          /**/, // *(Variety) Ctrl+Right       | Ctrl+Down
	CaretWordNextExtend    /**/, // *(Variety) Ctrl+Shift+Right | Ctrl+Shift+Down
	CaretWordStart         /**/, //
	CaretWordStartExtend   /**/, //
	CaretWordEnd           /**/, //
	CaretWordEndExtend     /**/, //
	CaretLinePrev          /**/, // *(Variety) Up         | Right
	CaretLinePrevExtend    /**/, // *(Variety) Shift+Up   | Shift+Right
	CaretLineNext          /**/, // *(Variety) Down       | Left
	CaretLineNextExtend    /**/, // *(Variety) Shift+Down | Shift+Left
	CaretLineStart         /**/, // Home
	CaretLineStartExtend   /**/, // Shift+Home
	CaretLineEnd           /**/, // End
	CaretLineEndExtend     /**/, // Shift+End
	CaretParaPrev          /**/, //
	CaretParaPrevExtend    /**/, //
	CaretParaNext          /**/, //
	CaretParaNextExtend    /**/, //
	CaretParaStart         /**/, //
	CaretParaStartExtend   /**/, //
	CaretParaEnd           /**/, //
	CaretParaEndExtend     /**/, //
	CaretPagePrev          /**/, // PageUp
	CaretPagePrevExtend    /**/, // Shift+PageUp
	CaretPageNext          /**/, // PageDown
	CaretPageNextExtend    /**/, // Shift+PageDown
	CaretPageStart         /**/, //
	CaretPageStartExtend   /**/, //
	CaretPageEnd           /**/, //
	CaretPageEndExtend     /**/, //
	CaretDocStart          /**/, // Ctrl+Home
	CaretDocStartExtend    /**/, // Ctrl+Shift+Home
	CaretDocEnd            /**/, // Ctrl+End
	CaretDocEndExtend      /**/, // Ctrl+Shift+End
	CaretBracket           /**/, // Ctrl+]
	CaretBracketExtend     /**/, // Ctrl+Shift+]
	CaretLastEditPos       /**/, // Ctrl+Shift+Backspace
	CaretLastEditPosExtend /**/, //
	CaretMainRotateLeft    /**/, //
	CaretMainRotateRight   /**/, //
	CaretSwapAnchor        /**/, //
	CaretAdd               /**/, // Ctrl+Alt+;
}

export class CodeEditorColor {
	Back: Vec4 = Vec4.Zero;
	Fore: Vec4 = Vec4.Zero;
	Text: Vec4 = Vec4.Zero;
}

export enum CodeEditorMarginType {
	LineNumber,
	Marker,
	Text,
	Folder,
	EditTrack,
}

export class CodeEditorMargin {
	Type: CodeEditorMarginType = CodeEditorMarginType.LineNumber;
	Style: number = 0;
	MarkerMask: number = 0; // only for CodeEditorMarginType::Marker
	TextLine: number = 0; // only for CodeEditorMarginType::Text, This will display the TextLine-th line of the text set by MarginSetText
	PixelWidth: DpiSize = DpiSize.Zero;
	Align: AlignType = AlignType.Near; // only for CodeEditorMarginType::LineNumber, CodeEditorMarginType::Text
	Cursor: CursorType = CursorType.Arrow;
};

export class CodeEditorStyleItem {
	Color: CodeEditorColor = new CodeEditorColor();
	Hidden: boolean = false;
	ReadOnly: boolean = false;
	Click: boolean = false;
}

export enum CodeEditorWrapMode {
	None,
	Char,
	Word,
	Whitespace,
}

export enum CodeEditorAnnotationView {
	Disable,
	BelowLine,
	AboveLine,
}

export enum CodeEditorFlowDirection {
	TopToBottom = 0,
	RightToLeft = 3,
};

export enum CodeEditorOp {
	Insert,
	Remove,
	Custom,
	Complex,
};

export type CodeEditorOpItem = {
	Type: CodeEditorOp;
	String: string;
};

export type CodeEdtiorSyntax = (sender: ICodeEditorDoc, charStart: number, charEnd: number, initialStyleIndex: number) => void;

export interface ICodeEditorDoc {

	//====================================================================================================
	// Doc

	GetLength(): number;
	Reset(): ICodeEditorDoc;

	CharAt(charPos: number): number;
	CharGet(charPos: number, charLength: number): string;
	CharInsert(charPos: number, text: string): ICodeEditorDoc;
	CharRemove(charPos: number, charLength: number): ICodeEditorDoc;

	StyleAt(charPos: number): number;
	StyleGet(charPos: number, charLength: number): number[];
	StyleSetAll(charPos: number, charLength: number, styleIndex: number): boolean;
	StyleSet(charPos: number, styleIndices: number[]): boolean;
	StyleStart(charPos: number): ICodeEditorDoc;
	StyleFillAll(charLength: number, styleIndex: number): boolean;
	StyleFill(styleIndices: number[]): boolean;

	LineGetCount(): number;
	LineIndex(charPos: number): number;
	LineStart(lineIndex: number): number;
	LineEnd(lineIndex: number): number;
	LineEnding(lineIndex: number): StringLineEnding;

	GetReadOnly(): boolean;
	SetReadOnly(b: boolean): ICodeEditorDoc;

	GetDefaultLineEnding(): StringLineEnding;
	SetDefaultLineEnding(lineEnding: StringLineEnding): ICodeEditorDoc;

	//====================================================================================================
	// Op

	OpSetEnable(b: boolean): ICodeEditorDoc;
	OpGetEnable(): boolean;

	OpSetSavePoint(): ICodeEditorDoc;
	OpIsSavePoint(): boolean;

	OpGetUndoCount(): number;
	OpGetRedoCount(): number;

	OpGetUndoRecord(index: number, count: number): CodeEditorOpItem[];
	OpGetRedoRecord(index: number, count: number): CodeEditorOpItem[];

	OpClear(): ICodeEditorDoc;
	OpUndo(count: number): number;
	OpRedo(count: number): number;

	// OpBeginOperationGroup(multiCaret: boolean): ICodeEditorDoc;
	// OpEndOperationGroup(): ICodeEditorDoc;

	// OpAddCustomOperation(data: ArrayBuffer): ICodeEditorDoc;

	//====================================================================================================
	// Marker

	MarkAdd(lineIndex: number, markIndex: number): boolean;
	MarkAddMask(lineIndex: number, markMask: number): boolean;
	MarkRemove(lineIndex: number, markIndex: number): boolean;
	MarkRemoveMask(lineIndex: number, markMask: number): boolean;
	MarkRemoveLine(lineIndex: number): boolean;
	MarkRemoveAllMask(markMask: number): boolean;
	MarkRemoveAll(): boolean;
	MarkGet(lineIndex: number): number;
	MarkGetNextLine(lineIndex: number, markMask: number): number;

	//====================================================================================================
	// Level

	LevelRemoveAll(): ICodeEditorDoc;
	LevelSet(lineIndex: number, level: number): number;
	LevelGet(lineIndex: number): number;

	//====================================================================================================
	// MarginText

	// MarginRemoveAll(): ICodeEditorDoc;
	// MarginSetText(lineIndex: number, text: string): ICodeEditorDoc;
	// MarginSetStyle(lineIndex: number, styleIndex: number): ICodeEditorDoc;
	// MarginSetStyles(lineIndex: number, styleIndices: number[]): ICodeEditorDoc;
	// MarginIsMultipleStyle(lineIndex: number): boolean;
	// MarginGetText(lineIndex: number): string;
	// MarginGetTextSubLine(lineIndex: number, subLine: number): string;
	// MarginGetTextLength(lineIndex: number): number;
	// MarginGetTextLength(lineIndex: number, subLine: number): number;
	// MarginGetTextLineCount(lineIndex: number): number;
	// MarginGetStyle(lineIndex: number): number;
	// MarginGetStyles(lineIndex: number): number[];
	// MarginGetStylesSubLine(lineIndex: number, subLine: number): number[];

	//====================================================================================================
	// Annotation

	// AnnoRemoveAll(): ICodeEditorDoc;
	// AnnoSetText(lineIndex: number, text: string): ICodeEditorDoc;
	// AnnoSetStyle(lineIndex: number, styleIndex: number): ICodeEditorDoc;
	// AnnoSetStyles(lineIndex: number, styleIndices: number[]): ICodeEditorDoc;
	// AnnoIsMultipleStyle(lineIndex: number): boolean;
	// AnnoGetText(lineIndex: number): string;
	// AnnoGetTextSubLine(lineIndex: number, subLine: number): string;
	// AnnoGetTextLength(lineIndex: number): number;
	// AnnoGetTextLength(lineIndex: number, subLine: number): number;
	// AnnoGetTextLineCount(lineIndex: number): number;
	// AnnoGetStyle(lineIndex: number): number;
	// AnnoGetStyles(lineIndex: number): number[];
	// AnnoGetStylesSubLine(lineIndex: number, subLine: number): number[];

	//====================================================================================================
	// Syntax

	// SetSyntax(fnLexer: CodeEdtiorSyntax, fnFolder: CodeEdtiorSyntax): ICodeEditorDoc;

}

export interface ICodeEditor extends IControl {
	new(window: WindowLike): ICodeEditor;

	//====================================================================================================
	// Common

	SetIme(b: boolean): CodeEditor;
	GetIme(): boolean;

	DocNew(): CodeEditor;
	DocGet(): ICodeEditorDoc;
	DocLink(p: CodeEditor): CodeEditor;

	ExecuteCommand(cmd: CodeEditorCommand): boolean;

	//====================================================================================================
	// View

	ViewReset(): CodeEditor;
	ViewCopyFrom(pFrom: CodeEditor): CodeEditor;

	ViewGetMarkerIcon(index: number): IconCache;
	ViewSetMarkerIcon(index: number, icon: IconCache): CodeEditor;

	ViewSetBackImage(img: Byo2Image): CodeEditor;
	ViewGetBackImageOpacity(): number;
	ViewSetBackImageOpacity(fOpacity: number): CodeEditor;

	ViewGetBackColor(): Vec4;
	ViewSetBackColor(color: Vec4): CodeEditor;

	ViewGetLineColor(): CodeEditorColor;
	ViewSetLineColor(color: CodeEditorColor): CodeEditor;

	ViewGetSelectionColor(): Vec4;
	ViewSetSelectionColor(color: Vec4): CodeEditor;

	ViewGetNoFocusSelectionColor(): Vec4;
	ViewSetNoFocusSelectionColor(color: Vec4): CodeEditor;

	ViewGetCaretColor(): Vec4;
	ViewSetCaretColor(color: Vec4): CodeEditor;

	ViewGetSecondaryCaretColor(): Vec4;
	ViewSetSecondaryCaretColor(color: Vec4): CodeEditor;

	ViewGetEolColor(): CodeEditorColor;
	ViewSetEolColor(color: CodeEditorColor): CodeEditor;

	ViewGetSpaceColor(): CodeEditorColor;
	ViewSetSpaceColor(color: CodeEditorColor): CodeEditor;

	ViewGetFoldedColor(): CodeEditorColor;
	ViewSetFoldedColor(color: CodeEditorColor): CodeEditor;

	ViewGetWrapMode(): CodeEditorWrapMode;
	ViewSetWrapMode(mode: CodeEditorWrapMode): CodeEditor;

	ViewGetViewEolSelection(): boolean;
	ViewSetViewEolSelection(b: boolean): CodeEditor;

	ViewGetViewEol(): boolean;
	ViewSetViewEol(b: boolean): CodeEditor;

	ViewGetViewSpace(): boolean;
	ViewSetViewSpace(b: boolean): CodeEditor;

	ViewGetAnnotationView(): CodeEditorAnnotationView;
	ViewSetAnnotationView(view: CodeEditorAnnotationView): CodeEditor;

	ViewGetFlowDirection(): CodeEditorFlowDirection;
	ViewSetFlowDirection(direction: CodeEditorFlowDirection): CodeEditor;

	//====================================================================================================
	// View - Margin

	VmClear(): CodeEditor;
	VmGetCount(): number;
	VmAdd(margin: CodeEditorMargin): CodeEditor;
	VmRemove(index: number): boolean;
	VmGet(index: number): CodeEditorMargin;
	VmSet(index: number, margin: CodeEditorMargin): boolean;

	//====================================================================================================
	// View - Style

	VsReset(count: number): boolean;
	VsGetCount(): number;
	VsAdd(sty: CodeEditorStyleItem, font: Byo2Font): CodeEditor;
	VsGetStyle(index: number): CodeEditorStyleItem;
	VsSetStyle(index: number, sty: CodeEditorStyleItem): boolean;
	VsGetFont(index: number): Byo2Font;
	VsSetFont(index: number, font: Byo2Font): CodeEditor;

	//====================================================================================================
	// View - Display

	VdGetLineExpand(lineIndex: number): boolean;
	VdSetLineExpand(lineIndex: number, action: ExpandAction): boolean;
	VdShowAll(): CodeEditor;

	//====================================================================================================
	// Selection

	//====================================================================================================
	// Key

	KeyDefault(): CodeEditor;
	KeyClear(): CodeEditor;
	KeySet(key: KbKey, modifier: InputModifier, cmd: CodeEditorCommand): boolean;
	KeyRemove(key: KbKey, modifier: InputModifier): boolean;
}

export class CodeEditor extends (AveLib.UiCodeEditor as ICodeEditor) {
}
