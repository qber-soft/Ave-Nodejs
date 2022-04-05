import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { Window } from "./UiWindow";
import {
    DpiSize,
    DpiSize_2,
    KnobControlType,
    Rect,
    IconCache,
} from "../UiCommon";
import { Vec4, Vec2 } from "../../Math/Vector";

export enum MatrixUnitType {
    Empty /**/,
    Switch /**/,
    Pointer /**/,
    Value /**/,
    Pie /**/,
    Pan /**/,
    Icon /**/,
    Color /**/,
}

export enum MatrixUnitFlag {
    Default /**/ = 0x0,
    Disabled /**/ = 0x1,
    Hidden /**/ = 0x2,
    Active /**/ = 0x4,
}

export class MatrixUnit {
    Type: MatrixUnitType = MatrixUnitType.Empty;
    Flag: MatrixUnitFlag = MatrixUnitFlag.Default;
    DataValue: number = 0;
    DataIcon: IconCache = 0;
    DataColor: Vec4 = new Vec4();
    BackColor: Vec4 = new Vec4();
    ForeColor: Vec4 = new Vec4();
    FillColor: Vec4 = new Vec4();
}

export interface IMatrixEditorDoc {
    SetDimension(vSize: Vec2): IMatrixEditorDoc;
    GetDimension(): Vec2;

    SetVirtualUnit(
        fn: (sender: IMatrixEditorDoc, x: number, y: number) => MatrixUnit
    ): IMatrixEditorDoc;
    SetVirtualColHeader(
        fn: (sender: IMatrixEditorDoc, n: number) => string
    ): IMatrixEditorDoc;
    SetVirtualRowHeader(
        fn: (sender: IMatrixEditorDoc, n: number) => string
    ): IMatrixEditorDoc;

    SetUnit(x: number, y: number, u: MatrixUnit): IMatrixEditorDoc;
    GetUnit(x: number, y: number): MatrixUnit;
    SetUnitBackColor(vColor: Vec4): IMatrixEditorDoc;
    GetUnitBackColor(): Vec4;
    SetUnitForeColor(vColor: Vec4): IMatrixEditorDoc;
    GetUnitForeColor(): Vec4;
    SetUnitFillColor(vColor: Vec4): IMatrixEditorDoc;
    GetUnitFillColor(): Vec4;

    ColClearName(): IMatrixEditorDoc;
    ColSetName(n: number, s: string): IMatrixEditorDoc;
    ColGetName(n: number): string;
    ColClearSplitter(): IMatrixEditorDoc;
    ColSetSplitter(n: number, nSize: DpiSize): IMatrixEditorDoc;
    ColGetSplitter(n: number): DpiSize;
    ColSetIcon(n: number, nIcon: IconCache): IMatrixEditorDoc;
    ColGetIcon(n: number): IconCache;
    ColSetBackColor(n: number, vColor: Vec4): IMatrixEditorDoc;
    ColGetBackColor(n: number): Vec4;
    ColSetVisible(n: number, b: boolean): IMatrixEditorDoc;
    ColGetVisible(n: number): boolean;
    ColSetEnable(n: number, b: boolean): IMatrixEditorDoc;
    ColGetEnable(n: number): boolean;

    RowClearName(): IMatrixEditorDoc;
    RowSetName(n: number, s: string): IMatrixEditorDoc;
    RowGetName(n: number): string;
    RowClearSplitter(): IMatrixEditorDoc;
    RowSetSplitter(n: number, nSize: DpiSize): IMatrixEditorDoc;
    RowGetSplitter(n: number): DpiSize;
    RowSetIcon(n: number, nIcon: IconCache): IMatrixEditorDoc;
    RowGetIcon(n: number): IconCache;
    RowSetBackColor(n: number, vColor: Vec4): IMatrixEditorDoc;
    RowGetBackColor(n: number): Vec4;
    RowSetVisible(n: number, b: boolean): IMatrixEditorDoc;
    RowGetVisible(n: number): boolean;
    RowSetEnable(n: number, b: boolean): IMatrixEditorDoc;
    RowGetEnable(n: number): boolean;

    ViewSetValueFormat(
        fn: (
            sender: IMatrixEditorDoc,
            x: number,
            y: number,
            v: number
        ) => string
    );

    Redraw(): IMatrixEditorDoc;
}

export interface IMatrixEditor extends IControl {
    new (window: Window): IMatrixEditor;

    DocNew(): MatrixEditor;
    DocGet(): IMatrixEditorDoc;
    DocLink(p: MatrixEditor): MatrixEditor;

    ViewReset(): MatrixEditor;
    ViewCopyFrom(p: MatrixEditor): MatrixEditor;

    ColSetSizeAll(nSize: DpiSize): MatrixEditor;
    ColGetSizeAll(): DpiSize;
    ColSetSize(n: number, nSize: DpiSize): MatrixEditor;
    ColGetSize(n: number): DpiSize;
    ColSetVertical(b: boolean): MatrixEditor;
    ColGetVertical(): boolean;

    RowSetSizeAll(nSize: DpiSize): MatrixEditor;
    RowGetSizeAll(): DpiSize;
    RowSetSize(n: number, nSize: DpiSize): MatrixEditor;
    RowGetSize(n: number): DpiSize;

    ViewSetCornerSize(vSize: DpiSize_2): MatrixEditor;
    ViewGetCornerSize(): DpiSize_2;
    ViewSetCornerContent(c: IControl): IControl;
    ViewGetCornerContent(): IControl;
    ViewSetBack(b: boolean): MatrixEditor;
    ViewGetBack(): boolean;
    ViewSetUnit(b: boolean): MatrixEditor;
    ViewGetUnit(): boolean;
    ViewSetPanel(b: boolean): MatrixEditor;
    ViewGetPanel(): boolean;
    ViewSetColHeader(b: boolean): MatrixEditor;
    ViewGetColHeader(): boolean;
    ViewSetRowHeader(b: boolean): MatrixEditor;
    ViewGetRowHeader(): boolean;
    ViewSetUnitBack(b: boolean): MatrixEditor;
    ViewGetUnitBack(): boolean;
    ViewSetCursor(b: boolean): MatrixEditor;
    ViewGetCursor(): boolean;
    ViewSetCursorEmpty(b: boolean): MatrixEditor;
    ViewGetCursorEmpty(): boolean;
    ViewSetGridX(b: boolean): MatrixEditor;
    ViewGetGridX(): boolean;
    ViewSetGridY(b: boolean): MatrixEditor;
    ViewGetGridY(): boolean;
    ViewSetScrollX(b: boolean): MatrixEditor;
    ViewGetScrollX(): boolean;
    ViewSetScrollY(b: boolean): MatrixEditor;
    ViewGetScrollY(): boolean;

    UnitGetRect(x: number, y: number): Rect;

    SetKnobControlType(nType: KnobControlType): MatrixEditor;
    GetKnobControlType(): KnobControlType;

    GetEditorRect(): Rect;

    OnUnitClick(
        fn: (sender: MatrixEditor, x: number, y: number, u: MatrixUnit) => void
    ): MatrixEditor;
    OnUnitRightClick(
        fn: (sender: MatrixEditor, x: number, y: number, u: MatrixUnit) => void
    ): MatrixEditor;
    OnUnitChange(
        fn: (sender: MatrixEditor, x: number, y: number, u: MatrixUnit) => void
    ): MatrixEditor;
    OnUnitChangeBegin(
        fn: (sender: MatrixEditor, x: number, y: number, u: MatrixUnit) => void
    ): MatrixEditor;
    OnUnitChangeEnd(
        fn: (
            sender: MatrixEditor,
            x: number,
            y: number,
            u: MatrixUnit,
            bCanceled: boolean
        ) => boolean
    ): MatrixEditor; // return false to reject the change, bCanceled is the recommanded behavior.
}

export class MatrixEditor extends (AveLib.UiMatrixEditor as IMatrixEditor) {
    private m_CornerContent: IControl;

    DocGet(): IMatrixEditorDoc {
        const doc = super.DocGet();

        const OriginalGetDimension = doc.GetDimension.bind(doc);
        doc.GetDimension = () => Vec2.FromNative(OriginalGetDimension());

        const OriginalGetUnitBackColor = doc.GetUnitBackColor.bind(doc);
        doc.GetUnitBackColor = () =>
            Vec4.FromNative(OriginalGetUnitBackColor());

        const OriginalGetUnitForeColor = doc.GetUnitForeColor.bind(doc);
        doc.GetUnitForeColor = () =>
            Vec4.FromNative(OriginalGetUnitForeColor());

        const OriginalGetUnitFillColor = doc.GetUnitFillColor.bind(doc);
        doc.GetUnitFillColor = () =>
            Vec4.FromNative(OriginalGetUnitFillColor());

        const OriginalColGetBackColor = doc.ColGetBackColor.bind(doc);
        doc.ColGetBackColor = () => Vec4.FromNative(OriginalColGetBackColor());

        const OriginalRowGetBackColor = doc.RowGetBackColor.bind(doc);
        doc.RowGetBackColor = () => Vec4.FromNative(OriginalRowGetBackColor());

        return doc;
    }

    UnitGetRect(x: number, y: number): Rect {
        return Rect.FromNative(super.UnitGetRect(x, y));
    }

    GetEditorRect(): Rect {
        return Rect.FromNative(super.GetEditorRect());
    }

    ViewSetCornerContent(c: IControl) {
        this.m_CornerContent = c;
        return super.ViewSetCornerContent(c);
    }
}
