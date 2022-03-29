#include "StdAfx.h"
#include "UiControl.h"

#define MakeThisFunc($x) MakeFunc( this, &UiControl::$x )

namespace Nav
{
	void UiControl::__OnMessagePost(Ui::IControl& sender, Ui::ControlMessage nMsg, const Ui::MessageParam& mp)
	{
		m_OnMessagePost(this, static_cast<uint32_t>(nMsg));

		switch (nMsg)
		{
		case Ave::Ui::ControlMessage::PointerEnter:
			m_OnPointerEnter(this);
			break;
		case Ave::Ui::ControlMessage::PointerLeave:
			m_OnPointerLeave(this);
			break;
		case Ave::Ui::ControlMessage::PointerPress:
			break;
		case Ave::Ui::ControlMessage::PointerRelease:
			break;
		case Ave::Ui::ControlMessage::PointerClickNdc:
			break;
		case Ave::Ui::ControlMessage::PointerMove:
			break;
		case Ave::Ui::ControlMessage::PointerVWheel:
			break;
		case Ave::Ui::ControlMessage::PointerHWheel:
			break;
		case Ave::Ui::ControlMessage::PointerHover:
			break;
		case Ave::Ui::ControlMessage::PointerLost:
			break;
		case Ave::Ui::ControlMessage::PointerCursor:
			break;

		default:
			break;
		}
	}

	WrapPointer<UiControl> UiControl::OnMessagePost(OnMessagePostCallback&& fn)
	{
		m_OnMessagePost = std::move(fn);
		return __GetUiControl();
	}

	WrapPointer<UiControl> UiControl::OnPointerEnter(Callback_t&& fn)
	{
		m_OnPointerEnter = std::move(fn);
		return __GetUiControl();
	}

	WrapPointer<UiControl> UiControl::OnPointerLeave(Callback_t&& fn)
	{
		m_OnPointerLeave = std::move(fn);
		return __GetUiControl();
	}

	void UiControl::ListenEvent()
	{
		// TODO: move it to constructor?
		GetControl().GetEvent<Ui::IControl::OnMessagePost>() += MakeThisFunc(__OnMessagePost);
	}
}
