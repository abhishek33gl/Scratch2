#pragma once
#include"..\Direct2d.h"
#include "..\Event.h"
#include"ViewCommon.h"
namespace ak 
{
	class View;
	class GUIWindow;
	class ViewWindow
	{
		void LayoutPass();
		void MeasurePass();
		void  OnPaint();
		void ResizeBitmapRender(int w, int h);
	public:
		ViewWindow();
		Rect GetClipRect();
	protected:
		virtual void  OnCreate();
		virtual void OnSize(SizeEvent& e);
		virtual void  OnPaint(D2Render *render);
		
		virtual void OnMeasure(int parentWidth, int parentHeight);
		
		virtual void OnLayout(int left, int top, int right, int bottom);
		/*
		* repaint a
		*/
		void Repaint(ak::Rect paintRect);

	protected:
		LayoutParams layParams{0,0};
		int x=10, y=10, measuredWidth=300, measuredHeight=200;
		D2Color bgColor=D2::RandomRGBA();
		std::wstring name=L"ViewWindow";
		GUIWindow* guiWindow = nullptr;
		friend class GUIWindow;
		ComPtr<D2BitmapRender> bitmapRender;
	};

}

