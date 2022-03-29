import { Vec2 } from "../Math/Vector";

export class StringKey {
    BaseKey: string | number;
    Offset: number;
    Count: number;

    constructor(basekey: string | number, offset: number, count: number) {
        this.BaseKey = basekey;
        this.Offset = offset;
        this.Count = count;
    }
}

export enum ButtonType {
    Normal,
    DropDown,
    Split,
}

export enum ButtonStyle {
    Push,
    Command,
}

export enum CheckValue {
    Unchecked,
    Checked,
    Mixed,
}

export enum AlignType {
    Near,
    Center,
    Far,
}

export enum VisualTextLayout {
    TextOnly,
    VisualOnly,
    HorzVisualText,
    VertVisualText,
}

export enum ProgressBarState {
    Normal,
    Paused,
    Error,
    Pulse,
    None, // Only for IWindowTaskbar
}

export enum StretchMode {
    None, // 100% display at left-top corner of the canvas
    Center, // 100% display at center of the canvas
    Fit, // Scale to fit the canvas (keep aspect ratio)
    Fill, // Fill up the the canvas (don't keep aspect ratio)
    FitFill, // Fill up the the canvas (keep aspect ratio), some parts of the image will be cut (out of the canvas)
}

export enum KnobControlType {
    Direction,
    Vertical,
    Horizontal,
}

export enum AxisDirection {
    Left,
    Top,
    Right,
    Bottom,
}

export enum CrossDirection {
    Vertical,
    Horizontal,
}

export enum ExpandAction {
    Collapse,
    Expand,
    Toggle,
}

export enum KbKey {
    None,

    // Function
    Escape,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,

    // Main keyboard
    D0,
    D1,
    D2,
    D3,
    D4,
    D5,
    D6,
    D7,
    D8,
    D9,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    Back,
    Tab,
    Enter,
    Shift,
    Control,
    Menu,
    Space,
    LShift,
    RShift,
    LControl,
    RControl,
    LMenu,
    RMenu,
    LWindows,
    RWindows,
    Application,

    Minus,
    Equal,
    LBracket,
    RBracket,
    Semicolon,
    Apostrophe,
    Grave,
    Backslash,
    Comma,
    Period,
    Slash,
    Capital,

    // Navigation
    Insert,
    Delete,
    Home,
    End,
    PageUp,
    PageDown,

    Left,
    Up,
    Right,
    Down,

    // Number Pad
    Pad0,
    Pad1,
    Pad2,
    Pad3,
    Pad4,
    Pad5,
    Pad6,
    Pad7,
    Pad8,
    Pad9,
    PadMultiply,
    PadAdd,
    PadSeparator,
    PadSubtract,
    PadDecimal,
    PadDivide,
    PadLock,
    PadEqual,

    // Power
    Power,
    Sleep,
    Wake,

    // Media
    MediaPlayPause,
    MediaPrevTrack,
    MediaNextTrack,
    MediaStop,
    MediaSelect,
    MediaVolumeDown,
    MediaVolumeUp,

    // Internet
    WebHome,
    WebSearch,
    WebFavorites,
    WebRefresh,
    WebStop,
    WebForward,
    WebBack,
    Mail,
    MyComputer,

    // Pointer
    Button1,
    Button2,
    Button3,
    Button4,
    Button5,

    // IME
    Kana,
    Convert,
    NonConvert,
    Yen,
    Kanji,
    Accept,
    ModeChange,
    Junja,
    Final,

    // Others
    Select,
    Execute,
    Print,
    Cancel,
    Clear,

    Help,

    __Count,

    // Sys
    SysRq = F13,
    Scroll = F14,
    Pause = F15,
}

export enum InputModifier {
    // Keyboard
    LControl /**/ = 0x00000001,
    LShift /**/ = 0x00000002,
    LMenu /**/ = 0x00000004,
    LSys /**/ = 0x00000008,
    RControl /**/ = 0x00000010,
    RShift /**/ = 0x00000020,
    RMenu /**/ = 0x00000040,
    RSys /**/ = 0x00000080,
    Control /**/ = 0x00000011,
    Shift /**/ = 0x00000022,
    Menu /**/ = 0x00000044,
    Sys /**/ = 0x00000088,
    Key /**/ = 0x000000ff,

    // Pointer
    Button1 /**/ = 0x00000100,
    Button2 /**/ = 0x00000200,
    Button3 /**/ = 0x00000400,
    Button4 /**/ = 0x00001000,
    Button5 /**/ = 0x00002000,
    Button /**/ = 0x00003700,

    // Pen
    Barrel /**/ = 0x00010000,
    Inverted /**/ = 0x00020000,
    Eraser /**/ = 0x00040000,
    Pen /**/ = 0x00070000,
}

export class Hotkey {
    Key: KbKey = KbKey.None;
    Modifier: InputModifier = 0;

    Refine(): Hotkey {
        this.Modifier &= InputModifier.Key;
        if (InputModifier.Control & this.Modifier)
            this.Modifier |= InputModifier.Control;
        if (InputModifier.Shift & this.Modifier)
            this.Modifier |= InputModifier.Shift;
        if (InputModifier.Menu & this.Modifier)
            this.Modifier |= InputModifier.Menu;
        if (InputModifier.Sys & this.Modifier)
            this.Modifier |= InputModifier.Sys;
        return this;
    }
}

export class DpiSize {
    private Data: number = 0;

    get IsDpiScaled() {
        return 0 != (0x40000000 & this.Data);
    }
    get IsSlice() {
        return 0 != (0x80000000 & this.Data);
    }

    get RawValue() {
        return this.Data;
    }
    set RawValue(x: number) {
        this.Data = 0xffffffff & x;
    }

    get Value() {
        return 0x3fffffff & this.Data;
    }
    set Value(x: number) {
        this.Data = (x & 0x3fffffff) | (this.Data & 0xc0000000);
    }

    set Pixel(x: number) {
        this.Data = 0x3fffffff & x;
    }
    set PixelScaled(x: number) {
        this.Data = (0x3fffffff & x) | 0x40000000;
    }
    set Slice(x: number) {
        this.Data = (0x3fffffff & x) | 0x80000000;
    }

    GetScaledValue(nDpi: number) {
        return this.IsDpiScaled
            ? DpiSize.Scale(this.RawValue, nDpi)
            : this.RawValue;
    }

    static Scale(x: number, dpi: number) {
        return (x * dpi) / 96;
    }

    static FromPixel(x: number) {
        let r = new DpiSize();
        r.Pixel = x;
        return r;
    }
    static FromPixelScaled(x: number) {
        let r = new DpiSize();
        r.PixelScaled = x;
        return r;
    }
    static FromSlice(x: number) {
        let r = new DpiSize();
        r.Slice = x;
        return r;
    }

    static get Zero() {
        return new DpiSize();
    }
    static get MaxPixel() {
        let t = new DpiSize();
        t.Data = 0x3fffffff;
        return t;
    }
}

export class DpiSize_2 {
    x: DpiSize = DpiSize.FromPixel(0);
    y: DpiSize = DpiSize.FromPixel(0);

    constructor(x: DpiSize, y: DpiSize) {
        this.x = x;
        this.y = y;
    }
}

export class DpiMargin {
    Left: DpiSize = DpiSize.FromPixel(0);
    Top: DpiSize = DpiSize.FromPixel(0);
    Right: DpiSize = DpiSize.FromPixel(0);
    Bottom: DpiSize = DpiSize.FromPixel(0);

    constructor(l: DpiSize, t: DpiSize, r: DpiSize, b: DpiSize) {
        this.Left = l;
        this.Top = t;
        this.Right = r;
        this.Bottom = b;
    }

    Set(l: DpiSize, t: DpiSize, r: DpiSize, b: DpiSize) {
        this.Left = l;
        this.Top = t;
        this.Right = r;
        this.Bottom = b;
        return this;
    }
    SetAll(x: DpiSize) {
        this.Left = this.Top = this.Right = this.Bottom = x;
        return this;
    }

    static FromPixel(l: number, t: number, r: number, b: number) {
        return new DpiMargin(
            DpiSize.FromPixel(l),
            DpiSize.FromPixel(t),
            DpiSize.FromPixel(r),
            DpiSize.FromPixel(b)
        );
    }
    static FromPixelScaled(l: number, t: number, r: number, b: number) {
        return new DpiMargin(
            DpiSize.FromPixelScaled(l),
            DpiSize.FromPixelScaled(t),
            DpiSize.FromPixelScaled(r),
            DpiSize.FromPixelScaled(b)
        );
    }
}

export class Rect {
    Position: Vec2 = new Vec2(0, 0);
    Size: Vec2 = new Vec2(0, 0);

    constructor(x: number, y: number, w: number, h: number) {
        this.Position.x = x;
        this.Position.y = y;
        this.Size.x = w;
        this.Size.y = h;
    }

    get x() {
        return this.Position.x;
    }
    get y() {
        return this.Position.y;
    }
    get w() {
        return this.Size.x;
    }
    get h() {
        return this.Size.y;
    }
    set x(r: number) {
        this.Position.x = r;
    }
    set y(r: number) {
        this.Position.y = r;
    }
    set w(r: number) {
        this.Size.x = r;
    }
    set h(r: number) {
        this.Size.y = r;
    }

    get Right() {
        return this.x + this.w;
    }
    get Bottom() {
        return this.y + this.h;
    }

    get CornerRT() {
        return new Vec2(this.Right, this.y);
    }
    get CornerLB() {
        return new Vec2(this.x, this.Bottom);
    }
    get CornerRB() {
        return new Vec2(this.Right, this.Bottom);
    }
    get Center() {
        return new Vec2(this.x + this.w / 2, this.y + this.h / 2);
    }

    get IsEmpty() {
        return this.w <= 0 || this.h <= 0;
    }

    Set(x: number, y: number, w: number, h: number) {
        this.Position.x = x;
        this.Position.y = y;
        this.Size.x = w;
        this.Size.y = h;
        return this;
    }

    Contain(r: Vec2) {
        return (
            r.x >= this.x &&
            r.x < this.x + this.w &&
            r.y > this.y &&
            r.y < this.y + this.h
        );
    }

    Intersect(rc: Rect, result?: Rect) {
        if (
            rc.x < this.Right &&
            rc.Right > this.x &&
            rc.y < this.Bottom &&
            rc.Bottom > this.y
        ) {
            if (result) {
                result.x = Math.max(this.x, rc.x);
                result.w = Math.min(this.Right, rc.Right) - result.x;
                result.y = Math.max(this.y, rc.y);
                result.h = Math.min(this.Bottom, rc.Bottom) - result.y;
            }
            return true;
        } else {
            if (result) result.Set(0, 0, 0, 0);
            return false;
        }
    }

    InflateAll(r: number) {
        this.x -= r;
        this.y -= r;
        this.w += Math.max(0, this.w + r * 2);
        this.h += Math.max(0, this.h + r * 2);
        return this;
    }

    Inflate2(dx: number, dy: number) {
        this.x -= dx;
        this.y -= dy;
        this.w += Math.max(0, this.w + dx * 2);
        this.h += Math.max(0, this.h + dy * 2);
        return this;
    }

    Inflate(dl: number, dt: number, dr: number, db: number) {
        this.x -= dl;
        this.y -= dt;
        this.w += Math.max(0, this.w + dl + dr);
        this.h += Math.max(0, this.h + dt + db);
        return this;
    }

    ClipBy(rc: Rect) {
        let nRight = this.Right - rc.Right;
        let nBottom = this.Bottom - rc.Bottom;
        let b = false;
        if (nRight > 0) {
            this.x -= nRight;
            b = true;
        }
        if (nBottom > 0) {
            this.y -= nBottom;
            b = true;
        }
        if (this.x < rc.x) {
            this.x = rc.x;
            b = true;
        }
        if (this.y < rc.y) {
            this.y = rc.y;
            b = true;
        }
        return b;
    }

    CenterTo(rc: Rect) {
        this.Position = rc.Position.Add(rc.Size.Sub(this.Size).Div(2));
    }

    UniformScale(rc: Rect) {
        if (rc.IsEmpty) return this;
        let fAspect = this.w / this.h;
        if (fAspect >= rc.w / rc.h) {
            this.w = rc.w;
            this.h = this.w / fAspect;
        } else {
            this.h = rc.h;
            this.w = this.h * fAspect;
        }
        this.Position = rc.Position.Add(rc.Size.Sub(this.Size).Div(2));
        return this;
    }

    UniformFill(rc: Rect) {
        if (rc.IsEmpty) return this;
        let fAspect = this.w / this.h;
        if (fAspect >= rc.w / rc.h) {
            this.h = rc.h;
            this.w = this.h * fAspect;
        } else {
            this.w = rc.w;
            this.h = this.w / fAspect;
        }
        this.Position = rc.Position.Add(rc.Size.Sub(this.Size).Div(2));
        return this;
    }

    Move(r: Vec2) {
        this.Position = this.Position.Add(r);
        return this;
    }

    Equal(r: Rect) {
        return this.Position.Equal(r.Position) && this.Size.Equal(r.Size);
    }
}

export class IconSource {
    ResId: number = 0;
    PixelSize: number = 0;

    constructor(resId: number, pixelSizeWhen100Percent: number) {
        this.ResId = resId;
        this.PixelSize = pixelSizeWhen100Percent;
    }
}

export type IconCache = number;

export interface IIconManager {}

export enum FontFlag {
    Standard /**/ = 0x0000,
    Bold /**/ = 0x0001,
    Italic /**/ = 0x0002,
    Underline /**/ = 0x0004,
    StrikeOut /**/ = 0x0008,
}

export enum FontResourceType {
    Name,
    File,
    ResourceId,
}

export class FontDescription {
    Type: FontResourceType = FontResourceType.Name;

    // Use one of Name, File and ResourceId due to Type
    // Specify multiple fonts to support display in different character-set, the Ave will find characeter with this order, for example, when display '𪚥', all of these fonts ("Segoe UI", "Microsoft YaHei UI", "Meiryo UI") don't have this char, finally will find this char in SimSun-ExtB font.
    Name: string[] = []; // Font names like ["Segoe UI", "Microsoft YaHei UI", "Meiryo UI", "SimSun-ExtB"]
    File: number[] = []; // Font files like ["D:\\1.ttf", "D:\\2.ttc"]
    ResourceId: number[] = []; // Resource IDs like [100, 102]

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // YOU MUST ALWAYS USE \ TO SPLIT PATH ON ALL PLATFORMS EVEN ON Linux AND macOS
    //
    // The Ave origin interface only has a string variable for all font names splitted with / with use syntax:
    //  Name1[:Path1[/Name2[:Path2[/Name3[:Path3]]]]]
    // For example:
    //  FontName1:d:\1.ttf/FontName2:d:\2.ttc
    //  FontName1:\home\1.ttf/FontName2:\home\2.ttc
    // If you use / to split path, "FontName1:/home/1.ttf/FontName2:/home/2.ttc" means 6 fonts
    //  [0]: Font name "FontName1" without file path
    //  [1]: Font name "home" without file path
    //  [2]: Font name "1.ttf" without file path
    //  ...
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // Optionally specify font index when use File or ResourceId if the target font resource has multiple fonts
    Index: number[] = [];

    Size: number = 10; // >0: pt  <0: px
    Flag: FontFlag = FontFlag.Standard;
}

export enum ResourceSourceType {
    Resource,
    FilePath,
    InMemory,
}

export class ResourceSource {
    Type: ResourceSourceType = ResourceSourceType.Resource;
    ResourceId: number = 0;
    FilePath: string = "";
    InMemory: ArrayBuffer = null;

    static FromResource(n: number) {
        let r = new ResourceSource();
        r.Type = ResourceSourceType.Resource;
        r.ResourceId = n;
        return r;
    }
    static FromFilePath(s: string) {
        let r = new ResourceSource();
        r.Type = ResourceSourceType.FilePath;
        r.FilePath = s;
        return r;
    }
    static FromBuffer(ab: ArrayBuffer){
        let r = new ResourceSource();
        r.Type = ResourceSourceType.InMemory;
        r.InMemory = ab;
        return r;
    }
}
