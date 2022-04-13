#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	using UiTreeItemHandle = U32;

	class UiTreeItem
	{
	public:
		U32									m_Flag;
		Ui::IconCache						m_Icon;
		WString								m_Text;
		UiTreeItemHandle					m_Item;
		U1									m_Blank;
	};

	NavDefineDataByMember_( UiTreeItem, Flag, Icon, Text, Item, Blank );

	class UiTreeInsert
	{
	public:
		UiTreeItemHandle					m_Parent;
		UiTreeItemHandle					m_After;
		WrapData<UiTreeItem>				m_Item;
	};

	NavDefineDataByMember_( UiTreeInsert, Parent, After, Item );

	class UiTreeHitTestResult
	{
	public:
		UiTreeItemHandle					m_Item;
		Ui::TreeItemPart					m_Part;
		Ui::TreeItemPlace					m_Place;
		Ui::TreeItemPlace					m_PlaceAb;
	};

	NavDefineDataByMember_( UiTreeHitTestResult, Item, Part, Place, PlaceAb );

	class UiTreeEdit
	{
	public:
		WString								m_Text;
		U1									m_CanEdit;
	};

	NavDefineDataByMember_( UiTreeEdit, Text, CanEdit );

	class UiTreeEditFinish
	{
	public:
		WString								m_Text;
		U1									m_Canceled;
	};

	NavDefineDataByMember_( UiTreeEditFinish, Text, Canceled );

	class UiTree : public UiControlHelper<UiTree, Ui::ITree>
	{
	public:
		AveWrapControl( UiTree );

		~UiTree()
		{
		}

		static PCAChar					GetExportName() { return "UiTree"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		static AveInline Ui::TreeItemHandle Hj2c( UiTreeItemHandle s )
		{
			switch ( s )
			{
			case 0x00000000: return Ui::TreeGenericHandle::Root;
			case 0xffffffff: return Ui::TreeGenericHandle::First;
			case 0xfffffffe: return Ui::TreeGenericHandle::Last;
			case 0xfffffffd: return Ui::TreeGenericHandle::Sort;
			default: return (Ui::TreeItemHandle) (USize) s;
			}
		}

		static AveInline UiTreeItemHandle Hc2j( Ui::TreeItemHandle s )
		{
			if ( Ui::TreeGenericHandle::Root == s ) return 0x00000000;
			else if ( Ui::TreeGenericHandle::First == s ) return 0xffffffff;
			else if ( Ui::TreeGenericHandle::Last == s ) return 0xfffffffe;
			else if ( Ui::TreeGenericHandle::Sort == s ) return 0xfffffffd;
			else return (U32) (USize) s;
		}

	private:
		using OnSelectionChange_t /**/ = JsFuncSafe<void( UiTree* sender )>;
		using OnClick_t           /**/ = JsFuncSafe<void( UiTree* sender, UiTreeItemHandle pItem )>;
		using OnEdit_t            /**/ = JsFuncSafe<WrapData<UiTreeEdit>( UiTree* sender, UiTreeItemHandle pItem, const WrapData<UiTreeEdit>& pEdit )>;
		using OnEditFinish_t      /**/ = JsFuncSafe<void( UiTree* sender, UiTreeItemHandle pItem, const WrapData<UiTreeEditFinish>& pEdit )>;
		using OnDragBegin_t       /**/ = JsFuncSafe<U1( UiTree* sender )>;

		OnSelectionChange_t				m_OnSelectionChange /**/;
		OnClick_t						m_OnDoubleClick     /**/;
		OnClick_t						m_OnRightClick      /**/;
		OnEdit_t						m_OnEditBegin       /**/;
		OnEdit_t						m_OnEditEnd         /**/;
		OnEditFinish_t					m_OnEditFinish      /**/;
		OnDragBegin_t					m_OnDragBegin       /**/;

		void							__OnSelectionChange /**/( Ui::ITree& sender );
		void							__OnDoubleClick     /**/( Ui::ITree& sender, Ui::TreeItemHandle pItem, U1& bCanToggle );
		void							__OnRightClick      /**/( Ui::ITree& sender, Ui::TreeItemHandle pItem );
		void							__OnEditBegin       /**/( Ui::ITree& sender, Ui::TreeItemHandle pItem, WString& sEdit, U1& bCanEdit );
		void							__OnEditEnd         /**/( Ui::ITree& sender, Ui::TreeItemHandle pItem, WString& sEdit, U1& bCanEdit );
		void							__OnEditFinish      /**/( Ui::ITree& sender, Ui::TreeItemHandle pItem, const WString& sEdit, U1 bCanceled );
		void							__OnDragBegin       /**/( Ui::ITree& sender, U1& bCanDrag );

	private:
		UiTreeItemHandle				ItemInsert( const WrapData<UiTreeInsert>& pInsert );
		U1								ItemRemove( UiTreeItemHandle pItem ) { return GetControlTyped().ItemRemove( Hj2c( pItem ) ); }
		UiTree*							ItemClear() { GetControlTyped().ItemClear(); return this; }
		UiTree*							ItemSelect( UiTreeItemHandle pItem ) { GetControlTyped().ItemSelect( Hj2c( pItem ) ); return this; }
		UiTree*							ItemSetSelected( UiTreeItemHandle pItem, U1 bSelect ) { GetControlTyped().ItemSelect( Hj2c( pItem ) ); return this; }
		UiTree*							ItemSort( UiTreeItemHandle pItem, U1 bSortChild ) { GetControlTyped().ItemSort( Hj2c( pItem ), bSortChild ); return this; }
		U1								ItemSet( const WrapData<UiTreeItem>& pItem );
		WrapData<UiTreeItem>			ItemGet( UiTreeItemHandle pItem );
		UiTreeItemHandle				ItemGetNext( UiTreeItemHandle pItem, Ui::TreeNextItem nNext ) const { return Hc2j( GetControlTyped().ItemGetNext( Hj2c( pItem ), nNext ) ); }
		S32								ItemGetCountPerPage( U1 bIncludePartial ) const { return GetControlTyped().ItemGetCountPerPage( bIncludePartial ); }
		S32								ItemGetSelectionCount() const { return GetControlTyped().ItemGetSelectionCount(); }
		UiTreeItemHandle				ItemGetSelection() const { return Hc2j( GetControlTyped().ItemGetSelection() ); }
		U1								ItemGetSelected( UiTreeItemHandle pItem ) const { return GetControlTyped().ItemGetSelection( Hj2c( pItem ) ); }
		List<UiTreeItemHandle>			ItemGetSelectionAll() const;
		UiTree*							ItemEnsure( UiTreeItemHandle pItem ) { GetControlTyped().ItemEnsure( Hj2c( pItem ) ); return this; }
		UiTreeItemHandle				ItemGetTop() const { return Hc2j( GetControlTyped().ItemGetTop() ); }
		S32								ItemGetTopIndex() const { return GetControlTyped().ItemGetTopIndex(); }
		UiTree*							ItemSetTopIndex( S32 nIndex ) { GetControlTyped().ItemSetTopIndex( nIndex ); return this; }
		U1								ItemIsVisible( UiTreeItemHandle pItem ) const { return GetControlTyped().ItemIsVisible( Hj2c( pItem ) ); }
		WrapData<S32_R>					ItemGetRect( UiTreeItemHandle pItem, Ui::TreeItemPart nPart ) const { S32_R rc; GetControlTyped().ItemGetRect( Hj2c( pItem ), nPart, rc ); return rc; }
		WrapData<UiTreeHitTestResult>	ItemHitTest( const WrapData<S32_2>& pt );
		UiTree*							ItemExpand( UiTreeItemHandle pItem, Ui::ExpandAction nExpand, U1 bIncludeChild ) { GetControlTyped().ItemExpand( Hj2c( pItem ), nExpand, bIncludeChild ); return this; }
		U1								ItemIsExpanded( UiTreeItemHandle pItem ) const { return GetControlTyped().ItemIsExpanded( Hj2c( pItem ) ); }
		U1								ItemEdit( UiTreeItemHandle pItem ) { return GetControlTyped().ItemEdit( Hj2c( pItem ) ); }
		U1								ItemIsEdit() const { return GetControlTyped().ItemIsEdit(); }
		UiTree*							ItemEditFinish( U1 bCancel ) { GetControlTyped().ItemEditFinish( bCancel ); return this; }
		UiTree*							ItemSetHighlight( UiTreeItemHandle pItem, Ui::TreeItemPlace nPlace ) { GetControlTyped().ItemSetHighlight( Hj2c( pItem ), nPlace ); return this; }

		UiTree*							SetAutoEdit( U1 bAutoEdit ) { GetControlTyped().SetAutoEdit( bAutoEdit ); return this; }
		U1								GetAutoEdit() const { return GetControlTyped().GetAutoEdit(); }

		UiTree*							SetAutoScrollOnHover( U1 b ) { GetControlTyped().SetAutoScrollOnHover( b ); return this; }
		U1								GetAutoScrollOnHover() const { return GetControlTyped().GetAutoScrollOnHover(); }

		UiTree*							SetNodeLine( U1 b ) { GetControlTyped().SetNodeLine( b ); return this; }
		U1								GetNodeLine() const { return GetControlTyped().GetNodeLine(); }

		UiTree*							SetNodeLineHighlight( U1 b ) { GetControlTyped().SetNodeLineHighlight( b ); return this; }
		U1								GetNodeLineHighlight() const { return GetControlTyped().GetNodeLineHighlight(); }

		UiTree*							SetSingleClickExpand( U1 b ) { GetControlTyped().SetSingleClickExpand( b ); return this; }
		U1								GetSingleClickExpand() const { return GetControlTyped().GetSingleClickExpand(); }

		UiTree*							SetSelectionMode( Ui::TreeSelectionMode nSelMode ) { GetControlTyped().SetSelectionMode( nSelMode ); return this; }
		Ui::TreeSelectionMode			GetSelectionMode() const { return GetControlTyped().GetSelectionMode(); }

		UiTree*							SetIndentWidth( const WrapData<Ui::DpiSize>& nWidth ) { GetControlTyped().SetIndentWidth( nWidth ); return this; }
		WrapData<Ui::DpiSize>			GetIndentWidth() const { return GetControlTyped().GetIndentWidth(); }

		UiTree*							SetScrollPosition( const WrapData<S32_2>& pt, U1 bScroll ) { GetControlTyped().SetScrollPosition( pt, bScroll ); return this; }
		WrapData<S32_2>					GetScrollPosition() const { return GetControlTyped().GetScrollPosition(); }
		WrapData<S32_2>					GetScrollSize() const { return GetControlTyped().GetScrollSize(); }
		WrapData<S32_2>					GetScrollMax() const;

		UiTree*							OnSelectionChange /**/( OnSelectionChange_t /**/ && fn ) { m_OnSelectionChange /**/ = std::move( fn ); return this; }
		UiTree*							OnDoubleClick     /**/( OnClick_t           /**/ && fn ) { m_OnDoubleClick     /**/ = std::move( fn ); return this; }
		UiTree*							OnRightClick      /**/( OnClick_t           /**/ && fn ) { m_OnRightClick      /**/ = std::move( fn ); return this; }
		UiTree*							OnEditBegin       /**/( OnEdit_t            /**/ && fn ) { m_OnEditBegin       /**/ = std::move( fn ); return this; }
		UiTree*							OnEditEnd         /**/( OnEdit_t            /**/ && fn ) { m_OnEditEnd         /**/ = std::move( fn ); return this; }
		UiTree*							OnEditFinish      /**/( OnEditFinish_t      /**/ && fn ) { m_OnEditFinish      /**/ = std::move( fn ); return this; }
		UiTree*							OnDragBegin       /**/( OnDragBegin_t       /**/ && fn ) { m_OnDragBegin       /**/ = std::move( fn ); return this; }
	};
}
