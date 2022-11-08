#pragma once

#include "UiVisualHelper.h"

namespace Nav
{

	class UiRichLabelColor
	{
	public:
		WrapData<U8_4>					m_Color;

		List<WrapData<R32_R>>			m_Rect;
		WrapData<R32_2>					m_Scaling;
		R32								m_RectSpeed;
		R32								m_PhaseSpeed;

		void Reset()
		{
			m_Color = NT<U8_4>::Zero;
			m_Rect.Clear();
			m_Scaling = NT<R32_2>::Zero;
			m_RectSpeed = 0.f;
			m_PhaseSpeed = 0.f;
		}

		void ToAve( Ui::RichLabelColor& d ) const
		{
			d.m_Color = m_Color;
			d.m_RectCount = Math::Min( (S32) m_Rect.Size(), (S32) CountOf( d.m_Rect ) );
			for ( S32 i = 0; i < d.m_RectCount; ++i )
				d.m_Rect[i] = m_Rect[i];
			d.m_Scaling = m_Scaling;
			d.m_RectSpeed = m_RectSpeed;
			d.m_PhaseSpeed = m_PhaseSpeed;
		}

		void FromAve( const Ui::RichLabelColor& d )
		{
			m_Color = d.m_Color;
			m_Rect.Resize( d.m_RectCount );
			for ( S32 i = 0; i < d.m_RectCount; ++i )
				m_Rect[i] = d.m_Rect[i];
			m_Scaling = d.m_Scaling;
			m_RectSpeed = d.m_RectSpeed;
			m_PhaseSpeed = d.m_PhaseSpeed;
		}
	};
	NavDefineDataByMember_( UiRichLabelColor, Color, Rect, Scaling, RectSpeed, PhaseSpeed );
	using UiRichLabelColor_t = WrapData<UiRichLabelColor>;

	class UiRichLabelTextColor
	{
	public:
		UiRichLabelColor_t				m_Text; // a==0: use Label default text color
		UiRichLabelColor_t				m_Border;
		UiRichLabelColor_t				m_Shadow;
	};
	NavDefineDataByMember_( UiRichLabelTextColor, Text, Border, Shadow );
	using UiRichLabelTextColor_t = WrapData<UiRichLabelTextColor>;

	template<>
	class WrapDataTransit<Ui::RichLabelTextColor> : public WrapDataTransitHelper<Ui::RichLabelTextColor, UiRichLabelTextColor>
	{
	public:
		static void Transit( Ui::RichLabelTextColor& d, const UiRichLabelTextColor& s )
		{
			s.m_Text.ToAve( d.m_Text );
			s.m_Border.ToAve( d.m_Border );
			s.m_Shadow.ToAve( d.m_Shadow );
		}

		static void Transit( UiRichLabelTextColor& d, const Ui::RichLabelTextColor& s )
		{
			d.m_Text.FromAve( s.m_Text );
			d.m_Border.FromAve( s.m_Border );
			d.m_Shadow.FromAve( s.m_Shadow );
		}
	};

	class UiRichLabelBackColor
	{
	public:
		UiRichLabelColor_t				m_Color;
	};
	NavDefineDataByMember_( UiRichLabelBackColor, Color );
	using UiRichLabelBackColor_t = WrapData<UiRichLabelBackColor>;

	template<>
	class WrapDataTransit<Ui::RichLabelBackColor> : public WrapDataTransitHelper<Ui::RichLabelBackColor, UiRichLabelBackColor>
	{
	public:
		static void Transit( Ui::RichLabelBackColor& d, const UiRichLabelBackColor& s )
		{
			s.m_Color.ToAve( d.m_Color );
		}

		static void Transit( UiRichLabelBackColor& d, const Ui::RichLabelBackColor& s )
		{
			d.m_Color.FromAve( s.m_Color );
		}
	};

	NavDefineDataByMember_( Ui::RichLabelSimpleShape, Size, Offset );

	class UiRichLabelUnderline
	{
	public:
		UiRichLabelColor_t					m_Color;
		WrapData<Ui::RichLabelSimpleShape>	m_Shape;
	};
	NavDefineDataByMember_( UiRichLabelUnderline, Color, Shape );

	template<>
	class WrapDataTransit<Ui::RichLabelUnderline> : public WrapDataTransitHelper<Ui::RichLabelUnderline, UiRichLabelUnderline>
	{
	public:
		static void Transit( Ui::RichLabelUnderline& d, const UiRichLabelUnderline& s )
		{
			s.m_Color.ToAve( d.m_Color );
			d.m_Shape = s.m_Shape;
		}

		static void Transit( UiRichLabelUnderline& d, const Ui::RichLabelUnderline& s )
		{
			d.m_Color.FromAve( s.m_Color );
			d.m_Shape = s.m_Shape;
		}
	};

	class UiRichLabelStrike
	{
	public:
		WrapData<UiRichLabelColor>			m_Color;
		WrapData<Ui::RichLabelSimpleShape>	m_Shape;
	};
	NavDefineDataByMember_( UiRichLabelStrike, Color, Shape );
	using UiRichLabelStrike_t = List<WrapData<UiRichLabelStrike>>;

	class UiRichLabelEmphasis
	{
	public:
		Ui::RichLabelEmphasisType			m_Type;
		WrapData<Ui::RichLabelSimpleShape>	m_Shape;
		U1									m_Near;
		UiRichLabelColor_t					m_Color;
		Ui::IconCache						m_Icon;
	};
	NavDefineDataByMember_( UiRichLabelEmphasis, Type, Shape, Near, Color, Icon );

	template<>
	class WrapDataTransit<Ui::RichLabelEmphasis> : public WrapDataTransitHelper<Ui::RichLabelEmphasis, UiRichLabelEmphasis>
	{
	public:
		static void Transit( Ui::RichLabelEmphasis& d, const UiRichLabelEmphasis& s )
		{
			d.m_Type = s.m_Type;
			d.m_Shape = s.m_Shape;
			d.m_Near = s.m_Near;
			if ( Ui::RichLabelEmphasisType::Icon != d.m_Type )
				s.m_Color.ToAve( d.m_Color );
			else
				d.m_Icon = s.m_Icon;
		}

		static void Transit( UiRichLabelEmphasis& d, const Ui::RichLabelEmphasis& s )
		{
			d.m_Type = s.m_Type;
			d.m_Shape = s.m_Shape;
			d.m_Near = s.m_Near;
			if ( Ui::RichLabelEmphasisType::Icon != d.m_Type )
			{
				d.m_Color.FromAve( s.m_Color );
				d.m_Icon = 0;
			}
			else
			{
				d.m_Color.Reset();
				d.m_Icon = s.m_Icon;
			}
		}
	};

	class UiRichLabelTextFxColor
	{
	public:
		List<WrapData<U8_4>>			m_Color;
		R32								m_Speed;

		void Reset()
		{
			m_Color.Clear();
			m_Speed = 0.f;
		}

		void ToAve( Ui::RichLabelTextFxColor& d ) const
		{
			d.m_ColorCount = Math::Min( (S32) m_Color.Size(), (S32) CountOf( d.m_Color ) );
			for ( U32 i = 0; i < d.m_ColorCount; ++i )
				d.m_Color[i] = m_Color[i];
			d.m_Speed = m_Speed;
		}

		void FromAve( const Ui::RichLabelTextFxColor& d )
		{
			m_Color.Resize( d.m_ColorCount );
			for ( U32 i = 0; i < d.m_ColorCount; ++i )
				m_Color[i] = d.m_Color[i];
			m_Speed = d.m_Speed;
		}
	};
	NavDefineDataByMember_( UiRichLabelTextFxColor, Color, Speed );
	using UiRichLabelTextFxColor_t = WrapData<UiRichLabelTextFxColor>;

	class UiRichLabelTextTransform
	{
	public:
		WrapData<R32_2>					m_TranslationRange;
		R32								m_RotationRange;
		WrapData<R32_2>					m_ScaleRange;
		R32								m_Speed;

		void Reset()
		{
			m_TranslationRange = NT<R32_2>::Zero;
			m_RotationRange = 0.f;
			m_ScaleRange = NT<R32_2>::Zero;
			m_Speed = 0.f;
		}

		void ToAve( Ui::RichLabelTextFxTransform& d ) const
		{
			d.m_TranslationRange = m_TranslationRange;
			d.m_RotationRange = m_RotationRange;
			d.m_ScaleRange = m_ScaleRange;
			d.m_Speed = m_Speed;
		}

		void FromAve( const Ui::RichLabelTextFxTransform& d )
		{
			m_TranslationRange = d.m_TranslationRange;
			m_RotationRange = d.m_RotationRange;
			m_ScaleRange = d.m_ScaleRange;
			m_Speed = d.m_Speed;
		}
	};
	NavDefineDataByMember_( UiRichLabelTextTransform, TranslationRange, RotationRange, ScaleRange, Speed );
	using UiRichLabelTextTransform_t = WrapData<UiRichLabelTextTransform>;

	NavDefineDataByMember_( Ui::RichLabelTextWave, Frequency, Amplitude, Speed );

	class UiRichLabelTextFx
	{
	public:
		Ui::RichLabelTextFxType			m_Type;
		U32								m_CustomId;
		UiRichLabelTextFxColor_t		m_Color;
		UiRichLabelTextTransform_t		m_Transform;
		WrapData<Ui::RichLabelTextWave>	m_Wave;
	};
	NavDefineDataByMember_( UiRichLabelTextFx, Type, CustomId, Color, Transform, Wave );

	template<>
	class WrapDataTransit<Ui::RichLabelTextFx> : public WrapDataTransitHelper<Ui::RichLabelTextFx, UiRichLabelTextFx>
	{
	public:
		static void Transit( Ui::RichLabelTextFx& d, const UiRichLabelTextFx& s )
		{
			d.m_Type = s.m_Type;
			switch ( d.m_Type )
			{
			case Ui::RichLabelTextFxType::Custom: d.m_CustomId = s.m_CustomId; break;
			case Ui::RichLabelTextFxType::Color: s.m_Color.ToAve( d.m_Color ); break;
			case Ui::RichLabelTextFxType::Transform: s.m_Transform.ToAve( d.m_Transform ); break;
			case Ui::RichLabelTextFxType::Wave: d.m_Wave = s.m_Wave; break;
			}
		}

		static void Transit( UiRichLabelTextFx& d, const Ui::RichLabelTextFx& s )
		{
			d.m_Type = s.m_Type;
			d.m_CustomId = 0;
			d.m_Color.Reset();
			d.m_Transform.Reset();
			d.m_Wave = {};
			switch ( d.m_Type )
			{
			case Ui::RichLabelTextFxType::Custom: d.m_CustomId = s.m_CustomId; break;
			case Ui::RichLabelTextFxType::Color: d.m_Color.FromAve( s.m_Color ); break;
			case Ui::RichLabelTextFxType::Transform: d.m_Transform.FromAve( s.m_Transform ); break;
			case Ui::RichLabelTextFxType::Wave: d.m_Wave = s.m_Wave; break;
			}
		}
	};

	class UiRichLabelCluster
	{
	public:
		WString							m_Char;
		S32								m_CharIndex;
		S32								m_ClusterIndex;
		R32								m_Progress;

		void FromAve( const Ui::RichLabelCluster& d )
		{
			m_Char.Clear();
			m_Char.Add( d.m_Char[0] );
			if ( 2 == d.m_CharLength )
				m_Char.Add( d.m_Char[1] );
			m_CharIndex = d.m_CharIndex;
			m_ClusterIndex = d.m_ClusterIndex;
			m_Progress = d.m_Progress;
		}
	};
	NavDefineDataByMember_( UiRichLabelCluster, Char, CharIndex, ClusterIndex, Progress );
	using UiRichLabelCluster_t = WrapData<UiRichLabelCluster>;

	class UiRichLabelTransform
	{
	public:
		WrapData<R32_2>					m_Translation;
		WrapData<R32_2>					m_Scaling;
		R32								m_Rotation;
	};
	NavDefineDataByMember_( UiRichLabelTransform, Translation, Scaling, Rotation );
	using UiRichLabelTransform_t = WrapData<UiRichLabelTransform>;

	class UiRichLabelDisplay
	{
	public:
		UiRichLabelTransform_t			m_Transform;
		UiRichLabelTextColor_t			m_TextColor;
		UiRichLabelBackColor_t			m_BackColor;
		R32								m_Opacity;

		void ToAve( Ui::RichLabelDisplay& d ) const
		{
			d.m_Transform.m_Translation = m_Transform.m_Translation;
			d.m_Transform.m_Scaling = m_Transform.m_Scaling;
			d.m_Transform.m_Rotation = m_Transform.m_Rotation;
			m_TextColor.m_Text.ToAve( d.m_TextColor.m_Text );
			m_TextColor.m_Border.ToAve( d.m_TextColor.m_Border );
			m_TextColor.m_Shadow.ToAve( d.m_TextColor.m_Shadow );
			m_BackColor.m_Color.ToAve( d.m_BackColor.m_Color );
			d.m_Opacity = m_Opacity;
		}

		void FromAve( const Ui::RichLabelDisplay& d )
		{
			m_Transform.m_Translation = d.m_Transform.m_Translation;
			m_Transform.m_Scaling = d.m_Transform.m_Scaling;
			m_Transform.m_Rotation = d.m_Transform.m_Rotation;
			m_TextColor.m_Text.FromAve( d.m_TextColor.m_Text );
			m_TextColor.m_Border.FromAve( d.m_TextColor.m_Border );
			m_TextColor.m_Shadow.FromAve( d.m_TextColor.m_Shadow );
			m_BackColor.m_Color.FromAve( d.m_BackColor.m_Color );
			m_Opacity = d.m_Opacity;
		}
	};
	NavDefineDataByMember_( UiRichLabelDisplay, Transform, TextColor, BackColor, Opacity );
	using UiRichLabelDisplay_t = WrapData<UiRichLabelDisplay>;

	class UiRichLabelCustomDisplay
	{
	public:
		List<UiRichLabelCluster_t>		m_Cluster;
		List<UiRichLabelDisplay_t>		m_Display;

		S32								m_TotalChar;
		S32								m_TotalCluster;

		R64								m_Time;
		R32								m_FrameTime;

		void FromAve( const Ui::RichLabelCustomDisplay& d )
		{
			m_Cluster.Resize( d.m_Count );
			m_Display.Resize( d.m_Count );
			for ( U32 i = 0; i < d.m_Count; ++i )
			{
				m_Cluster[i].FromAve( d.m_Cluster[i] );
				m_Display[i].FromAve( d.m_Display[i] );
			}
			m_TotalChar = d.m_TotalChar;
			m_TotalCluster = d.m_TotalCluster;
			m_Time = d.m_Time;
			m_FrameTime = d.m_FrameTime;
		}
	};
	NavDefineDataByMember_( UiRichLabelCustomDisplay, Cluster, Display, TotalChar, TotalCluster, Time, FrameTime );
	using RichLabelCustomDisplay_t = WrapData<UiRichLabelCustomDisplay>;

	class UiRichLabelQueryVariable
	{
	public:
		U1								m_IsName;
		U32								m_Id{ 0 };
		WString							m_Name;

		void FromAve( const Ui::RichLabelQueryVariable& d )
		{
			m_IsName = d.m_IsName;
			if ( m_IsName )
				m_Name = d.m_Name;
			else
				m_Id = d.m_Id;
		}
	};
	NavDefineDataByMember_( UiRichLabelQueryVariable, IsName, Id, Name );
	using UiRichLabelQueryVariable_t = WrapData<UiRichLabelQueryVariable>;

	class ImgImage;
	class Byo2Image;

	class UiRichLabel : public UiVisualHelper<UiRichLabel, Ui::IRichLabel>
	{
	public:
		AveWrapVisual( UiRichLabel );

		~UiRichLabel()
		{
		}

		static PCAChar					GetExportName() { return "UiRichLabel"; }
		static void						DefineControl();

		U1								Ctor( UiWindow* p, Napi::Value v );

	private:
		using OnQueryIconId_t			/**/ = JsFuncSafe<U32( UiRichLabel* sender, WString szName )>;
		using OnQueryVariable_t			/**/ = JsFuncSafe<WString( UiRichLabel* sender, const UiRichLabelQueryVariable_t& qv )>;
		using OnCustomTextFx_t			/**/ = JsFuncSafe<List<UiRichLabelDisplay_t>( UiRichLabel* sender, U32 nId, const RichLabelCustomDisplay_t& cd )>;
		using OnCustomPlay_t			/**/ = JsFuncSafe<List<UiRichLabelDisplay_t>( UiRichLabel* sender, const RichLabelCustomDisplay_t& cd )>;

		OnCustomTextFx_t				m_OnCustomTextFx;
		OnQueryIconId_t					m_OnQueryIconId;
		OnQueryVariable_t				m_OnQueryVariable;
		OnCustomPlay_t					m_OnCustomPlay;

		WString							m_QueryVariableResult;

		U32								__OnQueryIconId( Ui::IRichLabel& sender, PCWChar szName );
		PCWChar							__OnQueryVariable( Ui::IRichLabel& sender, const Ui::RichLabelQueryVariable& qv );
		void							__OnCustomTextFx( Ui::IRichLabel& sender, U32 nId, Ui::RichLabelCustomDisplay& cd );
		void							__OnCustomPlay( Ui::IRichLabel& sender, const Ui::RichLabelCustomDisplay& cd );

	private:
		UiRichLabel*					SetText( PCWChar szText ) { GetControlTyped().SetText( szText ? szText : AveWide( "" ) ); return this; }
		WString							GetText() const { return GetControlTyped().GetText(); }
		WString							GetTextData() const { return GetControlTyped().GetTextData(); }
		U1								IsTextValid() const { return GetControlTyped().IsTextValid(); }
		U1								Recompile() { return GetControlTyped().Recompile(); }

		UiRichLabel*					SetAlignHorz( Ui::AlignType nAlign ) { GetControlTyped().SetAlignHorz( nAlign ); return this; }
		Ui::AlignType					GetAlignHorz() const { return GetControlTyped().GetAlignHorz(); }

		UiRichLabel*					SetAlignVert( Ui::AlignType nAlign ) { GetControlTyped().SetAlignVert( nAlign ); return this; }
		Ui::AlignType					GetAlignVert() const { return GetControlTyped().GetAlignVert(); }

		UiRichLabel*					SetWrappable( U1 b ) { GetControlTyped().SetWrappable( b ); return this; }
		U1								GetWrappable() const { return GetControlTyped().GetWrappable(); }


		UiRichLabel*					FmReset( U32 nReset ) { GetControlTyped().FmReset( nReset ); return this; }

		UiRichLabel*					FmSetDefaultTextColor( const WrapData<Ui::RichLabelTextColor>& v ) { GetControlTyped().FmSetDefaultTextColor( v ); return this; }
		WrapData<Ui::RichLabelTextColor>FmGetDefaultTextColor() const { return GetControlTyped().FmGetDefaultTextColor(); }

		UiRichLabel*					FmSetDefaultBackColor( const WrapData<Ui::RichLabelBackColor>& v ) { GetControlTyped().FmSetDefaultBackColor( v ); return this; }
		WrapData<Ui::RichLabelBackColor>FmGetDefaultBackColor() const { return GetControlTyped().FmGetDefaultBackColor(); }

		UiRichLabel*					FmSetDefaultFont( WrapPointer<Byo2Font> pFont );
		Byo2Font*						FmGetDefaultFont( const CallbackInfo& ci ) const;

		UiRichLabel*					FmSetRubyFont( WrapPointer<Byo2Font> pFont );
		Byo2Font*						FmGetRubyFont( const CallbackInfo& ci ) const;

		UiRichLabel*					FmSetRubyForceSpace( U1 b ) { GetControlTyped().FmSetRubyForceSpace( b ); return this; }
		U1								FmGetRubyForceSpace() const { return GetControlTyped().FmGetRubyForceSpace(); }

		UiRichLabel*					FmSetRubyTextColor( const WrapData<Ui::RichLabelTextColor>& v ) { GetControlTyped().FmSetRubyTextColor( v ); return this; }
		WrapData<Ui::RichLabelTextColor>FmGetRubyTextColor() const { return GetControlTyped().FmGetRubyTextColor(); }

		UiRichLabel*					FmSetRubyBackColor( const WrapData<Ui::RichLabelBackColor>& v ) { GetControlTyped().FmSetRubyBackColor( v ); return this; }
		WrapData<Ui::RichLabelBackColor>FmGetRubyBackColor() const { return GetControlTyped().FmGetRubyBackColor(); }

		UiRichLabel*					FmSetSScriptSize( R32 fRatio ) { GetControlTyped().FmSetSScriptSize( fRatio ); return this; }
		R32								FmGetSScriptSize() const { return GetControlTyped().FmGetSScriptSize(); }

		UiRichLabel*					FmSetBorderOffset( const WrapData<Ui::DpiSize>& fSize ) { GetControlTyped().FmSetBorderOffset( fSize ); return this; }
		WrapData<Ui::DpiSize>			FmGetBorderOffset() const { return GetControlTyped().FmGetBorderOffset(); }

		UiRichLabel*					FmSetShadowOffset( const WrapData<Ui::DpiSize>& fSize ) { GetControlTyped().FmSetShadowOffset( fSize ); return this; }
		WrapData<Ui::DpiSize>			FmGetShadowOffset() const { return GetControlTyped().FmGetShadowOffset(); }

		UiRichLabel*					FmSetEmphasisNearSpace( const WrapData<Ui::DpiSize>& fSize ) { GetControlTyped().FmSetEmphasisNearSpace( fSize ); return this; }
		WrapData<Ui::DpiSize>			FmGetEmphasisNearSpace() const { return GetControlTyped().FmGetEmphasisNearSpace(); }

		UiRichLabel*					FmSetEmphasisFarSpace( const WrapData<Ui::DpiSize>& fSize ) { GetControlTyped().FmSetEmphasisFarSpace( fSize ); return this; }
		WrapData<Ui::DpiSize>			FmGetEmphasisFarSpace() const { return GetControlTyped().FmGetEmphasisFarSpace(); }

		UiRichLabel*					FmSetMaskResource( const WrapData<IoResourceSource>& rs ) { GetControlTyped().FmSetMask( rs.ToResourceSource() ); return this; }
		UiRichLabel*					FmSetMaskImageData( ImgImage* img );
		UiRichLabel*					FmSetMaskImage( Byo2Image* img );

		UiRichLabel*					FmSetUnderline( U32 nIndex, const WrapData<Ui::RichLabelUnderline>& p ) { GetControlTyped().FmSetUnderline( nIndex, p ); return this; }
		WrapData<Ui::RichLabelUnderline>FmGetUnderline( U32 nIndex ) const { return GetControlTyped().FmGetUnderline( nIndex ); }

		UiRichLabel*					FmSetStrikethrough( U32 nIndex, const UiRichLabelStrike_t& p );
		UiRichLabelStrike_t				FmGetStrikethrough( U32 nIndex );

		UiRichLabel*					FmSetEmphasis( U32 nIndex, const WrapData<Ui::RichLabelEmphasis>& p ) { GetControlTyped().FmSetEmphasis( nIndex, p ); return this; }
		WrapData<Ui::RichLabelEmphasis>	FmGetEmphasis( U32 nIndex ) const { return GetControlTyped().FmGetEmphasis( nIndex ); }

		UiRichLabel*					FmSetTextColor( U32 nIndex, const WrapData<Ui::RichLabelTextColor>& p, Nullable<PCWChar> szName ) { GetControlTyped().FmSetTextColor( nIndex, p, szName ); return this; }
		WrapData<Ui::RichLabelTextColor>FmGetTextColor( U32 nIndex ) const { return GetControlTyped().FmGetTextColor( nIndex ); }
		WrapData<Ui::RichLabelTextColor>FmGetTextColorByName( PCWChar szName ) const { if ( szName ) if ( auto p = GetControlTyped().FmGetTextColor( szName ) ) return *p; return nullptr; }

		UiRichLabel*					FmSetBackColor( U32 nIndex, const WrapData<Ui::RichLabelBackColor>& p, Nullable<PCWChar> szName ) { GetControlTyped().FmSetBackColor( nIndex, p, szName ); return this; }
		WrapData<Ui::RichLabelBackColor>FmGetBackColor( U32 nIndex ) const { return GetControlTyped().FmGetBackColor( nIndex ); }
		WrapData<Ui::RichLabelBackColor>FmGetBackColorByName( PCWChar szName ) const { if ( szName ) if ( auto p = GetControlTyped().FmGetBackColor( szName ) ) return *p; return nullptr; }

		UiRichLabel*					FmSetTextFont( U32 nIndex, WrapPointer<Byo2Font> p, Nullable<PCWChar> szName );
		Byo2Font*						FmGetTextFont( const CallbackInfo& ci, U32 nIndex ) const;
		Byo2Font*						FmGetTextFontByName( const CallbackInfo& ci, PCWChar szName ) const;

		UiRichLabel*					FmSetTextEffect( U32 nIndex, const WrapData<Ui::RichLabelTextFx>& p, Nullable<PCWChar> szName ) { GetControlTyped().FmSetTextEffect( nIndex, p, szName ); return this; }
		WrapData<Ui::RichLabelTextFx>	FmGetTextEffect( U32 nIndex ) const { return GetControlTyped().FmGetTextEffect( nIndex ); }
		WrapData<Ui::RichLabelTextFx>	FmGetTextEffectByName( PCWChar szName ) const { if ( szName ) if ( auto p = GetControlTyped().FmGetTextEffect( szName ) ) return *p; return nullptr; }
		UiRichLabel*					FmSetTextEffectCustom( OnCustomTextFx_t&& fn );

		UiRichLabel*					IconClear() { GetControlTyped().IconClear(); return this; }
		UiRichLabel*					IconSetId( PCWChar szName, U32 nId ) { GetControlTyped().IconSetId( szName, nId ); return this; }
		U32								IconGetId( PCWChar szName ) const { return GetControlTyped().IconGetId( szName ); }
		UiRichLabel*					IconRemoveId( PCWChar szName ) { GetControlTyped().IconRemoveId( szName ); return this; }
		UiRichLabel*					IconClearOffset() { GetControlTyped().IconClearOffset(); return this; }
		UiRichLabel*					IconRemoveOffset( U32 nId ) { GetControlTyped().IconRemoveOffset( nId ); return this; }
		UiRichLabel*					IconSetOffset( U32 nId, const WrapData<Ui::DpiSize>& nOffset ) { GetControlTyped().IconSetOffset( nId, nOffset ); return this; }
		WrapData<Ui::DpiSize>			IconGetOffset( U32 nId ) const { return GetControlTyped().IconGetOffset( nId ); }
		UiRichLabel*					IconSetManager( OnQueryIconId_t&& fn );

		UiRichLabel*					IconSetDefaultSize( S32 nSizeOn100Percent ) { GetControlTyped().IconSetDefaultSize( nSizeOn100Percent ); return this; }
		S32								IconGetDefaultSize() const { return GetControlTyped().IconGetDefaultSize(); }

		UiRichLabel*					VaClear() { GetControlTyped().VaClear(); return this; }
		UiRichLabel*					VaSetById( U32 nId, Nullable<PCWChar> szText ) { GetControlTyped().VaSet( nId, szText ); return this; }
		WString							VaGetById( U32 nId ) const { if ( auto p = GetControlTyped().VaGet( nId ) ) return p; return AveWide( "" ); }
		UiRichLabel*					VaSetByName( PCWChar szName, Nullable<PCWChar> szText ) { GetControlTyped().VaSet( szName, szText ); return this; }
		WString							VaGetByName( PCWChar szName ) const { if ( auto p = GetControlTyped().VaGet( szName ) ) return p; return AveWide( "" ); }
		UiRichLabel*					VaSetManager( OnQueryVariable_t&& fn );

		UiRichLabel*					PlStart() { GetControlTyped().PlStart(); return this; }
		UiRichLabel*					PlStop() { GetControlTyped().PlStop(); return this; }
		U1								PlIsPlaying() const { return GetControlTyped().PlIsPlaying(); }

		UiRichLabel*					PlSetPosition( R32 fPercent ) { GetControlTyped().PlSetPosition( fPercent ); return this; }
		R32								PlGetPosition() const { return GetControlTyped().PlGetPosition(); }

		UiRichLabel*					PlSetAdvanceSpeed( R32 fClusterPerSecond ) { GetControlTyped().PlSetAdvanceSpeed( fClusterPerSecond ); return this; }
		R32								PlGetAdvanceSpeed() const { return GetControlTyped().PlGetAdvanceSpeed(); }

		UiRichLabel*					PlSetClusterSpeed( R32 f1PerSecond ) { GetControlTyped().PlSetClusterSpeed( f1PerSecond ); return this; }
		R32								PlGetClusterSpeed() const { return GetControlTyped().PlGetClusterSpeed(); }

		UiRichLabel*					PlSetCustom( OnCustomPlay_t&& fn );
		S32								PlGetFirstCluster() const { return GetControlTyped().PlGetFirstCluster(); }
		S32								PlGetLastCluster() const { return GetControlTyped().PlGetLastCluster(); }
	};
}
