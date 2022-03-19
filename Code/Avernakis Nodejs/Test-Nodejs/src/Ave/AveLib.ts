import { IControl } from "./Ui/UiControl";
import { Vec2 } from "./Math/Vector";
import * as fs from "fs";

export interface IControlExtension {
    SetKeyTip(tip: string, nIndex?: number): IControl;
    GetPosition(): Vec2;
    GetSize(): Vec2;
    GetEnableWithParent(): boolean;
}

function AddControlExtension(ControlClass: IControl & { new (): IControl }) {
    return class extends ControlClass implements IControlExtension {
        SetKeyTip(tip: string, nIndex: number = 0): IControl {
            return super.SetKeyTip(tip, nIndex);
        }

        GetPosition() {
            return super.GetRect().Position;
        }

        GetSize() {
            return super.GetRect().Size;
        }

        GetEnableWithParent() {
            let p: IControl = this;
            for (; p && p.GetEnable(); p = p.GetParent());
            return !p;
        }
    };
}

let m_PathSplitter;

function PathRemoveLeaf(s: string) {
    let nIndex = s.lastIndexOf(m_PathSplitter);
    return nIndex >= 0 ? s.substr(0, nIndex) : s;
}

export interface IAppPath {
    // path for reading resources
    readonly AppPath: string;

    // path for writing save data or config files
    readonly SavePath: string;

    InitializeSavePath(bPortableMode: boolean): void;
}

class AppPathImpl implements IAppPath {
    AppPath: string;
    SavePath: string;

    BasePath: string;
    IsDebugFolder: boolean = false;

    InitializeSavePath(bPortableMode: boolean): void {
        if (bPortableMode) {
            try {
                // use user profile path if the apppath can't be written
                fs.accessSync(this.BasePath, fs.constants.W_OK);
                if (this.IsDebugFolder)
                    this.SavePath = this.BasePath + "_Local" + m_PathSplitter;
                else this.SavePath = this.BasePath + "Save" + m_PathSplitter;
                return;
            } catch {}
        }

        if (process.env.APPDATA) this.SavePath = process.env.APPDATA; // Windows
        else if ("darwin" == process.platform)
            // macOS
            this.SavePath = process.env.HOME + "/Library/Preferences/";
        else this.SavePath = process.env.HOME + "/.local/share/";

        if (this.SavePath.endsWith(m_PathSplitter))
            this.SavePath += m_PathSplitter;
    }

    // DEBUG: sAppPath should be the folder which contains Test-Nodejs.njsproj file
    // RELEASE: sAppPath should be the app folder
    InitializeAppPath(sAppPath: string) {
        // Prefer to use resource files in debug structure folder
        if (fs.existsSync(sAppPath + "/Test-Nodejs.njsproj")) {
            // should be <Avernakis Nodejs>\Code\Avernakis Nodejs
            let s = PathRemoveLeaf(sAppPath);

            // should be <Avernakis Nodejs>\Code
            s = PathRemoveLeaf(s);

            // should be <Avernakis Nodejs>
            s = PathRemoveLeaf(s);

            this.BasePath = s + m_PathSplitter;
            this.AppPath = this.BasePath + "Resource" + m_PathSplitter;
        } else {
            this.BasePath = sAppPath + m_PathSplitter;
            this.AppPath = this.BasePath;
        }

        // Default initialize save path in non portable mode
        this.InitializeSavePath(false);
    }
}

let AppPath: IAppPath = new AppPathImpl();

function RequireAveLib() {
    let sPath = __dirname;
    m_PathSplitter = sPath.indexOf("\\") >= 0 ? "\\" : "/";

    // should be <AppPath>\src\Ave, or <Avernakis Nodejs>\Code\Avernakis Nodejs\Test-Nodejs\src\Ave
    if (sPath.endsWith(m_PathSplitter))
        sPath = sPath.substr(0, sPath.length - 1);

    let ap = new AppPathImpl();
    AppPath = ap;

    // should be <AppPath>\src, or <Avernakis Nodejs>\Code\Avernakis Nodejs\Test-Nodejs\src
    sPath = PathRemoveLeaf(sPath);

    // should be <AppPath>, also <Avernakis Nodejs>\Code\Avernakis Nodejs\Test-Nodejs
    sPath = PathRemoveLeaf(sPath);

    ap.InitializeAppPath(sPath);

    // Try release path first
    if (fs.existsSync(sPath + "/lib/Avernakis-Nodejs.node"))
        return require(sPath + "/lib/Avernakis-Nodejs");

    ap.IsDebugFolder = true;

    // should be <Avernakis Nodejs>\Code\Avernakis Nodejs
    sPath = PathRemoveLeaf(sPath);

    // should be <Avernakis Nodejs>\Code
    sPath = PathRemoveLeaf(sPath);

    // should be <Avernakis Nodejs>
    sPath = PathRemoveLeaf(sPath);

    // Possible values: 'arm', 'arm64', 'ia32', 'mips', 'mipsel', 'ppc', 'ppc64', 's390', 's390x', 'x32', 'x64'.
    const sArch = require("process").arch;

    // Try debug path
    if (sArch == "x64") {
        if (
            fs.existsSync(
                sPath + "/_BuildOutput/x64_Debug/Avernakis-Nodejs.node"
            )
        )
            return require(sPath + "/_BuildOutput/x64_Debug/Avernakis-Nodejs");
    }

    if (sArch == "x32") {
        if (
            fs.existsSync(
                sPath + "/_BuildOutput/Win32_Debug/Avernakis-Nodejs.node"
            )
        )
            return require(sPath +
                "/_BuildOutput/Win32_Debug/Avernakis-Nodejs");
    }

    return null;
}

//
const AveLib = RequireAveLib();

[
    //--------------------------------------------------
    // Control
    //--------------------------------------------------
    "UiButton",
    "UiCalendar",
    "UiCheckBox",
    "UiColorPicker",
    "UiComboBox",
    "UiContainer3D",
    "UiDatePicker",
    //"UiDock",
    "UiGrid",
    "UiGroup",
    "UiHeader",
    "UiHyperlink",
    "UiKnob",
    "UiListBox",
    "UiMatrixEditor",
    "UiMenu",
    "UiMidiKey",
    "UiPager",
    "UiPlaceholder",
    "UiProgressBar",
    //"UiPropertyEditor",
    "UiRadioBox",
    "UiRichListBox",
    "UiScrollBar",
    "UiSpin",
    "UiStatusBar",
    "UiTab",
    "UiTextBox",
    "UiToolBar",
    "UiTrackBar",
    //"UiTrackEditor",
    "UiTree",
    "UiWindow",

    //--------------------------------------------------
    // Visual
    //--------------------------------------------------
    "UiAnimFrame",
    "UiColorView",
    "UiLabel",
    "UiPicture",

    //--------------------------------------------------
    // Ribbbon
    //--------------------------------------------------
    "UiRibbon",
    "UiRibbonApp",
    "UiRibbonBackstage",
    "UiRibbonButton",
    "UiRibbonGallery",
    "UiRibbonGroup",
    "UiRibbonTab",
].forEach((controlName) => {
    AveLib[controlName] = AddControlExtension(AveLib[controlName]);
});

export { AveLib };
export { AppPath };
