import { Button, Dialog, Grid, Vec2, Window, WindowCreation, WindowFlag } from "../../../../src";
import { PageHelper, PageRegister } from "./../Page";

class PageOwnedWindow extends PageHelper<PageOwnedWindow> {
	NameKey: string = "PageOwnedWindow";

	m_Window: Window;

	OnCreateControl(window: Window) {
		const grid = new Grid(window);
		grid.ColAddDpx(120).RowAddDpx(32, 6, 32);

		let ctl: Button;

		ctl = grid.ControlAdd(new Button(window)).SetGrid(0, 0).GetControl();
		ctl.SetText("Owned Window");
		ctl.OnClick(() => {
			if (!this.m_Window) {
				const cp = new WindowCreation();
				cp.Title = "Owned Window";
				cp.Layout.Size = new Vec2(320, 180);
				this.m_Window = new Window(cp);
			}
			if (!this.m_Window.IsWindowCreated()) this.m_Window.CreateWindow(this.WindowMain.WindowObject);
			if (this.m_Window.IsWindowCreated()) {
				this.m_Window.SetVisible(true);
				this.m_Window.Activate();
			}
		});

		ctl = grid.ControlAdd(new Button(window)).SetGrid(0, 2).GetControl();
		ctl.SetText("Show Dialog");
		ctl.OnClick(async () => {
			const cp = new WindowCreation();
			cp.Title = "Dialog";
			cp.Layout.Size = new Vec2(320, 180);
			const dlg = new Dialog(cp);
			dlg.OnWindowCancel(() => dlg.CloseDialog(0));
			dlg.OnCreateContent((sender) => {
				const grid = new Grid(sender);
				grid.RowAddSlice(1).RowAddDpx(32).RowAddSlice(1);
				grid.ColAddSlice(1).ColAddDpx(120, 4, 120).ColAddSlice(1);

				const btn0 = grid.ControlAdd(new Button(sender)).SetGrid(1, 1).GetControl();
				btn0.SetText("OK");
				btn0.OnClick(() => sender.CloseDialog(1));

				const btn1 = grid.ControlAdd(new Button(sender)).SetGrid(3, 1).GetControl();
				btn1.SetText("Confirm");
				btn1.OnClick(() => sender.CloseDialog(2));

				sender.SetContent(grid);
				return true;
			});
			const result = await dlg.ShowDialog(this.WindowMain.WindowObject);
			console.log(`Dialog Result: ${result}`);
		});

		return grid;
	}
}

export function Register() {
	PageRegister.Register(() => new PageOwnedWindow());
}
