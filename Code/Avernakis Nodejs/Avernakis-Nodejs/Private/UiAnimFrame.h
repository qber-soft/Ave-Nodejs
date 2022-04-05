#pragma once

#include "UiVisualHelper.h"
#include "IoCommon.h"

namespace Nav
{

	namespace __Detail
	{
		class UiAnimFrameInfo
		{
		public:
			WrapData<S32_2>		m_SizePerFrame;
			S32					m_FramePerRow;
			S32					m_FrameCount;
			S32					m_FrameRate;
		};
	}

	NavDefineDataByMember_( __Detail::UiAnimFrameInfo, SizePerFrame, FramePerRow, FrameCount, FrameRate );
	NavDefineTransitByMember_( Ui::AnimFrameInfo, __Detail::UiAnimFrameInfo, SizePerFrame, FramePerRow, FrameCount, FrameRate );

	class UiAnimFrame : public UiVisualHelper<UiAnimFrame, Ui::IAnimFrame>
	{
	public:
		AveWrapVisual( UiAnimFrame );

		~UiAnimFrame()
		{
		}

		static PCAChar					GetExportName() { return "UiAnimFrame"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:

	private:
		UiAnimFrame*					SetStretchMode( Ui::StretchMode nMode ) { GetControlTyped().SetStretchMode( nMode ); return this; }
		Ui::StretchMode					GetStretchMode() const { return GetControlTyped().GetStretchMode(); }

		UiAnimFrame*					SetFrameInfo( const WrapData<Ui::AnimFrameInfo>& info ) { GetControlTyped().SetFrameInfo( info ); return this; }
		WrapData<Ui::AnimFrameInfo>		GetFrameInfo() const { return GetControlTyped().GetFrameInfo(); }

		UiAnimFrame*					SetPicture( const WrapData<IoResourceSource>& rs ) { GetControlTyped().SetPicture( rs.ToResourceSource() ); return this; }

		UiAnimFrame*					Play() { GetControlTyped().Play(); return this; }
		UiAnimFrame*					Stop() { GetControlTyped().Stop(); return this; }

		UiAnimFrame*					SetPlayPosition( S32 nFrame ) { GetControlTyped().SetPlayPosition( nFrame ); return this; }
		S32								GetPlayPosition() const { return GetControlTyped().GetPlayPosition(); }

		U1								IsPlaying() const { return GetControlTyped().IsPlaying(); }

	};
}
