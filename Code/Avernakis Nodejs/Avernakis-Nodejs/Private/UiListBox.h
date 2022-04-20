#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiListBoxItemVirtual
	{
	public:
		U32									m_Misc;
		WString								m_String;
	};

	NavDefineDataByMember_( UiListBoxItemVirtual, Misc, String );

	using UiListBoxItemVirtual_t = WrapData<UiListBoxItemVirtual>;

	class UiListBox : public UiControlHelper<UiListBox, Ui::IListBox>
	{
	public:
		AveWrapControl( UiListBox );

		~UiListBox()
		{
		}

		static PCAChar					GetExportName() { return "UiListBox"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnSelectionChange_t = JsFuncSafe<void( UiListBox* sender )>;
		using OnClick_t = JsFuncSafe<void( UiListBox* sender, S32 nIndex )>;
		using Virtual_t = JsFuncSafe<UiListBoxItemVirtual_t( UiListBox* sender, S32 nIndex )>;

		OnSelectionChange_t				m_OnSelectionChange;
		OnSelectionChange_t				m_OnSelectionEnd;
		OnClick_t						m_OnDoubleClick;
		OnClick_t						m_OnRightClick;

		Virtual_t						m_Virtual;

		void							__OnSelectionChange( Ui::IListBox& sender );
		void							__OnSelectionEnd( Ui::IListBox& sender );
		void							__OnDoubleClick( Ui::IListBox& sender, S32 nIndex );
		void							__OnRightClick( Ui::IListBox& sender, S32 nIndex );
		
		void							__OnVirtual( Ui::IListBox& sender, Ui::ListBoxItemVirtual& iv );

	private:
		UiListBox*						Append( PCWChar szText ) { GetControlTyped().Append( szText ? szText : AveWide( "" ) ); return this; }
		UiListBox*						Insert( PCWChar szText, S32 nInsert ) { GetControlTyped().Insert( szText ? szText : AveWide( "" ), nInsert ); return this; }
		U1								Remove( S32 nIndex ) { return GetControlTyped().Remove( nIndex ); }
		UiListBox*						Clear() { GetControlTyped().Clear(); return this; }
		UiListBox*						Select( S32 nIndex ) { GetControlTyped().Select( nIndex ); return this; }
		UiListBox*						SetSelect( S32 nIndex, U1 bSelect ) { GetControlTyped().Select( nIndex, bSelect ); return this; }
		UiListBox*						SetSelectRange( S32 nStart, S32 nEnd, U1 bSelect ) { GetControlTyped().Select( nStart, nEnd, bSelect ); return this; }
		UiListBox*						Sort( U1 bAsc, U1 bCaseInsensitive ) { GetControlTyped().Sort( bAsc, bCaseInsensitive ); return this; }
		S32								Find( PCWChar szString, S32 nIndex, U1 bExact, U1 bCaseInsensitive ) { return GetControlTyped().Find( szString, nIndex, bExact, bCaseInsensitive ); }
		U1								Swap( S32 nIndex0, S32 nIndex1 ) { return GetControlTyped().Swap( nIndex0, nIndex1 ); }
		U1								Set( S32 nIndex, PCWChar szText ) { return GetControlTyped().Set( nIndex, szText ? szText : AveWide( "" ) ); }
		WString							Get( S32 nIndex ) const { auto p = GetControlTyped().Get( nIndex ); return p ? p : AveWide( "" ); }
		S32								GetCount() const { return GetControlTyped().GetCount(); }
		S32								GetSelection() const { return GetControlTyped().GetSelection(); }
		U1								IsSelected( S32 nIndex ) const { return GetControlTyped().GetSelection( nIndex ); }
		S32								GetNextSelection( S32 nIndex ) const { return GetControlTyped().GetNextSelection( nIndex ); }

		UiListBox*						Ensure( S32 nIndex ) { GetControlTyped().Ensure( nIndex ); return this; }
		UiListBox*						SetTopIndex( S32 nIndex ) { GetControlTyped().SetTopIndex( nIndex ); return this; }
		S32								GetTopIndex() const { return GetControlTyped().GetTopIndex(); }
		U1								ItemIsVisible( S32 nIndex ) const { return GetControlTyped().ItemIsVisible( nIndex ); }
		WrapData<S32_R>					ItemGetRect( S32 nIndex ) const { S32_R rc{}; GetControlTyped().ItemGetRect( nIndex, rc ); return rc; }
		S32								ItemHitTest( const WrapData<S32_2>& pt ) const { return GetControlTyped().ItemHitTest( pt ); }

		UiListBox*						SetCount( S32 nCount ) { GetControlTyped().SetCount( nCount ); return this; }

		UiListBox*						SetVirtual( Virtual_t&& fn );

		UiListBox*						SetSelectionMode( Ui::ListBoxSelectionMode nSelMode ) { GetControlTyped().SetSelectionMode( nSelMode ); return this; }
		Ui::ListBoxSelectionMode		GetSelectionMode() const { return GetControlTyped().GetSelectionMode(); }

		UiListBox*						OnSelectionChange /**/( OnSelectionChange_t /**/ && fn );
		UiListBox*						OnSelectionEnd    /**/( OnSelectionChange_t /**/ && fn );
		UiListBox*						OnDoubleClick     /**/( OnClick_t           /**/ && fn );
		UiListBox*						OnRightClick      /**/( OnClick_t           /**/ && fn );
	};
}
