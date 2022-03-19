#include "StdAfx.h"
#include "UiControlManager.h"
#include "UiCommon.h"
#include "UiControl.h"

#define ThisMethod($x) &UiControlManager::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiControlManager::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiControlManager> c_obj;
	}

	void UiControlManager::DefineObject()
	{
		AutoAddMethod( AddControl );
		AutoAddMethod( RemoveControl );
	}

	U1 UiControlManager::AddControl( WrapPointer<UiControl> c, Napi::Value key )
	{
		StringKey sk;
		if ( !sk.Set( key ) )
			return false;
		if ( sk.m_Count > 0 )
		{
			if ( sk.m_IdKey )
				m_ControlManager->AddControlEx( c->GetControl().GetType(), &c->GetControl(), sk.m_Offset, sk.m_IdKey, sk.m_Count );
			else
				m_ControlManager->AddControlEx( c->GetControl().GetType(), &c->GetControl(), sk.m_StrKey.c_str(), sk.m_Offset, sk.m_Count );
		}
		else
		{
			if ( sk.m_IdKey )
				m_ControlManager->AddControl( c->GetControl().GetType(), &c->GetControl(), sk.m_IdKey );
			else
				m_ControlManager->AddControl( c->GetControl().GetType(), &c->GetControl(), sk.m_StrKey.c_str() );
		}
		return true;
	}

	void UiControlManager::RemoveControl( WrapPointer<UiControl> c )
	{
		m_ControlManager->RemoveControl( &c->GetControl() );
	}

}
