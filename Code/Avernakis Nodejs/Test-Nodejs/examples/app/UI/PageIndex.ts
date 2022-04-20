import * as PageButton from "./Page/PageButton";
import * as PageOwnedWindow from "./Page/PageOwnedWindow";
import * as PagePopup from "./Page/PagePopup";
import * as PageRichListBox from "./Page/PageRichListBox";
import * as PageTextBox from "./Page/PageTextBox";

export function Register() {
	[
		PageButton,
		PageOwnedWindow,
		PagePopup,
		PageRichListBox,
		PageTextBox,
	].forEach((e) => e.Register());
}
