import { Window, RichListBoxItemVirtual, Grid, RichListBox, HeaderItem, HeaderItemFormat, DpiSize } from "../../../src";

export function main(window: Window) {
	const richListBox = new RichListBox(window);

	//
	const headers = [
		{
			name: "ID",
			align: HeaderItemFormat.Center,
			size: DpiSize.FromPixelScaled(200),
		},
		{
			name: "Name",
			align: HeaderItemFormat.Center,
			size: DpiSize.FromPixelScaled(200),
		},
	];
	headers.forEach((header) => {
		const headerItem = new HeaderItem(header.align, header.name, header.size);
		richListBox.GetHeader().Add(headerItem);
	});

	//
	const data = [
		{ id: 1, name: "a" },
		{ id: 2, name: "b" },
		{ id: 3, name: "c" },
		{ id: 4, name: "d" },
		{ id: 5, name: "e" },
		{ id: 6, name: "f" },
	];
	richListBox.SetVirtual((sender, rowIndex, headerIndex) => {
		const item = new RichListBoxItemVirtual();
		const itemData = data[rowIndex];
		switch (headerIndex) {
			case 0:
				item.String = itemData.id.toString();
				break;
			case 1:
				item.String = itemData.name;
				break;
		}
		return item;
	});
	richListBox.ItemSetCount(data.length);

	//
	richListBox.OnSelectionEnd((sender) => {
		const itemIndex = sender.ItemGetSelection();
		console.log(itemIndex);
	});

	//
	const container = getControlDemoContainer(window);
	container.ControlAdd(richListBox).SetGrid(1, 1);
	window.SetContent(container);
}

function getControlDemoContainer(window: Window, count = 1) {
	const container = new Grid(window);
	container.ColAddSlice(1);
	container.ColAddDpx(...Array.from<number>({ length: count }).fill(410));
	container.ColAddSlice(1);

	container.RowAddSlice(1);
	container.RowAddDpx(...Array.from<number>({ length: count }).fill(300));
	container.RowAddSlice(1);
	return container;
}
