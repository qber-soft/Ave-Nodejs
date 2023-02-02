#include "StdAfx.h"
#include "UiCommonUi.h"
#include "UiCommonUiWait.h"
#include "UiCommon.h"

#define ThisMethod($x) &UiCommonUi::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiCommonUi::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiCommonUi> c_obj;
	}

	//class UiCommonUi::WaitCall : public PromiseCall<UiCommonUi, WaitCall, Dee::AsyncOpState( Wait_t&& )>
	//{
	//public:
	//	using PromiseCall::PromiseCall;

	//	virtual void OnPrepare( const CallbackInfo& ci ) override
	//	{
	//		m_Wait = ci.NewJsObjectWithOwnership<UiCommonUiWait>();
	//	}

	//	Dee::AsyncOpState operator () ( Wait_t && fn )
	//	{
	//		return m_Owner->m_CommonUi->Wait( [this, &fn]( Ui::IDialogWaitOp& op )
	//		{
	//			m_Wait->SetOp( &op );
	//			App::GetSingleton().ExecuteInJsThread( [this, &fn]
	//			{
	//				fn.DirectCall( m_Wait );
	//			}, true );
	//		}, 1 );
	//	}

	//private:
	//	JsObject<UiCommonUiWait> m_Wait;
	//};

	class UiCommonUi::MessageCallback : public Ui::IDialogMessageCallback
	{
		virtual U1 OnDialogMessageCreate( Ui::IDialogMessageCreate& pmc ) override
		{
			return true;
		}

		virtual void OnDialogMessageLink( U32 nId ) override
		{
			m_OnMessageLink( nId );
		}

		UiCommonUiMessage::OnMessageLink_t m_OnMessageLink;

	public:
		MessageCallback( UiCommonUiMessage& extra )
		{
			m_OnMessageLink = std::move( extra.m_OnMessageLink );
		}
	};

	void UiCommonUi::DefineObject()
	{
		//AddComplexPromiseMethod<WaitCall>( "Wait" );

		AutoAddMethod( Message );
		AutoAddMethod( MessageEx );

		AutoAddMethod( Input );
		AutoAddMethod( InputText );
		AutoAddMethod( InputNumber );

		AutoAddMethod( PickColor );
		AutoAddMethod( PickColorEx );

		AutoAddMethod( OpenFile );
		AutoAddMethod( OpenFiles );

		AutoAddMethod( OpenFolder );
		AutoAddMethod( OpenFolders );

		AutoAddMethod( SaveFile );

		AutoAddMethod( ExploreFolder, WrapObjectUi );
		AutoAddMethod( ExploreFile, WrapObjectUi );
		AutoAddMethod( ExploreFiles, WrapObjectUi );
	}

	Ui::DialogMessageResult UiCommonUi::Message( PCWChar szMain, PCWChar szDetail, Ui::DialogMessageIcon nIcon, U32 nButton, PCWChar szTitle )
	{
		return m_CommonUi->Message( szMain, szDetail, nIcon, nButton, szTitle );
	}

	WrapData<UiCommonUiMessageResult> UiCommonUi::MessageEx( PCWChar szMain, PCWChar szDetail, Ui::DialogMessageIcon nIcon, U32 nButton, PCWChar szTitle, const WrapData<UiCommonUiMessage>& extra )
	{
		List<Ui::DialogMessageButtonItem> vRadio;
		List<Ui::DialogMessageButtonItem> vButton;
		List<Ui::DialogMessageButtonItem> vStdButton;

		auto pConvertButton = [&]( List<Ui::DialogMessageButtonItem>& vDst, const List<WrapData<UiCommonUiMessageButtonItem>>& vSrc )
		{
			if ( vSrc.IsEmpty() )
				return;
			vDst.Resize( vSrc.Size() );
			for ( auto& i : vSrc.RangeIndexAll() )
			{
				auto& radio = vDst[i.Index];
				radio.m_Id = i->m_Id;
				radio.m_Text = i->m_Text.c_str();
				radio.m_KeyTip = i->m_KeyTip.c_str();
				radio.m_Icon = i->m_Icon;
			}
		};
		pConvertButton( vRadio, extra.m_Radio );
		pConvertButton( vButton, extra.m_Button );
		pConvertButton( vStdButton, extra.m_StandardButton );

		Ui::DialogMessageExtra dme{};
		MessageCallback cb( (UiCommonUiMessage&) extra );
		dme.m_Icon = extra.m_Icon;
		dme.m_Default = extra.m_Default;
		dme.m_RadioCount = (U32) vRadio.Size();
		dme.m_RadioDefault = extra.m_RadioDefault;
		dme.m_Radio = vRadio.Data();
		dme.m_ButtonCount = (U32) vButton.Size();
		dme.m_Button = vButton.Data();
		dme.m_StandardButtonCount = (U32) vStdButton.Size();
		dme.m_StandardButton = vStdButton.Data();
		dme.m_Verification = extra.m_Verification.c_str();
		dme.m_VerificationKeyTip = extra.m_VerificationKeyTip.c_str();
		dme.m_VerificationDefault = extra.m_VerificationDefault;
		dme.m_VerificationTriple = extra.m_VerificationTriple;
		dme.m_FooterIcon = extra.m_FooterIcon;
		dme.m_FooterText = extra.m_FooterText.c_str();
		dme.m_FooterIsLink = extra.m_FooterIsLink;
		dme.m_MaxWidth = extra.m_MaxWidth;
		dme.m_Callback = &cb;

		UiCommonUiMessageResult result;
		result.m_Result = m_CommonUi->Message( szMain, szDetail, nIcon, nButton, szTitle, &dme );
		result.m_ButtonId = dme.m_ButtonId;
		result.m_RadioId = dme.m_RadioId;
		result.m_VerificationResult = dme.m_VerificationResult;

		return result;
	}

	WString UiCommonUi::Input( PCWChar szString, PCWChar szMain, PCWChar szDetail, PCWChar szCue, PCWChar szTitle )
	{
		WString s( szString );
		if ( m_CommonUi->Input( s, szMain, szDetail, szCue, szTitle ) )
			return std::move( s );
		else
			return szString;
	}

	WString UiCommonUi::InputText( PCWChar szString, PCWChar szMain, PCWChar szDetail, PCWChar szCue, PCWChar szTitle, const WrapData<UiCommonUiInputText>& extra )
	{
		WString s( szString );
		Ui::DialogInputExtra die{};
		die.m_Type = Ui::DialogInputType::Text;
		die.m_Text.m_MinLength = extra.m_MinLength;
		die.m_Text.m_MaxLength = extra.m_MaxLength;
		die.m_Text.m_Ime = extra.m_Ime;
		die.m_Text.m_Valid = extra.m_Valid.c_str();
		if ( m_CommonUi->Input( s, szMain, szDetail, szCue, szTitle, &die ) )
			return std::move( s );
		else
			return {};
	}

	R64 UiCommonUi::InputNumber( R64 fValue, PCWChar szMain, PCWChar szDetail, PCWChar szCue, PCWChar szTitle, const WrapData<Ui::DialogInputTypeNumber>& extra )
	{
		WString s( AveStr.ToStringW( fValue ) );
		Ui::DialogInputExtra die{};
		die.m_Type = Ui::DialogInputType::Number;
		die.m_Number = extra;
		if ( m_CommonUi->Input( s, szMain, szDetail, szCue, szTitle, &die ) )
			return AveStr.ToR64( s );
		else
			return {};
	}

	WrapData<U8_4> UiCommonUi::PickColor( const WrapData<U8_4>& vColor, U1 bAlpha )
	{
		U8_4 v = vColor;
		if ( m_CommonUi->PickColor( v, bAlpha ) )
			return v;
		return vColor;
	}

	WrapData<U8_4> UiCommonUi::PickColorEx( const WrapData<U8_4>& vColor, U1 bAlpha, ColorPreview_t && fn )
	{
		U8_4 v = vColor;
		Ui::DialogColorExtra dce{};
		dce.m_Preview = [&fn]( const Ui::DialogColorExtra& sender, const U8_4& vc )
		{
			fn( vc );
		};
		if ( m_CommonUi->PickColor( v, bAlpha, &dce ) )
			return v;
		return vColor;
	}

	WString UiCommonUi::OpenFile( const List<WrapData<UiCommonUiFilter>> & filter, PCWChar szDefaultExtension, PCWChar szFolder, PCWChar szFileName )
	{
		List<Ui::SysDialogFilter> vFilter( filter.Size() );
		for ( auto& i : filter.RangeIndexAll() )
		{
			vFilter[i.Index].m_Display = i->m_Display.c_str();
			vFilter[i.Index].m_Filter = i->m_Filter.c_str();
		}
		Ui::SysDialogOpen sdo{};
		if ( szDefaultExtension && *szDefaultExtension )
			sdo.m_DefaultExtension = szDefaultExtension;
		if ( szFolder && *szFolder )
			sdo.m_Folder = szFolder;
		if ( szFileName && *szFileName )
			sdo.m_FileName = szFileName;
		WString s;
		if ( App::GetSingleton().GetSysDialog().ShowOpenFileDialog( &m_Window->GetNativeWindow(), vFilter.Data(), vFilter.Size(), s, &sdo ) )
			return std::move( s );
		return {};
	}

	List<WString> UiCommonUi::OpenFiles( const List<WrapData<UiCommonUiFilter>> & filter, PCWChar szDefaultExtension, PCWChar szFolder )
	{
		List<Ui::SysDialogFilter> vFilter( filter.Size() );
		for ( auto& i : filter.RangeIndexAll() )
		{
			vFilter[i.Index].m_Display = i->m_Display.c_str();
			vFilter[i.Index].m_Filter = i->m_Filter.c_str();
		}
		Ui::SysDialogOpen sdo{};
		if ( szDefaultExtension && *szDefaultExtension )
			sdo.m_DefaultExtension = szDefaultExtension;
		if ( szFolder && *szFolder )
			sdo.m_Folder = szFolder;
		List<WString> v;
		if ( App::GetSingleton().GetSysDialog().ShowOpenFileDialog( &m_Window->GetNativeWindow(), vFilter.Data(), vFilter.Size(), v, &sdo ) )
			return std::move( v );
		return {};
	}

	WString UiCommonUi::OpenFolder( PCWChar szFolder, PCWChar szFileName )
	{
		WString s;
		Ui::SysDialogOpen sdo{};
		if ( szFolder && *szFolder )
			sdo.m_Folder = szFolder;
		if ( szFileName && *szFileName )
			sdo.m_FileName = szFileName;
		if ( App::GetSingleton().GetSysDialog().ShowOpenFolderDialog( &m_Window->GetNativeWindow(), s, &sdo ) )
			return std::move( s );
		return {};
	}

	List<WString> UiCommonUi::OpenFolders( PCWChar szFolder )
	{
		List<WString> v;
		Ui::SysDialogOpen sdo{};
		if ( szFolder && *szFolder )
			sdo.m_Folder = szFolder;
		if ( App::GetSingleton().GetSysDialog().ShowOpenFolderDialog( &m_Window->GetNativeWindow(), v, &sdo ) )
			return std::move( v );
		return {};
	}

	WString UiCommonUi::SaveFile( const List<WrapData<UiCommonUiFilter>> & filter, PCWChar szDefaultExtension, PCWChar szFolder, PCWChar szFileName )
	{
		List<Ui::SysDialogFilter> vFilter( filter.Size() );
		for ( auto& i : filter.RangeIndexAll() )
		{
			vFilter[i.Index].m_Display = i->m_Display.c_str();
			vFilter[i.Index].m_Filter = i->m_Filter.c_str();
		}
		Ui::SysDialogSave sds{};
		if ( szFolder && *szFolder )
			sds.m_Folder = szFolder;
		if ( szFileName && *szFileName )
			sds.m_FileName = szFileName;
		WString s;
		if ( App::GetSingleton().GetSysDialog().ShowSaveFileDialog( &m_Window->GetNativeWindow(), vFilter.Data(), vFilter.Size(), s, szDefaultExtension, &sds ) )
			return std::move( s );
		return {};
	}

	U1 UiCommonUi::ExploreFolder( PCWChar szFolder, U1 bBackground )
	{
		return App::GetSingleton().GetSysDialog().ExploreFolder( szFolder, bBackground );
	}

	U1 UiCommonUi::ExploreFile( PCWChar szFile, U1 bBackground )
	{
		return App::GetSingleton().GetSysDialog().ExploreFile( szFile, bBackground );
	}

	U1 UiCommonUi::ExploreFiles( const List<WString>& vFile, U1 bBackground )
	{
		return App::GetSingleton().GetSysDialog().ExploreFile( vFile, bBackground );
	}

}
