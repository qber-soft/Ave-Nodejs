#pragma once

#include "WrapObject.h"
#include "WrapData.h"
#include "UiCommon.h"

namespace Nav
{

	class UiMonitorItem
	{
	public:
		WrapData<S32_R>					m_AreaFull;
		WrapData<S32_R>					m_AreaWorking;

		// Extend infomation
		U32								m_Index;
		U1								m_Primary;
		Ui::MonitorConnectorType		m_ConnectorType;
		WString							m_Name;
		WrapData<U32_2>					m_DpiEffective;
		WrapData<U32_2>					m_DpiRaw;
		WrapData<R32_2>					m_ScaleEffective;
		WrapData<R32_2>					m_ScaleRaw;
	};

	NavDefineDataByMember_( UiMonitorItem, AreaFull, AreaWorking, Index, Primary, ConnectorType, Name, DpiEffective, DpiRaw, ScaleEffective, ScaleRaw );

	class UiPlatform : public WrapObject<UiPlatform, void(), WrapObjectUi>
	{
	public:
		AveWrapObject( UiPlatform );

		static PCAChar						GetExportName() { return "a3146be2745f408a924fe98547cb6e42"; }
		static void							DefineObject();

		U1									Ctor() { m_Platform = AveKak.QueryService<Ui::IPlatform>(); return !!m_Platform; }
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Ui::IPlatform*						m_Platform;

	private:
		Ui::PopupAlign						GetPopupAlign() const;

		WrapData<S32_2>						PointerGetPosition() const;
		void								PointerSetPosition( const WrapData<S32_2>& vPos ) const;
		Ui::CursorVisibility				PointerGetVisible() const;
		void								PointerSetVisible( U1 b );

		WrapData<S32_R>						ScreenGetArea() const;

		List<WrapData<UiMonitorItem>>		MonitorEnumerate() const;
		WrapData<UiMonitorItem>				MonitorGetNeareatPoint( const WrapData<S32_2>& vPos, U1 bExtendInfo ) const;
		WrapData<UiMonitorItem>				MonitorGetNeareatRect( const WrapData<S32_R>& vArea, U1 bExtendInfo ) const;

		List<WString>						FontEnumerate( U1 bIncludeVertical ) const;

	private:
		static AveInline void				__ConvertMonitorInfo( WrapData<UiMonitorItem>& d, Ui::MonitorItem& mi );

	public:
	};

}
