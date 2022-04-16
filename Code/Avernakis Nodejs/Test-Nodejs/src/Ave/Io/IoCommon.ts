import { TimePoint } from "../TimePoint";

export class InMemoryData {
	Data: ArrayBuffer = null;
	RowPitch: number = 0;
	SlicePitch: number = 0;

	constructor(ab: ArrayBuffer = null, rowPitch: number = 0, slicePitch: number = 0) {
		this.Data = ab;
		this.RowPitch = rowPitch;
		this.SlicePitch = slicePitch;
	}
}

export interface IAveStream {}

export interface IResourceProvider {
	IsExist(nId: number): boolean;
	GetAll(): number[];
	GetSize(nId: number): number;
	Open(nId: number): IAveStream;
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
	InMemory: InMemoryData = new InMemoryData();

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

	static ToArrayBuffer(buffer: Buffer) {
		const ab = buffer.buffer.slice(buffer.byteOffset, buffer.byteOffset + buffer.byteLength);
		return ab;
	}

	// https://stackoverflow.com/a/22165328
	static FromBuffer(buffer: Buffer, rowPitch: number = 0, slicePitch: number = 0) {
		const ab = ResourceSource.ToArrayBuffer(buffer);
		return ResourceSource.FromArrayBuffer(ab, rowPitch, slicePitch);
	}

	static FromArrayBuffer(ab: ArrayBuffer, rowPitch: number = 0, slicePitch: number = 0) {
		let r = new ResourceSource();
		r.Type = ResourceSourceType.InMemory;
		r.InMemory = new InMemoryData(ab, rowPitch, slicePitch);
		return r;
	}

	static get Empty() {
		let r = new ResourceSource();
		r.Type = ResourceSourceType.InMemory;
		r.InMemory = new InMemoryData(null, 0, 0);
		return r;
	}
}

// prettier-ignore
export enum FileAttribute {
    ReadOnly          /**/ = 0x00000001,
    Hidden            /**/ = 0x00000002,
    System            /**/ = 0x00000004,
    Directory         /**/ = 0x00000010,
    Archive           /**/ = 0x00000020,
    Device            /**/ = 0x00000040,
    Normal            /**/ = 0x00000080,
    Temporary         /**/ = 0x00000100,
    SparseFile        /**/ = 0x00000200,
    ReparsePoint      /**/ = 0x00000400,
    Compressed        /**/ = 0x00000800,
    Offline           /**/ = 0x00001000,
    NotContentIndexed /**/ = 0x00002000,
    Encrypted         /**/ = 0x00004000,
    IntegrityStream   /**/ = 0x00008000,
    Virtual           /**/ = 0x00010000,
    NoScrubData       /**/ = 0x00020000,
    Invalid           /**/ = 0x80000000,
}

export class FileInfo {
	Size: number;
	TimeCreate: TimePoint;
	TimeModify: TimePoint;
	TimeAccess: TimePoint;
	Attribute: FileAttribute;

	static FromNative(p: FileInfo) {
		let r = new FileInfo();
		r.Size = p.Size;
		r.TimeCreate = TimePoint.FromTick(p.TimeCreate.Tick);
		r.TimeModify = TimePoint.FromTick(p.TimeModify.Tick);
		r.TimeAccess = TimePoint.FromTick(p.TimeAccess.Tick);
		r.Attribute = p.Attribute;
		return r;
	}
}

export class FileFindItem {
	Info: FileInfo;
	Name: string;

	static FromNative(p: FileFindItem) {
		let r = new FileFindItem();
		r.Info = FileInfo.FromNative(p.Info);
		r.Name = p.Name;
		return r;
	}
}

export enum SeekMode {
	Begin,
	Current,
	End,
}
