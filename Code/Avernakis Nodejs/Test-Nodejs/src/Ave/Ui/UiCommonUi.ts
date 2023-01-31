import { Vec4 } from "../Math/Vector";
import { IconCache, CheckValue, DpiSize } from "./UiCommon";

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
	FooterIsLink: boolean = false;
	MaxWidth: DpiSize = DpiSize.Zero;

	OnMessageLink: (nId: number) => void;
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

	constructor(display: string, filter: string) {
		this.Display = display;
		this.Filter = filter;
	}
}

export interface ICommonUi {
	Message(sMain: string, sDetail: string, nIcon: MessageIcon, nButton: MessageButton, sTitle: string): Promise<MessageResult>;
	MessageEx(sMain: string, sDetail: string, nIcon: MessageIcon, nButton: MessageButton, sTitle: string, extra: MessageExtra): Promise<MessageExResult>;

	Input(s: string, sMain: string, sDetail: string, sCue: string, sTitle: string): Promise<string>;
	InputText(s: string, sMain: string, sDetail: string, sCue: string, sTitle: string, extra: InputText): Promise<string>;
	InputNumber(f: number, sMain: string, sDetail: string, sCue: string, sTitle: string, extra: InputNumber): Promise<number>;

	PickColor(vColor: Vec4, bAllowAlpha: boolean): Promise<Vec4>;
	PickColorEx(vColor: Vec4, bAllowAlpha: boolean, fnPreview: (vColor: Vec4) => void): Promise<Vec4>;

	OpenFile(filter: SysDialogFilter[], sDefaultExtension: string, sFolder: string, sFileName: string): Promise<string>;
	OpenFiles(filter: SysDialogFilter[], sDefaultExtension: string, sFolder: string): Promise<string[]>;

	OpenFolder(sFolder: string, sFileName: string): Promise<string>;
	OpenFolders(sFolder: string): Promise<string[]>;

	SaveFile(filter: SysDialogFilter[], sDefaultExtension: string, sFolder: string, sFileName: string): Promise<string>;

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
