import { Window, Button, CursorType, MessagePointer, MessageKey, InputModifier, KbKey, Vec2 } from "../../../src";
import { getControlDemoContainer } from "../utility";

const c_PointerTypeString = ["Mouse", "Touch", "Pen", "Unknown"];
const c_ButtonTypeString = ["None", "Main", "Secondary", "Middle", "XButton1", "XButton2"];

// prettier-ignore
const c_KeyName = [
    "None",
    "Escape", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "SysRq", "Scroll", "Pause", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
    "Back", "Tab", "Enter", "Shift", "Control", "Menu", "Space", "LShift", "RShift", "LControl", "RControl", "LMenu", "RMenu", "LWindows", "RWindows", "Application",
    "Minus", "Equal", "LBracket", "RBracket", "Semicolon", "Apostrophe", "Grave", "Backslash", "Comma", "Period", "Slash", "Capital",
    "Insert", "Delete", "Home", "End", "PageUp", "PageDown",
    "Left", "Up", "Right", "Down",
    "NUM 0", "NUM 1", "NUM 2", "NUM 3", "NUM 4", "NUM 5", "NUM 6", "NUM 7", "NUM 8", "NUM 9", "NUM *", "NUM +", "NUM Separator", "NUM -", "NUM .", "NUM /", "NUM Lock", "NUM =",
    "Power", "Sleep", "Wake",
    "MediaPlayPause", "MediaPrevTrack", "MediaNextTrack", "MediaStop", "MediaSelect", "MediaVolumeDown", "MediaVolumeUp",
    "WebHome", "WebSearch", "WebFavorites", "WebRefresh", "WebStop", "WebForward", "WebBack", "Mail", "MyComputer",
    "Button1", "Button2", "Button3", "Button4", "Button5",
    "Kana", "Convert", "NonConvert", "Yen", "Kanji", "Accept", "ModeChange", "Junja", "Final"
];

function IsModifierKey(k: KbKey) {
    switch (k) {
        case KbKey.Control:
        case KbKey.LControl:
        case KbKey.RControl:
        case KbKey.Shift:
        case KbKey.LShift:
        case KbKey.RShift:
        case KbKey.Menu:
        case KbKey.LMenu:
        case KbKey.RMenu:
        case KbKey.LWindows:
        case KbKey.RWindows:
        case KbKey.Application:
            return true;
        default:
            return false;
    }
}

function FormatMessageKey(m: MessageKey) {
    let s: string = "";
    if (InputModifier.Control & m.Modifier) s += "Ctrl + ";
    if (InputModifier.Shift & m.Modifier) s += "Shift + ";
    if (InputModifier.Menu & m.Modifier) s += "Alt + ";
    if (m.Key < c_KeyName.length)
        return s + c_KeyName[m.Key];
    else
        return s + m.Key.toString();
}

function FormatMessagePointer(m: MessagePointer) {
    return `ID=${m.Id}, Type=${c_PointerTypeString[m.Type]}, Pos=(${m.Position.x}, ${m.Position.y}), Button=${c_ButtonTypeString[m.Button]}, Count=${m.Count}`;
}

export function main(window: Window) {
    const button = new Button(window);
    let bEntered = false;
    let vPos = Vec2.Zero;

    const updateButton = () => button.SetText(`${bEntered ? "◆" : "◇"} ${vPos.x}, ${vPos.y}`);
    updateButton();

    button.OnKeyPress((sender, mk) => {
        if (!IsModifierKey(mk.Key))
            console.log(`Key        Press: ${FormatMessageKey(mk)}`);
    });
    button.OnKeyRelease((sender, mk) => {
        if (!IsModifierKey(mk.Key))
            console.log(`Key      Release: ${FormatMessageKey(mk)}`);
    });

    button.OnPointerEnter((sender, mp) => {
        bEntered = true;
        updateButton();
        //console.log("Pointer    Enter:");
    });
    button.OnPointerLeave((sender, mp) => {
        bEntered = false;
        updateButton();
        //console.log("Pointer    Leave:");
    });
    button.OnPointerPress((sender, mp) => {
        console.log(`Pointer    Press: ${FormatMessagePointer(mp)}`);
    });
    button.OnPointerRelease((sender, mp) => {
        console.log(`Pointer  Release: ${FormatMessagePointer(mp)}`);
    });
    button.OnPointerClickNdc((sender, mp) => {
        console.log(`Pointer ClickNdc: ${FormatMessagePointer(mp)}`);
    });
    button.OnPointerMove((sender, mp) => {
        vPos = mp.Position;
        updateButton();
    });
    button.OnPointerVWheel((sender, mp) => {
        console.log(`Pointer   VWheel: ${mp.Mouse.Wheel}`);
    });
    button.OnPointerHWheel((sender, mp) => {
        console.log(`Pointer   HWheel: ${mp.Mouse.Wheel}`);
    });
    button.OnPointerHover((sender, mp) => {
        console.log("Pointer    Hover:");
    });
    button.OnPointerLost((sender, mp) => {
        console.log(`Pointer     Lost: ID=${mp.Id}`);
    });
    button.OnPointerCursor((sender, mp) => {
        return CursorType.Link;
    });

    const container = getControlDemoContainer(window);
    container.ControlAdd(button).SetGrid(1, 1);
    window.SetContent(container);
}
