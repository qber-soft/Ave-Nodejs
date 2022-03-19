#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiStatusBar : public UiControlHelper<UiStatusBar, Ui::IStatusBar>
	{
	public:
		AveWrapControl( UiStatusBar );

		~UiStatusBar()
		{
		}

		static PCAChar					GetExportName() { return "UiStatusBar"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnClick_t = JsFuncSafe<void( UiStatusBar* sender, S32 nIndex )>;

		OnClick_t						m_OnClick;

		void							__OnClick( Ui::IStatusBar& sender, S32 nIndex );

	private:
		UiStatusBar*					SetPart( const List<WrapData<Ui::DpiSize>>& vPartWidth );
		List<WrapData<Ui::DpiSize>>		GetPart() const;
		UiStatusBar*					SetWidth( U32 nIndex, const WrapData<Ui::DpiSize>& nWidth ) { GetControlTyped().SetWidth( nIndex, nWidth ); return this; }
		WrapData<Ui::DpiSize>			GetWidth( U32 nIndex ) const { return GetControlTyped().GetWidth( nIndex ); }
		S32								GetWidthReal( U32 nIndex ) const { return GetControlTyped().GetWidthReal( nIndex ); }
		UiStatusBar*					SetMaxWidth( U32 nIndex, const WrapData<Ui::DpiSize>& nWidth ) { GetControlTyped().SetMaxWidth( nIndex, nWidth ); return this; }
		WrapData<Ui::DpiSize>			GetMaxWidth( U32 nIndex ) const { return GetControlTyped().GetMaxWidth( nIndex ); }
		UiStatusBar*					SetReducePriority( U32 nIndex, S32 nPriority ) { GetControlTyped().SetReducePriority( nIndex, nPriority ); return this; }
		S32								GetReducePriority( U32 nIndex ) const { return GetControlTyped().GetReducePriority( nIndex ); }
		UiStatusBar*					SetText( U32 nIndex, PCWChar szText ) { GetControlTyped().SetText( nIndex, szText ); return this; }
		WString							GetText( U32 nIndex ) const { return GetControlTyped().GetText( nIndex ); }
		UiStatusBar*					SetPartToolTip( U32 nIndex, PCWChar szText ) { GetControlTyped().SetToolTip( nIndex, szText ); return this; }
		UiStatusBar*					SetAlign( U32 nIndex, Ui::AlignType nType ) { GetControlTyped().SetAlign( nIndex, nType ); return this; }
		Ui::AlignType					GetAlign( U32 nIndex ) const { return GetControlTyped().GetAlign( nIndex ); }
		UiStatusBar*					SetIcon( U32 nIndex, Ui::IconCache nIcon ) { GetControlTyped().SetIcon( nIndex, nIcon ); return this; }
		Ui::IconCache					GetIcon( U32 nIndex ) const { return GetControlTyped().GetIcon( nIndex ); }
		UiStatusBar*					SetClickable( U32 nIndex, U1 bClick ) { GetControlTyped().SetClickable( nIndex, bClick ); return this; }
		U1								GetClickable( U32 nIndex ) const { return GetControlTyped().GetClickable( nIndex ); }
		WrapPointer<UiControl>			SetContent( U32 nIndex, WrapPointer<UiControl> pControl ) { return __ChangeContent( GetControlTyped().SetContent( nIndex, pControl->TakeOwnership() ) ); }
		WrapPointer<UiControl>			GetContent( U32 nIndex ) const { return __ReturnContent( GetControlTyped().GetContent( nIndex ) ); }
		UiStatusBar*					SetContentMargin( U32 nIndex, S32 nMargin ) { GetControlTyped().SetContentMargin( nIndex, nMargin ); return this; }
		S32								GetContentMargin( U32 nIndex ) const { return GetControlTyped().GetContentMargin( nIndex ); }
		S32								HitTest( const WrapData<S32_2>& pt, U1 bIncludeUnclickable ) const { return GetControlTyped().HitTest( pt, bIncludeUnclickable ); }
		WrapData<S32_R>					GetItemRect( U32 nIndex ) const { S32_R rc{}; GetControlTyped().GetItemRect( nIndex, rc ); return rc; }

		UiStatusBar*					SetBackground( U1 b ) { GetControlTyped().SetBackground( b ); return this; }
		U1								GetBackground() const { return GetControlTyped().GetBackground(); }

		UiStatusBar*					SetBackColor( const WrapData<U8_4>& vColor ) { GetControlTyped().SetBackColor( vColor ); return this; }
		WrapData<U8_4>					GetBackColor() const { return GetControlTyped().GetBackColor(); }

		UiStatusBar*					OnClick( OnClick_t&& fn ) { m_OnClick = std::move( fn ); return this; }
	};
}
