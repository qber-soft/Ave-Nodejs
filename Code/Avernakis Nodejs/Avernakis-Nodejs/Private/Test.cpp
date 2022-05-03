#include "StdAfx.h"
#include "Test.h"

#include "WrapData.h"

#define ThisMethod($x) &Test::$x
#define AutoAddMethod($x, ...) AddMethod<__VA_ARGS__>( #$x, ThisMethod( $x ) )
#define MakeThisFunc($x) MakeFunc( this, ThisMethod( $x ) )

namespace Nav
{

	namespace
	{
		ObjectRegister<Test> c_obj;
	}

	class AvePixelMatchOption
	{
	public:
		R32		m_threshold;
		U1		m_includeAA;
		R32		m_alpha;
	};

	NavDefineDataByMember_(AvePixelMatchOption, threshold, includeAA, alpha);

	U1 AvePixelMatch(const WrapArray<U8>& ab0, const WrapArray<U8>& ab1, Napi::Value abdiff, U32 nWidth, U32 nHeight, const WrapData<AvePixelMatchOption>& opt)
	{
		if (!abdiff.IsArrayBuffer())
			return false;
		Napi::ArrayBuffer ab = abdiff.As<Napi::ArrayBuffer>();
		if (ab0.m_Length != ab1.m_Length || ab0.m_Length != ab.ByteLength())
			return false;

		static List<U8, 64> vData[3];
		static List<U8, 64> vBack;
		const void* pData[] = { ab0, ab1, ab.Data() };

		U32 nAlignNeeded = 1;

		if (App::GetSingleton().GetSysInfo().CpuGetFeature<Sys::CpuFeature::AVX2>())
			nAlignNeeded = 32;
		//else if ( App::GetSingleton().GetSysInfo().CpuGetFeature<Sys::CpuFeature::SSE2>() )
		//	nAlignNeeded = 16;

		if (nAlignNeeded > 1)
		{
			const auto nMask = nAlignNeeded - 1;
			for (S32 i = 0; i < 3; ++i)
			{
				if (nMask & (USize)pData[i])
				{
					if (ab0.m_Length > vData[i].Size())
						vData[i].Resize(ab0.m_Length);
					if (i < 2)
						AveCopyMemoryAuto(vData[i].Data(), pData[i], ab0.m_Length);
					pData[i] = vData[i].Data();
				}
			}
		}

		auto nPixelCount = nWidth * nHeight;
		const auto nThreshold = U8(255.f * Math::Saturate(opt.m_threshold));
		const auto fAlpha = Math::Saturate(opt.m_alpha);
		const auto nAlpha = U8(255.f * fAlpha);

		if (App::GetSingleton().GetSysInfo().CpuGetFeature<Sys::CpuFeature::AVX2>())
		{
			if (ab0.m_Length > vBack.Size())
				vBack.Resize(ab0.m_Length);
			if (nAlpha > 0)
			{
				__m256i vAlpha = _mm256_set1_epi16(nAlpha);
				__m256i vWhite = _mm256_set1_epi16(0xff);
				__m256i vWhiteAdd = _mm256_set1_epi16((255 - nAlpha) << 8);
				__m256i vDiv = _mm256_set1_epi16(4);
				__m256i vShuffle = _mm256_set_epi8(14, 3, 3, 3, 6, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 6, 1, 1, 1);
				const auto nPackedCount = nPixelCount >> 2;

				auto p0 = (const __m128i*) pData[0];
				auto pd = (__m128i*) vBack.Data();
				for (U32 i = 0; i < nPackedCount; ++i)
				{
					__m256i v0 = _mm256_cvtepu8_epi16(_mm_load_si128(&p0[i]));
					v0 = _mm256_hadds_epi16(v0, v0);
					v0 = _mm256_hadds_epi16(v0, v0);
					v0 = _mm256_div_epi16(v0, vDiv);
					v0 = _mm256_mullo_epi16(v0, vAlpha);
					v0 = _mm256_add_epi16(v0, vWhiteAdd);
					v0 = _mm256_blend_epi16(v0, vWhite, 0b10001000);
					v0 = _mm256_shuffle_epi8(v0, vShuffle);
					__m128i vr0 = _mm256_extracti128_si256(v0, 0);
					__m128i vr1 = _mm256_extracti128_si256(v0, 1);
					_mm_stream_si128(&pd[i], _mm_blend_epi32(vr0, vr1, 0b1100));
				}
				_mm_sfence();
			}
			else
			{
				AveFillMemorySimd(vBack.Data(), _mm_castsi128_ps(_mm_set1_epi32(0xffffffff)), vBack.DataSize());
			}

			__m256i vThreshold = _mm256_set1_epi8((U8)nThreshold - (U8)128);
			__m256i vU2S = _mm256_set1_epi8((U8)128);
			__m256i vShuffle0 = _mm256_set_epi8(14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1, 14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);
			__m256i vShuffle1 = _mm256_set_epi8(12, 12, 14, 14, 8, 8, 10, 10, 4, 4, 6, 6, 0, 0, 2, 2, 12, 12, 14, 14, 8, 8, 10, 10, 4, 4, 6, 6, 0, 0, 2, 2);
			__m256i vRed = _mm256_set1_epi32(0xff0000ff);
			const auto nPackedCount = nPixelCount >> 3;
			auto p0 = (const __m256i*) pData[0];
			auto p1 = (const __m256i*) pData[1];
			auto p2 = (__m256i*) pData[2];
			auto pb = (const __m256i*) vBack.Data();

			for (U32 i = 0; i < nPackedCount; ++i)
			{
				__m256i v0 = _mm256_load_si256(&p0[i]);
				__m256i v1 = _mm256_load_si256(&p1[i]);
				__m256i vb = _mm256_load_si256(&pb[i]);
				__m256i vd = _mm256_subs_epu8(_mm256_max_epu8(v0, v1), _mm256_min_epu8(v0, v1));
				vd = _mm256_add_epi8(vd, vU2S);
				vd = _mm256_cmpgt_epi8(vd, vThreshold); // _mm256_cmpgt_epu8 need AVX512, here use _mm256_cmpgt_epi8
				vd = _mm256_or_si256(vd, _mm256_shuffle_epi8(vd, vShuffle0));
				vd = _mm256_or_si256(vd, _mm256_shuffle_epi8(vd, vShuffle1));
				__m256i vr = _mm256_blendv_epi8(vb, vRed, vd);
				_mm256_stream_si256(&p2[i], vr);
			}

			_mm_sfence();

			nPixelCount -= nPackedCount << 3;
			if (nPixelCount > 0)
			{
				pData[0] = &p0[nPackedCount];
				pData[1] = &p1[nPackedCount];
				pData[2] = &p2[nPackedCount];
			}
		}
		//else if ( App::GetSingleton().GetSysInfo().CpuGetFeature<Sys::CpuFeature::SSE2>() )
		//{
		//}

		if (nPixelCount > 0)
		{
			auto p0 = (const U8_4*)pData[0];
			auto p1 = (const U8_4*)pData[1];
			auto p2p = (U8_4*)pData[2];
			auto p2u = (U32*)pData[2];
			auto nb = U8(255 - nAlpha);
			for (U32 i = 0; i < nPixelCount; ++i)
			{
				if (p0[i].r - p1[i].r > nThreshold || p0[i].g - p1[i].g > nThreshold || p0[i].b - p1[i].b > nThreshold || p0[i].a - p1[i].a > nThreshold)
				{
					p2u[i] = 0xff0000ff;
				}
				else
				{
					if (0 == opt.m_alpha)
					{
						p2u[i] = 0xffffffff;
					}
					else
					{
						auto t = U8((p0[i].r + p0[i].g + p0[i].b + p0[i].a) * 0.25f * fAlpha + nb);
						p2p[i].r = t;
						p2p[i].g = t;
						p2p[i].b = t;
						p2p[i].a = 255;
					}
				}
			}
		}

		if (pData[2] != ab.Data())
			AveCopyMemoryAuto(ab.Data(), pData[2], ab.ByteLength());

		return true;
	}

	void Test::DefineObject()
	{
		AutoAddMethod(SetX);
		AutoAddMethod(GetX);

		AutoAddMethod(SetY);
		AutoAddMethod(GetY);

		AutoAddMethod(TestString);

		AutoAddMethod(ShowTestWindow);

		AutoAddMethod(ThrowJsException);

		AddGlobalMethod("AvePixelMatch", AvePixelMatch);
	}

	U1 Test::Ctor(S32 x, S32 y)
	{
		m_Pos = { x, y };
		return true;
	}

	void Test::SetX(S32 x)
	{
		m_Pos.x = x;
	}

	void Test::SetY(S32 y)
	{
		m_Pos.y = y;
	}

	S32 Test::GetX() const
	{
		return m_Pos.x;
	}

	S32 Test::GetY() const
	{
		return m_Pos.y;
	}

	WString Test::TestString(PCWChar szMessage) const
	{
		return WString(szMessage) + AveWide("我好啊");
	}

	WString Test::ShowTestWindow()
	{
		auto app = AveKak.CreateAppScope();
		{
			auto theme = AveKak.Create<Ave::Ui::IThemeImage>();
			if (!theme)
				return AveWide("Failed to create theme.");

			auto dark = AveKak.Create<Ave::Ui::IThemeImagePredefinedStyle_HyperOnyx>();
			dark->SetStyle(*theme, 0, {});

			Ave::Ui::IWindow::CreationParam cpWindow{};
			cpWindow.m_Theme = theme;
			cpWindow.m_Device.m_DeviceType = Ave::Ui::WindowDeviceType::Byo2;
			cpWindow.m_Device.m_DeviceId = AveGuidOf(Ave::Byo2::IDeviceD2D1);
			cpWindow.m_Window.m_Title = AveWide("Test Window");
			cpWindow.m_Window.m_Flag = Ave::Ui::IWindowNative::CreationParam::Flag_Default;
			cpWindow.m_Window.m_Flag |= Ave::Ui::IWindowNative::CreationParam::Flag_CustomFrame;
			cpWindow.m_Window.m_Flag |= Ave::Ui::IWindowNative::CreationParam::Flag_Layered;

			auto window = AveKak.Create<Ave::Ui::IWindow>(cpWindow);
			if (!window)
				return AveWide("Failed to initialize window.");

			if (!window->Create())
				return AveWide("Failed to create window.");

			window->SetFrame(window->GetTheme().GetFactory().Create<Ave::Ui::IWindowFrame>());

			window->SetVisible(true);
			window->GetNativeWindow().Activate();

			AveKak.GetApp().Run();

			return AveWide("Window closed.");
		}
	}

	void Test::ThrowJsException(const CallbackInfo& ci, S32 x)
	{
		ci.ThrowJsException("Throw exception, x is %0%."_strfp % x);
	}

}
