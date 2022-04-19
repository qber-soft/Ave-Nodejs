import { IControl } from "../UiControl";
import { AveLib } from "../../AveLib";
import { WindowLike } from "../Control/UiWindow";
import { RibbonGroup } from "./UiRibbonGroup";

export interface IRibbonTab extends IControl {
	new (window: WindowLike, key?: string | number): IRibbonTab;

	SetText(s: string): RibbonTab;
	GetText(): string;

	GroupGetCount(): number;
	GroupAdd(pChild: RibbonGroup): boolean;
	GroupInsert(nInsertBefore: number, pChild: RibbonGroup): boolean;
	GroupGetByIndex(nIndex: number): RibbonGroup;
	GroupGetById(nId: number): RibbonGroup;
	GroupRemoveByIndex(nIndex: number): RibbonGroup;
	GroupRemoveById(nId: number): RibbonGroup;
	GroupRemove(pChild: RibbonGroup): RibbonGroup;
	GroupRemoveAll(): RibbonTab;
}

export class RibbonTab extends (AveLib.UiRibbonTab as IRibbonTab) {
	private m_Group: Set<RibbonGroup> = new Set();

	GroupAdd(pChild: RibbonGroup) {
		this.m_Group.add(pChild);
		return super.GroupAdd(pChild);
	}

	GroupInsert(nInsertBefore: number, pChild: RibbonGroup) {
		this.m_Group.add(pChild);
		return super.GroupInsert(nInsertBefore, pChild);
	}

	GroupRemoveByIndex(nIndex: number) {
		const t = super.GroupRemoveByIndex(nIndex);
		this.m_Group.delete(t);
		return t;
	}

	GroupRemoveById(nId: number) {
		const t = super.GroupRemoveById(nId);
		this.m_Group.delete(t);
		return t;
	}

	GroupRemove(pChild: RibbonGroup) {
		this.m_Group.delete(pChild);
		return super.GroupRemove(pChild);
	}

	GroupRemoveAll() {
		this.m_Group.clear();
		return super.GroupRemoveAll();
	}
}
