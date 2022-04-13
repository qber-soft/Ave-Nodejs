import * as PageButton from "./Page/PageButton";
import * as PageRichListBox from "./Page/PageRichListBox";
import * as PageTextBox from "./Page/PageTextBox";

export function Register() {
	[PageButton, PageRichListBox, PageTextBox].forEach((e) => e.Register());
}
