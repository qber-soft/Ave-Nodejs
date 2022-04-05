#include "StdAfx.h"
#include "UiDragContext.h"
#include "UiCommon.h"
#include "IoStream.h"

#define ThisMethod($x) &UiDragContext::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiCommonUiWait::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiDragContext> c_obj;
	}

	void UiDragContext::DefineObject()
	{
		AutoAddMethod( GetModifier );
		AutoAddMethod( GetPosition );
		AutoAddMethod( SetDropTip );
		AutoAddMethod( SetDropBehavior );

		AutoAddMethod( HasVirtualFile );
		AutoAddMethod( HasFile );

		AutoAddMethod( VirtualFileGetCount );
		AutoAddMethod( VirtualFileGetInfo, WrapObjectMix );
		AutoAddMethod( VirtualFileOpen, WrapObjectMix );

		AutoAddMethod( FileGetCount );
		AutoAddMethod( FileGet, WrapObjectMix );
	}

	WrapData<IoFileFindItem> UiDragContext::VirtualFileGetInfo( const MixCallContext & cc, U32 nIndex ) const
	{
		IoFileFindItem r{};
		r.m_Info.m_Attribute = Io::FileAttribute::Invalid;
		if ( MixCallStage::InUi == cc.GetStage() )
		{
			Io::FileFinderItem<512> ffi;
			if ( m_DragContext->GetData().VirtualFileGetInfo( nIndex, ffi ) )
				cc.SetUserContext( new Io::FileFinderItem<512>( ffi ) );
		}
		else if ( MixCallStage::PostUi == cc.GetStage() )
		{
			if ( auto p = UniPtr( (Io::FileFinderItem<512>*) cc.GetUserContext() ) )
			{
				r.m_Info.m_Size = p->m_Info.m_Size;
				r.m_Info.m_TimeCreate = p->m_Info.m_TimeCreate;
				r.m_Info.m_TimeModify = p->m_Info.m_TimeModify;
				r.m_Info.m_TimeAccess = p->m_Info.m_TimeAccess;
				r.m_Info.m_Attribute = p->m_Info.m_Attribute;
				r.m_Name = p->m_Name;
			}
		}
		return r;
	}

	IoStream* UiDragContext::VirtualFileOpen( const MixCallContext& cc, U32 nIndex ) const
	{
		if ( MixCallStage::InUi == cc.GetStage() )
		{
			auto p = m_DragContext->GetData().VirtualFileOpen( nIndex );
			cc.SetUserContext( p.Detach() );
		}
		else if ( MixCallStage::PostUi == cc.GetStage() )
		{
			if ( auto ps = Io::AveStream( (Io::IAveStream*) cc.GetUserContext(), false ) )
			{
				if ( auto js = cc.NewJsObject<IoStream>() )
				{
					js->SetStream( std::move( ps ) );
					return js;
				}
			}
		}
		return nullptr;
	}

	List<WString> UiDragContext::FileGet( const MixCallContext & cc )
	{
		if ( MixCallStage::InUi == cc.GetStage() )
		{
			if ( !m_DragContext->GetData().FileGet( m_File ) )
				m_File.Clear();
		}
		else if ( MixCallStage::PostUi == cc.GetStage() )
		{
			return m_File;
		}
		return {};
	}

}
