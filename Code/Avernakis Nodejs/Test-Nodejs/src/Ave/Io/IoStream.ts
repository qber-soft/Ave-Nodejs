import { Duplex } from "stream";
import { SeekMode } from "./IoCommon";

export interface IAveStreamExtension {
    Tell(): number;
    IsBof(): boolean;
    IsEof(): boolean;
    PeekBinary(nSize: number): ArrayBuffer;
}

export interface IAveStream {
    Truncate(): boolean;
    Flush(): boolean;

    Size(): number;
    Seek(nPos: number, nSeekMode: SeekMode): number;

    // return null means failed (I/O error), an Uint8Array with length 0 means succeed but no more data anymore (just at the EOF)
    // returned length may less than nSize
    ReadBinary(nSize: number): ArrayBuffer;
    WriteBinary(pData: ArrayBuffer): number;
}

export function AveStreamAddExtension(avestream: IAveStream & { new(): IAveStream }) {
    return class extends avestream implements IAveStreamExtension {
        Tell(): number {
            return super.Seek(0, SeekMode.Current);
        }

        IsBof(): boolean {
            return 0 == this.Tell();
        }
        IsEof(): boolean {
            return this.Tell() == super.Size();
        }

        PeekBinary(nSize: number): ArrayBuffer {
            const pos = this.Tell();
            const r = super.ReadBinary(nSize);
            if (null == r)
                return r;
            super.Seek(pos, SeekMode.Begin);
            return r;
        }
    }
}
