#include "ViewWindow.h"
#include"GUIWindow.h"
namespace ak
{
	void ViewWindow::OnPaint()
	{
		bitmapRender->BeginDraw();
		bitmapRender->Clear(bgColor);
		OnPaint(bitmapRender.Get());
		bitmapRender->EndDraw();
	}
	void ViewWindow::ResizeBitmapRender(int w, int h)
	{
		
		if ((measuredWidth != w || measuredHeight != h))
		{
			bitmapRender.~ComPtr();
			guiWindow->hwndRender->CreateCompatibleRenderTarget(
			SizeF(w,h),&bitmapRender
			);
		}
	}
	ViewWindow::ViewWindow()
	{
		static int a = 0;
		x = Random::RangeInt(0, 1000);
		y = Random::RangeInt(0, 700);
		measuredWidth = Random::RangeInt(100, 200);
		measuredHeight = Random::RangeInt(100, 200);
		bgColor = D2::RandomRGBA();
		name += std::to_wstring(a);
		a++;
	}
	Rect ViewWindow::GetClipRect()
	{
		return Rect(x,y,measuredWidth,measuredHeight);
	}
	void ViewWindow::OnCreate()
	{
		guiWindow->hwndRender->CreateCompatibleRenderTarget(
			SizeF(measuredWidth, measuredHeight), &bitmapRender
		);
	}
	void ViewWindow::OnSize(SizeEvent& e)
	{
		ResizeBitmapRender(e.width, e.height);
	}
	void ViewWindow::OnPaint(D2Render* render)
	{
		
	}
	void ViewWindow::MeasurePass()
	{
	}
	void ViewWindow::OnMeasure(int parentWidth, int parentHeight)
	{
	}
	void ViewWindow::LayoutPass()
	{
	}
	void ViewWindow::OnLayout(int left, int top, int right, int bottom)
	{
	}
	void ViewWindow::Repaint(ak::Rect paintRect)
	{
	}
}