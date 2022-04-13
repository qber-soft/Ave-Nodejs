#pragma once

#include "UiCommon.h"
#include "UiDragContext.h"

namespace Nav
{
	
	class Byo2Font;

	class UiControl;
	class UiVisual;
	class UiDragContext;
	class UiPainter;

	using OnDrag_t = JsFuncSafe<void( UiControl* sender, UiDragContext* dc )>;
	using OnDragEnd_t = JsFuncSafe<void( UiControl* sender, UiDragContext* dc, U1 bOk )>;

	class UiMessagePointerMouse
	{
	public:
		S32										m_LinePerWheel;
		S32										m_Wheel;
	};

	NavDefineDataByMember_( UiMessagePointerMouse, LinePerWheel, Wheel );
	NavDefineTransitByMember_( Ui::MessagePointerMouse, UiMessagePointerMouse, LinePerWheel, Wheel );

	class UiMessagePointerTouch
	{
	public:
		R32										m_Pressure;
		R32										m_Orientation;
		WrapData<S32_R>							m_Contact;
	};

	NavDefineDataByMember_( UiMessagePointerTouch, Pressure, Orientation, Contact );
	NavDefineTransitByMember_( Ui::MessagePointerTouch, UiMessagePointerTouch, Pressure, Orientation, Contact );

	class UiMessagePointerPen
	{
	public:
		R32										m_Pressure;
		R32										m_Twist;
		WrapData<R32_2>							m_Tilt;
	};

	NavDefineDataByMember_( UiMessagePointerPen, Pressure, Twist, Tilt );
	NavDefineTransitByMember_( Ui::MessagePointerPen, UiMessagePointerPen, Pressure, Twist, Tilt );

	class UiMessagePointer
	{
	public:
		U64										m_Id;
		Ui::PointerType							m_Type;
		WrapData<S32_2>							m_Position;
		U32										m_Modifier;
		Ui::PointerButton						m_Button;
		U32										m_Count;

		WrapData<UiMessagePointerMouse>			m_Mouse;
		WrapData<UiMessagePointerTouch>			m_Touch;
		WrapData<UiMessagePointerPen>			m_Pen;

		AveInline void FromUiMessage( const Ui::MessagePointer& s )
		{
			m_Id = (U64) (USize) s.m_Id;
			m_Type = s.m_Type;
			m_Position = s.m_Position;
			m_Modifier = s.m_Modifier;
			m_Button = s.m_Button;
			m_Count = s.m_Count;
			switch ( s.m_Type )
			{
			case Ui::PointerType::Mouse: WrapDataTransit<Ui::MessagePointerMouse>::Transit( m_Mouse, s.m_Mouse ); break;
			case Ui::PointerType::Touch: WrapDataTransit<Ui::MessagePointerTouch>::Transit( m_Touch, s.m_Touch );  break;
			case Ui::PointerType::Pen: WrapDataTransit<Ui::MessagePointerPen>::Transit( m_Pen, s.m_Pen );  break;
			}
		}
	};

	NavDefineDataByMember_( UiMessagePointer, Id, Type, Position, Modifier, Button, Count, Mouse, Touch, Pen );

	NavDefineDataByMember_( Ui::MessageKey, Key, Modifier );

	class UiControl
	{
	protected:
		UiControl() {}
		~UiControl() {}

	public:
		virtual Napi::Value		GetObjectValue( Napi::Env env ) = 0;

		virtual Ui::IControl&	GetControl() = 0;
		virtual Ui::Control		TakeOwnership() = 0;
		virtual void			GiveOwnership( Ui::Control c ) = 0;

		virtual void			SetSharedControl( Ui::IControl* c ) = 0;

	protected:
		template<class T>
		static void __DefineObject()
		{
#		define AutoAddMethod($x) T::AddMethod( #$x, &T::$x )

			AutoAddMethod( SetVisible );
			AutoAddMethod( GetVisible );

			AutoAddMethod( SetEnable );
			AutoAddMethod( GetEnable );

			AutoAddMethod( GetRect );
			AutoAddMethod( GetRectClient );

			AutoAddMethod( GetIdealSize );

			AutoAddMethod( GetParent );

			AutoAddMethod( SetFocusEnable );
			AutoAddMethod( GetFocusEnable );
			AutoAddMethod( GetFocus );
			AutoAddMethod( SetFocus );

			AutoAddMethod( SetKeyTip );
			AutoAddMethod( GetKeyTip );

			AutoAddMethod( SetToolTip );
			AutoAddMethod( GetToolTip );

			AutoAddMethod( SetStyle );
			AutoAddMethod( GetStyle );

			AutoAddMethod( SetFont );

			AutoAddMethod( SetTextColor );
			AutoAddMethod( GetTextColor );

			AutoAddMethod( SetOpacity );
			AutoAddMethod( GetOpacity );

			AutoAddMethod( SetRotation );
			AutoAddMethod( GetRotation );
			AutoAddMethod( HasRotation );

			AutoAddMethod( SetTabStop );
			AutoAddMethod( GetTabStop );

			AutoAddMethod( MapRect );
			AutoAddMethod( Redraw );

			AutoAddMethod( GetLastInputType );
			AutoAddMethod( GetLastPointerType );
			AutoAddMethod( GetLastMessageTime );
			AutoAddMethod( IsVisual );

#		undef AutoAddMethod

#		define AutoAddMethod($x) T::template AddMethod<WrapObjectGeneric>( #$x, &T::$x )

			AutoAddMethod( OnKeyPress   /**/ );
			AutoAddMethod( OnKeyRelease /**/ );

			AutoAddMethod( OnPointerEnter    /**/ );
			AutoAddMethod( OnPointerLeave    /**/ );
			AutoAddMethod( OnPointerPress    /**/ );
			AutoAddMethod( OnPointerRelease  /**/ );
			AutoAddMethod( OnPointerClickNdc /**/ );
			AutoAddMethod( OnPointerMove     /**/ );
			AutoAddMethod( OnPointerVWheel   /**/ );
			AutoAddMethod( OnPointerHWheel   /**/ );
			AutoAddMethod( OnPointerHover    /**/ );
			AutoAddMethod( OnPointerLost     /**/ );
			AutoAddMethod( OnPointerCursor   /**/ );

			AutoAddMethod( OnDragEnter /**/ );
			AutoAddMethod( OnDragMove  /**/ );
			AutoAddMethod( OnDragLeave /**/ );
			AutoAddMethod( OnDragDrop  /**/ );
			AutoAddMethod( OnDragEnd   /**/ );

			AutoAddMethod( OnChangeFocus );
			AutoAddMethod( OnChangeSize );
			AutoAddMethod( OnPaintPost );

#		undef AutoAddMethod
		}

		AveInline WrapPointer<UiControl> __ChangeContent( Ui::Control&& c )
		{
			UiControl* p{};
			if ( c )
			{
				p = (UiControl*) c->GetUserContext();
				p->GiveOwnership( std::move( c ) );
			}			
			return { p };
		}

		AveInline WrapPointer<UiVisual> __ChangeContent( Ui::Visual&& c )
		{
			UiVisual* p{};
			if ( c )
			{
				p = (UiVisual*) c->GetUserContext();
				((UiControl*) p)->GiveOwnership( std::move( c ) );
			}
			return { p };
		}

		AveInline WrapPointer<UiControl> __ReturnContent( Ui::IControl* p ) const
		{
			return { p ? (UiControl*) p->GetUserContext() : nullptr };
		}

		AveInline WrapPointer<UiVisual> __ReturnContent( Ui::IVisual* p ) const
		{
			return { p ? (UiVisual*) p->GetUserContext() : nullptr };
		}

		void					__ListenEvent();
		void					__OnMessagePost( Ui::IControl& sender, Ui::ControlMessage nMsg, const Ui::MessageParam& mp );
		void					__OnChangeFocus( Ui::IControl& sender, U1 bFocus );
		void					__OnPaintPost( Ui::IControl& sender, Ui::IPainter& painter, Ui::IPainterTyped& paintert, const S32_R& rcClient );

	private:
		AveInline WrapPointer<UiControl> __GetUiControl()
		{
			return { (UiControl*) GetControl().GetUserContext() };
		}

	private:
		using OnKey_t			/**/ = JsFuncSafe<void( UiControl* sender, const WrapData<Ui::MessageKey>& mk )>;
		using OnPointer_t		/**/ = JsFuncSafe<void( UiControl* sender, const WrapData<UiMessagePointer>& mp )>;
		using OnPointerCursor_t /**/ = JsFuncSafe<Ui::CursorType( UiControl* sender, const WrapData<UiMessagePointer>& mp )>;
		using OnChangeFocus_t	/**/ = JsFuncSafe<void( UiControl* sender, U1 bFocus )>;
		using OnChangeSize_t	/**/ = JsFuncSafe<void( UiControl* sender, const WrapData<S32_2>& vSize )>;
		using OnPaintPost_t		/**/ = JsFuncSafe<void( UiControl* sender, UiPainter* painter, const WrapData<S32_R>& rc )>;

		OnKey_t					m_OnKeyPress   /**/;
		OnKey_t					m_OnKeyRelease /**/;

		OnPointer_t				m_OnPointerEnter    /**/;
		OnPointer_t				m_OnPointerLeave    /**/;
		OnPointer_t				m_OnPointerPress    /**/;
		OnPointer_t				m_OnPointerRelease  /**/;
		OnPointer_t				m_OnPointerClickNdc /**/;
		OnPointer_t				m_OnPointerMove     /**/;
		OnPointer_t				m_OnPointerVWheel   /**/;
		OnPointer_t				m_OnPointerHWheel   /**/;
		OnPointer_t				m_OnPointerHover    /**/;
		OnPointer_t				m_OnPointerLost     /**/;
		OnPointerCursor_t		m_OnPointerCursor   /**/;

		OnDrag_t				m_OnDragEnter /**/;
		OnDrag_t				m_OnDragMove  /**/;
		OnDrag_t				m_OnDragLeave /**/;
		OnDrag_t				m_OnDragDrop  /**/;
		OnDragEnd_t				m_OnDragEnd   /**/;

		OnChangeFocus_t			m_OnChangeFocus;
		OnChangeSize_t			m_OnChangeSize;
		OnPaintPost_t			m_OnPaintPost;

		JsObject<UiPainter>		m_Painter;

	private:
		WrapPointer<UiControl>	SetVisible( U1 b ) { GetControl().SetVisible( b ); return __GetUiControl(); }
		U1						GetVisible() { return GetControl().GetVisible(); }

		WrapPointer<UiControl>	SetEnable( U1 b ) { GetControl().SetEnable( b ); return __GetUiControl(); }
		U1						GetEnable() { return GetControl().GetEnable(); }

		WrapData<S32_R>			GetRect() { return GetControl().GetRect(); }
		WrapData<S32_R>			GetRectClient() { return GetControl().GetRectClient(); }

		WrapData<Ui::DpiSize_2>	GetIdealSize() { return GetControl().GetIdealSize(); }

		WrapPointer<UiControl>	GetParent() { if ( auto p = GetControl().GetParent() ) return { (UiControl*) p->GetUserContext() }; return {}; }

		WrapPointer<UiControl>	SetFocusEnable( U1 b ) { GetControl().SetFocusEnable( b ); return __GetUiControl(); }
		U1						GetFocusEnable() { return GetControl().GetFocusEnable(); }
		WrapPointer<UiControl>	GetFocus() { if ( auto p = GetControl().GetFocus() ) return __GetUiControl(); return {}; }
		WrapPointer<UiControl>	SetFocus() { GetControl().SetFocus(); return __GetUiControl(); }

		WrapPointer<UiControl>	SetKeyTip( PCWChar szTip, U32 nIndex ) { GetControl().SetKeyTip( szTip, nIndex ); return __GetUiControl(); }
		WString					GetKeyTip( U32 nIndex ) { return GetControl().GetKeyTip( nIndex ); }

		WrapPointer<UiControl>	SetToolTip( PCWChar szTip ) { GetControl().SetToolTip( szTip ); return __GetUiControl(); }
		WString					GetToolTip( const WrapData<S32_2>& v ) { S32_R rc, rce; return GetControl().GetToolTip( v, rc, rce ); }

		WrapPointer<UiControl>	SetStyle( U32 nStyle ) { GetControl().SetStyle( nStyle ); return __GetUiControl(); }
		U32						GetStyle() { return GetControl().GetStyle(); }

		WrapPointer<UiControl>	SetFont( WrapPointer<Byo2Font> pFont );

		WrapPointer<UiControl>	SetTextColor( const WrapData<U8_4>& v ) { GetControl().SetTextColor( v.a > 0 ? &v : nullptr ); return __GetUiControl(); }
		WrapData<U8_4>			GetTextColor() { if ( auto p = GetControl().GetTextColor() ) return *p; else return {}; }

		WrapPointer<UiControl>	SetOpacity( R32 f ) { GetControl().SetOpacity( f ); return __GetUiControl();}
		R32						GetOpacity() { return GetControl().GetOpacity(); }

		WrapPointer<UiControl>	SetRotation( R32 f ) { GetControl().SetRotation( f ); return __GetUiControl(); }
		R32						GetRotation() { return GetControl().GetRotation(); }
		U1						HasRotation() { return GetControl().HasRotation(); }

		WrapPointer<UiControl>	SetTabStop( U1 b ) { GetControl().SetTabStop( b ); return __GetUiControl(); }
		U1						GetTabStop() { return GetControl().GetTabStop(); }

		WrapData<S32_R>			MapRect( const WrapData<S32_R>& rc, U1 bClient ) { S32_R r = rc; GetControl().MapRect( r, bClient ); return r; }
		WrapPointer<UiControl>	Redraw() { GetControl().Redraw(); return __GetUiControl(); }

		Ui::InputType			GetLastInputType() { return GetControl().GetLastInputType(); }
		Ui::PointerType			GetLastPointerType() { return GetControl().GetLastPointerType(); }
		R64						GetLastMessageTime() { return GetControl().GetLastMessageTime(); }
		U1						IsVisual() { return GetControl().IsVisual(); }

		WrapPointer<UiControl>  OnKeyPress   /**/( OnKey_t&& fn ) { m_OnKeyPress   /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>  OnKeyRelease /**/( OnKey_t&& fn ) { m_OnKeyRelease /**/ = std::move( fn ); return __GetUiControl(); }

		WrapPointer<UiControl>  OnPointerEnter    /**/( OnPointer_t       /**/ && fn ) { m_OnPointerEnter    /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>  OnPointerLeave    /**/( OnPointer_t       /**/ && fn ) { m_OnPointerLeave    /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>  OnPointerPress    /**/( OnPointer_t       /**/ && fn ) { m_OnPointerPress    /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>  OnPointerRelease  /**/( OnPointer_t       /**/ && fn ) { m_OnPointerRelease  /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>  OnPointerClickNdc /**/( OnPointer_t       /**/ && fn ) { m_OnPointerClickNdc /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>  OnPointerMove     /**/( OnPointer_t       /**/ && fn ) { m_OnPointerMove     /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>  OnPointerVWheel   /**/( OnPointer_t       /**/ && fn ) { m_OnPointerVWheel   /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>  OnPointerHWheel   /**/( OnPointer_t       /**/ && fn ) { m_OnPointerHWheel   /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>  OnPointerHover    /**/( OnPointer_t       /**/ && fn ) { m_OnPointerHover    /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>  OnPointerLost     /**/( OnPointer_t       /**/ && fn ) { m_OnPointerLost     /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>  OnPointerCursor   /**/( OnPointerCursor_t /**/ && fn ) { m_OnPointerCursor   /**/ = std::move( fn ); return __GetUiControl(); }

		WrapPointer<UiControl>	OnDragEnter /**/( OnDrag_t    /**/ && fn ) { m_OnDragEnter /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>	OnDragMove  /**/( OnDrag_t    /**/ && fn ) { m_OnDragMove  /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>	OnDragLeave /**/( OnDrag_t    /**/ && fn ) { m_OnDragLeave /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>	OnDragDrop  /**/( OnDrag_t    /**/ && fn ) { m_OnDragDrop  /**/ = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>	OnDragEnd   /**/( OnDragEnd_t /**/ && fn ) { m_OnDragEnd   /**/ = std::move( fn ); return __GetUiControl(); }

		WrapPointer<UiControl>	OnChangeFocus( OnChangeFocus_t && fn ) { m_OnChangeFocus = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>	OnChangeSize( OnChangeSize_t && fn ) { m_OnChangeSize = std::move( fn ); return __GetUiControl(); }
		WrapPointer<UiControl>	OnPaintPost( const CallbackInfo& ci, OnPaintPost_t && fn );


	public:
		AveInline void FireDragEnter( UiDragContext* dc )
		{
			dc->SetControl( &GetControl() );
			m_OnDragEnter.BlockCall( this, dc );
		}

		AveInline void FireDragMove( UiDragContext* dc )
		{
			dc->SetControl( &GetControl() );
			m_OnDragMove.BlockCall( this, dc );
		}

		AveInline void FireDragLeave( UiDragContext* dc )
		{
			dc->SetControl( &GetControl() );
			m_OnDragLeave.BlockCall( this, dc );
		}

		AveInline U1 FireDragDrop( UiDragContext* dc )
		{
			if ( m_OnDragDrop )
			{
				dc->SetControl( &GetControl() );
				m_OnDragDrop.BlockCall( this, dc );
				return true;
			}
			return false;
		}

		AveInline void FireDragEnd( UiDragContext* dc, U1 bOk )
		{
			dc->SetControl( &GetControl() );
			m_OnDragEnd.BlockCall( this, dc, bOk );
		}
	};

}
