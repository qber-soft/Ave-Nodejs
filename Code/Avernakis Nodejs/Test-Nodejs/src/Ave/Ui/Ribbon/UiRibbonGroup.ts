import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { WindowLike } from "../Control/UiWindow";
import { IVisual } from "../UiVisual";

export interface IRibbonGroup extends IControl {
	new (window: WindowLike, key?: string | number): IRibbonGroup;

	SetText(s: string): RibbonGroup;
	GetText(): string;

	SetDetailButton(bDetailButton: boolean): RibbonGroup;
	GetDetailButton(): boolean;

	SetVisual(pv: IVisual): IVisual;
	GetVisual(): IVisual;

	ControlAdd(pChild: IControl): boolean;
	ControlInsert(nInsertBefore: number, pChild: IControl): boolean;
	ControlGetByIndex(nIndex: number): IControl;
	ControlGetById(nId: number): IControl;
	ControlRemoveByIndex(nIndex: number): IControl;
	ControlRemoveById(nId: number): IControl;
	ControlRemove(pChild: IControl): IControl;
	ControlRemoveAll(): RibbonGroup;

	OnDetailClick(fn: (sender: RibbonGroup) => void): RibbonGroup;
}

export class RibbonGroup extends (AveLib.UiRibbonGroup as IRibbonGroup) {
	private m_Visual: IVisual;
	private m_Control: Set<IControl> = new Set();

	SetVisual(pv: IVisual) {
		this.m_Visual = pv;
		return super.SetVisual(pv);
	}

	ControlAdd(pChild: IControl) {
		this.m_Control.add(pChild);
		return super.ControlAdd(pChild);
	}

	ControlInsert(nInsertBefore: number, pChild: IControl) {
		this.m_Control.add(pChild);
		return super.ControlInsert(nInsertBefore, pChild);
	}

	ControlRemoveByIndex(nIndex: number) {
		const t = super.ControlRemoveByIndex(nIndex);
		this.m_Control.delete(t);
		return t;
	}

	ControlRemoveById(nId: number) {
		const t = super.ControlRemoveById(nId);
		this.m_Control.delete(t);
		return t;
	}

	ControlRemove(pChild: IControl) {
		this.m_Control.delete(pChild);
		return super.ControlRemove(pChild);
	}

	ControlRemoveAll() {
		this.m_Control.clear();
		return super.ControlRemoveAll();
	}
}
