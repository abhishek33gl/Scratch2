#pragma once
#include <d2d1.h>
#include <dwrite.h>
#include <d2d1helper.h>
#include <wrl\client.h>
#include<string>
#include<vector>
#define cwstring const wchar_t*
using namespace D2D1;
using namespace Microsoft::WRL;
inline D2D_RECT_F RectF_XYWH(float x, float y, float w, float h)
{
	return RectF(x, y, x + w, y + h);
}
using D2Color = D2D1_COLOR_F;
using D2Render = ID2D1RenderTarget;
using D2BitmapRender = ID2D1BitmapRenderTarget;

namespace D2
{
	
	ID2D1Factory* GetD2Factory();

	IDWriteFactory* GetWriteFactory();

	void CreateHwndRenderTarget(void* hwnd,
		ID2D1HwndRenderTarget** render);

	void DrawBitmap(ID2D1RenderTarget* render, ID2D1Bitmap* bitmap,
		int x, int y);

	static ComPtr<ID2D1SolidColorBrush> CreateSolidBrush(
		ID2D1RenderTarget* render,
		D2D1_COLOR_F color=ColorF(ColorF::Chocolate)
	) {
		ComPtr<ID2D1SolidColorBrush> brush;
		render->CreateSolidColorBrush(color, &brush);

		return ComPtr<ID2D1SolidColorBrush>(brush.Detach());
	}
	
	static D2D1_MATRIX_3X2_F GetTransform(ID2D1RenderTarget* render) {
		D2D1_MATRIX_3X2_F mat;
		render->GetTransform(&mat);
		return mat;
	}
	

	D2D1_COLOR_F RandomRGB();
	D2D1_COLOR_F RandomRGBA();

	/*-----directwrite-----*/
	static ComPtr<IDWriteTextFormat> CreateTextFormat(
		float sizeInDIP=20.0f,
		cwstring name=L"Arial",
		DWRITE_FONT_WEIGHT    fontWeight= DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE     fontStyle = DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH   fontStretch = DWRITE_FONT_STRETCH_NORMAL
	) {
		ComPtr<IDWriteTextFormat> obj;
		GetWriteFactory()->CreateTextFormat(
			name,
			NULL,
			fontWeight,
			fontStyle,
			fontStretch,
			sizeInDIP,
			L"",
			&obj
		);

		obj->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		obj->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		return ComPtr<IDWriteTextFormat>(obj.Detach());
	}
	
}