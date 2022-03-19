import { Window, Tab, TabItem, Grid, Vec4 } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const tab = new Tab(window);

    const tabItem1 = new TabItem();
    tabItem1.Id = 1;
    tabItem1.Text = "tab1";
    tab.TabInsert(tabItem1);

    {
        const grid = new Grid(window);
        grid.SetBackColor(new Vec4(0, 146, 255, 255 * 0.75));
        tab.ContentSet(1, grid);
    }

    const tabItem2 = new TabItem();
    tabItem2.Id = 2;
    tabItem2.Text = "tab2";
    tab.TabInsert(tabItem2);

    {
        const grid = new Grid(window);
        grid.SetBackColor(new Vec4(238, 39, 70, 255));
        tab.ContentSet(2, grid);
    }

    const container = getControlDemoContainer(window, 1, 300, 150);
    container.ControlAdd(tab).SetGrid(1, 1);
    window.SetContent(container);
}
