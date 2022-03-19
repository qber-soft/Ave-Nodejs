import { Vec4 } from "../Math/Vector";
import { IconCache, CheckValue, DpiSize } from "./UiCommon";

export enum WaitOpState {
    Started, // The operation is in progress, this is the initial value
    Paused, // The operation is paused
    Completed, // The opeartion has been finished without error
    Failed, // The opeartion has been failed
    Canceling, // The opeartion is canceling
    Canceled, // The opeartion is canceled
}

export interface IWaitOp {
    // Here "a job" means a call to ICommonUi.Wait which can contains one or more threads

    // Gets the current thread index in range [0, nThreadCount) when call ICommonUi.Wait
    GetThreadIndex(): number;

    // Blocks the thread until all threads reaches SyncBarrier calls, you must call SyncBarrier on every thread with same times
    SyncBarrier(): void;

    // Returns whether the whole job is canceled by clicking the cancel button from UI
    IsCanceled(): boolean;

    // Returns whether the user paused the job by clicking the cancel button which will ask the user to confirm the cancel operation
    IsPaused(): boolean;

    // Call this method will block the current thread if the job is paused (the cancel confirm dialog is displaying)
    Pause(): void;

    // Sets the maximum quantified job amount, sets to 0 presents an indetermined state.
    SetMaximum(n: number): void;

    // Sets the current progress
    SetPosition(n: number): void;

    // Adds n to the current progress
    AddPosition(n: number): void;

    // Sets the current state displayed in waiting dialog
    SetState(s: string): void;

    // Sets the result to failed, you need to stop the job (like break loops)
    Fail(): void;

    // Updates the waiting dialog immediately, for performance reason the dialog only updates after a period of time
    UpdateUi(): void;
}

export enum MessageIcon {
    None,
    Infomation,
    Warning,
    Error,
}

export enum MessageButton {
    Ok /**/ = 0x01,
    Yes /**/ = 0x02,
    No /**/ = 0x04,
    Retry /**/ = 0x08,
    Cancel /**/ = 0x10,
    Close /**/ = 0x20,
    OkCancel /**/ = Ok | Cancel,
    YesNo /**/ = Yes | No,
    YesNoCancel /**/ = Yes | No | Cancel,
    RetryCancel /**/ = Retry | Cancel,
}

export enum MessageResult {
    Failed, // failed to show message
    Ok,
    Yes,
    No,
    Retry,
    Cancel,
    Close,
    Button, // one of custom buttons in DialogMessageExtra
    Default = Failed,
}

export class MessageButtonItem {
    Id: number = 0;
    Text: string = "";
    KeyTip: string = "";
    Icon: IconCache = 0;
}

export class MessageExtra {
    // Inputs
    Icon: IconCache = 0;
    Default: MessageResult = MessageResult.Ok;
    RadioDefault: number = 0;
    Radio: MessageButtonItem[] = null;
    Button: MessageButtonItem[] = null;
    StandardButton: MessageButtonItem[] = null;
    Verification: string = "";
    VerificationKeyTip: string = "";
    VerificationDefault: CheckValue = CheckValue.Unchecked;
    VerificationTriple: boolean = false;
    FooterIcon: IconCache = 0;
    FooterText: string = "";
    MaxWidth: DpiSize = DpiSize.Zero;
}

export class MessageExResult {
    Result: MessageResult = MessageResult.Failed;
    ButtonId: number = 0;
    RadioId: number = 0;
    VerificationResult: CheckValue = CheckValue.Unchecked;
}

export class InputText {
    // Minimum chars in utf-16-char, not cluster (or you can call it word)! Like the word '𪚥' is 2 utf-16 chars), same as maximum
    MinLength: number = 0;
    MaxLength: number = 100;
    Ime: boolean = false;
    Valid: string = ""; // Valid chars, sadly you can't set words need 2 utf-16 chars here
}

export class InputNumber {
    Frac: number = 0; // 0: integers, >0: Frac digits in decimal part
    Min: number = 0;
    Max: number = 100;
    Default: number = 0;
    Step: number = 1;
}

export class SysDialogFilter {
    Display: string = "";
    Filter: string = "";
}

export interface ICommonUi {
    Wait(fn: (op: IWaitOp) => void, nThreadCount: number): WaitOpState;

    Message(
        sMain: string,
        sDetail: string,
        nIcon: MessageIcon,
        nButton: MessageButton,
        sTitle: string
    ): MessageResult;
    MessageEx(
        sMain: string,
        sDetail: string,
        nIcon: MessageIcon,
        nButton: MessageButton,
        sTitle: string,
        extra: MessageExtra
    ): MessageExResult;

    Input(
        s: string,
        sMain: string,
        sDetail: string,
        sCue: string,
        sTitle: string
    ): string;
    InputText(
        s: string,
        sMain: string,
        sDetail: string,
        sCue: string,
        sTitle: string,
        extra: InputText
    ): string;
    InputNumber(
        f: number,
        sMain: string,
        sDetail: string,
        sCue: string,
        sTitle: string,
        extra: InputNumber
    ): number;

    PickColor(vColor: Vec4, bAllowAlpha: boolean): Vec4;
    PickColorEx(
        vColor: Vec4,
        bAllowAlpha: boolean,
        fnPreview: (vColor: Vec4) => void
    ): Vec4;

    OpenFile(
        filter: SysDialogFilter[],
        sDefaultExtension: string,
        sFolder: string,
        sFileName: string
    ): string;
    OpenFiles(
        filter: SysDialogFilter[],
        sDefaultExtension: string,
        sFolder: string
    ): string[];

    OpenFolder(sFolder: string, sFileName: string): string;
    OpenFolders(sFolder: string): string[];

    SaveFile(
        filter: SysDialogFilter[],
        sDefaultExtension: string,
        sFolder: string,
        sFileName: string
    ): string;

    ExploreFolder(sFolder: string, bBackground: boolean): boolean;
    ExploreFile(sFolder: string, bBackground: boolean): boolean;
    ExploreFiles(sFolder: string[], bBackground: boolean): boolean;
}

/* Wait fn example:
 *
 * (op: IWaitOp) => {
 *	let nSample = 0;
 *	let nMax = 0;
 *
 *	// Calculate some pre requests data
 *	op.SetState( 'Pre calculating...' );
 *	op.SetMaximum( 0 );
 *	for ( ... ) {
 *		// Check pause/cancel on every 100 calculates, you can adjust this amount to satisfy your data
 *		// Call op.Pause/op.SetPosition... too much may waste CPU resources
 *		if ( ++nSample == 100 ) {
 *			nSample = 0;
 *			op.Pause();
 *			if ( op.IsCanceled() )
 *				break;
 *		}
 *		...
 *	}
 *
 *	// Waits all threads completes the pre requests data
 *	op.SyncBarrier();
 *
 *	if ( op.IsCanceled() )
 *		return;
 *
 *	// Combines results in the first thread of every result from all threads into a whole piece
 *	if ( 0 == op.GetThreadIndex() ) {
 *		...
 *
 *		// Here we know the total amount so reset the progressbar
 *		op.SetMaximum( nMax );
 *		op.SetPosition( 0 );
 *	}
 *
 *	// Waits the combine operation complete
 *	op.SyncBarrier();
 *
 *	if ( op.IsCanceled() )
 *		return;
 *
 *	op.SetState( 'Calculating...' );
 *	// Calculate final results in each threads
 *	for ( ... ) {
 *		if ( ++nSample == 100 ) {
 *			nSample = 0;
 *			op.AddPosition( 100 );
 *			op.Pause();
 *			if ( op.IsCanceled() )
 *				break;
 *		}
 *		...
 *	}
 * }
 **/
