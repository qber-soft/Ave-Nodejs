#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiRibbonGalleryItem
	{
	public:
		U32									m_Flag;
		S32									m_Index;
		Ui::IconCache						m_Icon;
		WString								m_Text;
		WString								m_Tooltip;
		S32									m_Group;
	};

	NavDefineDataByMember_( UiRibbonGalleryItem, Flag, Index, Icon, Text, Tooltip, Group );
	NavDefineTransitByMemberOut_( Ui::RibbonGalleryItem, UiRibbonGalleryItem, Flag, Index, Icon, Text, Tooltip, Group );

	class UiRibbonGalleryMenu
	{
	public:
		U32									m_Flag;
		S32									m_Index;
		U32									m_Id;
		Ui::IconCache						m_Icon;
		U32									m_State;
		WString								m_Text;
	};

	NavDefineDataByMember_( UiRibbonGalleryMenu, Flag, Index, Id, Icon, State, Text );
	NavDefineTransitByMemberOut_( Ui::RibbonGalleryMenu, UiRibbonGalleryMenu, Flag, Index, Id, Icon, State, Text );

	class UiRibbonGallery : public UiControlHelper<UiRibbonGallery, Ui::IRibbonGallery>
	{
	public:
		AveWrapControl( UiRibbonGallery );

		~UiRibbonGallery()
		{
		}

		static PCAChar					GetExportName() { return "UiRibbonGallery"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using Callback_t    /**/ = JsFuncSafe<void( UiRibbonGallery* sender )>;
		using OnPreview_t   /**/ = JsFuncSafe<void( UiRibbonGallery* sender, S32 nIndex )>;
		using OnMenuClick_t /**/ = JsFuncSafe<void( UiRibbonGallery* sender, U32 nId )>;

		Callback_t						m_OnSelect    /**/;
		OnPreview_t						m_OnPreview   /**/;
		Callback_t						m_OnDrop      /**/;
		OnMenuClick_t					m_OnMenuClick /**/;

		void							__OnSelect    /**/( Ui::IRibbonGallery& sender );
		void							__OnPreview   /**/( Ui::IRibbonGallery& sender, S32 nIndex );
		void							__OnDrop      /**/( Ui::IRibbonGallery& sender );
		void							__OnMenuClick /**/( Ui::IRibbonGallery& sender, U32 nId );

	private:
		S32								ItemInsert( const WrapData<UiRibbonGalleryItem>& pItem );
		U1								ItemRemove( S32 nIndex ) { return GetControlTyped().ItemRemove( nIndex ); }
		UiRibbonGallery*				ItemClear() { GetControlTyped().ItemClear(); return this; }
		UiRibbonGallery*				ItemSelect( S32 nIndex ) { GetControlTyped().ItemSelect( nIndex ); return this; }
		U1								ItemSet( const WrapData<UiRibbonGalleryItem>& pItem );
		WrapData<UiRibbonGalleryItem>	ItemGet( S32 nIndex ) const;
		S32								ItemGetCount() const { return GetControlTyped().ItemGetCount(); }
		S32								ItemGetSelection() const { return GetControlTyped().ItemGetSelection(); }

		S32								GroupInsert( PCWChar szText, S32 nInsertBefore ) { return GetControlTyped().GroupInsert( szText, nInsertBefore ); }
		U1								GroupRemove( S32 nIndex ) { return GetControlTyped().GroupRemove( nIndex ); }
		UiRibbonGallery*				GroupClear() { GetControlTyped().GroupClear(); return this; }
		U1								GroupSet( S32 nIndex, PCWChar szText ) { return GetControlTyped().GroupSet( nIndex, szText ); }
		WString 						GroupGet( S32 nIndex ) const { if ( auto p = GetControlTyped().GroupGet( nIndex ) ) return p; return {}; }
		S32								GroupGetCount() const { return GetControlTyped().GroupGetCount(); }

		S32								MenuInsert( const WrapData<UiRibbonGalleryMenu>& pItem );
		U1								MenuRemove( S32 nIndex ) { return GetControlTyped().MenuRemove( nIndex ); }
		UiRibbonGallery*				MenuClear() { GetControlTyped().MenuClear(); return this; }
		U1								MenuSet( const WrapData<UiRibbonGalleryMenu>& pItem );
		WrapData<UiRibbonGalleryMenu>	MenuGet( S32 nIndex ) const;
		UiRibbonGallery*				MenuSetEnable( U32 nId, U1 b ) { GetControlTyped().MenuSetEnable( nId, b ); return this; }
		U1								MenuGetEnable( U32 nId ) const { return GetControlTyped().MenuGetEnable( nId ); }
		S32								MenuGetCount() const { return GetControlTyped().MenuGetCount(); }

		UiRibbonGallery*				ViewSetMode( Ui::RibbonGalleryViewMode nViewMode ) { GetControlTyped().ViewSetMode( nViewMode ); return this; }
		Ui::RibbonGalleryViewMode		ViewGetMode() const { return GetControlTyped().ViewGetMode(); }

		UiRibbonGallery*				ViewSetItemWidth( const WrapData<Ui::DpiSize>& nWidth ) { GetControlTyped().ViewSetItemWidth( nWidth ); return this; }
		WrapData<Ui::DpiSize>			ViewGetItemWidth() const { return GetControlTyped().ViewGetItemWidth(); }

		UiRibbonGallery*				ViewSetDefaultItemCountPerLine( S32 nCount ) { GetControlTyped().ViewSetDefaultItemCountPerLine( nCount ); return this; }
		S32								ViewGetDefaultItemCountPerLine() const { return GetControlTyped().ViewGetDefaultItemCountPerLine(); }

		UiRibbonGallery*				ViewSetItemCountPerLineRange( const WrapData<S32_2>& vRange ) { GetControlTyped().ViewSetItemCountPerLineRange( vRange ); return this; }
		WrapData<S32_2>					ViewGetItemCountPerLineRange() const { return GetControlTyped().ViewGetItemCountPerLineRange(); }

		UiRibbonGallery*				ViewSetWidthWeight( S32 nWeight ) { GetControlTyped().ViewSetWidthWeight( nWeight ); return this; }
		S32								ViewGetWidthWeight() const { return GetControlTyped().ViewGetWidthWeight(); }

		UiRibbonGallery*				OnSelect    /**/( Callback_t    /**/ && fn );
		UiRibbonGallery*				OnPreview   /**/( OnPreview_t   /**/ && fn );
		UiRibbonGallery*				OnDrop      /**/( Callback_t    /**/ && fn );
		UiRibbonGallery*				OnMenuClick /**/( OnMenuClick_t /**/ && fn );
	};
}
