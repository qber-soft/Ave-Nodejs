import * as PageButton from "./Page/PageButton";
import * as PageOwnedWindow from "./Page/PageOwnedWindow";
import * as PageRichListBox from "./Page/PageRichListBox";
import * as PageTextBox from "./Page/PageTextBox";

export function Register() {
	[
		PageButton,
		PageOwnedWindow,
		PageRichListBox,
		PageTextBox,
	].forEach((e) => e.Register());
}
