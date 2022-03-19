import { Window, Calendar, TimePoint } from "../../../src";
import { getControlDemoContainer } from "../utility";

export function main(window: Window) {
    const calendar = new Calendar(window);
    calendar.SetDate(new TimePoint(2021, 11, 5));
    calendar.SetDateMark(new TimePoint(2021, 11, 5));

    const container = getControlDemoContainer(window, 1, 500, 500);
    container.ControlAdd(calendar).SetGrid(1, 1);
    window.SetContent(container);
}
