import { Window, Button } from "../../../src";
import { getControlDemoContainer, IThemeManager } from "../utility";

export function main(window: Window, themeManager: IThemeManager) {
    const button = new Button(window);
    button.SetText("Toggling Themes");

    let isDark = false;
    button.OnClick((sender) => {
        if (!isDark) {
            themeManager.themeDark.SetStyle(themeManager.theme, 0);
        } else {
            themeManager.theme.ResetTheme();
        }
        isDark = !isDark;
    });

    const container = getControlDemoContainer(window);
    container.ControlAdd(button).SetGrid(1, 1);
    window.SetContent(container);
}
