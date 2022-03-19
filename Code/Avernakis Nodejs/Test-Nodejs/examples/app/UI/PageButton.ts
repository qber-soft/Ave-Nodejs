import {
    Button,
    ButtonType,
    Grid,
    IconSource,
    VisualTextLayout,
    Window,
} from "../../../src";
import { ResId } from "../ResId";
import { PageHelper, PageRegister } from "./Page";

class PageButton extends PageHelper<PageButton> {
    NameKey: string = "PageButton";

    OnCreateControl(window: Window) {
        const grid = new Grid(window);
        grid.ColAddDpx(120, 6, 120, 6, 120).RowAddDpx(32, 6, 32);

        let ctl: Button;

        ctl = grid.ControlAdd(new Button(window)).SetGrid(0, 0).GetControl();
        ctl.SetText("Button");

        ctl = grid.ControlAdd(new Button(window)).SetGrid(2, 0).GetControl();
        ctl.SetText("DropDown");
        ctl.SetButtonType(ButtonType.DropDown);

        ctl = grid.ControlAdd(new Button(window)).SetGrid(4, 0).GetControl();
        ctl.SetText("Split");
        ctl.SetButtonType(ButtonType.Split);

        ctl = grid.ControlAdd(new Button(window)).SetGrid(0, 2).GetControl();
        ctl.SetText("Icon");
        ctl.SetVisualTextLayout(VisualTextLayout.HorzVisualText);
        ctl.SetVisual(
            window.CreateManagedIcon(new IconSource(ResId.Icon_Clock_png, 16))
        );

        return grid;
    }
}

export function Register() {
    PageRegister.Register(() => new PageButton());
}
