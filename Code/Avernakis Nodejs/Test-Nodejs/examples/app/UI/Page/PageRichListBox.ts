import { ComboBox, DpiSize, Grid, HeaderItem, HeaderItemFormat, IconSource, RichListBox, RichListBoxItemVirtual, RichListBoxViewMode, StringKey, Window } from "../../../../src";
import { ResId } from "../../ResId";
import { PageHelper, PageRegister } from "./../Page";

class PageRichListBox extends PageHelper<PageRichListBox> {
	NameKey: string = "PageRichListBox";

	OnCreateControl(window: Window) {
		const grid = new Grid(window);
		grid.ColAddSlice(1, 1).RowAddDpx(32, 6).RowAddSlice(1);

		const cboView = grid
			.ControlAdd(new ComboBox(window, new StringKey("PageRichListBoxView", 0, 5)))
			.SetGrid(0, 0)
			.GetControl();
		cboView.Append("", "", "", "", "");
		cboView.Select(0);

		let ctl: RichListBox;

		const icons = [window.CacheIcon(new IconSource(ResId.Icon_Clock_png, 16)), window.CacheIcon(new IconSource(ResId.Icon_Clock_png, 32)), window.CacheIcon(new IconSource(ResId.Icon_Clock_png, 48))];
		let nIconIndex = 0;

		ctl = grid.ControlAdd(new RichListBox(window)).SetGrid(0, 2).GetControl();
		ctl.GetHeader().Add(new HeaderItem(HeaderItemFormat.Right, "ID", DpiSize.FromPixelScaled(80)));
		ctl.GetHeader().Add(new HeaderItem(HeaderItemFormat.Left, "Name", DpiSize.FromPixelScaled(120)));
		ctl.GetHeader().Add(new HeaderItem(HeaderItemFormat.Right, "Size", DpiSize.FromPixelScaled(100)));
		ctl.SetVirtual((s: RichListBox, nIndex: number, nSubIndex: number) => {
			let r = new RichListBoxItemVirtual();
			switch (nSubIndex) {
				case 0:
					r.String = `${nIndex + 1}`;
					r.Icon = icons[nIconIndex];
					break;
				case 1:
					r.String = `Item${nIndex + 1}`;
					break;
				case 2:
					r.String = "1,000 KB";
					break;
			}
			return r;
		});
		ctl.SetIconSize(RichListBoxViewMode.Detail, DpiSize.FromPixelScaled(16));
		ctl.SetIconSize(RichListBoxViewMode.Tile, DpiSize.FromPixelScaled(48));
		ctl.SetIconSize(RichListBoxViewMode.List, DpiSize.FromPixelScaled(16));
		ctl.SetIconNameColumn(1);

		ctl.ItemSetCount(100000);

		cboView.OnSelectionChange((s) => {
			const n = s.GetSelection();
			switch (n) {
				case 0:
					nIconIndex = 0;
					ctl.SetViewMode(RichListBoxViewMode.Detail);
					break;
				case 1:
					nIconIndex = 2;
					ctl.SetViewMode(RichListBoxViewMode.Tile);
					break;
				case 2:
					nIconIndex = 0;
					ctl.SetViewMode(RichListBoxViewMode.Icon).SetIconSize(RichListBoxViewMode.Icon, DpiSize.FromPixelScaled(16));
					break;
				case 3:
					nIconIndex = 1;
					ctl.SetViewMode(RichListBoxViewMode.Icon).SetIconSize(RichListBoxViewMode.Icon, DpiSize.FromPixelScaled(32));
					break;
				case 4:
					nIconIndex = 0;
					ctl.SetViewMode(RichListBoxViewMode.List);
					break;
			}
		});

		return grid;
	}
}

export function Register() {
	PageRegister.Register(() => new PageRichListBox());
}
