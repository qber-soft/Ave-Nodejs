import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { WindowLike } from "./UiWindow";
import { DpiSize, DpiSize_2, DpiMargin } from "../UiCommon";
import { Vec4 } from "../../Math/Vector";

export enum DockMode {
	None,
	Left,
	Top,
	Right,
	Bottom,
	Fill,
}

export enum AnchorMode {
	Left /**/ = 0x1,
	Top /**/ = 0x2,
	Right /**/ = 0x4,
	Bottom /**/ = 0x8,
	All /**/ = Left | Top | Right | Bottom,
	CornerLT /**/ = Left | Top,
	CornerRT /**/ = Right | Top,
	CornerLB /**/ = Left | Bottom,
	CornerRB /**/ = Right | Bottom,
	ExceptL /**/ = All & ~Left,
	ExceptT /**/ = All & ~Top,
	ExceptR /**/ = All & ~Right,
	ExceptB /**/ = All & ~Bottom,
}

export class GridDefinition {
	Size: DpiSize = DpiSize.FromPixel(0);
	Minimum: DpiSize = DpiSize.FromPixel(0);
	Maximum: DpiSize = DpiSize.FromPixel(0);
}

export interface IGridControl<T extends IControl = IControl> {
	GetControl(): T;

	SetDock(v: DockMode): IGridControl<T>;
	GetDock(): DockMode;
	SetAnchor(v: AnchorMode): IGridControl<T>;
	GetAnchor(): AnchorMode;
	SetMargin(v: DpiMargin): IGridControl<T>;
	GetMargin(): DpiMargin;
	SetGrid(x: number, y: number, xspan?: number, yspan?: number): IGridControl<T>;
	GetGrid(): Vec4;
	SetPos(v: DpiSize_2): IGridControl<T>;
	SetPos(x: DpiSize, y: DpiSize): IGridControl<T>;
	SetSize(v: DpiSize_2): IGridControl<T>;
	SetPosZ(v: number): IGridControl<T>;
	GetPosZ(): number;
	BringToFront(): IGridControl<T>;
	BringToBack(): IGridControl<T>;
}

export interface IGrid extends IControl {
	new (x: WindowLike): IGrid;

	SetBackground(b: boolean): Grid;
	GetBackground(): boolean;

	SetBackColor(vColor: Vec4): Grid;
	GetBackColor(): Vec4;

	SetSplitterX(n: DpiSize): Grid;
	GetSplitterX(): DpiSize;
	SetSplitterY(n: DpiSize): Grid;
	GetSplitterY(): DpiSize;

	RowGetClear(): Grid;
	RowGetCount(): number;
	RowGetOffset(nIndex: number): number;
	RowGetSize(nIndex: number): number;
	RowGetDef(nIndex: number): GridDefinition;
	RowAdd(def: GridDefinition): Grid;
	RowInsert(nInsertBefore: number, def: GridDefinition): Grid;
	RowRemove(nIndex: number): Grid;
	RowSet(nIndex: number, def: DpiSize): Grid;
	RowSetDef(nIndex: number, def: GridDefinition): Grid;

	ColGetClear(): Grid;
	ColGetCount(): number;
	ColGetOffset(nIndex: number): number;
	ColGetSize(nIndex: number): number;
	ColGetDef(nIndex: number): GridDefinition;
	ColAdd(def: GridDefinition): Grid;
	ColInsert(nInsertBefore: number, def: GridDefinition): Grid;
	ColRemove(nIndex: number): Grid;
	ColSet(nIndex: number, def: DpiSize): Grid;
	ColSetDef(nIndex: number, def: GridDefinition): Grid;

	ControlAdd(c: IControl, bIsParasite?: boolean): any;
	ControlGet<T extends IControl>(c: T): IGridControl<T>;
	ControlRemove(c: IControl): IControl;
	ControlRemoveAll(): Grid;
}

export class Grid extends (AveLib.UiGrid as IGrid) {
	// prevent gc
	private children: Set<IControl>;

	constructor(window: WindowLike) {
		super(window);
		this.children = new Set();
	}

	RowAdd(defOrSize: GridDefinition | DpiSize, nMin: DpiSize = DpiSize.Zero, nMax: DpiSize = DpiSize.MaxPixel) {
		if (defOrSize instanceof GridDefinition) return super.RowAdd(defOrSize);
		else {
			let gd = new GridDefinition();
			gd.Size = defOrSize;
			gd.Minimum = nMin;
			gd.Maximum = nMax;
			return super.RowAdd(gd);
		}
	}

	RowAddPx(...x: number[]) {
		x.forEach((e) => this.RowAdd(DpiSize.FromPixel(e)));
		return this;
	}

	RowAddDpx(...x: number[]) {
		x.forEach((e) => this.RowAdd(DpiSize.FromPixelScaled(e)));
		return this;
	}

	RowAddSlice(...x: number[]) {
		x.forEach((e) => this.RowAdd(DpiSize.FromSlice(e)));
		return this;
	}

	RowInsert(nInsertBefore: number, defOrSize: GridDefinition | DpiSize, nMin: DpiSize = DpiSize.Zero, nMax: DpiSize = DpiSize.MaxPixel): Grid {
		if (defOrSize instanceof GridDefinition) return super.RowInsert(nInsertBefore, defOrSize);
		else {
			let gd = new GridDefinition();
			gd.Size = defOrSize;
			gd.Minimum = nMin;
			gd.Maximum = nMax;
			return super.RowInsert(nInsertBefore, gd);
		}
	}

	ColAdd(defOrSize: GridDefinition | DpiSize, nMin: DpiSize = DpiSize.Zero, nMax: DpiSize = DpiSize.MaxPixel) {
		if (defOrSize instanceof GridDefinition) return super.ColAdd(defOrSize);
		else {
			let gd = new GridDefinition();
			gd.Size = defOrSize;
			gd.Minimum = nMin;
			gd.Maximum = nMax;
			return super.ColAdd(gd);
		}
	}

	ColAddPx(...x: number[]) {
		x.forEach((e) => this.ColAdd(DpiSize.FromPixel(e)));
		return this;
	}

	ColAddDpx(...x: number[]) {
		x.forEach((e) => this.ColAdd(DpiSize.FromPixelScaled(e)));
		return this;
	}

	ColAddSlice(...x: number[]) {
		x.forEach((e) => this.ColAdd(DpiSize.FromSlice(e)));
		return this;
	}

	ColInsert(nInsertBefore: number, defOrSize: GridDefinition | DpiSize, nMin: DpiSize = DpiSize.Zero, nMax: DpiSize = DpiSize.MaxPixel): Grid {
		if (defOrSize instanceof GridDefinition) return super.ColInsert(nInsertBefore, defOrSize);
		else {
			let gd = new GridDefinition();
			gd.Size = defOrSize;
			gd.Minimum = nMin;
			gd.Maximum = nMax;
			return super.ColInsert(nInsertBefore, gd);
		}
	}

	GetBackColor(): Vec4 {
		return Vec4.FromNative(super.GetBackColor());
	}

	private AddGridExtension<T extends IControl>(gridControl: IGridControl<T>): IGridControl<T> {
		const SetGrid: typeof gridControl.SetGrid = gridControl.SetGrid.bind(gridControl);
		const SetPos: typeof gridControl.SetPos = gridControl.SetPos.bind(gridControl);

		gridControl.SetGrid = (x: number, y: number, xspan: number = 1, yspan: number = 1) => SetGrid(x, y, xspan, yspan);
		gridControl.SetPos = (x: DpiSize | DpiSize_2, y?: DpiSize) => (x instanceof DpiSize_2 ? SetPos(x) : SetPos(new DpiSize_2(x, y)));
		gridControl.BringToFront = () => gridControl.SetPosZ(0);
		gridControl.BringToBack = () => gridControl.SetPosZ(2147483647);

		const OriginalGetGrid = gridControl.GetGrid.bind(gridControl);
		gridControl.GetGrid = (): Vec4 => Vec4.FromNative(OriginalGetGrid());
		return gridControl;
	}

	ControlAdd<T extends IControl>(c: T, bIsParasite: boolean = false) {
		this.children.add(c);
		super.ControlAdd(c, bIsParasite);
		return this.AddGridExtension(super.ControlGet(c));
	}

	ControlGet<T extends IControl>(c: T) {
		return this.AddGridExtension(super.ControlGet(c));
	}

	ControlRemove(c: IControl) {
		this.children.delete(c);
		return super.ControlRemove(c);
	}

	ControlRemoveAll() {
		this.children.clear();
		return super.ControlRemoveAll();
	}
}
