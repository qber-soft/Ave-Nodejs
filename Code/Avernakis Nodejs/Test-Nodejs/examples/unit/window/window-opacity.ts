import {
    App,
    WindowCreation,
    WindowFlag,
    Window,
    Grid,
    Vec4,
    DockMode,
} from "../../../src";

export function run() {
    const app = new App();
    globalThis.app = app;

    const cpWindow = new WindowCreation();
    cpWindow.Title = "Window";
    cpWindow.Flag |= WindowFlag.Layered;

    const window = new Window(cpWindow);
    globalThis.window = window;

    window.OnCreateContent((sender) => {
        sender.SetBackground(false);

        const grid = new Grid(sender);
        {
            const gridChild = new Grid(sender);
            grid.ControlAdd(gridChild).SetDock(DockMode.Fill);
            const red = new Vec4(0, 0, 255, 255);
            gridChild.SetBackColor(red);
            gridChild.SetOpacity(0.5);
        }
        window.SetContent(grid);
        return true;
    });

    if (!window.CreateWindow()) process.exit(-1);

    window.SetVisible(true);
    window.Activate();
}
