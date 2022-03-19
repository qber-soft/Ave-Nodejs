import { Grid, TextBox, Window } from "../../../src";
import { PageHelper, PageRegister } from "./Page";

class PageTextBox extends PageHelper<PageTextBox> {
    NameKey: string = "PageTextBox";

    OnCreateControl(window: Window) {
        const grid = new Grid(window);
        grid.ColAddDpx(200).RowAddDpx(28, 6, 28);

        let ctl: TextBox;

        ctl = grid.ControlAdd(new TextBox(window)).SetGrid(0, 0).GetControl();

        ctl = grid.ControlAdd(new TextBox(window)).SetGrid(0, 2).GetControl();
        ctl.SetIme(true);

        return grid;
    }
}

export function Register() {
    PageRegister.Register(() => new PageTextBox());
}
