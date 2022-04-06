import * as PageButton from "./PageButton";
import * as PageRichListBox from "./PageRichListBox";
import * as PageTextBox from "./PageTextBox";

export function Register() {
	[PageButton, PageRichListBox, PageTextBox].forEach((e) => e.Register());
}
