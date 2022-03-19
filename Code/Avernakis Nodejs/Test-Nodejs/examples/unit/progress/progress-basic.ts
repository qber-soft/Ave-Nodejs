import { Window, ProgressBar, Grid } from "../../../src";

export function main(window: Window) {
    const progressBar = new ProgressBar(window);
    progressBar.SetMaximum(100).SetAnimation(true);
    progressBar.SetValue(75);

    const container = getControlDemoContainer(window);
    container.ControlAdd(progressBar).SetGrid(1, 1);
    window.SetContent(container);
}

function getControlDemoContainer(window: Window, count = 1) {
    const container = new Grid(window);
    container.ColAddSlice(1);
    container.ColAddDpx(...Array.from<number>({ length: count }).fill(240));
    container.ColAddSlice(1);

    container.RowAddSlice(1);
    container.RowAddDpx(...Array.from<number>({ length: count }).fill(32));
    container.RowAddSlice(1);
    return container;
}
