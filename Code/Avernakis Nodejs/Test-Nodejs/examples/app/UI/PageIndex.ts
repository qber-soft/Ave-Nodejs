import * as PageButton from "./Page/PageButton";
import * as PageCodeEditor from "./Page/PageCodeEditor";
import * as PageOwnedWindow from "./Page/PageOwnedWindow";
import * as PagePopup from "./Page/PagePopup";
import * as PageRichLabel from "./Page/PageRichLabel";
import * as PageRichListBox from "./Page/PageRichListBox";
import * as PageTextBox from "./Page/PageTextBox";

export function Register() {
	[
		PageButton,
		PageCodeEditor,
		PageOwnedWindow,
		PagePopup,
		PageRichLabel,
		PageRichListBox,
		PageTextBox,
	].forEach((e) => e.Register());
}
