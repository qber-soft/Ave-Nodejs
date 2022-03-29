#pragma once

#include "UiCommon.h"

namespace Nav
{

	class UiVisual;

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
			AutoAddMethod( GetRect );
			AutoAddMethod( Redraw );

			AutoAddMethod( ListenEvent );
			AutoAddMethod( OnMessagePost );

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

	private:
		AveInline WrapPointer<UiControl> __GetUiControl()
		{
			return { (UiControl*) GetControl().GetUserContext() };
		}

	private:
		using OnMessagePostCallback = JsFuncSafe<void(UiControl* sender, U32 nMsg)>;

		OnMessagePostCallback	m_OnMessagePost;

		void					__OnMessagePost(Ui::IControl& sender, Ui::ControlMessage nMsg, const Ui::MessageParam& mp);

	private:
		WrapPointer<UiControl>	SetVisible( U1 b ) { GetControl().SetVisible( b ); return __GetUiControl(); }
		U1						GetVisible() { return GetControl().GetVisible(); }

		WrapPointer<UiControl>	SetEnable( U1 b ) { GetControl().SetEnable( b ); return __GetUiControl(); }
		U1						GetEnable() { return GetControl().GetEnable(); }

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
		WrapData<S32_R>			GetRect() { return GetControl().GetRect(); }
		WrapPointer<UiControl>	Redraw() { GetControl().Redraw(); return __GetUiControl(); }

		WrapPointer<UiControl>  OnMessagePost(OnMessagePostCallback&& fn);
		void					ListenEvent();
	};

}
