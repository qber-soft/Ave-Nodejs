import { AlignType, Byo2Font, CodeEditor, CodeEditorMargin, CodeEditorMarginType, CodeEditorStyleItem, CursorType, Grid, TextBox, Vec4, Window } from "../../../../src";
import { PageHelper, PageRegister } from "./../Page";

enum StyleIndex {
	Default,
	LineNumber,

	Count,
}

class PageCodeEditor extends PageHelper<PageCodeEditor> {
	NameKey: string = "PageCodeEditor";

	OnCreateControl(window: Window) {
		const ce = new CodeEditor(window);

		const vsDef = new CodeEditorStyleItem();
		vsDef.Color.Text = new Vec4(170, 180, 180, 255);

		const vsLineNumber = new CodeEditorStyleItem();
		vsLineNumber.Color.Text = new Vec4(50, 150, 200, 255);
		vsLineNumber.Color.Back = new Vec4(0, 0, 0, 50);

		let fd = window.GetTheme().GetFont();
		fd.Size = 16;
		const fontDef = new Byo2Font(window, fd);

		let marginLineNubmer = new CodeEditorMargin();
		marginLineNubmer.Type = CodeEditorMarginType.LineNumber;
		marginLineNubmer.Style = StyleIndex.LineNumber;
		marginLineNubmer.Align = AlignType.Far;
		marginLineNubmer.Cursor = CursorType.ArrowInvert;

		ce.VsReset(StyleIndex.Count);
		ce.VsSetStyle(StyleIndex.Default, vsDef);
		ce.VsSetStyle(StyleIndex.LineNumber, vsLineNumber);
		ce.VsSetFont(0, fontDef);
		ce.VsSetFont(1, fontDef);
		ce.ViewSetCaretColor(new Vec4(255, 255, 255, 255));

		ce.VmAdd(marginLineNubmer);

		ce.DocGet().OpSetEnable(false); // Disable undo/redo
		ce.DocGet().CharInsert(0, "test\r\nsecond line");
		ce.DocGet().OpSetEnable(true);

		return ce;
	}
}

export function Register() {
	PageRegister.Register(() => new PageCodeEditor());
}
