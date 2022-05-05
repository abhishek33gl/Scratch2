#include "GUIWindow.h"
#include"ViewWindow.h"
namespace ak
{
	void GUIWindow::AddChild(ViewWindow* child)
	{
		childViewWins.push_back(child);
		{
			child->guiWindow = this;
			child->OnCreate();
			SizeEvent e;
			e.width = child->measuredWidth;
			e.height = child->measuredHeight;
			child->OnSize(e);
		}
	}
	void GUIWindow::OnCreate()
	{
		D2Window::OnCreate();
	}
	void GUIWindow::OnSize(SizeEvent& e)
	{
		D2Window::OnSize(e);
	}
	void GUIWindow::OnPaint(ID2D1RenderTarget* render, PaintEvent& e)
	{
		for (auto& child : childViewWins) {
			if (e.dirtyRect.IntersectsWith(child->GetClipRect()))
			{
				child->OnPaint();
				ComPtr<ID2D1Bitmap> bitmap;
				child->bitmapRender->GetBitmap(&bitmap);
				auto size = bitmap->GetPixelSize();
				render->DrawBitmap(bitmap.Get(), RectF_XYWH(child->x, child->y, size.width, size.height));
				Log::Error("{0} painted \n", W_S(child->name));
			}
		}

	}
	
	void GUIWindow::OnPaint(PaintEvent& e)
	{
		e.dirtyRect.SetXYWH(0, 0, GetWidth(), GetHeight());
		hwndRender->BeginDraw();
		hwndRender->Clear(ColorF(ColorF::GhostWhite));
		OnPaint(hwndRender.Get(),e);
		hwndRender->EndDraw();
	}
	void GUIWindow::Repaint(ak::Rect paintRect)
	{
		
	}
}