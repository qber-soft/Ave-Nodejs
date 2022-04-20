#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiTabItem
	{
	public:
		U32									m_Id;
		S32									m_Order;
		Ui::IconCache						m_Icon;
		WString								m_Text;
		WString								m_StackGroup;
		WString								m_StackText;
		U32									m_GroupId;
		U32									m_Misc;
		U32									m_ButtonMask;
		WrapData<U8_4>						m_Color;
	};

	NavDefineDataByMember_( UiTabItem, Id, Order, Icon, Text, StackGroup, StackText, GroupId, Misc, ButtonMask, Color );
	NavDefineTransitByMember_( Ui::TabItem, UiTabItem, Id, Order, Icon, Text, StackGroup, StackText, GroupId, Misc, ButtonMask, Color );

	class UiTabGroup
	{
	public:
		U32									m_Flag;
		U32									m_Id;
		S32									m_OrderNormal;
		S32									m_OrderPinned;
		Ui::IconCache						m_Icon;
		WString								m_Text;
		U32									m_ButtonMask;
		WrapData<U8_4>						m_Color;
	};

	NavDefineDataByMember_( UiTabGroup, Flag, Id, OrderNormal, OrderPinned, Icon, Text, ButtonMask, Color );
	NavDefineTransitByMember_( Ui::TabGroup, UiTabGroup, Flag, Id, OrderNormal, OrderPinned, Icon, Text, ButtonMask, Color );
	
	class UiTab : public UiControlHelper<UiTab, Ui::ITab>
	{
	public:
		AveWrapControl( UiTab );

		~UiTab()
		{
		}

		static PCAChar					GetExportName() { return "UiTab"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnSelectionChange_t /**/ = JsFuncSafe<void( UiTab* sender )>;
		using OnTabClick_t        /**/ = JsFuncSafe<void( UiTab* sender, U32 nId, Ui::TabObjectType nType )>;
		using OnDrag_t            /**/ = JsFuncSafe<void( UiTab* sender, U32 nId, Ui::TabObjectType nType, const WrapData<S32_2>& vDragStartPosition )>;
		using OnButtonClick_t     /**/ = JsFuncSafe<void( UiTab* sender, U32 nId, Ui::TabObjectType nType, U32 nButtonIndex )>;

		OnSelectionChange_t				m_OnSelectionChange /**/;
		OnTabClick_t					m_OnDoubleClick     /**/;
		OnTabClick_t					m_OnRightClick      /**/;
		OnTabClick_t					m_OnMiddleClick     /**/;
		OnDrag_t						m_OnDrag            /**/;
		OnButtonClick_t					m_OnButtonClick     /**/;
		
		void							__OnSelectionChange /**/( Ui::ITab& sender );
		void							__OnDoubleClick     /**/( Ui::ITab& sender, U32 nId, Ui::TabObjectType nType );
		void							__OnRightClick      /**/( Ui::ITab& sender, U32 nId, Ui::TabObjectType nType );
		void							__OnMiddleClick     /**/( Ui::ITab& sender, U32 nId, Ui::TabObjectType nType );
		void							__OnDrag            /**/( Ui::ITab& sender, U32 nId, Ui::TabObjectType nType, const S32_2& vDragStartPosition );
		void							__OnButtonClick     /**/( Ui::ITab& sender, U32 nId, Ui::TabObjectType nType, U32 nButtonIndex );

	private:
		U1								TabInsert( const WrapData<UiTabItem>& pTab );
		List<U32>						TabGetAll() const { List<U32> v( GetControlTyped().TabGetCount() ); if ( !v.IsEmpty() ) GetControlTyped().TabGetAll( v.Data(), (U32) v.Size() ); return std::move( v ); }
		WrapData<UiTabItem>				TabGet( U32 nId ) const;
		U1								TabSet( const WrapData<UiTabItem>& pTab );
		U1								TabRemove( U32 nId ) { return GetControlTyped().TabRemove( nId ); }
		UiTab*							TabClear() { GetControlTyped().TabClear(); return this; }

		U1								TabSelect( U32 nId ) { return GetControlTyped().TabSelect( nId ); }
		U32								TabGetSelection() const { return GetControlTyped().TabGetSelection(); }
		UiTab*							TabSetSelected( U32 nId, U1 bSelect ) { GetControlTyped().TabSelect( nId, bSelect ); return this; }
		U1								TabGetSelected( U32 nId ) const { return GetControlTyped().TabGetSelection( nId ); }
		U32								TabGetSelectionCount() const { return GetControlTyped().TabGetSelectionCount(); }
		List<U32>						TabGetAllSelection() const { return GetControlTyped().TabGetAllSelection(); }
		UiTab*							TabSetMultipleSelection( U1 b ) { GetControlTyped().TabSetMultipleSelection( b ); return this; }
		U1								TabGetMultipleSelection() const { return GetControlTyped().TabGetMultipleSelection(); }

		WrapData<S32_R>					TabGetRect( U32 nId, U1 bReal ) const { S32_R rc{}; GetControlTyped().TabGetRect( nId, rc, bReal ); return rc; }
		WrapData<S32_R>					TabGetHeaderRect() const { return GetControlTyped().TabGetRect(); }

		UiTab*							TabSetDirection( Ui::AxisDirection nDir ) { GetControlTyped().TabSetDirection( nDir ); return this; }
		Ui::AxisDirection				TabGetDirection() const { return GetControlTyped().TabGetDirection(); }

		UiTab*							TabSetVertical( U1 b ) { GetControlTyped().TabSetVertical( b ); return this; }
		U1								TabGetVertical() const { return GetControlTyped().TabGetVertical(); }

		UiTab*							TabSetOverflow( Ui::TabOverflow nOverflow ) { GetControlTyped().TabSetOverflow( nOverflow ); return this; }
		Ui::TabOverflow					TabGetOverflow() const { return GetControlTyped().TabGetOverflow(); }

		UiTab*							TabSetSort( Ui::TabSort nSort ) { GetControlTyped().TabSetSort( nSort ); return this; }
		Ui::TabSort						TabGetSort() const { return GetControlTyped().TabGetSort(); }

		UiTab*							TabSetHeaderSize( const WrapData<Ui::DpiSize>& nSize ) { GetControlTyped().TabSetHeaderSize( nSize ); return this; }
		WrapData<Ui::DpiSize>			TabGetHeaderSize() const { return GetControlTyped().TabGetHeaderSize(); }

		UiTab*							TabSetMaxHeaderSize( const WrapData<Ui::DpiSize>& nSize ) { GetControlTyped().TabSetMaxHeaderSize( nSize ); return this; }
		WrapData<Ui::DpiSize>			TabGetMaxHeaderSize() const { return GetControlTyped().TabGetMaxHeaderSize(); }

		UiTab*							TabSetUngroupedPosition( Ui::TabUngroupedPosition nPos ) { GetControlTyped().UngroupedSetPosition( nPos ); return this; }
		Ui::TabUngroupedPosition		TabGetUngroupedPosition() const { return GetControlTyped().UngroupedGetPosition(); }
		UiTab*							TabSetUngroupedName( PCWChar s ) { GetControlTyped().UngroupedSetName( s ); return this; }
		WString							TabGetUngroupedName() const { return GetControlTyped().UngroupedGetName(); }

		UiTab*							TabSetReorderable( U1 b ) { GetControlTyped().TabSetReorderable( b ); return this; }
		U1								TabGetReorderable() const { return GetControlTyped().TabGetReorderable(); }
		UiTab*							TabSetRegroup( U1 b ) { GetControlTyped().TabSetRegroup( b ); return this; }
		U1								TabGetRegroup() const { return GetControlTyped().TabGetRegroup(); }

		U1								GroupInsert( const WrapData<UiTabGroup>& pGroup );
		List<U32>						GroupGetAll() const { List<U32> v( GetControlTyped().GroupGetAll() ); if ( !v.IsEmpty() ) GetControlTyped().GroupGetAll( v.Data(), (U32) v.Size() ); return std::move( v ); }
		WrapData<UiTabGroup>			GroupGet( U32 nId ) const;
		U1								GroupSet( const WrapData<UiTabGroup>& pGroup );
		U1								GroupRemove( U32 nId ) { return GetControlTyped().GroupRemove( nId ); }
		UiTab*							GroupClear() { GetControlTyped().GroupClear(); return this; }
		UiTab*							GroupExpand( U32 nId, U1 bPinned, Ui::ExpandAction nAction ) { GetControlTyped().GroupExpand( nId, bPinned, nAction ); return this; }
		U1								GroupIsExpanded( U32 nId, U1 bPinned ) const { return GetControlTyped().GroupIsExpanded( nId, bPinned ); }

		UiTab*							GroupSetGlyphVisible( U1 b ) { GetControlTyped().GroupSetGlyphVisible( b ); return this; }
		U1								GroupGetGlyphVisible() const { return GetControlTyped().GroupGetGlyphVisible(); }

		UiTab*							ButtonClear() { GetControlTyped().ButtonClear(); return this; }
		UiTab*							ButtonSetIcon( U32 nIndex, Ui::IconCache nIcon ) { GetControlTyped().ButtonSetIcon( nIndex, nIcon ); return this; }
		Ui::IconCache					ButtonGetIcon( U32 nIndex ) const { return GetControlTyped().ButtonGetIcon( nIndex ); }
		UiTab*							ButtonSetDisplay( U32 nIndex, Ui::TabButtonDisplay nDisplay ) { GetControlTyped().ButtonSetDisplay( nIndex, nDisplay ); return this; }
		Ui::TabButtonDisplay			ButtonGetDisplay( U32 nIndex ) const { return GetControlTyped().ButtonGetDisplay( nIndex ); }
		UiTab*							ButtonSetName( U32 nIndex, PCWChar s ) { GetControlTyped().ButtonSetName( nIndex, s ); return this; }
		WString							ButtonGetName( U32 nIndex ) const { return GetControlTyped().ButtonGetName( nIndex ); }

		UiTab*							HeaderSetNearSize( const WrapData<Ui::DpiSize_2>& vSize ) { GetControlTyped().HeaderSetNearSize( vSize ); return this; }
		WrapData<Ui::DpiSize_2>			HeaderGetNearSize() const { return GetControlTyped().HeaderGetNearSize(); }
		WrapPointer<UiControl>			HeaderSetNearContent( WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().HeaderSetNearContent( pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			HeaderGetNearContent() const { return __ReturnContent( GetControlTyped().HeaderGetNearContent() ); }
		UiTab*							HeaderSetFarSize( const WrapData<Ui::DpiSize_2>& vSize ) { GetControlTyped().HeaderSetFarSize( vSize ); return this; }
		WrapData<Ui::DpiSize_2>			HeaderGetFarSize() const { return GetControlTyped().HeaderGetFarSize(); }
		WrapPointer<UiControl>			HeaderSetFarContent( WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().HeaderSetFarContent( pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			HeaderGetFarContent() const { return __ReturnContent( GetControlTyped().HeaderGetFarContent() ); }

		UiTab*							SetSimpleTab( U1 b ) { GetControlTyped().SetSimpleTab( b ); return this; }
		U1								GetSimpleTab() const { return GetControlTyped().GetSimpleTab(); }
		UiTab*							SetSimpleColor( const WrapData<U8_4>& vColor ) { GetControlTyped().SetSimpleColor( vColor ); return this; }
		WrapData<U8_4>					GetSimpleColor() const { return GetControlTyped().GetSimpleColor(); }

		WrapPointer<UiControl>			ContentSet( U32 nId, WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().ContentSet( nId, pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			ContentGet( U32 nId ) const { return __ReturnContent( GetControlTyped().ContentGet( nId ) ); }
		WrapData<S32_R>					ContentGetRect() const { return GetControlTyped().ContentGetRect(); }

		UiTab*							ContentSetMargin( U1 b ) { GetControlTyped().ContentSetMargin( b ); return this; }
		U1								ContentGetMargin() const { return GetControlTyped().ContentGetMargin(); }

		UiTab*							StopReordering( U1 bCancel ) { GetControlTyped().StopReordering( bCancel ); return this; }

		UiTab*							SetTabKeyTip( PCWChar sKeyTip, U32 nId ) { GetControlTyped().SetKeyTip( sKeyTip, nId ); return this; }
		WString							GetTabKeyTip( U32 nId ) const { return GetControlTyped().GetKeyTip( nId ); }

		UiTab*							OnSelectionChange /**/( OnSelectionChange_t /**/ && fn );
		UiTab*							OnDoubleClick     /**/( OnTabClick_t        /**/ && fn );
		UiTab*							OnRightClick      /**/( OnTabClick_t        /**/ && fn );
		UiTab*							OnMiddleClick     /**/( OnTabClick_t        /**/ && fn );
		UiTab*							OnDrag            /**/( OnDrag_t            /**/ && fn );
		UiTab*							OnButtonClick     /**/( OnButtonClick_t     /**/ && fn );
	};
}
