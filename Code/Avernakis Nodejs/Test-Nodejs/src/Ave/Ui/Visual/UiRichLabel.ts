import { AveLib } from "../../AveLib";
import { AlignType, DpiSize, IconCache, Rect } from "../UiCommon";
import { IVisual } from "../UiVisual";
import { WindowLike } from "../Control/UiWindow";
import { Vec2, Vec4 } from "../../Math";
import { Byo2Font, Byo2Image } from "../../Byo2";
import { ResourceSource } from "../../Io";
import { AveImage } from "../../Image";

/*
Format tags:

[A]					Optional parameter A

Simple text formats
====================================================================================================
<b></b>				Bold text ON/OFF
<i></i>				Italic text ON/OFF
<sp></sp>			Superscript text ON/OFF
<sb></sb>			Subscript text ON/OFF
<u [i]></u>			Underline text ON/OFF		Default i = 0, Define with FmSetUnderline
<s [i]></s>			Strikethrough text ON/OFF	Default i = 0, Define with FmSetStrikethrough
<e [i]></e>			Emphasis mark ON/OFF		Default i = 0, Define with FmSetEmphasis
<f [i]>				Set font index				Default i = 0, Define with FmSetTextFont
</f>				Set font index to -1
<c COLOR>			Set text color				See "COLOR syntax" for details
</c>				Set text color to default
<g COLOR>			Set back color				See "COLOR syntax" for details
</g>				Set back color to default


Advanced text formats
====================================================================================================
<r RUBY></r>		Ruby ON/OFF					This is usually used for pronunciation comment
												CAUTION: "<ruby />aa</ruby>" is a valid sentence while ruby doesn't support self closing, so the result is text "aa" with ruby "/"
<fx FX0 [FX1...]>	Enable specified effect		See "FX syntax" for details
</fx FX0 [FX1...]>	Disable specified effect	See "FX syntax" for details
<fx>				Do nothing					This is different than </fx> while </fx> disable all, this is NOT enable all
</fx>				Disable all effects


Others
====================================================================================================
<ic ICON [size]/>	Insert an icon				size is a pixel value in 100%. Default size can be set with SetIconSize
<ic ICON [size]>	Insert an icon with text
</ic>				Stop put text to icon
</>					Reset all to default

Variable
====================================================================================================
`VAR`				Use variable				Define with VaSet, See "VAR syntax" for details


COLOR syntax
====================================================================================================
RRGGBBAA	(hex): Example: Red is <c ff0000ff>
RRGGBB		(hex): Example: Red is <c ff0000>
RGB			(hex): Example: Red is <c f00>
RGBA		(hex): Example: Red is <c f00f>
R G B A		(dec): Example: Red is <c 255 0 0 255>
R G B		(dec): Example: Red is <c 255 0 0>
. R G B A	(dec): Example: Red is <c . 1 0 0 1>
. R G B		(dec): Example: Red is <c . 1 0 0>
#Index		(dec): Define with SetTextColor/SetBackColor
%Name		(txt): Define with SetTextColor/SetBackColor


ICON syntax
====================================================================================================
ID			(dec): Specify icon ID
0xID		(hex): Specify icon ID				Can't use 0X, must use 0x
%Name		(txt): Specify icon name			Define with IconSetId or IconSetManager


FX syntax
====================================================================================================
Index		(dec): Specify FX index, define with SetTextEffect
%Name		(txt): Specify FX name, define with SetTextEffect


VAR syntax
====================================================================================================
Name		(txt): Specify variable name. Example: `Var1`
#Id			(dec): Specify variable ID. Example: `#1`


New Line
====================================================================================================
Always use \n for manual new line, Never use \r, \r\n, Unicode-PS or Unicode-LS.


Nesting
====================================================================================================
Tags never nest, nested tag will overwrite previous state.
<ruby> and <ico> will cause error if nesting.
	
Example:
	
"This is <c 00f>Blue <c 0f0>Green </c>Text."
  The last "</c>" will cancel text color option (revert to default).

"<ruby ruby>Text1<ruby abc>Text2</ruby></ruby>
  The final result will be empty.


Misc
====================================================================================================
use << to display <
use >> to display >, If there is no leading "<", ">" can be used directly. In fact only the text part in "<ruby text>" can use >> escaping.
use `` to display `
*/

export class RichLabelSimpleShape {
	Size: number = 0; // >0: auto scaled size, <0: -size
	Offset: number = 0;
}

export class RichLabelColor {
	static FromNative(color: RichLabelColor) {
		color.Color = Vec4.FromNative(color.Color);
		color.Rect = color.Rect?.map((each) => Rect.FromNative(each));
		color.Scaling = Vec2.FromNative(color.Scaling);
		return color;
	}

	Color: Vec4 = Vec4.Zero; // .a==0: use default
	Rect: Rect[] = null;
	Scaling: Vec2 = Vec2.Zero;
	RectSpeed: number = 0;
	PhaseSpeed: number = 0;
}

export class RichLabelUnderline {
	static FromNative(underline: RichLabelUnderline) {
		underline.Color = RichLabelColor.FromNative(underline.Color);
		return underline;
	}

	Color: RichLabelColor = new RichLabelColor();
	Shape: RichLabelSimpleShape = new RichLabelSimpleShape(); // .Offset is auto scaled pixel
}

export class RichLabelStrike {
	static FromNative(strike: RichLabelStrike) {
		strike.Color = RichLabelColor.FromNative(strike.Color);
		return strike;
	}

	Color: RichLabelColor = new RichLabelColor();
	Shape: RichLabelSimpleShape = new RichLabelSimpleShape(); // .Offset is normalized value in the whole line excluding ruby
}

export enum RichLabelEmphasisType {
	Rectangle,
	Circle,
	Icon,
}

export class RichLabelEmphasis {
	static FromNative(emphasis: RichLabelEmphasis) {
		emphasis.Color = RichLabelColor.FromNative(emphasis.Color);
		return emphasis;
	}

	Type: RichLabelEmphasisType = RichLabelEmphasisType.Rectangle;
	Shape: RichLabelSimpleShape = new RichLabelSimpleShape(); // .Offset is auto scaled pixel
	Near: boolean = false; // true: display at nearer to begining of text flow direction
	Color: RichLabelColor = new RichLabelColor();
	Icon: IconCache = 0;
}

export class RichLabelTextColor {
	static FromNative(color: RichLabelTextColor) {
		color.Text = RichLabelColor.FromNative(color.Text);
		color.Border = RichLabelColor.FromNative(color.Border);
		color.Shadow = RichLabelColor.FromNative(color.Shadow);
		return color;
	}

	Text: RichLabelColor = new RichLabelColor(); // .Color.a==0: use Label default text color (FmSetDefaultTextColor)
	Border: RichLabelColor = new RichLabelColor();
	Shadow: RichLabelColor = new RichLabelColor();
}

export class RichLabelBackColor {
	static FromNative(color: RichLabelBackColor) {
		color.Color = RichLabelColor.FromNative(color.Color);
		return color;
	}

	Color: RichLabelColor = new RichLabelColor();
}

export class RichLabelTextFxColor {
	static FromNative(color: RichLabelTextFxColor) {
		color.Color = color.Color?.map((each) => Vec4.FromNative(each));
		return color;
	}

	Color: Vec4[] = [];
	Speed: number = 0; // unit: 1/s. 0.5 means need 2 seconds to translate between all m_ColorCount colors
}

export class RichLabelTextFxTransform {
	static FromNative(transform: RichLabelTextFxTransform) {
		transform.TranslationRange = Vec2.FromNative(transform.TranslationRange);
		transform.ScaleRange = Vec2.FromNative(transform.ScaleRange);
		return transform;
	}

	TranslationRange: Vec2 = Vec2.Zero;
	RotationRange: number = 0;
	ScaleRange: Vec2 = Vec2.Zero;
	Speed: number = 0; // unit: 1/s.
}

export enum RichLabelTextFxType {
	Custom,
	Color,
	Transform,
	Wave,
}

export class RichLabelTextWave {
	Frequency: number = 0;
	Amplitude: number = 0;
	Speed: number = 0; // unit: 1/s.
}

export class RichLabelTextFx {
	static FromNative(fx: RichLabelTextFx) {
		fx.Color = RichLabelTextFxColor.FromNative(fx.Color);
		fx.Transform = RichLabelTextFxTransform.FromNative(fx.Transform);
		return fx;
	}

	Type: RichLabelTextFxType = RichLabelTextFxType.Custom;
	CustomId: number = 0;
	Color: RichLabelTextFxColor = new RichLabelTextFxColor();
	Transform: RichLabelTextFxTransform = new RichLabelTextFxTransform();
	Wave: RichLabelTextWave = new RichLabelTextWave();
}

export type RichLabelCluster = {
	Char: string; // this is a cluster which contains 1 UTF-16 char or 2 UTF-16 chars
	CharIndex: number;
	ClusterIndex: number;
	Progress: number;
};

export class RichLabelTransform {
	Translation: Vec2 = Vec2.Zero;
	Scaling: Vec2 = Vec2.Zero;
	Rotation: number = 0;
}

export class RichLabelDisplay {
	Transform: RichLabelTransform = new RichLabelTransform();
	TextColor: RichLabelTextColor = new RichLabelTextColor();
	BackColor: RichLabelBackColor = new RichLabelBackColor();
	Opacity: number = 0;
}

export type RichLabelQueryVariable = {
	IsName: boolean;
	Id: number;
	Name: string;
}

export type RichLabelCustomDisplay = {
	Cluster: RichLabelCluster[];
	Display: RichLabelDisplay[];
	TotalChar: number;
	TotalCluster: number;
	Time: number;
	FrameTime: number;
}

// prettier-ignore
export enum RichLabelReset {
	Mask          /**/ = 0x01,
	Underline     /**/ = 0x02,
	Strikethrough /**/ = 0x04,
	Emphasis      /**/ = 0x08,
	TextColor     /**/ = 0x10,
	BackColor     /**/ = 0x20,
	TextFont      /**/ = 0x40,
	TextEffect    /**/ = 0x80,
	All           /**/ = 0xff,
}

export interface IRichLabel extends IVisual {
	new (window: WindowLike, key?: string | number): IRichLabel;

	// ====================================================================================================
	// Basic
	// ====================================================================================================
	SetText(s: string): RichLabel;
	GetText(): string;
	GetTextData(): string;
	IsTextValid(): boolean;
	Recompile(): boolean;

	SetAlignHorz(n: AlignType): RichLabel;
	GetAlignHorz(): AlignType;

	SetAlignVert(n: AlignType): RichLabel;
	GetAlignVert(): AlignType;

	SetWrappable(b: boolean): RichLabel;
	GetWrappable(): boolean;

	// ====================================================================================================
	// Format defines
	// ====================================================================================================
	FmReset(resetFlag: RichLabelReset): RichLabel;

	FmSetDefaultTextColor(color: RichLabelTextColor): RichLabel;
	FmGetDefaultTextColor(): RichLabelTextColor;

	FmSetDefaultBackColor(color: RichLabelTextColor): RichLabel;
	FmGetDefaultBackColor(): RichLabelTextColor;

	FmSetDefaultFont(font: Byo2Font): RichLabel;
	FmGetDefaultFont(): Byo2Font;

	FmSetRubyFont(font: Byo2Font): RichLabel;
	FmGetRubyFont(): Byo2Font;

	FmSetRubyForceSpace(b: boolean): RichLabel;
	FmGetRubyForceSpace(): boolean;

	FmSetRubyTextColor(color: RichLabelTextColor): RichLabel;
	FmGetRubyTextColor(): RichLabelTextColor;

	FmSetRubyBackColor(color: RichLabelBackColor): RichLabel;
	FmGetRubyBackColor(): RichLabelBackColor;

	// superscript and subscript size multipiler
	FmSetSScriptSize(ratio: number): RichLabel;
	FmGetSScriptSize(): number;

	FmSetBorderOffset(size: DpiSize): RichLabel;
	FmGetBorderOffset(): DpiSize;

	FmSetShadowOffset(size: DpiSize): RichLabel;
	FmGetShadowOffset(): DpiSize;

	FmSetEmphasisNearSpace(size: DpiSize): RichLabel;
	FmGetEmphasisNearSpace(): DpiSize;

	FmSetEmphasisFarSpace(size: DpiSize): RichLabel;
	FmGetEmphasisFarSpace(): DpiSize;

	FmSetMaskResource(rs: ResourceSource): RichLabel;
	FmSetMaskImageData(img: AveImage): RichLabel;
	FmSetMaskImage(img: Byo2Image): RichLabel;

	FmSetUnderline(index: number, p: RichLabelUnderline): RichLabel;
	FmGetUnderline(index: number): RichLabelUnderline;

	FmSetStrikethrough(index: number, p: RichLabelStrike[]): RichLabel;
	FmGetStrikethrough(index: number): RichLabelStrike[];

	FmSetEmphasis(index: number, p: RichLabelEmphasis): RichLabel;
	FmGetEmphasis(index: number): RichLabelEmphasis;

	FmSetTextColor(index: number, p: RichLabelTextColor, name?: string): RichLabel;
	FmGetTextColor(index: number): RichLabelTextColor;
	FmGetTextColorByName(name: string): RichLabelTextColor;

	FmSetBackColor(index: number, p: RichLabelBackColor, name?: string): RichLabel;
	FmGetBackColor(index: number): RichLabelBackColor;
	FmGetBackColorByName(name: string): RichLabelBackColor;

	FmSetTextFont(index: number, font: Byo2Font, name?: string): RichLabel;
	FmGetTextFont(index: number): Byo2Font;
	FmGetTextFontByName(name: string): Byo2Font;

	FmSetTextEffect(index: number, fx: RichLabelTextFx, name?: string): RichLabel;
	FmGetTextEffect(index: number): RichLabelTextFx;
	FmGetTextEffectByName(name: string): RichLabelTextFx;
	FmSetTextEffectCustom(fn: (sender: RichLabel, nId: number, cd: RichLabelCustomDisplay) => RichLabelDisplay[]): RichLabel;

	// ====================================================================================================
	// Icon
	// ====================================================================================================
	IconClear(): RichLabel;
	IconSetId(name: string, iconId: number): RichLabel;
	IconGetId(name: string): number;
	IconRemoveId(name: string): RichLabel;
	IconClearOffset(): RichLabel;
	IconRemoveOffset(iconId: number): RichLabel;
	IconSetOffset(iconId: number, offset: DpiSize): RichLabel;
	IconGetOffset(iconId: number): DpiSize;
	IconSetManager(fn: (sender: RichLabel, name: string) => number): RichLabel;

	IconSetDefaultSize(sizeOn100Percent: number): RichLabel;
	IconGetDefaultSize(): number;

	// ====================================================================================================
	// Variable
	// ====================================================================================================
	VaClear(): RichLabel;
	VaSetById(nId: number, text?: string): RichLabel; // Set text to null to remove variable
	VaGetById(nId: number): string;
	VaSetByName(name: string, text?: string): RichLabel; // Set text to null to remove variable
	VaGetByName(name: string): string;
	VaSetManager(fn: (sender: RichLabel, qv: RichLabelQueryVariable) => string): RichLabel;

	// ====================================================================================================
	// Play
	// ====================================================================================================
	PlStart(): RichLabel;
	PlStop(): RichLabel;
	PlIsPlaying(): RichLabel;

	PlSetPosition(normalizedPosition: number): RichLabel;
	PlGetPosition(): number;

	PlSetAdvanceSpeed(clusterPerSecond: number): RichLabel;
	PlGetAdvanceSpeed(): number;

	PlSetClusterSpeed(_1PerSecond: number): RichLabel;
	PlGetClusterSpeed(): number;

	PlSetCustom(fn: (sender: RichLabel, cd: RichLabelCustomDisplay) => RichLabelDisplay[]): RichLabel;
	PlGetFirstCluster(): number;
	PlGetLastCluster(): number;
}

export class RichLabel extends (AveLib.UiRichLabel as IRichLabel) {
	FmGetDefaultTextColor(): RichLabelTextColor {
		return RichLabelTextColor.FromNative(super.FmGetDefaultTextColor());
	}

	FmGetDefaultBackColor(): RichLabelTextColor {
		return RichLabelTextColor.FromNative(super.FmGetDefaultBackColor());
	}

	FmGetRubyTextColor(): RichLabelTextColor {
		return RichLabelTextColor.FromNative(super.FmGetRubyTextColor());
	}

	FmGetRubyBackColor(): RichLabelBackColor {
		return RichLabelBackColor.FromNative(super.FmGetRubyBackColor());
	}

	FmGetUnderline(index: number): RichLabelUnderline {
		return RichLabelUnderline.FromNative(super.FmGetUnderline(index));
	}

	FmGetStrikethrough(index: number): RichLabelStrike[] {
		return super.FmGetStrikethrough(index).map((each) => RichLabelStrike.FromNative(each));
	}

	FmGetEmphasis(index: number): RichLabelEmphasis {
		return RichLabelEmphasis.FromNative(super.FmGetEmphasis(index));
	}

	FmGetTextColor(index: number): RichLabelTextColor {
		return RichLabelTextColor.FromNative(super.FmGetTextColor(index));
	}

	FmGetTextColorByName(name: string): RichLabelTextColor {
		return RichLabelTextColor.FromNative(super.FmGetTextColorByName(name));
	}

	FmGetBackColor(index: number): RichLabelBackColor {
		return RichLabelBackColor.FromNative(super.FmGetBackColor(index));
	}

	FmGetBackColorByName(name: string): RichLabelBackColor {
		return RichLabelBackColor.FromNative(super.FmGetBackColorByName(name));
	}

	FmGetTextEffect(index: number): RichLabelTextFx {
		return RichLabelTextFx.FromNative(super.FmGetTextEffect(index));
	}

	FmGetTextEffectByName(name: string): RichLabelTextFx {
		return RichLabelTextFx.FromNative(super.FmGetTextEffectByName(name));
	}
}
