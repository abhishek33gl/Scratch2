#pragma once
#include "NativeWindow.h"
#include"Direct2d.h"
extern ID2D1SolidColorBrush* myBrush;
namespace ak
{
	class D2Window :
		public NativeWindow
	{
	protected:
		virtual void  OnCreate() override;
		virtual void OnSize(SizeEvent& e);
		virtual void  OnPaint(ID2D1RenderTarget *render);
		void  OnPaint(PaintEvent &e) override;
	protected:
		ComPtr<ID2D1HwndRenderTarget> hwndRender;
	};
}

