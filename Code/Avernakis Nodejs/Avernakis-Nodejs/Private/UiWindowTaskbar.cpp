#include "StdAfx.h"
#include "UiWindowTaskbar.h"
#include "UiCommon.h"

#include "ImgImage.h"

#define ThisMethod($x) &UiWindowTaskbar::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiWindowTaskbar::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiWindowTaskbar> c_obj;
	}

	void UiWindowTaskbar::DefineObject()
	{
		AutoAddMethod( GetWindow );
		AutoAddMethod( SetState );
		AutoAddMethod( GetState );
		AutoAddMethod( SetMaximum );
		AutoAddMethod( GetMaximum );
		AutoAddMethod( SetValue );
		AutoAddMethod( GetValue );
		AutoAddMethod( SetStep );
		AutoAddMethod( GetStep );
		AutoAddMethod( Step );
		AutoAddMethod( SetForceBigIconSize100 );
		AutoAddMethod( GetForceBigIconSize100 );
		AutoAddMethod( SetIconicImage );
		AutoAddMethod( GetIconicImage );
		AutoAddMethod( SetIconicThumbnail );
		AutoAddMethod( SetIconicLivePreview );
		AutoAddMethod( GetButtonCount );
		AutoAddMethod( SetButtonVisible );
		AutoAddMethod( GetButtonVisible );
		AutoAddMethod( SetButtonEnable );
		AutoAddMethod( GetButtonEnable );
		AutoAddMethod( SetButtonIcon );
		AutoAddMethod( GetButtonIcon );
		AutoAddMethod( SetButtonTooltip );
		AutoAddMethod( GetButtonTooltip );
		AutoAddMethod( SetIconCount );
		AutoAddMethod( GetIconCount );
		AutoAddMethod( SetIcon );
		AutoAddMethod( GetIcon );

		AutoAddMethod( OnIconicUpdate );
		AutoAddMethod( OnButtonClick );
	}

	void UiWindowTaskbar::__OnIconicUpdate( Ui::IWindowTaskbar & sender, const Ui::WindowTaskbarIconicImage & ii )
	{
		m_OnIconicUpdate.BlockCall( this, ii );
	}

	void UiWindowTaskbar::__OnButtonClick( Ui::IWindowTaskbar & sender, U32 nIndex )
	{
		m_OnButtonClick( this, nIndex );
	}

	UiWindowTaskbar * UiWindowTaskbar::SetIconicThumbnail( ImgImage * img )
	{
		if ( img && img->Get() )
			m_Taskbar->SetIconicThumbnail( *img->Get() );
		return this;
	}

	UiWindowTaskbar * UiWindowTaskbar::SetIconicLivePreview( ImgImage * img )
	{
		if ( img && img->Get() )
			m_Taskbar->SetIconicLivePreview( *img->Get() );
		return this;
	}

	UiWindowTaskbar * UiWindowTaskbar::SetIcon( U32 nIndex, ImgImage * img )
	{
		if ( img )
			m_Taskbar->SetIcon( nIndex, img->CloneImage() );
		return this;
	}

	ImgImage * UiWindowTaskbar::GetIcon( const CallbackInfo & ci, U32 nIndex ) const
	{
		if ( auto pImage = m_Taskbar->GetIcon( nIndex ) )
		{
			if ( auto p = ci.NewJsObject<ImgImage>() )
			{
				p->SetImage( Img::Image( (Img::IImage*) pImage, true ) );
				return p;
			}
		}
		return nullptr;
	}

	UiWindowTaskbar * UiWindowTaskbar::OnIconicUpdate( OnIconicUpdate_t && fn )
	{
		if ( !m_OnIconicUpdate && fn )
			m_Taskbar->GetEvent<Ui::IWindowTaskbar::OnIconicUpdate>() += MakeThisFunc( __OnIconicUpdate );
		else if ( m_OnIconicUpdate && !fn )
			m_Taskbar->GetEvent<Ui::IWindowTaskbar::OnIconicUpdate>() -= MakeThisFunc( __OnIconicUpdate );
		m_OnIconicUpdate = std::move( fn );
		return this;
	}

	UiWindowTaskbar * UiWindowTaskbar::OnButtonClick( OnButtonClick_t && fn )
	{
		if ( !m_OnButtonClick && fn )
			m_Taskbar->GetEvent<Ui::IWindowTaskbar::OnButtonClick>() += MakeThisFunc( __OnButtonClick );
		else if ( m_OnButtonClick && !fn )
			m_Taskbar->GetEvent<Ui::IWindowTaskbar::OnButtonClick>() -= MakeThisFunc( __OnButtonClick );
		m_OnButtonClick = std::move( fn );
		return this;
	}

}
