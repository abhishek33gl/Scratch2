#pragma once
#include "..\D2Window.h"
#include"..\Direct2d.h"
namespace ak {
	class ViewWindow;
	class GUIWindow :
		public D2Window
	{
	protected:
		virtual void AddChild(ViewWindow* child);
		virtual void  OnCreate() override;
		virtual void OnSize(SizeEvent& e);
		virtual void  OnPaint(ID2D1RenderTarget* render,PaintEvent &e);
		void  OnPaint(PaintEvent& e) override;
		/*
		 repaint all child ViewWindow which intersect with paintRect 
		 if empty repaint all child
		*/
		void Repaint(ak::Rect paintRect);
	protected:
		std::vector<ViewWindow*> childViewWins;
		friend class ViewWindow;
	};
}

