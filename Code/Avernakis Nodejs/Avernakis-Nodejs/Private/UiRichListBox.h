#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiHeader;
	class UiScrollBar;

	class UiRichListBoxItem
	{
	public:
		U32						m_Flag;
		S32						m_Index;
		S32						m_IndexSub;
		Ui::IconCache			m_Icon;
		WString					m_Text;
		U32						m_Indent;
		U32						m_GroupId;
		U32						m_Misc;
		U32						m_Context;
	};

	NavDefineDataByMember_( UiRichListBoxItem, Flag, Index, IndexSub, Icon, Text, Indent, GroupId, Misc, Context );

	using UiRichListBoxItem_t = WrapData<UiRichListBoxItem>;

	class UiRichListBoxHitTestResult
	{
	public:
		S32								m_Index{ -1 };
		S32								m_SubIndex{ -1 };
		Ui::RichListBoxItemPlace		m_Place{ Ui::RichListBoxItemPlace::Item };
		Ui::RichListBoxItemPlace		m_PlaceAb{ Ui::RichListBoxItemPlace::Above };
	};

	NavDefineDataByMember_( UiRichListBoxHitTestResult, Index, SubIndex, Place, PlaceAb );

	using UiRichListBoxHitTestResult_t = WrapData<UiRichListBoxHitTestResult>;

	class UiRichListBoxItemVirtual
	{
	public:
		Ui::IconCache						m_Icon;
		U32									m_Indent;
		U32									m_Misc;
		WString								m_String;
	};

	NavDefineDataByMember_( UiRichListBoxItemVirtual, Icon, Indent, Misc, String );

	using UiRichListBoxItemVirtual_t = WrapData<UiRichListBoxItemVirtual>;

	class UiRichListBox : public UiControlHelper<UiRichListBox, Ui::IRichListBox>
	{
	public:
		AveWrapControlCi( UiRichListBox );

		~UiRichListBox()
		{
		}

		static PCAChar					GetExportName() { return "UiRichListBox"; }
		static void						DefineControl();

		U1								Ctor( const CallbackInfo& ci, UiWindow* p, Napi::Value v );

	private:
		using OnCallback0_t = JsFuncSafe<void( UiRichListBox* sender )>;
		using OnCallback1_t = JsFuncSafe<void( UiRichListBox* sender, S32 nIndex )>;

		using Virtual_t = JsFuncSafe<UiRichListBoxItemVirtual_t( UiRichListBox* sender, S32 nIndex, S32 nSubIndex )>;

		OnCallback0_t					m_OnSelectionChange /**/;
		OnCallback0_t					m_OnSelectionEnd    /**/;
		OnCallback1_t					m_OnDoubleClick     /**/;
		OnCallback1_t					m_OnRightClick      /**/;
		OnCallback0_t					m_OnDragBegin       /**/;
		OnCallback1_t					m_OnGlyphClick      /**/;
		OnCallback1_t					m_OnItemCheck       /**/;

		Virtual_t						m_Virtual;

		JsObject<UiHeader>				m_Header;

		void							__OnSelectionChange /**/( Ui::IRichListBox& sender );
		void							__OnSelectionEnd    /**/( Ui::IRichListBox& sender );
		void							__OnDoubleClick     /**/( Ui::IRichListBox& sender, S32 nIndex );
		void							__OnRightClick      /**/( Ui::IRichListBox& sender, S32 nIndex );
		void							__OnDragBegin       /**/( Ui::IRichListBox& sender );
		void							__OnGlyphClick      /**/( Ui::IRichListBox& sender, S32 nIndex );
		void							__OnItemCheck       /**/( Ui::IRichListBox& sender, S32 nIndex );

		void							__OnVirtual( Ui::IRichListBox& sender, Ui::RichListBoxItemVirtual& iv );

	private:
	public:
		S32								ItemInsert( const UiRichListBoxItem_t& pItem, U1 bReserveSelection );
		U1								ItemRemove( S32 nIndex, U1 bReserveSelection ) { return GetControlTyped().ItemRemove( nIndex, bReserveSelection ); }
		UiRichListBox*					ItemClear() { GetControlTyped().ItemClear(); return this; }
		UiRichListBox*					ItemSelect( S32 nIndex ) { GetControlTyped().ItemSelect( nIndex ); return this; }
		UiRichListBox*					ItemSetSelect( S32 nIndex, U1 bSelect ) { GetControlTyped().ItemSelect( nIndex, bSelect ); return this; }
		UiRichListBox*					ItemSetSelectRange( S32 nStart, S32 nEnd, U1 bSelect ) { GetControlTyped().ItemSelect( nStart, nEnd, bSelect ); return this; }
		UiRichListBox*					ItemSort( U32 nSubItem, U1 bAsc, U1 bCaseInsensitive ) { GetControlTyped().ItemSort( nSubItem, bAsc, bCaseInsensitive ); return this; }
		S32								ItemFind( PCWChar szString, S32 nIndex, U1 bExact, U1 bCaseInsensitive ) const { return GetControlTyped().ItemFind( szString, nIndex, bExact, bCaseInsensitive ); }
		U1								ItemSet( const UiRichListBoxItem_t& pItem );
		UiRichListBoxItem_t				ItemGet( U32 nFlag, S32 nIndex, S32 nSubIndex );
		S32								ItemGetCount() const { return GetControlTyped().ItemGetCount(); }
		S32								ItemGetCountPerPage( U1 bIncludePartial ) const { return GetControlTyped().ItemGetCountPerPage( bIncludePartial ); }
		S32								ItemGetSelectionCount() const { return GetControlTyped().ItemGetSelectionCount(); }
		S32								ItemGetSelection() const { return GetControlTyped().ItemGetSelection(); }
		U1								ItemIsSelected( S32 nIndex ) const { return GetControlTyped().ItemGetSelection( nIndex ); }
		S32								ItemGetNextSelection( S32 nIndex ) const { return GetControlTyped().ItemGetNextSelection( nIndex ); }
		UiRichListBox*					ItemEnsure( S32 nIndex ) { GetControlTyped().ItemEnsure( nIndex ); return this; }
		S32								ItemGetTopIndex() const { return GetControlTyped().ItemGetTopIndex(); }
		U1								ItemIsVisible( S32 nIndex ) const { return GetControlTyped().ItemIsVisible( nIndex ); }
		WrapData<S32_R>					ItemGetRect( S32 nIndex ) const { S32_R rc{}; GetControlTyped().ItemGetRect( nIndex, rc ); return rc; }
		UiRichListBoxHitTestResult_t	ItemHitTest( const WrapData<S32_2>& pt, U1 bMustOnContent, U1 bIncludePlaceholder ) const;
		UiRichListBox*					ItemSetCount( S32 nCount ) { GetControlTyped().ItemSetCount( nCount ); return this; }
		UiRichListBox*					ItemSetHighlight( S32 nIndex, Ui::RichListBoxItemPlace nPlace ) { GetControlTyped().ItemSetHighlight( nIndex, nPlace ); return this; }
		UiRichListBox*					ItemSetMinimumHeight( const WrapData<Ui::DpiSize>& nHeight ) { GetControlTyped().ItemSetMinimumHeight( nHeight ); return this; }
		WrapData<Ui::DpiSize>			ItemGetMinimumHeight() const { return GetControlTyped().ItemGetMinimumHeight(); }

		UiRichListBox*					SetVirtual( Virtual_t&& fn );

		UiHeader*						GetHeader() { return m_Header; }
		UiRichListBox*					SetHeaderAutoWidth( U1 b ) { GetControlTyped().SetHeaderAutoWidth( b ); return this; }
		U1								GetHeaderAutoWidth() const { return GetControlTyped().GetHeaderAutoWidth(); }

		UiRichListBox*					SetScrollPosition( const WrapData<S32_2>& pt ) { GetControlTyped().SetScrollPosition( pt ); return this; }
		WrapData<S32_2>					GetScrollPosition() const { return GetControlTyped().GetScrollPosition(); }

		UiRichListBox*					SetSelectionMode( Ui::RichListBoxSelectionMode nSelMode ) { GetControlTyped().SetSelectionMode( nSelMode ); return this; }
		Ui::RichListBoxSelectionMode	GetSelectionMode() const { return GetControlTyped().GetSelectionMode(); }

		UiRichListBox*					SetViewMode( Ui::RichListBoxViewMode nViewMode ) { GetControlTyped().SetViewMode( nViewMode ); return this; }
		Ui::RichListBoxViewMode			GetViewMode() const { return GetControlTyped().GetViewMode(); }

		UiRichListBox*					SetTileSize( const WrapData<Ui::DpiSize_2>& ptSize ) { GetControlTyped().SetTileSize( ptSize ); return this; }
		WrapData<Ui::DpiSize_2>			GetTileSize() const { return GetControlTyped().GetTileSize(); }
		UiRichListBox*					SetTileColumnPriority( const WrapArray<U32>& pOrder ) { GetControlTyped().SetTileColumnPriority( pOrder, (U32) pOrder.m_Length ); return this; }
		List<U32>						GetTileColumnPriority() const { List<U32> v( GetControlTyped().GetTileColumnPriority( nullptr, 0 ) ); if ( !v.IsEmpty() ) GetControlTyped().GetTileColumnPriority( v.Data(), (U32) v.Size() ); return std::move( v ); }

		UiRichListBox*					SetItemSpace( const WrapData<Ui::DpiSize_2>& ptSize ) { GetControlTyped().SetItemSpace( ptSize ); return this; }
		WrapData<Ui::DpiSize_2>			GetItemSpace() const { return GetControlTyped().GetItemSpace(); }

		UiRichListBox*					SetTreeStyle( U1 b ) { GetControlTyped().SetTreeStyle( b ); return this; }
		U1								GetTreeStyle() const { return GetControlTyped().GetTreeStyle(); }

		UiRichListBox*					SetItemCheck( Ui::RichListBoxItemCheck nCheck ) { GetControlTyped().SetItemCheck( nCheck ); return this; }
		Ui::RichListBoxItemCheck		GetItemCheck() const { return GetControlTyped().GetItemCheck(); }

		UiRichListBox*					SetIconSize( Ui::RichListBoxViewMode nMode, const WrapData<Ui::DpiSize>& nSize ) { GetControlTyped().SetIconSize( nMode, nSize ); return this; }
		WrapData<Ui::DpiSize>			GetIconSize( Ui::RichListBoxViewMode nMode ) const { return GetControlTyped().GetIconSize( nMode ); }

		UiRichListBox*					SetIconNameColumn( U32 nColumn ) { GetControlTyped().SetIconNameColumn( nColumn ); return this; }
		U32								GetIconNameColumn() const { return GetControlTyped().GetIconNameColumn(); }

		UiRichListBox*					SetListItemWidth( const WrapData<Ui::DpiSize>& nSize ) { GetControlTyped().SetListItemWidth( nSize ); return this; }
		WrapData<Ui::DpiSize>			GetListItemWidth() const { return GetControlTyped().GetListItemWidth(); }

		WrapData<S32_R>					GetListRect() const { return GetControlTyped().GetListRect(); }

		UiRichListBox*					OnSelectionChange /**/( OnCallback0_t&& fn ) { m_OnSelectionChange /**/ = std::move( fn ); return this; }
		UiRichListBox*					OnSelectionEnd    /**/( OnCallback0_t&& fn ) { m_OnSelectionEnd    /**/ = std::move( fn ); return this; }
		UiRichListBox*					OnDoubleClick     /**/( OnCallback1_t&& fn ) { m_OnDoubleClick     /**/ = std::move( fn ); return this; }
		UiRichListBox*					OnRightClick      /**/( OnCallback1_t&& fn ) { m_OnRightClick      /**/ = std::move( fn ); return this; }
		UiRichListBox*					OnDragBegin       /**/( OnCallback0_t&& fn ) { m_OnDragBegin       /**/ = std::move( fn ); return this; }
		UiRichListBox*					OnGlyphClick      /**/( OnCallback1_t&& fn ) { m_OnGlyphClick      /**/ = std::move( fn ); return this; }
		UiRichListBox*					OnItemCheck       /**/( OnCallback1_t&& fn ) { m_OnItemCheck       /**/ = std::move( fn ); return this; }
	};

}
