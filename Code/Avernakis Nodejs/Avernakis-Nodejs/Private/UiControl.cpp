#include "StdAfx.h"
#include "UiControl.h"

#define MakeThisFunc($x) MakeFunc( this, &UiControl::$x )

namespace Nav
{
	void UiControl::__OnMessagePost(Ui::IControl& sender, Ui::ControlMessage nMsg, const Ui::MessageParam& mp)
	{
		m_OnMessagePost(this, static_cast<uint32_t>(nMsg));
	}

	WrapPointer<UiControl> UiControl::OnMessagePost(OnMessagePostCallback&& fn)
	{
		m_OnMessagePost = std::move(fn);
		return __GetUiControl();
	}

	void UiControl::ListenEvent()
	{
		// TODO: move it to constructor?
		GetControl().GetEvent<Ui::IControl::OnMessagePost>() += MakeThisFunc(__OnMessagePost);
	}
}
