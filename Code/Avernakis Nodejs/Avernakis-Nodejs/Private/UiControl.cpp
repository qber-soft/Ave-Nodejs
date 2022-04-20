#include "StdAfx.h"
#include "UiControl.h"
#include "UiPainter.h"

#include "UiWindow.h"
#include "Byo2Font.h"

#define MakeThisFunc($x) MakeFunc( this, &UiControl::$x )

namespace Nav
{

	void UiControl::AcquirePainter( const CallbackInfo & ci )
	{
		if ( 1 == ++m_PainterRefCount )
		{
			if ( !m_Painter )
				m_Painter = ci.NewJsObjectWithOwnership<UiPainter>();
		}
	}

	void UiControl::ReleasePainter()
	{
		if ( 0 == --m_PainterRefCount )
		{
			m_Painter.Reset();
		}
	}

	UiPainter * UiControl::GetPainter( Ui::IPainter * p )
	{
		m_Painter->SetPainter( p );
		return m_Painter;
	}

	void UiControl::__ListenMessagePost( U1 b )
	{
		U32 n;
		if ( b )
			n = ++m_MessagePostRefCount;
		else
			n = --m_MessagePostRefCount;

		if ( 1 == n )
		{
			GetControl().GetEvent<Ui::IControl::OnMessagePost>() += MakeThisFunc( __OnMessagePost );
		}
		else if ( 0 == n )
		{
			GetControl().GetEvent<Ui::IControl::OnMessagePost>() -= MakeThisFunc( __OnMessagePost );
		}
	}

	void UiControl::__OnMessagePost( Ui::IControl& sender, Ui::ControlMessage nMsg, const Ui::MessageParam& mp )
	{
		UiMessagePointer msgPointer;
		switch ( nMsg )
		{
		case Ui::ControlMessage::KeyPress   /**/: m_OnKeyPress   /**/.BlockCall( this, mp.m_Key ); break;
		case Ui::ControlMessage::KeyRelease /**/: m_OnKeyRelease /**/.BlockCall( this, mp.m_Key ); break;

		case Ui::ControlMessage::PointerEnter    /**/: if ( m_OnPointerEnter    /**/ ) { msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerEnter    /**/.BlockCall( this, msgPointer ); } break;
		case Ui::ControlMessage::PointerLeave    /**/: if ( m_OnPointerLeave    /**/ ) { msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerLeave    /**/.BlockCall( this, msgPointer ); } break;
		case Ui::ControlMessage::PointerPress    /**/: if ( m_OnPointerPress    /**/ ) { msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerPress    /**/.BlockCall( this, msgPointer ); } break;
		case Ui::ControlMessage::PointerRelease  /**/: if ( m_OnPointerRelease  /**/ ) { msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerRelease  /**/.BlockCall( this, msgPointer ); } break;
		case Ui::ControlMessage::PointerClickNdc /**/: if ( m_OnPointerClickNdc /**/ ) { msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerClickNdc /**/( this, msgPointer ); } break;
		case Ui::ControlMessage::PointerMove     /**/: if ( m_OnPointerMove     /**/ ) { msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerMove     /**/.BlockCall( this, msgPointer ); } break;
		case Ui::ControlMessage::PointerVWheel   /**/: if ( m_OnPointerVWheel   /**/ ) { msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerVWheel   /**/( this, msgPointer ); } break;
		case Ui::ControlMessage::PointerHWheel   /**/: if ( m_OnPointerHWheel   /**/ ) { msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerHWheel   /**/( this, msgPointer ); } break;
		case Ui::ControlMessage::PointerHover    /**/: if ( m_OnPointerHover    /**/ ) { msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerHover    /**/( this, msgPointer ); } break;
		case Ui::ControlMessage::PointerLost     /**/: if ( m_OnPointerLost     /**/ ) { msgPointer.FromUiMessage( mp.m_Pointer ); m_OnPointerLost     /**/.BlockCall( this, msgPointer ); } break;

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
		if ( auto p = GetPainter( &painter ) )
			m_OnPaintPost.BlockCall( this, p, rcClient );
	}

	WrapPointer<UiControl> UiControl::SetFont( WrapPointer<Byo2Font> pFont )
	{
		GetControl().SetFont( pFont->CloneFont() );
		return __GetUiControl();
	}

	WrapPointer<UiControl> UiControl::OnChangeFocus( OnChangeFocus_t && fn )
	{
		if ( fn )
			GetControl().GetEvent<Ui::IControl::OnChangeFocus>() += MakeThisFunc( __OnChangeFocus );
		else
			GetControl().GetEvent<Ui::IControl::OnChangeFocus>() -= MakeThisFunc( __OnChangeFocus );
		m_OnChangeFocus = std::move( fn );
		return __GetUiControl();
	}

	WrapPointer<UiControl> UiControl::OnPaintPost( const CallbackInfo& ci, OnPaintPost_t && fn )
	{
		if ( fn )
		{
			AcquirePainter( ci );
			GetControl().GetEvent<Ui::IControl::OnPaintPost>() += MakeThisFunc( __OnPaintPost );
		}
		else
		{
			GetControl().GetEvent<Ui::IControl::OnPaintPost>() -= MakeThisFunc( __OnPaintPost );
			ReleasePainter();
		}
		m_OnPaintPost = std::move( fn );
		return __GetUiControl();
	}

}
