import { Button, ButtonType, DpiSize, DpiSize_2, Grid, IconSource, Menu, MenuItem, MenuType, PopupParam, Tab, TabItem, TextBox, VisualTextLayout, Window } from "../../../../src";
import { ResId } from "../../ResId";
import { PageHelper, PageRegister } from "./../Page";

class PagePopup extends PageHelper<PagePopup> {
	NameKey: string = "PagePopup";

	OnCreateControl(window: Window) {
		const grid = new Grid(window);
		grid.ColAddDpx(120, 6, 120, 6, 120).RowAddDpx(32, 6, 32);

		let ctl: Button;

		const mnu = grid.ControlAdd(new Menu(window), true).GetControl();
		mnu.InsertItem(new MenuItem(1, MenuType.Section, 0, "Cars"));
		mnu.InsertItem(new MenuItem(2, MenuType.Text, 0, "Cat"));
		mnu.InsertItem(new MenuItem(3, MenuType.Text, 0, "Dog"));
		mnu.InsertItem(new MenuItem(4, MenuType.Content));
		mnu.InsertItem(new MenuItem(100, MenuType.Section, 0, "Animals"));
		mnu.InsertItem(new MenuItem(101, MenuType.Text, 0, "Apple"));
		mnu.InsertItem(new MenuItem(102, MenuType.Text, 0, "Orange"));

		const txt = new TextBox(window);
		txt.SetIdealSize(new DpiSize_2(DpiSize.FromPixelScaled(120),DpiSize.FromPixelScaled(24)));
		txt.SetCue("TextBox");
		mnu.SetContentById(4, txt);


		const gridPopup = grid.ControlAdd(new Grid(window), true).GetControl();


		gridPopup.ColAddDpx(160).RowAddDpx(120);
		gridPopup.SetBackground(true);
		const tab = gridPopup.ControlAdd(new Tab(window)).SetGrid(0, 0).GetControl();
		tab.SetIdealSize(new DpiSize_2(DpiSize.FromPixelScaled(160), DpiSize.FromPixelScaled(120)));
		const tabitem = new TabItem();
		tabitem.Id = 1; tabitem.Text = "Cars"; tab.TabInsert(tabitem);
		tabitem.Id = 2; tabitem.Text = "Animals"; tab.TabInsert(tabitem);

		const grd0 = new Grid(window);
		grd0.ColAddSlice(1).RowAddDpx(24, 4, 24);
		grd0.ControlAdd(new TextBox(window)).SetGrid(0,0);
		grd0.ControlAdd(new Button(window)).SetGrid(0,2).GetControl().SetText("OK").OnClick((sender)=>sender.HidePopup());
		tab.ContentSet(1, grd0);

		ctl = grid.ControlAdd(new Button(window)).SetGrid(0, 0).GetControl();
		ctl.SetText("Popup Menu");
		ctl.OnClick((sender) => {
			const pp = new PopupParam(sender.GetRectClient());
			sender.ShowPopup(mnu, sender.GetRectClient().CornerLB, pp);
		});

		ctl = grid.ControlAdd(new Button(window)).SetGrid(2, 0).GetControl();
		ctl.SetText("Custom Popup");
		ctl.OnClick((sender) => {
			const pp = new PopupParam(sender.GetRectClient());
			sender.ShowPopup(gridPopup, sender.GetRectClient().CornerLB, pp);
		});

		return grid;
	}
}

export function Register() {
	PageRegister.Register(() => new PagePopup());
}
