#include "D2Window.h"
 ID2D1SolidColorBrush* myBrush=nullptr;
namespace ak
{
	void D2Window::OnCreate()
	{
		D2::CreateHwndRenderTarget(GetHandle(), &hwndRender);

		if(!myBrush)
		hwndRender->CreateSolidColorBrush(
			ColorF(0xff0000,0.5f),
			&myBrush
		);
	}
	void D2Window::OnSize(SizeEvent& e)
	{
		hwndRender->Resize(SizeU(e.width, e.height));
	}
	void D2Window::OnPaint(ID2D1RenderTarget* render)
	{
		
	
	}
	void D2Window::OnPaint(PaintEvent &e)
	{
		hwndRender->BeginDraw();
		hwndRender->Clear(ColorF(ColorF::GhostWhite));
		OnPaint(hwndRender.Get());
		hwndRender->EndDraw();
		
	}
}