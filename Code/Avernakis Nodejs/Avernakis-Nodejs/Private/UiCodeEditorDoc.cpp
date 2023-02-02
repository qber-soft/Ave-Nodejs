#include "StdAfx.h"
#include "UiCodeEditorDoc.h"

#define ThisMethod($x) &UiCodeEditorDoc::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, &UiCodeEditorDoc::$x )

namespace Nav
{

	namespace
	{
		ObjectRegister<UiCodeEditorDoc> c_obj;
	}

	void UiCodeEditorDoc::DefineObject()
	{
		AutoAddMethod( GetLength, WrapObjectGeneric );
		AutoAddMethod( Reset );
		AutoAddMethod( CharAt, WrapObjectGeneric );
		AutoAddMethod( CharGet, WrapObjectGeneric );
		AutoAddMethod( CharInsert );
		AutoAddMethod( CharRemove );
		AutoAddMethod( StyleAt, WrapObjectGeneric );
		AutoAddMethod( StyleGet, WrapObjectGeneric );
		AutoAddMethod( StyleSetAll, WrapObjectGeneric );
		AutoAddMethod( StyleSet );
		AutoAddMethod( StyleStart, WrapObjectGeneric );
		AutoAddMethod( StyleFillAll );
		AutoAddMethod( StyleFill );
		AutoAddMethod( LineGetCount, WrapObjectGeneric );
		AutoAddMethod( LineIndex, WrapObjectGeneric );
		AutoAddMethod( LineStart, WrapObjectGeneric );
		AutoAddMethod( LineEnd, WrapObjectGeneric );
		AutoAddMethod( LineEnding, WrapObjectGeneric );
		AutoAddMethod( GetReadOnly, WrapObjectGeneric );
		AutoAddMethod( SetReadOnly, WrapObjectGeneric );
		AutoAddMethod( GetDefaultLineEnding, WrapObjectGeneric );
		AutoAddMethod( SetDefaultLineEnding, WrapObjectGeneric );
		AutoAddMethod( OpSetEnable, WrapObjectGeneric );
		AutoAddMethod( OpGetEnable, WrapObjectGeneric );
		AutoAddMethod( OpSetSavePoint, WrapObjectGeneric );
		AutoAddMethod( OpIsSavePoint, WrapObjectGeneric );
		AutoAddMethod( OpGetUndoCount, WrapObjectGeneric );
		AutoAddMethod( OpGetRedoCount, WrapObjectGeneric );
		AutoAddMethod( OpGetUndoRecord, WrapObjectGeneric );
		AutoAddMethod( OpGetRedoRecord, WrapObjectGeneric );
		AutoAddMethod( OpClear );
		AutoAddMethod( OpUndo );
		AutoAddMethod( OpRedo );
		//AutoAddMethod( OpBeginOperationGroup );
		//AutoAddMethod( OpEndOperationGroup );
		//AutoAddMethod( OpAddCustomOperation );
		AutoAddMethod( MarkAdd );
		AutoAddMethod( MarkAddMask );
		AutoAddMethod( MarkRemove );
		AutoAddMethod( MarkRemoveMask );
		AutoAddMethod( MarkRemoveLine );
		AutoAddMethod( MarkRemoveAllMask );
		AutoAddMethod( MarkRemoveAll );
		AutoAddMethod( MarkGet, WrapObjectGeneric );
		AutoAddMethod( MarkGetNextLine, WrapObjectGeneric );
		AutoAddMethod( LevelRemoveAll );
		AutoAddMethod( LevelSet );
		AutoAddMethod( LevelGet, WrapObjectGeneric );
	}

	void UiCodeEditorDoc::SetDoc( Ui::ICodeEditorDoc * p )
	{
		m_Doc = p;
	}

	List<UiCodeEditorOpItem_t> UiCodeEditorDoc::OpGetUndoRecord( U32 nIndex, U32 nCount ) const
	{
		List<UiCodeEditorOpItem_t> v;
		List<Ui::CodeEditorOpItem> vt( nCount );
		vt.Resize( __GetOp().GetUndoRecord( vt.Data(), nIndex, nCount ) );
		v.Resize( vt.Size() );
		for ( auto& i : vt.RangeIndexAll() )
		{
			v[i.Index].m_Type = i->m_Type;
			v[i.Index].m_String = WString( i->m_String, i->m_CharLength );
		}
		return std::move( v );
	}

	List<UiCodeEditorOpItem_t> UiCodeEditorDoc::OpGetRedoRecord( U32 nIndex, U32 nCount ) const
	{
		List<UiCodeEditorOpItem_t> v;
		List<Ui::CodeEditorOpItem> vt( nCount );
		vt.Resize( __GetOp().GetRedoRecord( vt.Data(), nIndex, nCount ) );
		v.Resize( vt.Size() );
		for ( auto& i : vt.RangeIndexAll() )
		{
			v[i.Index].m_Type = i->m_Type;
			v[i.Index].m_String = WString( i->m_String, i->m_CharLength );
		}
		return std::move( v );
	}

}
