#pragma once

#include "WrapObject.h"
#include "IoCommon.h"

namespace Nav
{

	class UiWindow;
	class IoStream;

	class UiDragContext : public WrapObject<UiDragContext, void(), WrapObjectUi>
	{
	public:
		AveWrapObject( UiDragContext );

		static PCAChar					GetExportName() { return "9e1b4c88dd0d4b54a974485fc68a9e47"; }
		static void						DefineObject();

		U1								Ctor() { return true; }
		Napi::Value						GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		Ui::IWindow*					m_Window;
		Ui::IWindowDragContext*			m_DragContext;
		U32								m_Modifier;
		S32_2							m_PosOri;
		S32_2							m_Pos;

		U1								m_HasVirtualFile;
		U1								m_HasFile;

		U32								m_VirtualFileCount;
		U32								m_FileCount;
		List<WString>					m_File;

		U32								m_Behavior;

	public:
		U32								GetModifier() const { return m_Modifier; }
		WrapData<S32_2>					GetPosition() const { return m_Pos; }

		void							SetDropTip( Ui::DragDropImage nImage, PCWChar szMessage ) { m_DragContext->SetDropTip( nImage, szMessage ); }
		void							SetDropBehavior( U32 nBehavior ) { m_DragContext->SetDropBehavior( m_Behavior = nBehavior ); }

		U1								HasVirtualFile() const { return m_HasVirtualFile; }
		U1								HasFile() const { return m_HasFile; }

		U32								VirtualFileGetCount() const { return m_HasVirtualFile; }
		WrapData<IoFileFindItem>		VirtualFileGetInfo( const MixCallContext& cc, U32 nIndex ) const;
		IoStream*						VirtualFileOpen( const MixCallContext& cc, U32 nIndex ) const;

		U32								FileGetCount() const { return m_FileCount; }
		List<WString>					FileGet( const MixCallContext& cc );

	public:
		AveInline U32 GetBehavior() const
		{
			return m_Behavior;
		}

		AveInline void SetDragContext( Ui::IWindow* pWindow, Ui::IWindowDragContext* pDragDrop )
		{
			m_Window = pWindow;
			m_DragContext = pDragDrop;
			m_Modifier = 0;// m_DragContext->GetModifer();
			m_PosOri = m_DragContext->GetPosition();
			m_Behavior = 0;

			m_HasVirtualFile = m_DragContext->GetData().HasType<Ui::ShellDataType_VirtualFile>();
			m_HasFile = m_DragContext->GetData().HasType<Ui::ShellDataType_File>();

			m_VirtualFileCount = m_DragContext->GetData().VirtualFileGetCount();
			m_FileCount = m_DragContext->GetData().FileGetCount();

			SetControl( nullptr );
		}

		AveInline void SetControl( Ui::IControl* pc )
		{
			m_Pos = m_PosOri;
			if ( pc )
			{
				auto rc = pc->GetRect();
				pc->MapRect( rc );
				m_Pos -= rc.m_Position;
			}
		}
	};

}
