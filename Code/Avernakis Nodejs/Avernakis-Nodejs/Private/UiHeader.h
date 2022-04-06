#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiHeaderItem
	{
	public:
		U32						m_Flag;
		U32						m_Format;
		WrapData<Ui::DpiSize>	m_Width;
		WrapData<Ui::DpiSize>	m_MinWidth;
		WString					m_Text;
		U32						m_Context;
	};

	NavDefineDataByMember_( UiHeaderItem, Flag, Format, Width, MinWidth, Text, Context );

	using UiHeaderItem_t = WrapData<UiHeaderItem>;

	class UiHeader : public UiControlHelper<UiHeader, Ui::IHeader>
	{
	public:
		AveWrapControl( UiHeader );

		~UiHeader()
		{
		}

		static PCAChar					GetExportName() { return "UiHeader"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnCallback0_t = JsFuncSafe<void( UiHeader* sender )>;
		using OnCallback1_t = JsFuncSafe<void( UiHeader* sender, S32 nIndex )>;
		using OnAdjustWidth_t = JsFuncSafe<void( UiHeader* sender, U32 nIndex, U1 bAdjusting )>;
		using OnOrder_t = JsFuncSafe<void( UiHeader* sender, U32 nNewIndex, U32 nOldIndex )>;

		OnCallback1_t					m_OnClick       /**/;
		OnAdjustWidth_t					m_OnAdjustWidth /**/;
		OnOrder_t						m_OnOrder       /**/;
		OnCallback1_t					m_OnDropDown    /**/;
		OnCallback1_t					m_OnCheckItem   /**/;
		OnCallback0_t					m_OnCheckHeader /**/;

		void							__OnClick       /**/( Ui::IHeader& sender, U32 nIndex );
		void							__OnAdjustWidth /**/( Ui::IHeader& sender, U32 nIndex, U1 bAdjusting );
		void							__OnOrder       /**/( Ui::IHeader& sender, U32 nNewIndex, U32 nOldIndex );
		void							__OnDropDown    /**/( Ui::IHeader& sender, U32 nIndex );
		void							__OnCheckItem   /**/( Ui::IHeader& sender, U32 nIndex );
		void							__OnCheckHeader /**/( Ui::IHeader& sender );

	private:
		UiHeader*						Add( const UiHeaderItem_t& pItem );
		U1								Insert( U32 nInsertBefore, const UiHeaderItem_t& pItem );
		U32								GetCount() const { return GetControlTyped().GetCount(); }
		UiHeaderItem_t					Get( U32 nIndex );
		WrapData<S32_R>					GetRect( U32 nIndex ) const { return GetControlTyped().GetRect( nIndex ); }
		U1								Set( U32 nIndex, const UiHeaderItem_t& pItem );
		U1								Remove( U32 nIndex ) { return GetControlTyped().Remove( nIndex ); }
		UiHeader*						RemoveAll() { GetControlTyped().RemoveAll(); return this; }

		UiHeader*						ItemSetDownDrop( U32 nIndex, U1 b ) { GetControlTyped().ItemSetDownDrop( nIndex, b ); return this; }
		U1								ItemGetDownDrop( U32 nIndex ) const { return GetControlTyped().ItemGetDownDrop( nIndex ); }
		UiHeader*						ItemSetFilter( U32 nIndex, U1 b ) { GetControlTyped().ItemSetFilter( nIndex, b ); return this; }
		U1								ItemGetFilter( U32 nIndex ) const { return GetControlTyped().ItemGetFilter( nIndex ); }
		UiHeader*						ItemSetCheckValue( U32 nIndex, U1 b ) { GetControlTyped().ItemSetCheckValue( nIndex, b ); return this; }
		U1								ItemGetCheckValue( U32 nIndex ) const { return GetControlTyped().ItemGetCheckValue( nIndex ); }

		U1								SetOrder( const WrapArray<U32>& pOrder ) { return GetControlTyped().SetOrder( pOrder, (U32) pOrder.m_Length ); }
		List<U32>						GetOrder() const { List<U32> v( GetControlTyped().GetCount() ); if ( !v.IsEmpty() ) GetControlTyped().GetOrder( v.Data(), (U32) v.Size() ); return std::move( v ); }

		UiHeader*						SetSort( S32 nIndex, Ui::HeaderItemSort nOrder, Ui::HeaderItemSort nDefault ) { GetControlTyped().SetSort( nIndex, nOrder, nDefault ); return this; }

		S32								GetSortIndex() const { return GetControlTyped().GetSortIndex(); }
		Ui::HeaderItemSort				GetSortOrder() const { return GetControlTyped().GetSortOrder(); }

		UiHeader*						SetDrag( U1 b ) { GetControlTyped().SetDrag( b ); return this; }
		U1								GetDrag() const { return GetControlTyped().GetDrag(); }

		UiHeader*						SetButton( U1 b ) { GetControlTyped().SetButton( b ); return this; }
		U1								GetButton() const { return GetControlTyped().GetButton(); }

		UiHeader*						SetCheckMode( U1 b ) { GetControlTyped().SetCheckMode( b ); return this; }
		U1								GetCheckMode() const { return GetControlTyped().GetCheckMode(); }

		UiHeader*						SetCheckValue( U1 b ) { GetControlTyped().SetCheckValue( b ); return this; }
		U1								GetCheckValue() const { return GetControlTyped().GetCheckValue(); }

		UiHeader*						OnClick       /**/( OnCallback1_t	 /**/ && fn ) { m_OnClick       /**/ = std::move( fn ); return this; }
		UiHeader*						OnAdjustWidth /**/( OnAdjustWidth_t	 /**/ && fn ) { m_OnAdjustWidth /**/ = std::move( fn ); return this; }
		UiHeader*						OnOrder       /**/( OnOrder_t		 /**/ && fn ) { m_OnOrder       /**/ = std::move( fn ); return this; }
		UiHeader*						OnDropDown    /**/( OnCallback1_t	 /**/ && fn ) { m_OnDropDown    /**/ = std::move( fn ); return this; }
		UiHeader*						OnCheckItem   /**/( OnCallback1_t	 /**/ && fn ) { m_OnCheckItem   /**/ = std::move( fn ); return this; }
		UiHeader*						OnCheckHeader /**/( OnCallback0_t	 /**/ && fn ) { m_OnCheckHeader /**/ = std::move( fn ); return this; }
	};
}
