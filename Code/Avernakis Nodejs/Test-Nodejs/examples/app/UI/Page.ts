import { Window, IControl, App } from "../../../src";
import { IWindowMain } from "./WindowMain";

export interface IPage {
	readonly NameKey: string;
	readonly Control: IControl;

	CreateControl(windowMain: IWindowMain, app: App): IControl;

	OnCreateControl(window: Window): IControl;
	OnShow?(): void;
	OnHide?(): void;
	OnApplyLanguage?(): void;
	OnChangeDpiConfig?(): void;
	OnChangeTheme?(): void;
}

export type IPageCreator = () => IPage;

export class PageHelper<T> implements IPage {
	protected App: App;
	protected WindowMain: IWindowMain;

	NameKey: string;
	Control: IControl = null as any;

	CreateControl(windowMain: IWindowMain, app: App): IControl {
		if (this.Control) return null as any;
		this.App = app;
		this.WindowMain = windowMain;
		this.Control = (this as unknown as IPage).OnCreateControl(windowMain.WindowObject);
		return this.Control;
	}

	OnCreateControl(window: Window): IControl {
		throw new Error("Method not implemented.");
	}
}

let m_PageItem: Array<IPageCreator> = [];

export class PageRegister {
	static Register(p: IPageCreator) {
		m_PageItem.push(p);
	}

	static GetPage() {
		return m_PageItem;
	}
}
