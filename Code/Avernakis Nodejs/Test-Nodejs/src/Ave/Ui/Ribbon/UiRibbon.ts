import { IControl } from "../UiControl";
import { AveLib, ExtendControlInstance } from "../../AveLib";
import { WindowLike } from "../Control/UiWindow";
import { RibbonApp } from "./UiRibbonApp";
import { ToolBar } from "../Control/UiToolBar";
import { RibbonTab } from "./UiRibbonTab";
import { DpiSize, Rect } from "../UiCommon";

export interface IRibbon extends IControl {
	new (window: WindowLike): IRibbon;

	GetApp(): RibbonApp;
	GetToolBar(): ToolBar;

	SetBackground(b: boolean): Ribbon;
	GetBackground(): boolean;

	SetMinimized(b: boolean): Ribbon;
	GetMinimized(): boolean;

	SetCanMinimize(b: boolean): Ribbon;
	GetCanMinimize(): boolean;

	SetAutoMinimizeThreshold(n: DpiSize): Ribbon;
	GetAutoMinimizeThreshold(): DpiSize;

	TabGetCount(): number;
	TabAdd(pChild: RibbonTab): boolean;
	TabInsert(nInsertBefore: number, pChild: RibbonTab): boolean;
	TabGetByIndex(nIndex: number): RibbonTab;
	TabGetById(nId: number): RibbonTab;
	TabRemoveByIndex(nIndex: number): RibbonTab;
	TabRemoveById(nId: number): RibbonTab;
	TabRemove(pChild: RibbonTab): RibbonTab;
	TabRemoveAll(): Ribbon;
	TabSelect(nIndex: number): Ribbon;
	TabGetRect(nIndex: number): Rect;
	TabGetContentRect(): Rect;
	TabGetIndex(p: RibbonTab): number;

	SetContent(pControl: IControl): IControl;
	GetContent(): IControl;

	SetAppMenu(pControl: IControl): IControl;
	GetAppMenu(): IControl;

	SetBackstage(pControl: IControl): IControl;
	GetBackstage(): IControl;

	SetBackstageVisible(b: boolean): Ribbon;
	GetBackstageVisible(): boolean;
}

export class Ribbon extends (AveLib.UiRibbon as IRibbon) {
	private m_Content: IControl;
	private m_AppMenu: IControl;
	private m_Backstage: IControl;
	private m_Tab: Set<RibbonTab> = new Set();

	GetApp(): RibbonApp {
		const app = super.GetApp();
		ExtendControlInstance(app);
		return app;
	}

	GetToolBar(): ToolBar {
		const toolbar = super.GetToolBar();
		ExtendControlInstance(toolbar);
		return toolbar;
	}

	TabAdd(pChild: RibbonTab) {
		this.m_Tab.add(pChild);
		return super.TabAdd(pChild);
	}

	TabInsert(nInsertBefore: number, pChild: RibbonTab) {
		this.m_Tab.add(pChild);
		return super.TabInsert(nInsertBefore, pChild);
	}

	TabRemoveByIndex(nIndex: number) {
		const t = super.TabRemoveByIndex(nIndex);
		this.m_Tab.delete(t);
		return t;
	}

	TabRemoveById(nId: number) {
		const t = super.TabRemoveById(nId);
		this.m_Tab.delete(t);
		return t;
	}

	TabRemove(pChild: RibbonTab) {
		this.m_Tab.delete(pChild);
		return super.TabRemove(pChild);
	}

	TabRemoveAll() {
		this.m_Tab.clear();
		return super.TabRemoveAll();
	}

	SetContent(pControl: IControl) {
		this.m_Content = pControl;
		return super.SetContent(pControl);
	}

	SetAppMenu(pControl: IControl) {
		this.m_AppMenu = pControl;
		return super.SetAppMenu(pControl);
	}

	SetBackstage(pControl: IControl) {
		this.m_Backstage = pControl;
		return super.SetBackstage(pControl);
	}

	TabGetRect(nIndex: number): Rect {
		return Rect.FromNative(super.TabGetRect(nIndex));
	}

	TabGetContentRect(): Rect {
		return Rect.FromNative(super.TabGetContentRect());
	}
}
