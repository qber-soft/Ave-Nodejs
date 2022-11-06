#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiMenuItem
	{
	public:
		U32									m_Flag;
		U32									m_State;
		Ui::MenuType						m_Type;
		S32									m_Index;
		U32									m_Id;
		Ui::IconCache						m_Icon;
		WString								m_Text;
		WString								m_TextSub;
		WString								m_Key;
		WrapData<Ui::DpiSize_2>				m_Size;

		void FromMenuItem( const Ui::MenuItem& s )
		{
			m_Flag    /**/ = s.m_Flag    /**/;
			m_State   /**/ = s.m_State   /**/;
			m_Type    /**/ = s.m_Type    /**/;
			m_Index   /**/ = s.m_Index   /**/;
			m_Id      /**/ = s.m_Id      /**/;
			m_Icon    /**/ = s.m_Icon    /**/;
			m_Text    /**/ = s.m_Text    /**/;
			m_TextSub /**/ = s.m_TextSub /**/;
			m_Size    /**/ = s.m_Size    /**/;
			m_Key.Clear();
			if ( s.m_Key )
				m_Key += s.m_Key;
		}
	};

	NavDefineDataByMember_( UiMenuItem, Flag, State, Type, Index, Id, Icon, Text, TextSub, Key, Size );

	template<>
	class WrapDataTransit<Ui::MenuItem> : public WrapDataTransitHelper<Ui::MenuItem, UiMenuItem>
	{
	public:
		static void Transit( Ui::MenuItem& d, const UiMenuItem& s )
		{
			d.m_Flag    /**/ = s.m_Flag    /**/;
			d.m_State   /**/ = s.m_State   /**/;
			d.m_Type    /**/ = s.m_Type    /**/;
			d.m_Index   /**/ = s.m_Index   /**/;
			d.m_Id      /**/ = s.m_Id      /**/;
			d.m_Icon    /**/ = s.m_Icon    /**/;
			d.m_Size    /**/ = s.m_Size    /**/;
			d.m_Text    /**/ = (PWChar) s.m_Text    /**/.c_str();
			d.m_TextSub /**/ = (PWChar) s.m_TextSub /**/.c_str();
			d.m_Key     /**/ = 1 == s.m_Key.Length() && (s.m_Key[0] < 0xd800 || s.m_Key[0] > 0xdfff) ? s.m_Key[0] : 0;
			d.m_Context = nullptr;
			d.m_TextCharLength = 0;
			d.m_TextSubCharLength = 0;
		}
	};

	class UiMenu : public UiControlHelper<UiMenu, Ui::IMenu>
	{
	public:
		AveWrapControl( UiMenu );

		~UiMenu()
		{
		}

		static PCAChar					GetExportName() { return "UiMenu"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using Callback_t        /**/ = JsFuncSafe<void( UiMenu* sender, U32 nId )>;
		using OnVisibleChange_t /**/ = JsFuncSafe<void( UiMenu* sender )>;

		UiWindow*						m_Window{};

		Callback_t						m_OnClick       /**/;
		Callback_t						m_OnRightClick  /**/;
		Callback_t						m_OnMiddleClick /**/;
		OnVisibleChange_t				m_OnShow        /**/;
		OnVisibleChange_t				m_OnHide        /**/;

		void							__OnClick       /**/( Ui::IMenu& sender, U32 nId );
		void							__OnRightClick  /**/( Ui::IMenu& sender, U32 nId );
		void							__OnMiddleClick /**/( Ui::IMenu& sender, U32 nId );
		void							__OnShow        /**/( Ui::IMenu& sender );
		void							__OnHide        /**/( Ui::IMenu& sender );

	private:
		S32								InsertItem( const WrapData<UiMenuItem>& pItem );
		UiMenu*							InsertSubMenu( const MixCallContext& cc, const WrapData<UiMenuItem>& pItem );
		U1								RemoveById( U32 nId ) { return GetControlTyped().RemoveById( nId ); }
		U1								RemoveByIndex( S32 nIndex ) { return GetControlTyped().RemoveByIndex( nIndex ); }
		U1								SetById( const WrapData<UiMenuItem>& pItem );
		U1								SetByIndex( const WrapData<UiMenuItem>& pItem );
		WrapData<UiMenuItem>			GetById( U32 nId ) const;
		WrapData<UiMenuItem>			GetByIndex( U32 nIndex ) const;
		UiMenu*							GetSubMenuById( const MixCallContext& cc, U32 nId ) const;
		UiMenu*							GetSubMenuByIndex( const MixCallContext& cc, S32 nIndex ) const;
		UiMenu*							Clear() { GetControlTyped().Clear(); return this; }
		S32								GetCount() const { return GetControlTyped().GetCount(); }
		UiMenu*							SetItemHeight( const WrapData<Ui::DpiSize>& nHeight ) { GetControlTyped().SetItemHeight( nHeight ); return this; }
		WrapData<Ui::DpiSize>			GetItemHeight() const { return GetControlTyped().GetItemHeight(); }
		S32								SetCheckById( U32 nId, U1 b ) { return GetControlTyped().SetCheckById( nId, b ); }
		U1								GetCheckById( U32 nId ) const { return GetControlTyped().GetCheckById( nId ); }
		S32								SetRadioId( U32 nId ) { return GetControlTyped().SetRadioId( nId ); }
		U32								GetRadioId() const { return GetControlTyped().GetRadioId(); }
		S32								SetGroupRadioId( U32 nIdStart, U32 nIdEnd, U32 nId ) { return GetControlTyped().SetGroupRadioId( nIdStart, nIdEnd, nId ); } // range: [nIdStart, nIdEnd)
		U32								GetGroupRadioId( U32 nIdStart, U32 nIdEnd ) const { return GetControlTyped().GetGroupRadioId( nIdStart, nIdEnd ); } // range: [nIdStart, nIdEnd)
		WrapPointer<UiControl>			SetContentById( U32 nId, WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().SetContentById( nId, pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			SetContentByIndex( S32 nIndex, WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().SetContentByIndex( nIndex, pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			GetContentById( U32 nId ) const { return __ReturnContent( GetControlTyped().GetContentById( nId ) ); }
		WrapPointer<UiControl>			GetContentByIndex( S32 nIndex ) const { return __ReturnContent( GetControlTyped().GetContentByIndex( nIndex ) ); }

		UiMenu*							OnClick       /**/( Callback_t       /**/&& fn );
		UiMenu*							OnRightClick  /**/( Callback_t       /**/&& fn );
		UiMenu*							OnMiddleClick /**/( Callback_t       /**/&& fn );
		UiMenu*							OnShow        /**/( OnVisibleChange_t/**/&& fn );
		UiMenu*							OnHide        /**/( OnVisibleChange_t/**/&& fn );
	};
}
