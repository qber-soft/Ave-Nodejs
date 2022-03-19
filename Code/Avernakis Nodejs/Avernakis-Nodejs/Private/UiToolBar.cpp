#include "StdAfx.h"
#include "UiToolBar.h"

#define ThisMethod($x) &UiToolBar::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiToolBar::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiToolBar> c_obj;
	}

	void WrapDataTransit<Ui::ToolBarItem>::Transit( Ui::ToolBarItem& d, const UiToolBarItem& s )
	{
		d.m_Flag    /**/ = s.m_Flag    /**/;
		d.m_Id      /**/ = s.m_Id      /**/;
		d.m_Type    /**/ = s.m_Type    /**/;
		d.m_Icon    /**/ = s.m_Icon    /**/;
		d.m_Width   /**/ = s.m_Width   /**/;
		d.m_Text    /**/ = (PWChar) s.m_Text    /**/.c_str();
		d.m_Tooltip /**/ = (PWChar) s.m_Tooltip /**/.c_str();
	}

	void UiToolBar::DefineControl()
	{
		AutoAddMethod( ToolInsert );
		AutoAddMethod( ToolRemove );
		AutoAddMethod( ToolRemoveAll );
		AutoAddMethod( ToolGet );
		AutoAddMethod( ToolSet );
		AutoAddMethod( ToolGetById );
		AutoAddMethod( ToolSetById );
		AutoAddMethod( ToolGetCount );
		AutoAddMethod( ToolSetEnable );
		AutoAddMethod( ToolGetEnable );
		AutoAddMethod( ToolSetVisible );
		AutoAddMethod( ToolGetVisible );
		AutoAddMethod( ToolSetCheck );
		AutoAddMethod( ToolGetCheck );
		AutoAddMethod( ToolHitTest );
		AutoAddMethod( ContentSet );
		AutoAddMethod( ContentGet );
		AutoAddMethod( ContentSetById );
		AutoAddMethod( ContentGetById );
		AutoAddMethod( DropSet );
		AutoAddMethod( DropGet );
		AutoAddMethod( DropSetById );
		AutoAddMethod( DropGetById );
		AutoAddMethod( SetBackground );
		AutoAddMethod( GetBackground );
		AutoAddMethod( SetIconTextDirection );
		AutoAddMethod( GetIconTextDirection );
		AutoAddMethod( OnClick );
		AutoAddMethod( OnDrop );
	}

	U1 UiToolBar::Ctor( UiWindow * p, Napi::Value v )
	{
		if ( !__CreateControl( p, v ) )
			return false;

		GetControlTyped().SetIconManager( p->PublicCloneIconManager() );

		GetControlTyped().GetEvent<Ui::IToolBar::OnClick>() += MakeThisFunc( __OnClick );
		GetControlTyped().GetEvent<Ui::IToolBar::OnDrop>() += MakeThisFunc( __OnDrop );

		return true;
	}

	void UiToolBar::__OnClick( Ui::IToolBar & sender, const Ui::ToolBarItem & item )
	{
		m_OnClick( this, item.m_Id );
	}

	void UiToolBar::__OnDrop( Ui::IToolBar & sender, const Ui::ToolBarItem & item )
	{
		m_OnDrop( this, item.m_Id );
	}

	U1 UiToolBar::ToolInsert( const WrapData<UiToolBarItem>& item, U32 nIndexBefore )
	{
		Ui::ToolBarItem ti{};
		WrapDataTransit<Ui::ToolBarItem>::Transit( ti, item );
		return GetControlTyped().ToolInsert( ti, nIndexBefore );
	}

	WrapData<UiToolBarItem> UiToolBar::ToolGet( U32 nIndex ) const
	{
		Ui::ToolBarItem ti{ Ui::ToolBarItem::Flag_Id | Ui::ToolBarItem::Flag_Type | Ui::ToolBarItem::Flag_Icon | Ui::ToolBarItem::Flag_Text | Ui::ToolBarItem::Flag_Tooltip | Ui::ToolBarItem::Flag_Width };
		GetControlTyped().ToolGet( nIndex, ti );
		WrapData<UiToolBarItem> r{};
		WrapDataTransit<Ui::ToolBarItem>::Transit( r, ti );
		return r;
	}

	U1 UiToolBar::ToolSet( U32 nIndex, const WrapData<UiToolBarItem>& item )
	{
		Ui::ToolBarItem ti{};
		WrapDataTransit<Ui::ToolBarItem>::Transit( ti, item );
		return GetControlTyped().ToolSet( nIndex, ti );
	}

	WrapData<UiToolBarItem> UiToolBar::ToolGetById( U32 nId ) const
	{
		Ui::ToolBarItem ti{ Ui::ToolBarItem::Flag_Id | Ui::ToolBarItem::Flag_Type | Ui::ToolBarItem::Flag_Icon | Ui::ToolBarItem::Flag_Text | Ui::ToolBarItem::Flag_Tooltip | Ui::ToolBarItem::Flag_Width };
		GetControlTyped().ToolGetById( nId, ti );
		WrapData<UiToolBarItem> r{};
		WrapDataTransit<Ui::ToolBarItem>::Transit( r, ti );
		return r;
	}

	U1 UiToolBar::ToolSetById( U32 nId, const WrapData<UiToolBarItem>& item )
	{
		Ui::ToolBarItem ti{};
		WrapDataTransit<Ui::ToolBarItem>::Transit( ti, item );
		return GetControlTyped().ToolSetById( nId, ti );
	}

}
