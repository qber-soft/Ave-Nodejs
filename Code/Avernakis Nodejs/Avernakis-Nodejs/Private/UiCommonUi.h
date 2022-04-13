#pragma once

#include "WrapObject.h"
#include "WrapData.h"

#include "../../../External/Avernakis/Code/Avernakis-AppFeature/Include/AppHelperWindow.h"

namespace Nav
{

	class UiCommonUiWait;

	class UiCommonUiFilter
	{
	public:
		WString		m_Display;
		WString		m_Filter;
	};

	NavDefineDataByMember_( UiCommonUiFilter, Display, Filter );

	class UiCommonUiMessageButtonItem
	{
	public:
		U32												m_Id;
		WString											m_Text;
		WString											m_KeyTip;
		Ui::IconCache									m_Icon;
	};

	NavDefineDataByMember_( UiCommonUiMessageButtonItem, Id, Text, KeyTip, Icon );

	class UiCommonUiMessage
	{
	public:
		Ui::IconCache									m_Icon;
		Ui::DialogMessageResult							m_Default;
		U32												m_RadioDefault;
		List<WrapData<UiCommonUiMessageButtonItem>>		m_Radio;
		List<WrapData<UiCommonUiMessageButtonItem>>		m_Button;
		List<WrapData<UiCommonUiMessageButtonItem>>		m_StandardButton;
		WString											m_Verification;
		WString											m_VerificationKeyTip;
		Ui::CheckValue									m_VerificationDefault;
		U1												m_VerificationTriple;
		Ui::IconCache									m_FooterIcon;
		WString											m_FooterText;
		WrapData<Ui::DpiSize>							m_MaxWidth;
	};

	NavDefineDataByMember_( UiCommonUiMessage, Icon, Default, RadioDefault, Radio, Button, StandardButton, Verification, VerificationKeyTip, VerificationDefault, VerificationTriple, FooterIcon, FooterText, MaxWidth );

	class UiCommonUiMessageResult
	{
	public:
		Ui::DialogMessageResult							m_Result;
		U32												m_ButtonId;
		U32												m_RadioId;
		Ui::CheckValue									m_VerificationResult;
	};

	NavDefineDataByMember_( UiCommonUiMessageResult, Result, ButtonId, RadioId, VerificationResult );

	class UiCommonUiInputText
	{
	public:
		S32									m_MinLength;
		S32									m_MaxLength;
		U1									m_Ime;
		WString								m_Valid;
	};

	NavDefineDataByMember_( UiCommonUiInputText, MinLength, MaxLength, Ime, Valid );
	NavDefineDataByMember_( Ui::DialogInputTypeNumber, Frac, Min, Max, Default, Step );

	class UiCommonUi : public WrapObject<UiCommonUi, void(), WrapObjectPromise>
	{
	public:
		AveWrapObject( UiCommonUi );

		static PCAChar						GetExportName() { return "7930a7d06094402e9ecfe95050489f64"; }
		static void							DefineObject();

		U1									Ctor() { return true; }
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		using Wait_t = JsFuncSafe<void( UiCommonUiWait* op )>;
		using ColorPreview_t = JsFuncSafe<void( const WrapData<U8_4>& )>;

		Ui::IWindow*						m_Window;
		AppHelper::IWindowCommonUi*			m_CommonUi;

		class WaitCall;

	private:
		Ui::DialogMessageResult				Message( PCWChar szMain, PCWChar szDetail, Ui::DialogMessageIcon nIcon, U32 nButton, PCWChar szTitle );
		WrapData<UiCommonUiMessageResult>	MessageEx( PCWChar szMain, PCWChar szDetail, Ui::DialogMessageIcon nIcon, U32 nButton, PCWChar szTitle, const WrapData<UiCommonUiMessage>& extra );

		WString								Input( PCWChar szString, PCWChar szMain, PCWChar szDetail, PCWChar szCue, PCWChar szTitle );
		WString								InputText( PCWChar szString, PCWChar szMain, PCWChar szDetail, PCWChar szCue, PCWChar szTitle, const WrapData<UiCommonUiInputText>& extra );
		R64									InputNumber( R64 fValue, PCWChar szMain, PCWChar szDetail, PCWChar szCue, PCWChar szTitle, const WrapData<Ui::DialogInputTypeNumber>& extra );

		WrapData<U8_4>						PickColor( const WrapData<U8_4>& vColor, U1 bAlpha );
		WrapData<U8_4>						PickColorEx( const WrapData<U8_4>& vColor, U1 bAlpha, ColorPreview_t&& fn );

		WString								OpenFile( const List<WrapData<UiCommonUiFilter>>& filter, PCWChar szDefaultExtension, PCWChar szFolder, PCWChar szFileName );
		List<WString>						OpenFiles( const List<WrapData<UiCommonUiFilter>>& filter, PCWChar szDefaultExtension, PCWChar szFolder );

		WString								OpenFolder( PCWChar szFolder, PCWChar szFileName );
		List<WString>						OpenFolders( PCWChar szFolder );

		WString								SaveFile( const List<WrapData<UiCommonUiFilter>>& filter, PCWChar szDefaultExtension, PCWChar szFolder, PCWChar szFileName );

		U1									ExploreFolder( PCWChar szFolder, U1 bBackground );
		U1									ExploreFile( PCWChar szFile, U1 bBackground );
		U1									ExploreFiles( const List<WString>& vFile, U1 bBackground );

	public:
		AveInline UiCommonUi*				SetCommonUi( Ui::IWindow* pWindow, AppHelper::IWindowCommonUi* p ) { m_Window = pWindow; m_CommonUi = p; return this; }
	};

}
