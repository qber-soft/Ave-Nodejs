import { DpiSize, Grid, HeaderItem, HeaderItemFormat, RichListBox, RichListBoxItemVirtual, ThemeImage, ThemePredefined_Dark, Window, WindowCreation, WindowFlag, Ribbon, RibbonTab, RibbonGroup, RibbonButton, IconSource, ButtonType, ToolBar, ToolBarItem, ToolBarItemType, RibbonGallery, RibbonGalleryItem, RibbonGalleryViewMode, StringKey, Menu, MenuItem, MenuType, StatusBar, Vec4, Byo2ImageCreation, Byo2ImageDataType, AppPath, Byo2Image, Vec2, MessageIcon, MessageButton, SysDialogFilter } from "../../../src";
import { ResourceSource } from "../../../src/Ave/Io/IoCommon";
import { DrawImageFlag, DrawImageParam } from "../../../src/Ave/Ui/UiPainter";
import { DefaultString } from "../DefaultString";
import { ResId } from "../ResId";
import { IPage, PageRegister } from "./Page";
import * as PageIndex from "./PageIndex";

export interface IWindowMain {
	readonly WindowObject: Window;
}

export class WindowMain implements IWindowMain {
	WindowObject: Window;

	private m_Theme: ThemeImage;
	private m_ThemeDark: ThemePredefined_Dark;

	private m_Page: Array<IPage> = null;
	private m_PageCurrent: IPage = null;

	private CreateUIMain(sender: Window) {
		const page = PageRegister.GetPage();

		const grid0 = new Grid(sender);
		grid0.SetBackground(true);
		grid0.ColAddSlice(1).RowAddSlice(1).RowAddDpx(24);

		const statusbar = grid0.ControlAdd(new StatusBar(sender)).SetGrid(0, 1).GetControl();
		statusbar.SetPart([DpiSize.FromPixelScaled(100), DpiSize.FromPixelScaled(100), DpiSize.FromSlice(1)]);
		statusbar.SetText(0, "Idle");
		statusbar.SetText(1, "Clickable").SetClickable(1, true);

		const grid = grid0.ControlAdd(new Grid(sender)).SetGrid(0, 0).GetControl();
		grid.ColAddDpx(200).ColAddSlice(1).RowAddSlice(1).SetSplitterX(DpiSize.FromPixelScaled(6));

		const lstPage = grid.ControlAdd(new RichListBox(sender)).SetGrid(0, 0).GetControl();
		lstPage.OnSelectionChange(this.OnPageSelectionChange.bind(this));
		lstPage.GetHeader().Add(new HeaderItem(HeaderItemFormat.Left, "Test Pages", DpiSize.FromSlice(1)));
		lstPage.SetHeaderAutoWidth(true);
		lstPage.SetVirtual((s, nIndex, nSubIndex) => {
			let r = new RichListBoxItemVirtual();
			if (nIndex >= 0 && nIndex < this.m_Page.length && 0 == nSubIndex) {
				r.String = DefaultString[this.m_Page[nIndex].NameKey];
			}
			return r;
		});

		this.m_Page = new Array<IPage>(page.length);
		for (let i = 0; i < page.length; ++i) {
			const p = page[i]();
			grid.ControlAdd(p.CreateControl(this)).SetGrid(1, 0);
			p.Control.SetVisible(false);
			this.m_Page[i] = p;
		}
		this.m_Page.sort((x, y) => (DefaultString[x.NameKey] < DefaultString[y.NameKey] ? -1 : 1));

		lstPage.ItemSetCount(this.m_Page.length);

		return grid0;
	}

	private CreateUIRibbonButton(key: string, nIcon: number, bSmall: boolean = false) {
		const btn = new RibbonButton(this.WindowObject, key);
		btn.SetSmallVisual(this.WindowObject.CreateManagedIcon(new IconSource(nIcon, 16)));
		btn.SetSmall(bSmall);
		if (!bSmall) btn.SetBigVisual(this.WindowObject.CreateManagedIcon(new IconSource(nIcon, 32)));
		return btn;
	}

	private CreateUIRibbon(sender: Window) {
		const rib = new Ribbon(sender);
		sender.GetControlManager().AddControl(rib.GetApp(), "RibApp");

		rib.SetContent(this.CreateUIMain(sender));

		//----------------------------------------------------------------------------------------------------
		// Home

		const pHome = new RibbonTab(sender, "RibHome");
		rib.TabAdd(pHome);

		//----------------------------------------------------------------------------------------------------
		// Home - Edit

		const pHomeClip = new RibbonGroup(sender, "RibHomeClip");
		pHome.GroupAdd(pHomeClip);

		const pHomeEditPaste = this.CreateUIRibbonButton("RibHomeClipPaste", ResId.Icon_Paste_png);
		pHomeEditPaste.SetButtonType(ButtonType.Split);
		pHomeEditPaste.OnClick(() => {
		});
		pHomeClip.ControlAdd(pHomeEditPaste);

		const pHomeEditCut = this.CreateUIRibbonButton("RibHomeClipCut", ResId.Icon_Cut_png, true);
		pHomeClip.ControlAdd(pHomeEditCut);

		const pHomeEditCopy = this.CreateUIRibbonButton("RibHomeClipCopy", ResId.Icon_Copy_png, true);
		pHomeEditCopy.SetButtonType(ButtonType.Split);
		pHomeClip.ControlAdd(pHomeEditCopy);

		const pHomeEditDelete = this.CreateUIRibbonButton("RibHomeClipDelete", ResId.Icon_Delete_png, true);
		pHomeClip.ControlAdd(pHomeEditDelete);

		//----------------------------------------------------------------------------------------------------
		// Home - Selection

		const pHomeSel = new RibbonGroup(sender, "RibHomeSel");
		pHome.GroupAdd(pHomeSel);

		pHomeSel.ControlAdd(this.CreateUIRibbonButton("RibHomeSelSel", ResId.Icon_Paste_png));
		pHomeSel.ControlAdd(this.CreateUIRibbonButton("RibHomeSelMove", ResId.Icon_Cut_png));
		pHomeSel.ControlAdd(this.CreateUIRibbonButton("RibHomeSelScale", ResId.Icon_Copy_png));
		pHomeSel.ControlAdd(this.CreateUIRibbonButton("RibHomeSelRot", ResId.Icon_Delete_png));

		//----------------------------------------------------------------------------------------------------
		// Home - Font

		const pHomeFont = new RibbonGroup(sender, "RibHomeFont");
		pHome.GroupAdd(pHomeFont);

		const pHomeFontToolbar = new ToolBar(sender);
		pHomeFontToolbar.SetBackground(false);
		pHomeFontToolbar.ToolInsert(new ToolBarItem(1, ToolBarItemType.Button, sender.CacheIcon(new IconSource(ResId.Icon_File_png, 16))), -1);
		pHomeFontToolbar.ToolInsert(new ToolBarItem(2, ToolBarItemType.Button, sender.CacheIcon(new IconSource(ResId.Icon_FileOpen_png, 16))), -1);
		pHomeFontToolbar.ToolInsert(new ToolBarItem(3, ToolBarItemType.Button, sender.CacheIcon(new IconSource(ResId.Icon_FileSave_png, 16))), -1);
		pHomeFontToolbar.ToolInsert(new ToolBarItem(4, ToolBarItemType.Button, sender.CacheIcon(new IconSource(ResId.Icon_FileSaveAs_png, 16))), -1);
		pHomeFontToolbar.ToolInsert(new ToolBarItem(5, ToolBarItemType.Button, sender.CacheIcon(new IconSource(ResId.Icon_Cut_png, 16))), -1);
		pHomeFontToolbar.ToolInsert(new ToolBarItem(6, ToolBarItemType.Button, sender.CacheIcon(new IconSource(ResId.Icon_Copy_png, 16))), -1);
		pHomeFontToolbar.ToolInsert(new ToolBarItem(7, ToolBarItemType.Button, sender.CacheIcon(new IconSource(ResId.Icon_Paste_png, 16))), -1);
		pHomeFont.ControlAdd(pHomeFontToolbar);

		const pHomeFontToolbar1 = new ToolBar(sender);
		pHomeFontToolbar1.SetBackground(false);
		pHomeFontToolbar1.ToolInsert(new ToolBarItem(1, ToolBarItemType.Button, sender.CacheIcon(new IconSource(ResId.Icon_File_png, 16))), -1);
		pHomeFontToolbar1.ToolInsert(new ToolBarItem(2, ToolBarItemType.Button, sender.CacheIcon(new IconSource(ResId.Icon_FileOpen_png, 16))), -1);
		pHomeFontToolbar1.ToolInsert(new ToolBarItem(3, ToolBarItemType.Button, sender.CacheIcon(new IconSource(ResId.Icon_FileSave_png, 16))), -1);
		pHomeFont.ControlAdd(pHomeFontToolbar1);

		const pHomeStyle = new RibbonGroup(sender, "RibHomeStyle");
		pHome.GroupAdd(pHomeStyle);

		const pHomeStyleGallery = new RibbonGallery(sender);
		pHomeStyleGallery.ViewSetMode(RibbonGalleryViewMode.IconText2Line);
		let galitem = new RibbonGalleryItem();
		galitem.Index = -1; // Append
		for (let i = 0; i < 32; ++i) {
			galitem.Icon = sender.CacheIcon(new IconSource(Math.floor((ResId.$AppRes_Icon_Min >> 4) + (ResId.$AppRes_Icon_Max >> 4) * Math.random()) << 4, 24));
			galitem.Text = `Item ${i}`;
			pHomeStyleGallery.ItemInsert(galitem);
		}
		pHomeStyle.ControlAdd(pHomeStyleGallery);

		//----------------------------------------------------------------------------------------------------
		// Creation

		const pCreate = new RibbonTab(sender, "RibCreate");
		rib.TabAdd(pCreate);

		//----------------------------------------------------------------------------------------------------
		// Creation - Basic

		const pCreateBasic = new RibbonGroup(sender, "RibCreateBasic");
		pCreate.GroupAdd(pCreateBasic);

		pCreateBasic.ControlAdd(this.CreateUIRibbonButton("RibCreateBasicPlane", ResId.Icon_Paste_png));
		pCreateBasic.ControlAdd(this.CreateUIRibbonButton("RibCreateBasicBox", ResId.Icon_Cut_png));
		pCreateBasic.ControlAdd(this.CreateUIRibbonButton("RibCreateBasicSphere", ResId.Icon_Copy_png));
		pCreateBasic.ControlAdd(this.CreateUIRibbonButton("RibCreateBasicCylinder", ResId.Icon_Delete_png));

		//----------------------------------------------------------------------------------------------------
		// HOME - Selection

		const pCreateExt = new RibbonGroup(sender, "RibCreateExt");
		pCreate.GroupAdd(pCreateExt);

		pCreateExt.ControlAdd(this.CreateUIRibbonButton("RibCreateExtSky", ResId.Icon_Paste_png));
		pCreateExt.ControlAdd(this.CreateUIRibbonButton("RibCreateExtOcean", ResId.Icon_Cut_png));
		pCreateExt.ControlAdd(this.CreateUIRibbonButton("RibCreateExtForest", ResId.Icon_Copy_png));

		return rib;
	}

	private CreateUIAppToolbar(sender: Window) {
		const tbrApp = new ToolBar(sender, new StringKey("WdMainAppbar", 0, 10));
		tbrApp.SetBackground(false);
		tbrApp.ToolInsert(new ToolBarItem(0, ToolBarItemType.Splitter), -1);
		tbrApp.ToolInsert(new ToolBarItem(1, ToolBarItemType.Button, sender.CacheIcon(new IconSource(ResId.Icon_FileSave_png, 16))), -1);
		tbrApp.ToolInsert(new ToolBarItem(2, ToolBarItemType.Button, sender.CacheIcon(new IconSource(ResId.Icon_Undo_png, 16))), -1);
		tbrApp.ToolInsert(new ToolBarItem(3, ToolBarItemType.Button, sender.CacheIcon(new IconSource(ResId.Icon_Redo_png, 16))), -1);
		tbrApp.ToolInsert(new ToolBarItem(0, ToolBarItemType.Splitter), -1);
		tbrApp.ToolInsert(new ToolBarItem(10, ToolBarItemType.Menu), -1);
		tbrApp.ToolInsert(new ToolBarItem(11, ToolBarItemType.Menu), -1);
		tbrApp.ToolInsert(new ToolBarItem(12, ToolBarItemType.Menu), -1);
		tbrApp.ToolInsert(new ToolBarItem(13, ToolBarItemType.Menu), -1);
		tbrApp.ToolInsert(new ToolBarItem(14, ToolBarItemType.Menu), -1);
		tbrApp.ToolInsert(new ToolBarItem(0, ToolBarItemType.Splitter), -1);
		tbrApp.SetKeyTip("1", 1);
		tbrApp.SetKeyTip("2", 2);
		tbrApp.SetKeyTip("3", 3);
		tbrApp.SetKeyTip("F", 5);
		tbrApp.SetKeyTip("E", 6);
		tbrApp.SetKeyTip("V", 7);
		tbrApp.SetKeyTip("T", 8);
		tbrApp.SetKeyTip("H", 9);

		const mnuFile = new Menu(sender, new StringKey("WdMainFile", 0, 6));
		mnuFile.InsertItem(new MenuItem(1, MenuType.Text, 0, "", "Ctrl+N", "N"));
		mnuFile.InsertItem(new MenuItem(2, MenuType.Text, 0, "", "Ctrl+O", "O"));
		mnuFile.InsertItem(new MenuItem(3, MenuType.Text, sender.CacheIcon(new IconSource(ResId.Icon_FileSave_png, 16)), "", "Ctrl+S", "S"));
		mnuFile.InsertItem(new MenuItem(4, MenuType.Text, 0, "", "Ctrl+Shift+S", "A"));
		mnuFile.InsertItem(new MenuItem(0, MenuType.Separator));
		mnuFile.InsertItem(new MenuItem(5, MenuType.Text, 0, "", "Alt+F4", "X"));
		tbrApp.DropSetById(10, mnuFile);

		const mnuEdit = new Menu(sender, new StringKey("WdMainEdit", 0, 7));
		mnuEdit.InsertItem(new MenuItem(1, MenuType.Text, sender.CacheIcon(new IconSource(ResId.Icon_Undo_png, 16)), "", "Ctrl+Z", "U"));
		mnuEdit.InsertItem(new MenuItem(2, MenuType.Text, sender.CacheIcon(new IconSource(ResId.Icon_Redo_png, 16)), "", "Ctrl+Y", "R"));
		mnuEdit.InsertItem(new MenuItem(0, MenuType.Separator));
		mnuEdit.InsertItem(new MenuItem(3, MenuType.Text, 0, "", "Ctrl+X", "T"));
		mnuEdit.InsertItem(new MenuItem(4, MenuType.Text, 0, "", "Ctrl+C", "C"));
		mnuEdit.InsertItem(new MenuItem(5, MenuType.Text, 0, "", "Ctrl+V", "P"));
		mnuEdit.InsertItem(new MenuItem(6, MenuType.Text, 0, "", "Delete", "D"));
		tbrApp.DropSetById(11, mnuEdit);

		const mnuView = new Menu(sender);
		for (let i = 0; i < 16; ++i) mnuView.InsertItem(new MenuItem(i + 1, MenuType.Text, 0, `View Item ${i}`));
		mnuView.InsertItem(new MenuItem(0, MenuType.Separator));
		const mnuViewSub = mnuView.InsertSubMenu(new MenuItem(100, MenuType.Text, 0, "Sub Menu"));
		for (let i = 0; i < 16; ++i) mnuViewSub.InsertItem(new MenuItem(200 + i, MenuType.Text, 0, `Sub Item ${i}`));
		tbrApp.DropSetById(12, mnuView);

		// Create a very tall menu
		const mnuTool = new Menu(sender, new StringKey("WdMainTool", 0, 1));
		mnuTool.InsertItem(new MenuItem(1, MenuType.Text, 0, "", "", "O"));
		mnuTool.InsertItem(new MenuItem(0, MenuType.Separator));
		mnuTool.SetItemHeight(DpiSize.FromPixelScaled(64));
		for (let i = 0; i < 100; ++i) mnuTool.InsertItem(new MenuItem(100 + i, MenuType.Text, 0, `Menu Item ${i}`));
		tbrApp.DropSetById(13, mnuTool);

		const mnuHelp = new Menu(sender, new StringKey("WdMainHelp", 0, 2));
		mnuHelp.InsertItem(new MenuItem(1, MenuType.Text, 0, "", "F1", "H"));
		mnuHelp.InsertItem(new MenuItem(2, MenuType.Text, 0, "", "", "A"));
		tbrApp.DropSetById(14, mnuHelp);

		return tbrApp;
	}

	private CreateUISubAppToolbar(sender: Window) {
		const tbrApp = new ToolBar(sender);
		tbrApp.SetBackground(false);
		tbrApp.ToolInsert(new ToolBarItem(1, ToolBarItemType.ButtonDrop, sender.CacheIcon(new IconSource(ResId.Icon_ZoomIn_png, 16))), -1);
		tbrApp.ToolInsert(new ToolBarItem(2, ToolBarItemType.ButtonDrop, sender.CacheIcon(new IconSource(ResId.Icon_Language_png, 16))), -1);
		return tbrApp;
	}

	private CreateUI(sender: Window) {
		PageIndex.Register();

		sender.SetBackground(false);
		sender.SetContent(this.CreateUIRibbon(sender));

		const tbrLeft = this.CreateUIAppToolbar(sender);
		const tbrRight = this.CreateUISubAppToolbar(sender);

		sender.GetFrame().SetToolBarLeft(tbrLeft);
		sender.GetFrame().SetToolBarRight(tbrRight);
	}

	private OnCreateContent(sender: Window) {
		sender.SetTabStop(true);
		sender.SetIcon(ResId.Icon_Ui_png);
		this.CreateUI(sender);
		return true;
	}

	private OnApplyLanguage(sender: Window) {
		this.m_Page?.forEach((e) => e.OnApplyLanguage?.call(e));
	}

	private OnPageSelectionChange(sender: RichListBox) {
		if (this.m_PageCurrent) {
			this.m_PageCurrent.OnHide?.call(this.m_PageCurrent);
			this.m_PageCurrent.Control.SetVisible(false);
			this.m_PageCurrent = null;
		}
		const nIndex = sender.ItemGetSelection();
		if (nIndex >= 0 && nIndex < this.m_Page.length) this.m_PageCurrent = this.m_Page[nIndex];
		if (this.m_PageCurrent) {
			this.m_PageCurrent.OnShow?.call(this.m_PageCurrent);
			this.m_PageCurrent.Control.SetVisible(true);
		}
	}

	CreateAndShow() {
		this.m_Theme = new ThemeImage();
		if (!this.m_Theme) process.exit(-1);

		this.m_ThemeDark = new ThemePredefined_Dark();
		this.m_ThemeDark.SetStyle(this.m_Theme, 0);

		let cpWindow = new WindowCreation();
		cpWindow.Title = "Test Window";
		cpWindow.Icon = "1";
		cpWindow.Theme = this.m_Theme;
		//cpWindow.Device = WindowDevice.Default3D;
		cpWindow.Flag |= WindowFlag.Layered;

		this.WindowObject = new Window(cpWindow);

		this.WindowObject.OnCreateContent(this.OnCreateContent.bind(this));
		this.WindowObject.OnLanguageChange(this.OnApplyLanguage.bind(this));

		if (!this.WindowObject.CreateWindow()) process.exit(-1);

		this.WindowObject.SetVisible(true);
		this.WindowObject.Activate();

		return this;
	}
}
