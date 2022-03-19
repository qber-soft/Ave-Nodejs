#pragma once

#include "WrapBase.h"

namespace Nav
{

	namespace __Detail
	{
		class __DataField
		{
		public:
			PCAChar		m_Name;
			USize		m_Offset;
			U1( *m_Check )(const Napi::Value&);
			void(*m_ToCpp)(void*, const Napi::Value&);
			Napi::Value( *m_ToJs )(Napi::Env, const void*);
		};
	}

	template<class TData>
	class WrapDataDefine;

	template<class TData>
	class WrapData;

	template<class TData>
	class WrapDataBase
	{
		friend class WrapData<TData>;

	protected:
		WrapDataBase() {}
		~WrapDataBase() {}

	private:
		static List<__Detail::__DataField> s_Field;

		class InitField
		{
		public:
			InitField() { WrapDataDefine<TData>::DefineData(); }
		};

	protected:
		static U1 __Check( const Napi::Object& obj )
		{
			for ( auto& i : s_Field )
			{
				auto v = obj.Get( i.m_Name );
				if ( !i.m_Check( v ) )
					return false;
			}
			return true;
		}

		static void __SetData( TData& p, const Napi::Object& obj )
		{
			for ( auto& i : s_Field )
				(*i.m_ToCpp)((U8*) &p + i.m_Offset, obj.Get( i.m_Name ));
		}

		static Napi::Value __GetData( const TData& p, Napi::Env env )
		{
			auto obj = Napi::Object::New( env );
			for ( auto& i : s_Field )
			{
				auto v = (*i.m_ToJs)(env, (U8*) &p + i.m_Offset);
				obj.Set( i.m_Name, v );
			}
			return obj;
		}

		static void __Init()
		{
			static InitField __Init;
		}

	protected:
		template<class T, typename std::enable_if<!std::is_enum<T>::value, S32>::type = 0>
		static void AddField( PCAChar szName, T TData::* p )
		{
			__Detail::__DataField df{};
			df.m_Name = szName;
			df.m_Offset = (USize) & (((TData*) nullptr)->*p);
			df.m_Check = &__Detail::__CheckType<T>::Check;
			df.m_ToCpp = &__Detail::__ConvertType<T>::ToCpp;
			df.m_ToJs = &__Detail::__ConvertType<T>::ToJs;
			s_Field.Add( df );
		}

		template<class T, USize TCount, typename std::enable_if<!std::is_enum<T>::value, S32>::type = 0>
		static void AddField( PCAChar szName, T( TData::*p )[TCount], USize n )
		{
			__Detail::__DataField df{};
			df.m_Name = szName;
			df.m_Offset = (USize) & ((((TData*) nullptr)->*p)[n]);
			df.m_Check = &__Detail::__CheckType<T>::Check;
			df.m_ToCpp = &__Detail::__ConvertType<T>::ToCpp;
			df.m_ToJs = &__Detail::__ConvertType<T>::ToJs;
			s_Field.Add( df );
		}

		template<class T, typename std::enable_if<std::is_enum<T>::value && sizeof( U32 ) == sizeof( T ), S32>::type = 0>
		static void AddField( PCAChar szName, T TData::* p )
		{
			__Detail::__DataField df{};
			df.m_Name = szName;
			df.m_Offset = (USize) & (((TData*) nullptr)->*p);
			df.m_Check = &__Detail::__CheckType<U32>::Check;
			df.m_ToCpp = &__Detail::__ConvertType<U32>::ToCpp;
			df.m_ToJs = &__Detail::__ConvertType<U32>::ToJs;
			s_Field.Add( df );
		}
	};

	template<class TData>
	List<__Detail::__DataField> WrapDataBase<TData>::s_Field;

	template<class TData>
	class WrapDataTransit : WrapDataBase<TData>
	{
		friend class WrapData<TData>;
	};

	template<class TData, class TTransit>
	class WrapDataTransitHelper : WrapDataBase<TTransit>
	{
		friend class WrapData<TData>;

		static void __Init()
		{
			WrapDataBase<TTransit>::__Init();
		}

		static void __SetData( TData& p, const Napi::Object& obj )
		{
			TTransit t;
			WrapDataBase<TTransit>::__SetData( t, obj );
			WrapDataTransit<TData>::Transit( p, t );
		}

		static Napi::Value __GetData( const TData& p, Napi::Env env )
		{
			TTransit t;
			WrapDataTransit<TData>::Transit( t, p );
			return WrapDataBase<TTransit>::__GetData( t, env );
		}
	};

	template<class TData>
	class WrapData final : public TData
	{
		friend class __Detail::__CheckType<WrapData>;
		friend class __Detail::__CheckType<const WrapData&>;
		friend class __Detail::__ConvertType<WrapData>;
		friend class __Detail::__ConvertType<const WrapData&>;

	public:
		WrapData()
		{
			WrapDataTransit<TData>::__Init();
		}

		WrapData( const TData& r )
		{
			WrapDataTransit<TData>::__Init();
			(TData&) *this = r;
		}

		~WrapData() {}

	private:
		class DataField
		{
		public:
			PCAChar		m_Name;
			USize		m_Offset;
			U1( *m_Check )(const Napi::Value&);
			void(*m_ToCpp)(void*, const Napi::Value&);
			Napi::Value( *m_ToJs )(Napi::Env, const void*);
		};

	private:
		static AveInline U1 __Check( const Napi::Object& obj )
		{
			WrapDataTransit<TData>::__Init();
			return WrapDataTransit<TData>::__Check( obj );
		}

		AveInline void __SetData( const Napi::Object& obj )
		{
			WrapDataTransit<TData>::__SetData( *this, obj );
		}

		AveInline Napi::Value __GetData( Napi::Env env )
		{
			return WrapDataTransit<TData>::__GetData( *this, env );
		}
	};

#define AveMacroExpand(...) __VA_ARGS__
#define AveMacroParamCounter($1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21,$22,$23,$24,$25,$26,$27,$28,$29,$30,$31,$32,$n, ...) $n
#define AveMacroParamCount(...) AveMacroExpand(AveMacroParamCounter(__VA_ARGS__,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
#define __AveMacroConnect($x,$y) $x##$y
#define AveMacroConnect($x,$y) __AveMacroConnect($x,$y)

#define ___$ProcessField1($t,$m,$0) $m($t,$0)
#define ___$ProcessField2($t,$m,$0,$1) $m($t,$0) $m($t,$1)
#define ___$ProcessField3($t,$m,$0,$1,$2) $m($t,$0) $m($t,$1) $m($t,$2)
#define ___$ProcessField4($t,$m,$0,$1,$2,$3) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3)
#define ___$ProcessField5($t,$m,$0,$1,$2,$3,$4) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4)
#define ___$ProcessField6($t,$m,$0,$1,$2,$3,$4,$5) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5)
#define ___$ProcessField7($t,$m,$0,$1,$2,$3,$4,$5,$6) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6)
#define ___$ProcessField8($t,$m,$0,$1,$2,$3,$4,$5,$6,$7) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7)
#define ___$ProcessField9($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8)
#define ___$ProcessField10($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9)
#define ___$ProcessField11($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10)
#define ___$ProcessField12($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11)
#define ___$ProcessField13($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12)
#define ___$ProcessField14($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13)
#define ___$ProcessField15($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14)
#define ___$ProcessField16($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15)
#define ___$ProcessField17($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16)
#define ___$ProcessField18($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17)
#define ___$ProcessField19($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17) $m($t,$18)
#define ___$ProcessField20($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17) $m($t,$18) $m($t,$19)
#define ___$ProcessField21($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17) $m($t,$18) $m($t,$19) $m($t,$20)
#define ___$ProcessField22($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17) $m($t,$18) $m($t,$19) $m($t,$20) $m($t,$21)
#define ___$ProcessField23($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21,$22) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17) $m($t,$18) $m($t,$19) $m($t,$20) $m($t,$21) $m($t,$22)
#define ___$ProcessField24($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21,$22,$23) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17) $m($t,$18) $m($t,$19) $m($t,$20) $m($t,$21) $m($t,$22) $m($t,$23)
#define ___$ProcessField25($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21,$22,$23,$24) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17) $m($t,$18) $m($t,$19) $m($t,$20) $m($t,$21) $m($t,$22) $m($t,$23) $m($t,$24)
#define ___$ProcessField26($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21,$22,$23,$24,$25) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17) $m($t,$18) $m($t,$19) $m($t,$20) $m($t,$21) $m($t,$22) $m($t,$23) $m($t,$24) $m($t,$25)
#define ___$ProcessField27($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21,$22,$23,$24,$25,$26) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17) $m($t,$18) $m($t,$19) $m($t,$20) $m($t,$21) $m($t,$22) $m($t,$23) $m($t,$24) $m($t,$25) $m($t,$26)
#define ___$ProcessField28($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21,$22,$23,$24,$25,$26,$27) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17) $m($t,$18) $m($t,$19) $m($t,$20) $m($t,$21) $m($t,$22) $m($t,$23) $m($t,$24) $m($t,$25) $m($t,$26) $m($t,$27)
#define ___$ProcessField29($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21,$22,$23,$24,$25,$26,$27,$28) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17) $m($t,$18) $m($t,$19) $m($t,$20) $m($t,$21) $m($t,$22) $m($t,$23) $m($t,$24) $m($t,$25) $m($t,$26) $m($t,$27) $m($t,$28)
#define ___$ProcessField30($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21,$22,$23,$24,$25,$26,$27,$28,$29) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17) $m($t,$18) $m($t,$19) $m($t,$20) $m($t,$21) $m($t,$22) $m($t,$23) $m($t,$24) $m($t,$25) $m($t,$26) $m($t,$27) $m($t,$28) $m($t,$29)
#define ___$ProcessField31($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21,$22,$23,$24,$25,$26,$27,$28,$29,$30) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17) $m($t,$18) $m($t,$19) $m($t,$20) $m($t,$21) $m($t,$22) $m($t,$23) $m($t,$24) $m($t,$25) $m($t,$26) $m($t,$27) $m($t,$28) $m($t,$29) $m($t,$30)
#define ___$ProcessField32($t,$m,$0,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21,$22,$23,$24,$25,$26,$27,$28,$29,$30,$31) $m($t,$0) $m($t,$1) $m($t,$2) $m($t,$3) $m($t,$4) $m($t,$5) $m($t,$6) $m($t,$7) $m($t,$8) $m($t,$9) $m($t,$10) $m($t,$11) $m($t,$12) $m($t,$13) $m($t,$14) $m($t,$15) $m($t,$16) $m($t,$17) $m($t,$18) $m($t,$19) $m($t,$20) $m($t,$21) $m($t,$22) $m($t,$23) $m($t,$24) $m($t,$25) $m($t,$26) $m($t,$27) $m($t,$28) $m($t,$29) $m($t,$30) $m($t,$31)
#define ___$ProcessFields($t,$m,...) AveMacroExpand(AveMacroConnect(___$ProcessField,AveMacroParamCount(__VA_ARGS__))($t,$m,__VA_ARGS__))


#define ___$AddField0$___($t,$x) AddField( #$x, &$t::$x );
#define ___$AddField1$___($t,$x) AddField( #$x, &$t::m_##$x );
#define NavDefineDataByMember($type, ...) template<> class WrapDataDefine<$type> : WrapDataBase<$type> { public: static void DefineData() { ___$ProcessFields( $type, ___$AddField0$___, __VA_ARGS__ ); } };
#define NavDefineDataByMember_($type, ...) template<> class WrapDataDefine<$type> : WrapDataBase<$type> { public: static void DefineData() { ___$ProcessFields( $type, ___$AddField1$___, __VA_ARGS__ ); } };


#define ___$TransitField0$___($t,$x) d.$x = s.$x;
#define ___$TransitField1$___($t,$x) d.m_##$x = s.m_##$x;
#define ___$TransitField2$___($t,$x) d.$x = (decltype(d.$x)) s.$x;
#define ___$TransitField3$___($t,$x) d.m_##$x = (decltype(d.m_##$x)) s.m_##$x;
#define NavDefineTransitByMember($type, $intertype, ...) template<> class WrapDataTransit<$type> : public WrapDataTransitHelper<$type, $intertype> { public: template<class T, class U> static void Transit( T& d, const U& s ) { ___$ProcessFields( , ___$TransitField0$___, __VA_ARGS__ ); } };
#define NavDefineTransitByMember_($type, $intertype, ...) template<> class WrapDataTransit<$type> : public WrapDataTransitHelper<$type, $intertype> { public: template<class T, class U> static void Transit( T& d, const U& s ) { ___$ProcessFields( , ___$TransitField1$___, __VA_ARGS__ ); } };
#define NavDefineTransitByMemberC($type, $intertype, ...) template<> class WrapDataTransit<$type> : public WrapDataTransitHelper<$type, $intertype> { public: template<class T, class U> static void Transit( T& d, const U& s ) { ___$ProcessFields( , ___$TransitField2$___, __VA_ARGS__ ); } };
#define NavDefineTransitByMemberC_($type, $intertype, ...) template<> class WrapDataTransit<$type> : public WrapDataTransitHelper<$type, $intertype> { public: template<class T, class U> static void Transit( T& d, const U& s ) { ___$ProcessFields( , ___$TransitField3$___, __VA_ARGS__ ); } };
#define NavDefineTransitByMemberIn_($type, $intertype, ...) template<> class WrapDataTransit<$type> : public WrapDataTransitHelper<$type, $intertype> { public: static void Transit( $type& d, const $intertype& s ) { ___$ProcessFields( , ___$TransitField1$___, __VA_ARGS__ ); } static void Transit( $intertype& d, const $type& s ); };
#define NavDefineTransitByMemberOut_($type, $intertype, ...) template<> class WrapDataTransit<$type> : public WrapDataTransitHelper<$type, $intertype> { public: static void Transit( $intertype& d, const $type& s ) { ___$ProcessFields( , ___$TransitField1$___, __VA_ARGS__ ); } static void Transit( $type& d, const $intertype& s ); };

}
