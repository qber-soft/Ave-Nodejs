import { IControl, IDragContext, MessagePointer } from "./Ui/UiControl";
import { Vec2, Vec4 } from "./Math/Vector";
import { Mat32 } from "./Math/Matrix";
import { Rect } from "./Ui/UiCommon";
import { ImageData } from "./Image/ImgCommon";
import * as fs from "fs";
import { Byo2Font } from "./Byo2/Byo2Font";

export interface IControlExtension {
	SetKeyTip(tip: string, nIndex?: number): IControl;
	GetPosition(): Vec2;
	GetSize(): Vec2;
	GetEnableWithParent(): boolean;
	GetFont(): Byo2Font;
}

export function ExtendControlInstance(instance: IControl) {
	const SetKeyTip = instance.SetKeyTip.bind(instance);
	instance.SetKeyTip = (tip: string, nIndex: number = 0): IControl => {
		return SetKeyTip(tip, nIndex);
	};

	const MapRect = instance.MapRect.bind(instance);
	instance.MapRect = (rc: Rect, bClient: boolean): Rect => {
		return Rect.FromNative(MapRect(rc, bClient));
	};

	const GetRect = instance.GetRect.bind(instance);
	instance.GetRect = () => {
		return Rect.FromNative(GetRect());
	};

	const GetTransform = instance.GetTransform.bind(instance);
	instance.GetTransform = () => {
		return Mat32.FromNative(GetTransform());
	};

	const GetTransformInv = instance.GetTransformInv.bind(instance);
	instance.GetTransformInv = () => {
		return Mat32.FromNative(GetTransformInv());
	};

	const GetRectClient = instance.GetRectClient?.bind(instance);
	// GetRectClient is undefined in Window
	if (GetRectClient) {
		instance.GetRectClient = () => {
			return Rect.FromNative(GetRectClient());
		};
	}

	instance.GetPosition = () => {
		return instance.GetRect().Position;
	};

	instance.GetSize = () => {
		return instance.GetRect().Size;
	};

	const GetTextColor = instance.GetTextColor.bind(instance);
	instance.GetTextColor = (): Vec4 => {
		return Vec4.FromNative(GetTextColor());
	};

	instance.GetEnableWithParent = () => {
		let p: IControl = instance;
		for (; p && p.GetEnable(); p = p.GetParent());
		return !p;
	};

	const SetFont = instance.SetFont.bind(instance);
	instance.SetFont = (pFont: Byo2Font): IControl => {
		(instance as any).m_Font = pFont;
		SetFont(pFont);
		return instance;
	};
	instance.GetFont = (): Byo2Font => {
		return (instance as any).m_Font;
	};

	//
	const SetViewReadback = instance.SetViewReadback?.bind(instance);
	if (SetViewReadback) {
		type Handler = (sender: IControl, data: ImageData) => void;
		type Method = (fn: Handler, nCount: number) => IControl;
		const createSetViewReadback: (original: Method) => Method = (original) => {
			return (fn, nCount) => original((sender, data) => fn(sender, ImageData.FromNative(data)), nCount);
		};
		instance.SetViewReadback = createSetViewReadback(SetViewReadback);
	}

	//
	type DragHandler = (sender: IControl, dc: IDragContext) => void;
	type OnDragMethod = (fn: DragHandler) => IControl;
	const createOnDragMethod: (original: OnDragMethod) => OnDragMethod = (original) => {
		return (fn) =>
			original((sender: IControl, dc: IDragContext) => {
				const OriginalGetPosition = dc.GetPosition.bind(sender);
				dc.GetPosition = () => Vec2.FromNative(OriginalGetPosition());
				return fn(sender, dc);
			});
	};

	// OnDragEnter is undefined in Window
	const OnDragEnter = instance.OnDragEnter?.bind(instance);
	if (OnDragEnter) {
		instance.OnDragEnter = createOnDragMethod(OnDragEnter);
	}

	const OnDragMove = instance.OnDragMove?.bind(instance);
	if (OnDragMove) {
		instance.OnDragMove = createOnDragMethod(OnDragMove);
	}

	const OnDragLeave = instance.OnDragLeave?.bind(instance);
	if (OnDragLeave) {
		instance.OnDragLeave = createOnDragMethod(OnDragLeave);
	}

	const OnDragDrop = instance.OnDragDrop?.bind(instance);
	if (OnDragDrop) {
		instance.OnDragDrop = createOnDragMethod(OnDragDrop);
	}

	const OnDragEnd = instance.OnDragEnd?.bind(instance);
	if (OnDragEnd) {
		instance.OnDragEnd = createOnDragMethod(OnDragEnd);
	}

	//
	type PointerHandler = (sender: IControl, mp: MessagePointer) => void;
	type OnPointerMethod = (fn: PointerHandler) => IControl;
	const createOnPointerMethod: (original: OnPointerMethod) => OnPointerMethod = (original) => {
		return (fn) => {
			return original((sender: IControl, mp: MessagePointer) => fn(sender, MessagePointer.FromNative(mp)));
		};
	};

	const OnPointerEnter = instance.OnPointerEnter.bind(instance);
	instance.OnPointerEnter = createOnPointerMethod(OnPointerEnter);

	const OnPointerLeave = instance.OnPointerLeave.bind(instance);
	instance.OnPointerLeave = createOnPointerMethod(OnPointerLeave);

	const OnPointerPress = instance.OnPointerPress.bind(instance);
	instance.OnPointerPress = createOnPointerMethod(OnPointerPress);

	const OnPointerRelease = instance.OnPointerRelease.bind(instance);
	instance.OnPointerRelease = createOnPointerMethod(OnPointerRelease);

	const OnPointerClickNdc = instance.OnPointerClickNdc.bind(instance);
	instance.OnPointerClickNdc = createOnPointerMethod(OnPointerClickNdc);

	const OnPointerMove = instance.OnPointerMove.bind(instance);
	instance.OnPointerMove = createOnPointerMethod(OnPointerMove);

	const OnPointerVWheel = instance.OnPointerVWheel.bind(instance);
	instance.OnPointerVWheel = createOnPointerMethod(OnPointerVWheel);

	const OnPointerHWheel = instance.OnPointerHWheel.bind(instance);
	instance.OnPointerHWheel = createOnPointerMethod(OnPointerHWheel);

	const OnPointerHover = instance.OnPointerHover.bind(instance);
	instance.OnPointerHover = createOnPointerMethod(OnPointerHover);

	const OnPointerLost = instance.OnPointerLost.bind(instance);
	instance.OnPointerLost = createOnPointerMethod(OnPointerLost);

	const OnPointerCursor = instance.OnPointerCursor.bind(instance);
	instance.OnPointerCursor = createOnPointerMethod(OnPointerCursor);
}

function AddControlExtension(ControlClass: IControl & { new (...args: any[]): IControl }) {
	return class extends ControlClass implements IControlExtension {
		constructor(...args: any[]) {
			super(...args);
			ExtendControlInstance(this);
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
				if (this.IsDebugFolder) this.SavePath = this.BasePath + "_Local" + m_PathSplitter;
				else this.SavePath = this.BasePath + "Save" + m_PathSplitter;
				return;
			} catch {}
		}

		if (process.env.APPDATA) this.SavePath = process.env.APPDATA; // Windows
		else if ("darwin" == process.platform)
			// macOS
			this.SavePath = process.env.HOME + "/Library/Preferences/";
		else this.SavePath = process.env.HOME + "/.local/share/";

		if (this.SavePath.endsWith(m_PathSplitter)) this.SavePath += m_PathSplitter;
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
	if (sPath.endsWith(m_PathSplitter)) sPath = sPath.substr(0, sPath.length - 1);

	let ap = new AppPathImpl();
	AppPath = ap;

	// should be <AppPath>\src, or <Avernakis Nodejs>\Code\Avernakis Nodejs\Test-Nodejs\src
	sPath = PathRemoveLeaf(sPath);

	// should be <AppPath>, also <Avernakis Nodejs>\Code\Avernakis Nodejs\Test-Nodejs
	sPath = PathRemoveLeaf(sPath);

	ap.InitializeAppPath(sPath);

	// Try release path first
	if (process.env.AVE_BUILD_ENV !== "DEBUG_BUILD" && fs.existsSync(sPath + "/lib/Avernakis-Nodejs.node")) return require(sPath + "/lib/Avernakis-Nodejs");

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
		if (fs.existsSync(sPath + "/_BuildOutput/x64_Debug/Avernakis-Nodejs.node")) return require(sPath + "/_BuildOutput/x64_Debug/Avernakis-Nodejs");
	}

	if (sArch == "x32") {
		if (fs.existsSync(sPath + "/_BuildOutput/Win32_Debug/Avernakis-Nodejs.node")) return require(sPath + "/_BuildOutput/Win32_Debug/Avernakis-Nodejs");
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

export class AveVersion {
	Major: number = 0;
	Minor: number = 0;
	Patch: number = 0;
	Private: number = 0;

	static FromNative(r: AveVersion) {
		const v = new AveVersion();
		v.Major = r.Major;
		v.Minor = r.Minor;
		v.Patch = r.Patch;
		v.Private = r.Private;
		return v;
	}

	get IsPrivateVersion() {
		return 0 == this.Major && 0 == this.Minor;
	}

	get VersionString() {
		return `${this.Major}.${this.Minor}.${this.Patch}.${this.Private}`;
	}
}

export function AveGetSDKVersion(): AveVersion {
	return AveVersion.FromNative(AveLib.AveGetSDKVersion());
}

export { AveLib };
export { AppPath };
