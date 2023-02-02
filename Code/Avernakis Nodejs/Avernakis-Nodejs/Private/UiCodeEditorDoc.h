#pragma once

#include "UiControlHelper.h"

namespace Nav
{

	class UiCodeEditorOpItem
	{
	public:
		Ui::CodeEditorOp						m_Type;
		WString									m_String;
	};
	NavDefineDataByMember_( UiCodeEditorOpItem, Type, String );
	using UiCodeEditorOpItem_t = WrapData<UiCodeEditorOpItem>;

	class UiCodeEditorDoc : public WrapObject<UiCodeEditorDoc, void(), WrapObjectUi>
	{
	public:
		AveWrapObject( UiCodeEditorDoc );

		static PCAChar						GetExportName() { return "cde58fbdb7ba472988384d0d29c83737"; }
		static void							DefineObject();

		U1									Ctor() { return true; }
		Napi::Value							GetObjectValue( Napi::Env env ) { return __GetObjectValue( env ); }

	private:
		using Syntax_t						/**/ = JsFuncSafe<void( UiCodeEditorDoc* sender, Ui::CodeEditorPos nStart, Ui::CodeEditorPos nEnd, Ui::CodeEditorStyle nInitStyle )>;

		Ui::ICodeEditorDoc*					m_Doc{ nullptr };

		Syntax_t							m_Lexer;
		Syntax_t							m_Folder;

	private:
		AveInline Ui::ICodeEditorOpManager&	__GetOp() const { return m_Doc->GetOp(); }
		AveInline Ui::ICodeEditorMarker&	__GetMarker() const { return m_Doc->GetMarker(); }
		AveInline Ui::ICodeEditorLevel&		__GetLevel() const { return m_Doc->GetLevel(); }
		AveInline Ui::ICodeEditorLineText&	__GetMarginText() const { return m_Doc->GetMarginText(); }
		AveInline Ui::ICodeEditorLineText&	__GetAnnotation() const { return m_Doc->GetAnnotation(); }

	private:
		//====================================================================================================
		// Doc

		Ui::CodeEditorPos					GetLength() const { return m_Doc->GetLength(); }
		UiCodeEditorDoc*					Reset() { m_Doc->Reset(); return this; }

		U16									CharAt( Ui::CodeEditorPos nPos ) const { return m_Doc->CharAt( nPos ); }
		WString								CharGet( Ui::CodeEditorPos nPos, Ui::CodeEditorPos nCharLength ) const { WString s( (USize) nCharLength, 0 ); s.Resize( m_Doc->CharGet( nPos, nCharLength, s.Data() ) ); return std::move( s ); }
		UiCodeEditorDoc*					CharInsert( Ui::CodeEditorPos nPos, PCWChar szText ) { m_Doc->CharInsert( nPos, szText ); return this; }
		UiCodeEditorDoc*					CharRemove( Ui::CodeEditorPos nPos, Ui::CodeEditorPos nCharLength ) { m_Doc->CharRemove( nPos, nCharLength ); return this; }

		Ui::CodeEditorStyle					StyleAt( Ui::CodeEditorPos nPos ) const { return m_Doc->StyleAt( nPos ); }
		List<Ui::CodeEditorStyle>			StyleGet( Ui::CodeEditorPos nPos, Ui::CodeEditorPos nCharLength ) const { List<Ui::CodeEditorStyle> v( nCharLength ); v.Resize( m_Doc->StyleGet( nPos, nCharLength, v.Data() ) ); return std::move( v ); }
		U1									StyleSetAll( Ui::CodeEditorPos nPos, Ui::CodeEditorPos nLength, Ui::CodeEditorStyle nStyle ) { return m_Doc->StyleSet( nPos, nLength, nStyle ); }
		U1									StyleSet( Ui::CodeEditorPos nPos, const List<Ui::CodeEditorStyle>& vStyle ) { return m_Doc->StyleSet( nPos, (Ui::CodeEditorPos) vStyle.Size(), vStyle.Data() ); }
		UiCodeEditorDoc*					StyleStart( Ui::CodeEditorPos nPos ) { m_Doc->StyleStart( nPos ); return this; }
		U1									StyleFillAll( Ui::CodeEditorPos nLength, Ui::CodeEditorStyle nStyle ) { return m_Doc->StyleFill( nLength, nStyle ); }
		U1									StyleFill( const List<Ui::CodeEditorStyle>& vStyle ) { return m_Doc->StyleFill( (Ui::CodeEditorPos) vStyle.Size(), vStyle.Data() ); }

		S32									LineGetCount() const { return m_Doc->LineGetCount(); }
		S32									LineIndex( Ui::CodeEditorPos nPos ) const { return m_Doc->LineIndex( nPos ); }
		Ui::CodeEditorPos					LineStart( S32 nLine ) const { return m_Doc->LineStart( nLine ); }
		Ui::CodeEditorPos					LineEnd( S32 nLine ) const { return m_Doc->LineEnd( nLine ); }
		StringLineEnding					LineEnding( S32 nLine ) const { return m_Doc->LineEnding( nLine ); }

		U1									GetReadOnly() const { return m_Doc->GetReadOnly(); }
		UiCodeEditorDoc*					SetReadOnly( U1 b ) { m_Doc->SetReadOnly( b ); return this; }

		StringLineEnding					GetDefaultLineEnding() const { return m_Doc->GetDefaultLineEnding(); }
		UiCodeEditorDoc*					SetDefaultLineEnding( StringLineEnding nLineEnding ) { m_Doc->SetDefaultLineEnding( nLineEnding ); return this; }

		//====================================================================================================
		// Op

		UiCodeEditorDoc*					OpSetEnable( U1 b ) { __GetOp().SetEnable( b ); return this; }
		U1									OpGetEnable() const { return __GetOp().GetEnable(); }

		UiCodeEditorDoc*					OpSetSavePoint() { __GetOp().SetSavePoint(); return this; }
		U1									OpIsSavePoint() const { return __GetOp().IsSavePoint(); }

		U32									OpGetUndoCount() const { return __GetOp().GetUndoCount(); }
		U32									OpGetRedoCount() const { return __GetOp().GetRedoCount(); }

		List<UiCodeEditorOpItem_t>			OpGetUndoRecord( U32 nIndex, U32 nCount ) const;
		List<UiCodeEditorOpItem_t>			OpGetRedoRecord( U32 nIndex, U32 nCount ) const;

		UiCodeEditorDoc*					OpClear() { __GetOp().Clear(); return this; }
		U32									OpUndo( U32 nCount ) { return __GetOp().Undo( nCount ); }
		U32									OpRedo( U32 nCount ) { return __GetOp().Redo( nCount ); }

		UiCodeEditorDoc*					OpBeginOperationGroup( U1 bMultiCaret );
		UiCodeEditorDoc*					OpEndOperationGroup();

		UiCodeEditorDoc*					OpAddCustomOperation( const void* pData, USize nByteSize );

		//====================================================================================================
		// Marker

		U1									MarkAdd( S32 nLine, U32 nMarkIndex ) { return __GetMarker().Add( nLine, nMarkIndex ); }
		U1									MarkAddMask( S32 nLine, U32 nMarkMask ) { return __GetMarker().AddMask( nLine, nMarkMask ); }
		U1									MarkRemove( S32 nLine, U32 nMarkIndex ) { return __GetMarker().Remove( nLine, nMarkIndex ); }
		U1									MarkRemoveMask( S32 nLine, U32 nMarkMask ) { return __GetMarker().RemoveMask( nLine, nMarkMask ); }
		U1									MarkRemoveLine( S32 nLine ) { return __GetMarker().Remove( nLine ); }
		U1									MarkRemoveAllMask( U32 nMarkMask ) { return __GetMarker().RemoveAll( nMarkMask ); }
		U1									MarkRemoveAll() { return __GetMarker().RemoveAll(); }
		U32									MarkGet( S32 nLine ) const { return __GetMarker().Get( nLine ); }
		S32									MarkGetNextLine( S32 nLine, U32 nMarkMask ) const { return __GetMarker().GetNextLine( nLine, nMarkMask ); }

		//====================================================================================================
		// Level

		UiCodeEditorDoc*					LevelRemoveAll() { __GetLevel().RemoveAll(); return this; }
		S32									LevelSet( S32 nLine, S32 nLevel ) { return __GetLevel().Set( nLine, nLine ); }
		S32									LevelGet( S32 nLine ) const { return __GetLevel().Get( nLine ); }

		//====================================================================================================
		// MarginText

		UiCodeEditorDoc*					MarginRemoveAll();
		UiCodeEditorDoc*					MarginSetText( S32 nLine, PCWChar szText = nullptr );
		UiCodeEditorDoc*					MarginSetStyle( S32 nLine, Ui::CodeEditorStyle nStyle );
		UiCodeEditorDoc*					MarginSetStyles( S32 nLine, const List<Ui::CodeEditorStyle>& vStyle );
		U1									MarginIsMultipleStyle( S32 nLine ) const;
		WString								MarginGetText( S32 nLine ) const;
		WString								MarginGetTextSubLine( S32 nLine, S32 nSubLine ) const;
		U32									MarginGetTextLength( S32 nLine ) const;
		U32									MarginGetTextLength( S32 nLine, S32 nSubLine ) const;
		S32									MarginGetTextLineCount( S32 nLine ) const;
		Ui::CodeEditorStyle					MarginGetStyle( S32 nLine ) const;
		List<Ui::CodeEditorStyle>			MarginGetStyles( S32 nLine ) const;
		List<Ui::CodeEditorStyle>			MarginGetStylesSubLine( S32 nLine, S32 nSubLine ) const;

		//====================================================================================================
		// Annotation

		UiCodeEditorDoc*					AnnoRemoveAll();
		UiCodeEditorDoc*					AnnoSetText( S32 nLine, PCWChar szText = nullptr );
		UiCodeEditorDoc*					AnnoSetStyle( S32 nLine, Ui::CodeEditorStyle nStyle );
		UiCodeEditorDoc*					AnnoSetStyles( S32 nLine, const List<Ui::CodeEditorStyle>& vStyle );
		U1									AnnoIsMultipleStyle( S32 nLine ) const;
		WString								AnnoGetText( S32 nLine ) const;
		WString								AnnoGetTextSubLine( S32 nLine, S32 nSubLine ) const;
		U32									AnnoGetTextLength( S32 nLine ) const;
		U32									AnnoGetTextLength( S32 nLine, S32 nSubLine ) const;
		S32									AnnoGetTextLineCount( S32 nLine ) const;
		Ui::CodeEditorStyle					AnnoGetStyle( S32 nLine ) const;
		List<Ui::CodeEditorStyle>			AnnoGetStyles( S32 nLine ) const;
		List<Ui::CodeEditorStyle>			AnnoGetStylesSubLine( S32 nLine, S32 nSubLine ) const;

		//====================================================================================================
		// Syntax

		UiCodeEditorDoc*					SetSyntax( Syntax_t&& fnLexer, Syntax_t&& fnFolder );

	public:
		void								SetDoc( Ui::ICodeEditorDoc* p );
	};
}
