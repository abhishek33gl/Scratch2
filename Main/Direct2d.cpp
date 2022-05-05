#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"Dwrite.lib")
#include<Windows.h>
#include"Direct2d.h"
#include"Helper.h"
static ID2D1Factory* id2d1Factory = nullptr;
static IDWriteFactory* idWriteFactory = nullptr;

namespace D2
{

	ID2D1Factory* GetD2Factory()
	{
		if (id2d1Factory == nullptr)
		{
			CoInitialize(NULL);
			//direct2d factory
			D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
				&id2d1Factory);
		}
		return id2d1Factory;
	}

	IDWriteFactory* GetWriteFactory()
	{
		if (idWriteFactory == nullptr)
		{
			CoInitialize(NULL);
			//directWrite factory
			DWriteCreateFactory(
				DWRITE_FACTORY_TYPE_SHARED,
				__uuidof(IDWriteFactory),
				reinterpret_cast<IUnknown**>(&idWriteFactory)
			);
		}
		return idWriteFactory;
	}

	void CreateHwndRenderTarget(void* hwnd, ID2D1HwndRenderTarget** render)
	{
		const auto _WINHANDLE = (HWND)(hwnd);
		RECT rc;
		::GetClientRect(_WINHANDLE, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);
		GetD2Factory()->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE),
			D2D1::HwndRenderTargetProperties(_WINHANDLE, size),
			render
		);
	}

	void DrawBitmap(ID2D1RenderTarget* render, ID2D1Bitmap* bitmap, int x, int y)
	{
		auto wh = bitmap->GetSize();
		render->DrawBitmap(
			bitmap,
			RectF_XYWH(x, y, wh.width, wh.height)
		);
	}

	D2D1_COLOR_F RandomRGB()
	{
		return ColorF(ak::Random::RangeFloat(0.0f, 1.0f), ak::Random::RangeFloat(0.0f, 1.0f),
			ak::Random::RangeFloat(0.0f, 1.0f));
	}

	D2D1_COLOR_F RandomRGBA()
	{
		return ColorF(ak::Random::RangeFloat(0.0f, 1.0f), ak::Random::RangeFloat(0.0f, 1.0f),
			ak::Random::RangeFloat(0.0f, 1.0f), ak::Random::RangeFloat(0.0f, 1.0f));
	}

}