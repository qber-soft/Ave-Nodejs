#include "StdAfx.h"
#include "UiControl.h"
#include "UiPainter.h"

#include "UiWindow.h"
#include "Byo2Font.h"

#define MakeThisFunc($x) MakeFunc( this, &UiControl::$x )

namespace Nav
{

	void UiControl::__ListenEvent()
	{
		GetControl().GetEvent<Ui::IControl::OnMessagePost>() += MakeThisFunc( __OnMessagePost );
		GetControl().GetEvent<Ui::IControl::OnChangeFocus>() += MakeThisFunc( __OnChangeFocus );
	}

	void UiControl::__OnMessagePost( Ui::IControl& sender, Ui::ControlMessage nMsg, const Ui::MessageParam& mp )
	{
		UiMessagePointer msgPointer;
		switch ( nMsg )
		{
		case Ui::ControlMessage::KeyPress   /**/: m_OnKeyPress   /**/.BlockCall( this, mp.m_Key ); break;
		case Ui::ControlMessage::KeyRelease /**/: m_OnKeyRelease /**/.BlockCall( this, mp.m_Key ); break;

		case Ui::ControlMessage::PointerEnter    /**/: msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerEnter    /**/.BlockCall( this, msgPointer ); break;
		case Ui::ControlMessage::PointerLeave    /**/: msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerLeave    /**/.BlockCall( this, msgPointer ); break;
		case Ui::ControlMessage::PointerPress    /**/: msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerPress    /**/.BlockCall( this, msgPointer ); break;
		case Ui::ControlMessage::PointerRelease  /**/: msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerRelease  /**/.BlockCall( this, msgPointer ); break;
		case Ui::ControlMessage::PointerClickNdc /**/: msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerClickNdc /**/( this, msgPointer ); break;
		case Ui::ControlMessage::PointerMove     /**/: msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerMove     /**/.BlockCall( this, msgPointer ); break;
		case Ui::ControlMessage::PointerVWheel   /**/: msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerVWheel   /**/( this, msgPointer ); break;
		case Ui::ControlMessage::PointerHWheel   /**/: msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerHWheel   /**/( this, msgPointer ); break;
		case Ui::ControlMessage::PointerHover    /**/: msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerHover    /**/( this, msgPointer ); break;
		case Ui::ControlMessage::PointerLost     /**/: msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerLost     /**/.BlockCall( this, msgPointer ); break;

		case Ui::ControlMessage::PointerCursor:
			if ( m_OnPointerCursor )
			{
				msgPointer.FromUiMessage( mp.m_Pointer );
				m_OnPointerCursor.BlockCall( this, msgPointer, *mp.m_Pointer.m_CursorType );
			}
			break;

		case Ui::ControlMessage::ChangedSize:
			m_OnChangeSize( this, mp.m_ChangedSize );
			break;
		}
	}

	void UiControl::__OnChangeFocus( Ui::IControl & sender, U1 bFocus )
	{
		m_OnChangeFocus( this, bFocus );
	}

	void UiControl::__OnPaintPost( Ui::IControl & sender, Ui::IPainter & painter, Ui::IPainterTyped & paintert, const S32_R & rcClient )
	{
		m_Painter->SetPainter( &painter );
		m_OnPaintPost.BlockCall( this, m_Painter, rcClient );
		m_Painter->SetPainter( nullptr );
	}

	WrapPointer<UiControl> UiControl::SetFont( WrapPointer<Byo2Font> pFont )
	{
		GetControl().SetFont( pFont->CloneFont() );
		return __GetUiControl();
	}

	WrapPointer<UiControl> UiControl::OnPaintPost( const CallbackInfo& ci, OnPaintPost_t && fn )
	{
		if ( fn && !m_Painter )
		{
			m_Painter = ci.NewJsObjectWithOwnership<UiPainter>();
			GetControl().GetEvent<Ui::IControl::OnPaintPost>() += MakeThisFunc( __OnPaintPost );
		}
		m_OnPaintPost = std::move( fn );
		return __GetUiControl();
	}

}
