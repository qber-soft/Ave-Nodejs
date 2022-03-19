import { Window, Grid, Vec4 } from "../../../src";

export function main(window: Window) {
    const grid = new Grid(window);
    const lightBlue = new Vec4(0, 146, 255, 255 * 0.75);
    grid.SetBackColor(lightBlue);
    window.SetContent(grid);
}
