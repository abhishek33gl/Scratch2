#pragma once
#include<iostream>
#include"Event.h"
#include"Log.h"
namespace ak
{
	class NativeWindow
	{
	public:
		struct InitInfo
		{
			int width_ = 500, height_ = 300;
			const wchar_t* name_ = L"Win32 NativeWindow";
		};
		

		struct PrivateInfo;
		void CreateWin(InitInfo info);
	public:

		NativeWindow(InitInfo info = InitInfo());
		~NativeWindow();
		//NativeWindow
		void SetName(const wchar_t* name);
		void Hide();
		void Show();
		void Enable();
		void Disable();
		void Maximized();
		void Minimized();
		bool IsEnable();
		bool IsVisible();
		bool IsCreated();
		int GetWidth();
		int GetHeight();
		void Destroy();
		void Repaint();
		void* GetHandle();
		//dc
		void* GetDC();
		//key
		void CaptureKey();
		void ReleaseKeyCapture();
		//mouse
		bool IsMouseDown();
		void CaptureMouse();
		void ReleaseMouseCapture();
		//others
		static void EventLoop();

	protected:
		virtual void  OnCreate();
		virtual void OnSize(SizeEvent& e);
		virtual void  OnPaint(PaintEvent& e);
		virtual void  OnDestroy();
		virtual void  OnEnable();
		virtual void  OnDisable();
		virtual void  OnVisible();
		virtual void  OnHide();
		virtual void  OnActivate();
		virtual void  OnDeactivate();
		//mouse event 
		virtual void  OnMouseMove(MouseEvent& e);
		virtual void  OnMouseEnter();
		virtual void  OnMouseExit();
		virtual void  OnMouseUp(MouseEvent& e);
		virtual void  OnMouseDown(MouseEvent& e);
		virtual void  OnMouseWheel(MouseEvent& e);
		virtual void  OnMouseCapture();
		virtual void  OnMouseReleaseCapture();
		//key
		virtual void  OnKeyDown(KeyEvent& e);
		virtual void  OnKeyUp(KeyEvent& e);
		virtual void  OnKeyCapture();
		virtual void  OnKeyReleaseCapture();
		//
	protected:
		PrivateInfo* privateInfo_ = nullptr;
		friend class _NativeWindowHelper;
		InitInfo initInfo_;
		
	};
}


