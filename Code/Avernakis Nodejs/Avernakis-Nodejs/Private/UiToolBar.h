#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiToolBarItem
	{
	public:
		U32						m_Flag;
		U32						m_Id;
		Ui::ToolBarItemType		m_Type;
		Ui::IconCache			m_Icon;
		WrapData<Ui::DpiSize>	m_Width;
		WString					m_Text;
		WString					m_Tooltip;
	};

	NavDefineDataByMember_( UiToolBarItem, Flag, Id, Type, Icon, Width, Text, Tooltip );
	NavDefineTransitByMemberOut_( Ui::ToolBarItem, UiToolBarItem, Flag, Id, Type, Icon, Width, Text, Tooltip );

	class UiToolBar : public UiControlHelper<UiToolBar, Ui::IToolBar>
	{
	public:
		AveWrapControl( UiToolBar );

		~UiToolBar()
		{
		}

		static PCAChar					GetExportName() { return "UiToolBar"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using Callback_t = JsFuncSafe<void( UiToolBar* sender, U32 nId )>;

		Callback_t						m_OnClick;
		Callback_t						m_OnDrop;

		void							__OnClick( Ui::IToolBar& sender, const Ui::ToolBarItem& item );
		void							__OnDrop( Ui::IToolBar& sender, const Ui::ToolBarItem& item );

	private:
		U1								ToolInsert( const WrapData<UiToolBarItem>& item, U32 nIndexBefore );
		U1								ToolRemove( U32 nIndex ) { return GetControlTyped().ToolRemove( nIndex ); }
		UiToolBar*						ToolRemoveAll() { GetControlTyped().ToolRemoveAll(); return this; }
		WrapData<UiToolBarItem>			ToolGet( U32 nIndex ) const;
		U1								ToolSet( U32 nIndex, const WrapData<UiToolBarItem>& item );
		WrapData<UiToolBarItem>			ToolGetById( U32 nId ) const;
		U1								ToolSetById( U32 nId, const WrapData<UiToolBarItem>& item );
		U32								ToolGetCount() const { return GetControlTyped().ToolGetCount(); }

		UiToolBar*						ToolSetEnable( U32 nId, U1 bEnable ) { GetControlTyped().ToolSetEnable( nId, bEnable ); return this; }
		U1								ToolGetEnable( U32 nId ) const { return GetControlTyped().ToolGetEnable( nId ); }

		UiToolBar*						ToolSetVisible( U32 nId, U1 bVisible ) { GetControlTyped().ToolSetVisible( nId, bVisible ); return this; }
		U1								ToolGetVisible( U32 nId ) const { return GetControlTyped().ToolGetVisible( nId ); }

		UiToolBar*						ToolSetCheck( U32 nId, U1 bCheck ) { GetControlTyped().ToolSetCheck( nId, bCheck ); return this; }
		U1								ToolGetCheck( U32 nId ) const { return GetControlTyped().ToolGetCheck( nId ); }

		S32								ToolHitTest( const WrapData<S32_2>& pt, U1 bIncludeInvisible, U1 bIncludeDisabled ) const { return GetControlTyped().ToolHitTest( pt, bIncludeInvisible, bIncludeDisabled ); }

		WrapPointer<UiControl>			ContentSet( U32 nIndex, WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().ContentSet( nIndex, pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			ContentGet( U32 nIndex ) const { return __ReturnContent( GetControlTyped().ContentGet( nIndex ) ); }
		WrapPointer<UiControl>			ContentSetById( U32 nId, WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().ContentSetById( nId, pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			ContentGetById( U32 nId ) const { return __ReturnContent( GetControlTyped().ContentGetById( nId ) ); }

		WrapPointer<UiControl>			DropSet( U32 nIndex, WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().DropSet( nIndex, pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			DropGet( U32 nIndex ) const { return __ReturnContent( GetControlTyped().DropGet( nIndex ) ); }
		WrapPointer<UiControl>			DropSetById( U32 nId, WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().DropSetById( nId, pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			DropGetById( U32 nId ) const { return __ReturnContent( GetControlTyped().DropGetById( nId ) ); }

		UiToolBar*						SetBackground( U1 b ) { GetControlTyped().SetBackground( b ); return this; }
		U1								GetBackground() const { return GetControlTyped().GetBackground(); }

		UiToolBar*						SetIconTextDirection( Ui::CrossDirection nDir ) { GetControlTyped().SetIconTextDirection( nDir ); return this; }
		Ui::CrossDirection				GetIconTextDirection() const { return GetControlTyped().GetIconTextDirection(); }

		UiToolBar*						OnClick( Callback_t&& fn ) { m_OnClick = std::move( fn ); return this; }
		UiToolBar*						OnDrop( Callback_t&& fn ) { m_OnDrop = std::move( fn ); return this; }
	};
}
