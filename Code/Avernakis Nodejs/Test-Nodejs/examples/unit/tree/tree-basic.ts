import { Window, Tree, TreeInsert, TreeGenericHandle, TreeItemFlag } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
	const tree = new Tree(window);
	tree.OnSelectionChange((sender) => {
		const handler = sender.ItemGetSelection();
		const treeItem = sender.ItemGet(handler);
		console.log(`select ${treeItem.Text}`);
	});

	const A = new TreeInsert();
	A.Parent = TreeGenericHandle.Root;
	A.After = TreeGenericHandle.Last;
	A.Item.Flag = TreeItemFlag.Text;
	A.Item.Text = "A";
	const handlerA = tree.ItemInsert(A);

	const B = new TreeInsert();
	B.Parent = handlerA;
	B.After = TreeGenericHandle.Last;
	B.Item.Flag = TreeItemFlag.Text;
	B.Item.Text = "B";
	tree.ItemInsert(B);

	const C = new TreeInsert();
	C.Parent = handlerA;
	C.After = TreeGenericHandle.First;
	C.Item.Flag = TreeItemFlag.Text;
	C.Item.Text = "C";
	const handlerC = tree.ItemInsert(C);

	const D = new TreeInsert();
	D.Parent = handlerC;
	D.After = TreeGenericHandle.Last;
	D.Item.Flag = TreeItemFlag.Text;
	D.Item.Text = "D";
	tree.ItemInsert(D);

	const container = getControlDemoContainer(window, 1, 500, 300);
	container.ControlAdd(tree).SetGrid(1, 1);
	window.SetContent(container);
}
