import * as PageButton from "./Page/PageButton";
import * as PageOwnedWindow from "./Page/PageOwnedWindow";
import * as PagePopup from "./Page/PagePopup";
import * as PageRichLabel from "./Page/PageRichLabel";
import * as PageRichListBox from "./Page/PageRichListBox";
import * as PageTextBox from "./Page/PageTextBox";

export function Register() {
	[
		PageButton,
		PageOwnedWindow,
		PagePopup,
		PageRichLabel,
		PageRichListBox,
		PageTextBox,
	].forEach((e) => e.Register());
}
