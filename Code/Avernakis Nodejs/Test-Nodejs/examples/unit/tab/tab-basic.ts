import { Window, Tab, TabItem } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const tab = new Tab(window);

	const tabItem1 = new TabItem();
	tabItem1.Id = 1;
	tabItem1.Text = "tab1";
	tab.TabInsert(tabItem1);

	const tabItem2 = new TabItem();
	tabItem2.Id = 2;
	tabItem2.Text = "tab2";
	tab.TabInsert(tabItem2);

	const container = getControlDemoContainer(window, 1, 300, 150);
	container.ControlAdd(tab).SetGrid(1, 1);
	window.SetContent(container);
}
