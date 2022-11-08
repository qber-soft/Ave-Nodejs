import { Vec2 } from "../Math/Vector";
import { PopupAlign, Rect } from "./UiCommon";

export enum PointerVisibility {
	Hidden,
	Visible,
	Suppressed, // Visible but not drawing by system because the user is providing input through touch or pen instead of the mouse
}

// prettier-ignore
export enum MonitorConnectorType {
	Unknown              /**/ = -2,
	Other                /**/ = -1,
	HD15                 /**/ = 0, // VGA
	SVideo               /**/ = 1, // S-Video
	Composite            /**/ = 2, // Composite Video
	Component            /**/ = 3, // Component Video
	DVI                  /**/ = 4, // Digital Video Interface
	HDMI                 /**/ = 5, // High-Definition Multimedia Interface
	LVDS                 /**/ = 6, // Low Voltage Differential Swing
	JapaneseD            /**/ = 8, // Japanese D
	SDI                  /**/ = 9, // SDI
	DisplayPort_External /**/ = 10, // External DP
	DisplayPort_Embedded /**/ = 11, // Embedded DP
	UDI_External         /**/ = 12, // Unified Display Interface
	UDI_Embedded         /**/ = 13, // Unified Display Interface
	SDTV                 /**/ = 14, // Standard Definition Television
}

export class MonitorItem {
	static FromNative(item: MonitorItem) {
		item.AreaFull = Rect.FromNative(item.AreaFull);
		item.AreaWorking = Rect.FromNative(item.AreaWorking);
		item.DpiEffective = Vec2.FromNative(item.DpiEffective);
		item.DpiRaw = Vec2.FromNative(item.DpiRaw);
		item.ScaleEffective = Vec2.FromNative(item.ScaleEffective);
		item.ScaleRaw = Vec2.FromNative(item.ScaleRaw);
		return item;
	}
	AreaFull: Rect;
	AreaWorking: Rect; // Taskbar is excluded

	// Extend infomation
	Index: number;
	Primary: boolean;
	ConnectorType: MonitorConnectorType;
	Name: string;
	DpiEffective: Vec2;
	DpiRaw: Vec2;
	ScaleEffective: Vec2;
	ScaleRaw: Vec2;
}

export interface IPlatform {
	GetPopupAlign(): PopupAlign;

	PointerGetPosition(): Vec2;
	PointerSetPosition(vPos: Vec2): void;
	PointerGetVisible(): PointerVisibility;
	PointerSetVisible(b: boolean): void;

	ScreenGetArea(): Rect;

	MonitorEnumerate(): MonitorItem[];
	MonitorGetNeareatPoint(vPos: Vec2, bExtendInfo: boolean): MonitorItem;
	MonitorGetNeareatRect(vPos: Rect, bExtendInfo: boolean): MonitorItem;

	FontEnumerate(bIncludeVertical: boolean): string[];
}
