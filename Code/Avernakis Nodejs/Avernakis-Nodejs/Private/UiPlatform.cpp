#include "StdAfx.h"
#include "UiPlatform.h"

#define ThisMethod($x) &UiPlatform::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiPlatform::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiPlatform> c_obj;
	}

	void UiPlatform::DefineObject()
	{
		AutoAddMethod( GetPopupAlign );

		AutoAddMethod( PointerGetPosition );
		AutoAddMethod( PointerSetPosition );
		AutoAddMethod( PointerGetVisible );
		AutoAddMethod( PointerSetVisible );

		AutoAddMethod( ScreenGetArea );

		AutoAddMethod( MonitorEnumerate );
		AutoAddMethod( MonitorGetNeareatPoint );
		AutoAddMethod( MonitorGetNeareatRect );

		AutoAddMethod( FontEnumerate );
	}

	Ui::PopupAlign UiPlatform::GetPopupAlign() const
	{
		return m_Platform->GetPopupAlign();
	}

	WrapData<S32_2> UiPlatform::PointerGetPosition() const
	{
		return m_Platform->CursorGetPosition();
	}

	void UiPlatform::PointerSetPosition( const WrapData<S32_2>& vPos ) const
	{
		m_Platform->CursorSetPosition( vPos );
	}

	Ui::CursorVisibility UiPlatform::PointerGetVisible() const
	{
		return m_Platform->CursorGetVisible();
	}

	void UiPlatform::PointerSetVisible( U1 b )
	{
		m_Platform->CursorSetVisible( b );
	}

	WrapData<S32_R> UiPlatform::ScreenGetArea() const
	{
		return m_Platform->ScreenGetArea();
	}

	List<WrapData<UiMonitorItem>> UiPlatform::MonitorEnumerate() const
	{
		List<Ui::MonitorItem> v;
		Ui::MonitorEnumerator_List me( v );
		List<WrapData<UiMonitorItem>> vr;
		if ( m_Platform->MonitorEnumerate( me ) )
		{
			vr.Resize( v.Size() );
			for ( auto& i : v.RangeIndexAll() )
				__ConvertMonitorInfo( vr[i.Index], *i );
		}
		return std::move( vr );
	}

	WrapData<UiMonitorItem> UiPlatform::MonitorGetNeareatPoint( const WrapData<S32_2> & vPos, U1 bExtendInfo ) const
	{
		Ui::MonitorItem mi{};
		m_Platform->MonitorGetNeareat( vPos, mi, bExtendInfo );
		WrapData<UiMonitorItem> r{};
		__ConvertMonitorInfo( r, mi );
		return r;
	}

	WrapData<UiMonitorItem> UiPlatform::MonitorGetNeareatRect( const WrapData<S32_R> & vArea, U1 bExtendInfo ) const
	{
		Ui::MonitorItem mi{};
		m_Platform->MonitorGetNeareat( vArea, mi, bExtendInfo );
		WrapData<UiMonitorItem> r{};
		__ConvertMonitorInfo( r, mi );
		return r;
	}

	List<WString> UiPlatform::FontEnumerate( U1 bIncludeVertical ) const
	{
		return m_Platform->FontEnumerate( bIncludeVertical );
	}

	AveInline void UiPlatform::__ConvertMonitorInfo( WrapData<UiMonitorItem>& d, Ui::MonitorItem& mi )
	{
		d.m_AreaFull = mi.m_AreaFull;
		d.m_AreaWorking = mi.m_AreaWorking;
		d.m_Index = mi.m_Index;
		d.m_Primary = mi.m_Primary;
		d.m_ConnectorType = mi.m_ConnectorType;
		d.m_Name = mi.m_Name;
		d.m_DpiEffective = mi.m_DpiEffective;
		d.m_DpiRaw = mi.m_DpiRaw;
		d.m_ScaleEffective = mi.m_ScaleEffective;
		d.m_ScaleRaw = mi.m_ScaleRaw;
	}

}
