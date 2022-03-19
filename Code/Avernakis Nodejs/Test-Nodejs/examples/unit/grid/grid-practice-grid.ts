import { Window, Grid, Vec4 } from "../../../src";

const Color = {
    White: new Vec4(255, 255, 255, 255),
    DarkBlue: new Vec4(0, 146, 255, 255),
    LightBlue: new Vec4(0, 146, 255, 255 * 0.75),
};

function createGrid(color: Vec4, window: Window) {
    return new Grid(window).SetBackColor(color);
}

export function main(window: Window) {
    const grid = new Grid(window);

    // 添加24列
    grid.ColAddSlice(...Array.from<number>({ length: 24 }).fill(1));
    // 有颜色的那一行为50dpx，间隙（空白的行）为25dpx
    grid.RowAddDpx(...[50, 25, 50, 25, 50, 25, 50, 25]);

    //
    grid.ControlAdd(createGrid(Color.LightBlue, window)).SetGrid(0, 0, 24, 1);
    grid.ControlAdd(createGrid(Color.White, window)).SetGrid(0, 1, 24, 1);

    grid.ControlAdd(createGrid(Color.LightBlue, window)).SetGrid(0, 2, 12, 1);
    grid.ControlAdd(createGrid(Color.DarkBlue, window)).SetGrid(12, 2, 12, 1);
    grid.ControlAdd(createGrid(Color.White, window)).SetGrid(0, 3, 24, 1);

    grid.ControlAdd(createGrid(Color.LightBlue, window)).SetGrid(0, 4, 8, 1);
    grid.ControlAdd(createGrid(Color.DarkBlue, window)).SetGrid(8, 4, 8, 1);
    grid.ControlAdd(createGrid(Color.LightBlue, window)).SetGrid(16, 4, 8, 1);
    grid.ControlAdd(createGrid(Color.White, window)).SetGrid(0, 5, 24, 1);

    grid.ControlAdd(createGrid(Color.LightBlue, window)).SetGrid(0, 6, 6, 1);
    grid.ControlAdd(createGrid(Color.DarkBlue, window)).SetGrid(6, 6, 6, 1);
    grid.ControlAdd(createGrid(Color.LightBlue, window)).SetGrid(12, 6, 6, 1);
    grid.ControlAdd(createGrid(Color.DarkBlue, window)).SetGrid(18, 6, 6, 1);

    window.SetContent(grid);
}
