import { Window, CheckBox, Grid, CheckValue } from "../../../src";

export function main(window: Window) {
    const container = getControlDemoContainer(window);

    //
    let useAllCheckbox: CheckBox = null;

    //
    const checkBoxes: CheckBox[] = [];
    const updateCheckBoxes = (checkAll: boolean) => {
        checkBoxes.forEach((each) =>
            each.SetValue(checkAll ? CheckValue.Checked : CheckValue.Unchecked)
        );
    };

    //
    const currentChecked: Set<string> = new Set();
    const updateCurrentChecked = (name: string, checked: boolean) => {
        if (checked) {
            currentChecked.add(name);
        } else {
            currentChecked.delete(name);
        }

        if (currentChecked.size === 0) {
            useAllCheckbox.SetValue(CheckValue.Unchecked);
        } else if (currentChecked.size === checkBoxes.length) {
            useAllCheckbox.SetValue(CheckValue.Checked);
        } else {
            useAllCheckbox.SetValue(CheckValue.Mixed);
        }
    };

    //
    const checkBoxCallback = (sender: CheckBox) => {
        const checkValue = sender.GetValue();
        updateCurrentChecked(
            sender.GetText(),
            checkValue === CheckValue.Checked
        );
    };

    //
    {
        const checkBox = new CheckBox(window);
        useAllCheckbox = checkBox;

        checkBox.SetText("Use all");
        checkBox.SetTriple(true);
        checkBox.OnChecking((sender: CheckBox) => {
            const current = sender.GetValue();
            console.log("current", current);
            console.log("next", sender.GetNextValue());

            if (current === CheckValue.Unchecked) {
                updateCheckBoxes(true);
                return true;
            } else if (current === CheckValue.Checked) {
                checkBox.SetValue(CheckValue.Unchecked);
                updateCheckBoxes(false);
                return false;
            } else if (current === CheckValue.Mixed) {
                checkBox.SetValue(CheckValue.Checked);
                updateCheckBoxes(true);
                return false;
            }
        });

        container.ControlAdd(checkBox).SetGrid(1, 1);
    }

    {
        const checkBox = new CheckBox(window);
        checkBoxes.push(checkBox);

        checkBox.SetText("React");
        checkBox.OnCheck(checkBoxCallback);

        container.ControlAdd(checkBox).SetGrid(1, 2);
    }

    {
        const checkBox = new CheckBox(window);
        checkBoxes.push(checkBox);

        checkBox.SetText("Vue");
        checkBox.OnCheck(checkBoxCallback);

        container.ControlAdd(checkBox).SetGrid(2, 2);
    }

    {
        const checkBox = new CheckBox(window);
        checkBoxes.push(checkBox);

        checkBox.SetText("Svelte");
        checkBox.OnCheck(checkBoxCallback);

        container.ControlAdd(checkBox).SetGrid(3, 2);
    }

    window.SetContent(container);
}

function getControlDemoContainer(window: Window, count = 1) {
    const container = new Grid(window);
    container.ColAddSlice(1);
    container.ColAddDpx(...Array.from<number>({ length: count }).fill(120));
    container.ColAddDpx(...Array.from<number>({ length: count }).fill(120));
    container.ColAddSlice(1);

    container.RowAddSlice(1);
    container.RowAddDpx(...Array.from<number>({ length: count }).fill(32));
    container.RowAddDpx(...Array.from<number>({ length: count }).fill(32));
    container.RowAddSlice(1);
    return container;
}
