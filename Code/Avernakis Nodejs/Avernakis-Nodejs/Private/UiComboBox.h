#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiComboBox : public UiControlHelper<UiComboBox, Ui::IComboBox>
	{
	public:
		AveWrapControl( UiComboBox );

		~UiComboBox()
		{
		}

		static PCAChar					GetExportName() { return "UiComboBox"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnSelectionChange_t = JsFuncSafe<void( UiComboBox* sender )>;

		OnSelectionChange_t				m_OnSelectionChange;

		void							__OnSelectionChange( Ui::IComboBox& sender );

	private:
		UiComboBox*						Append( PCWChar szText ) { GetControlTyped().Append( szText ? szText : AveWide( "" ) ); return this; }
		UiComboBox*						Insert( PCWChar szText, S32 nInsert ) { GetControlTyped().Insert( szText ? szText : AveWide( "" ), nInsert ); return this; }
		U1								Remove( S32 nIndex ) { return GetControlTyped().Remove( nIndex ); }
		UiComboBox*						Clear() { GetControlTyped().Clear(); return this; }
		UiComboBox*						Select( S32 nIndex ) { GetControlTyped().Select( nIndex ); return this; }
		UiComboBox*						Sort( U1 bAsc, U1 bCaseInsensitive ) { GetControlTyped().Sort( bAsc, bCaseInsensitive ); return this; }
		S32								Find( PCWChar szString, S32 nIndex, U1 bExact, U1 bCaseInsensitive ) { return GetControlTyped().Find( szString, nIndex, bExact, bCaseInsensitive ); }
		U1								Set( S32 nIndex, PCWChar szText ) { return GetControlTyped().Set( nIndex, szText ? szText : AveWide( "" ) ); }
		WString							Get( S32 nIndex ) const { auto p = GetControlTyped().Get( nIndex ); return p ? p : AveWide( "" ); }
		S32								GetCount() const { return GetControlTyped().GetCount(); }
		S32								GetSelection() const { return GetControlTyped().GetSelection(); }

		UiComboBox*						SetCount( S32 nCount ) { GetControlTyped().SetCount( nCount ); return this; }

		UiComboBox*						SetMode( Ui::ComboBoxMode nMode ) { GetControlTyped().SetMode( nMode ); return this; }
		Ui::ComboBoxMode				GetMode() const { return GetControlTyped().GetMode(); }

		UiComboBox*						SetDropHeight( const WrapData<Ui::DpiSize>& nHeight ) { GetControlTyped().SetDropHeight( nHeight ); return this; }
		WrapData<Ui::DpiSize>			GetDropHeight() const { return GetControlTyped().GetDropHeight(); }

		UiComboBox*						SetFindExact( U1 b ) { GetControlTyped().SetFindExact( b ); return this; }
		U1								GetFindExact() const { return GetControlTyped().GetFindExact(); }

		UiComboBox*						SetFindCaseInsensitive( U1 b ) { GetControlTyped().SetFindCaseInsensitive( b ); return this; }
		U1								GetFindCaseInsensitive() const { return GetControlTyped().GetFindCaseInsensitive(); }

		UiComboBox*						SetBorder( U1 b ) { GetControlTyped().SetBorder( b ); return this; }
		U1								GetBorder() const { return GetControlTyped().GetBorder(); }

		UiComboBox*						OnSelectionChange( OnSelectionChange_t&& fn );
	};
}
