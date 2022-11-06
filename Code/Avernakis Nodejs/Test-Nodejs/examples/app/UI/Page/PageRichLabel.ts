import { Byo2Font, DpiSize, FontDescription, Grid, Rect, ResourceSource, RichLabel, RichLabelDisplay, RichLabelEmphasis, RichLabelEmphasisType, RichLabelStrike, RichLabelTextColor, RichLabelTextFx, RichLabelTextFxType, RichLabelUnderline, ToolBar, ToolBarItem, ToolBarItemType, Vec2, Vec4, Window } from "../../../../src";
import { ResId } from "../../ResId";
import { PageHelper, PageRegister } from "./../Page";
import * as fs from "fs";
import * as path from "path";

class PageRichLabel extends PageHelper<PageRichLabel> {
	NameKey: string = "PageRichLabel";

	OnCreateControl(window: Window) {
		const grid = new Grid(window);
		grid.ColAddSlice(1).RowAddDpx(24).RowAddSlice(1);

		let ctl = grid.ControlAdd(new RichLabel(window)).SetGrid(0, 1).GetControl();

		let fd = window.GetTheme().GetFont();
		fd.Size = 24;
		const fontDef = new Byo2Font(window, fd);

		fd.Size = 12;
		const fontRuby = new Byo2Font(window, fd);

		fd = new FontDescription();
		fd.Name = ["Microsoft YaHei UI"];
		fd.Size = 24;
		const fontChs = new Byo2Font(window, fd);

		const tcRainbow = new RichLabelTextColor();
		tcRainbow.Text.Rect = [new Rect(0, 1, 256, 1)];
		tcRainbow.Text.PhaseSpeed = 100;
		tcRainbow.Text.Scaling.x = 1;

		const tcBlueG = new RichLabelTextColor();
		tcBlueG.Text.Rect = [new Rect(1, 5, 2, 120)];
		tcBlueG.Text.Scaling.x = 1000;

		const tcBlueGBorder = new RichLabelTextColor();
		tcBlueGBorder.Text.Rect = [new Rect(1, 5, 2, 120)];
		tcBlueGBorder.Text.Scaling.x = 1000;
		tcBlueGBorder.Border.Rect = [new Rect(5, 5, 2, 120)];
		tcBlueGBorder.Border.Scaling.x = 1000;

		const tcTex = new RichLabelTextColor();
		tcTex.Text.Rect = [new Rect(41, 37, 32, 32), new Rect(9, 5, 32, 32)];
		tcTex.Text.RectSpeed = 0.2;
		tcTex.Text.Scaling = Vec2.One;
		tcTex.Border.Rect = [new Rect(256, 1, 256, 1), new Rect(0, 1, 256, 1)];
		tcTex.Border.RectSpeed = 0.2;
		tcTex.Border.Scaling.x = 1;

		const ul = new RichLabelUnderline();
		ul.Color.Color = new Vec4(150, 255, 150, 255);
		ul.Shape.Size = 2;
		ul.Shape.Offset = 1;

		const ulR = new RichLabelUnderline();
		ulR.Color.Rect = [new Rect(256, 1, 256, 1)];
		ulR.Color.PhaseSpeed = -50;
		ulR.Color.Scaling.x = 1;
		ulR.Shape.Size = 2;
		ulR.Shape.Offset = 1;

		const strike = [new RichLabelStrike(), new RichLabelStrike()];
		strike[0].Color.Color = new Vec4(255, 150, 150, 255);
		strike[0].Shape.Size = 2;
		strike[0].Shape.Offset = 0.3;
		strike[1].Color.Rect = [new Rect(0, 1, 256, 1)];
		strike[1].Color.PhaseSpeed = 50;
		strike[1].Color.Scaling.x = 1;
		strike[1].Shape.Size = 2;
		strike[1].Shape.Offset = 0.45;

		const emp = new RichLabelEmphasis();
		emp.Type = RichLabelEmphasisType.Circle;
		emp.Color.Color = new Vec4(255, 150, 150, 255);
		emp.Shape.Size = 6;
		emp.Shape.Offset = 12;

		const empR = new RichLabelEmphasis();
		empR.Type = RichLabelEmphasisType.Circle;
		empR.Color.Rect = [new Rect(0, 1, 256, 1)];
		empR.Color.PhaseSpeed = 75;
		empR.Color.Scaling.x = 1;
		empR.Shape.Size = 6;
		empR.Shape.Offset = 12;

		const fx0 = new RichLabelTextFx();
		fx0.Type = RichLabelTextFxType.Color;
		fx0.Color.Color = [new Vec4(255, 150, 150, 255), new Vec4(150, 255, 150, 255), new Vec4(150, 150, 255, 255), new Vec4(255, 150, 150, 255)];
		fx0.Color.Speed = 1;

		const fx1 = new RichLabelTextFx();
		fx1.Type = RichLabelTextFxType.Transform;
		fx1.Transform.TranslationRange = new Vec2(2, 2);
		fx1.Transform.RotationRange = (5.0 / 180.0) * Math.PI;
		fx1.Transform.ScaleRange = new Vec2(0.2, 0.2);
		fx1.Transform.Speed = 10;

		const fx2 = new RichLabelTextFx();
		fx2.Type = RichLabelTextFxType.Wave;
		fx2.Wave.Frequency = 0.3;
		fx2.Wave.Amplitude = 5;
		fx2.Wave.Speed = 5;

		const tc = new RichLabelTextColor();
		tc.Text.Color = new Vec4(210, 210, 210, 255);

		const tc0 = new RichLabelTextColor();
		tc0.Border.Color = new Vec4(200, 50, 50, 255);

		const tc1 = new RichLabelTextColor();
		tc1.Shadow.Color = new Vec4(20, 20, 20, 255);

		const maskData = fs.readFileSync(path.resolve(__dirname, "./PageRichLabel.png"));
		const maskSource = ResourceSource.FromBuffer(maskData);

		ctl.FmSetMaskResource(maskSource);
		ctl.FmSetDefaultFont(fontDef);
		ctl.FmSetDefaultTextColor(tc);
		ctl.FmSetTextColor(0, tc0, "b");
		ctl.FmSetTextColor(1, tc1, "s");
		ctl.FmSetTextColor(2, tcRainbow, "rb0");
		ctl.FmSetTextColor(3, tcBlueG, "bg");
		ctl.FmSetTextColor(4, tcBlueGBorder, "bb");
		ctl.FmSetTextColor(5, tcTex, "tex");
		ctl.FmSetUnderline(0, ul);
		ctl.FmSetUnderline(1, ulR);
		ctl.FmSetStrikethrough(0, strike);
		ctl.FmSetEmphasis(0, emp);
		ctl.FmSetEmphasis(1, empR);
		ctl.FmSetBorderOffset(DpiSize.FromPixelScaled(1));
		ctl.FmSetShadowOffset(DpiSize.FromPixelScaled(2));
		ctl.FmSetRubyFont(fontRuby);
		ctl.FmSetRubyTextColor(tcRainbow);
		ctl.FmSetRubyForceSpace(true);
		ctl.FmSetTextFont(1, fontChs, "z");
		ctl.FmSetTextEffect(0, fx0, "c");
		ctl.FmSetTextEffect(1, fx1, "t");
		ctl.FmSetTextEffect(2, fx2, "w");

		ctl.PlSetAdvanceSpeed(20);
		ctl.PlSetClusterSpeed(1);

		ctl.IconSetDefaultSize(24);
		ctl.IconSetOffset(ResId.Icon_Language_png, DpiSize.FromPixelScaled(4));
		ctl.IconSetManager((sender, name) => {
			switch (name) {
				case "a":
					return ResId.Icon_Copy_png;
				case "b":
					return ResId.Icon_Cut_png;
				case "c":
					return ResId.Icon_Language_png;
				default:
					return 0;
			}
		});

		ctl.VaSetManager((sender, qv) => {
			if (!qv.IsName && 1 == qv.Id) return "<ic %c><c f00>c</c></ic> Open";
			return "";
		});

		// FIXME: this causes lag
		ctl.PlSetCustom((sender, cp, cd) => {
			cd.Transform.Translation.x = 256.0 * (1.0 - cp.Progress);
			cd.Transform.Scaling.x = 1.0 + 3.0 * (1.0 - cp.Progress);
			cd.Transform.Scaling.y = cd.Transform.Scaling.x;
			cd.Transform.Rotation = (45.0 / 180.0) * Math.PI * (cp.Progress - 1);
			return cd;
		});

		ctl.SetText("" + "<fx %w>Hello, <fx %c %t>this  is</fx %c %t> an <e>rich</e> <r what?>label</r>. " + "<b>Bold text</b>, <i>Italic text</i>.</fx %w> <u>Underline</u>, <s>Strikethrough</s>, " + "1.5<sp><i>sin(2)</i></sp><sb><b>abc</b></sb>, " + "<c f00>Red text</c>, <c %b>Bordered text</c>, <c %s>Shadow text</c>, " + "<ic %a/> Copy, <ic %b/> Cut, `#1`, " + "<e 1><f %z><r da>射</r><r niao>雕</r><r gou>英</r><r xiong>雄</r><r chuanchuan>传</r></f></e>, " + "<c %rb0>Rainbow text</c>, <c %bg>Blue gradient text</c>, <c %bb>Blue with border text</c>, <c %tex>textured text ●■◆</c>, " + "<u 1>Rainbow underline</u>");

		let tbr = grid.ControlAdd(new ToolBar(window)).SetGrid(0, 0).GetControl();
		tbr.ToolInsert(new ToolBarItem(1, ToolBarItemType.Button, 0, DpiSize.Zero, "Replay"), -1);
		tbr.ToolInsert(new ToolBarItem(2, ToolBarItemType.Button, 0, DpiSize.Zero, "Pause"), -1);
		tbr.ToolInsert(new ToolBarItem(3, ToolBarItemType.Button, 0, DpiSize.Zero, "Rewind"), -1);
		tbr.OnClick((sender, nId) => {
			if (1 == nId) {
				ctl.PlSetPosition(0);
				ctl.PlStart();
			} else if (2 == nId) {
				ctl.PlIsPlaying() ? ctl.PlStop() : ctl.PlStart();
			} else if (3 == nId) {
				ctl.PlSetPosition(0);
			}
		});

		return grid;
	}
}

export function Register() {
	PageRegister.Register(() => new PageRichLabel());
}
