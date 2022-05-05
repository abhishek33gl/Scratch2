#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"Dwrite.lib")

#include "NativeWindow.h"
#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include <windowsx.h>
#include<iostream>

#define PRIV_INFO privateInfo_
#define  M_HWND privateInfo_->winHWND_
#define WIN_HWND win->privateInfo_->winHWND_
#define WIN_PRIV win->privateInfo_
char ConvertKeyChar(WPARAM wparam)
{
	char c = (char)wparam;
	switch (wparam)
	{
	case 0x08:
		c = ak::Key::BACKSPACE;
		break;
	case 0x0A:
		// Process a linefeed. 
		break;
	case 0x1B:
		c = ak::Key::ESC;
		break;
	case 0x09:
		c = ak::Key::TAB;
		break;
	case 0x0D:
		c = ak::Key::ENTER;
		break;
	}
	return c;
}
char ConvertKeyDown(WPARAM wparam)
{
	char c = 0;
	switch (wparam)
	{
		case VK_LEFT:
			c = ak::Key::LEFT;
			break;
		case VK_RIGHT:
			c = ak::Key::RIGHT;
			break;
		case VK_UP:
			c = ak::Key::UP;
			break;
		case VK_DOWN:
			c = ak::Key::DOWN;
			break;
		case VK_HOME:
			c = ak::Key::HOME;
			break;
		case VK_END:
			c = ak::Key::END;
			break;
		case VK_INSERT:
			c = ak::Key::INSERT;
			break;
		case VK_DELETE:
			c = ak::Key::DEL;
			break;
		case VK_F2:
			c = ak::Key::F2;
			break;
	}
	return c;
}
namespace ak
{
	class MouseTracker
	{
		bool m_bMouseTracking;

	public:
		MouseTracker() : m_bMouseTracking(false)
		{
		}

		void OnMouseMove(HWND hwnd)
		{
			if (!m_bMouseTracking)
			{
				// Enable mouse tracking.
				TRACKMOUSEEVENT tme;
				tme.cbSize = sizeof(tme);
				tme.hwndTrack = hwnd;
				tme.dwFlags = TME_HOVER | TME_LEAVE;
				tme.dwHoverTime = HOVER_DEFAULT;
				TrackMouseEvent(&tme);
				m_bMouseTracking = true;
			}
		}
		void Reset(HWND hwnd)
		{
			m_bMouseTracking = false;
		}
	};
	struct NativeWindow::PrivateInfo
	{
		HWND winHWND_=NULL;
		MouseTracker tracker_;
		bool isMouseDown_ = false;
		bool isCreated_ = false;
		bool isMouseExit_ = false;
		HDC hdc_ = nullptr;
	};
	class _NativeWindowHelper
	{
	public:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			NativeWindow* win = NULL;
			if (uMsg == WM_NCCREATE)
			{
				CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
				win = (NativeWindow*)pCreate->lpCreateParams;
				SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)win);
				WIN_HWND = hwnd;
				return 1;
			
			}
			win = (NativeWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if (win)
			{
				switch (uMsg)
				{
					//key focus
				case WM_SETFOCUS:
				{
					win->OnKeyCapture();
					return 0;
				}
				case WM_KILLFOCUS:
				{
					win->OnKeyReleaseCapture();
					return 0;
				}
				/*--------------------Key---------------*/
				case WM_CHAR:
				{
					ak::KeyEvent e{};
					e.key = ConvertKeyChar(wParam);
					win->OnKeyDown(e);
					return 0;
				}
				case WM_KEYDOWN:
				{
					ak::KeyEvent e{};
					e.key = ConvertKeyDown(wParam);
					win->OnKeyDown(e);
					return 0;
				}
				case WM_KEYUP:
				{
					ak::KeyEvent e{};
					e.key = (char)wParam;
					win->OnKeyUp(e);
					return 0;
				}
				case WM_LBUTTONDOWN:
				case WM_RBUTTONDOWN:
				{
					WIN_PRIV->isMouseDown_ = true;
					ak::MouseEvent e;
					e.extraButton = (int)wParam;
					if (uMsg == WM_LBUTTONDOWN)
						e.button = e.B_LEFT;
					else if (uMsg == WM_RBUTTONDOWN)
						e.button = e.B_RIGHT;
					e.x = GET_X_LPARAM(lParam);
					e.y = GET_Y_LPARAM(lParam);
					win->OnMouseDown(e);
					return 0;
				}
				case WM_LBUTTONUP:
				case WM_RBUTTONUP:
				{
					WIN_PRIV->isMouseDown_ = false;
					ak::MouseEvent e;
					e.extraButton = (int)wParam;
					if (uMsg == WM_LBUTTONUP)
						e.button = e.
						B_LEFT;
					else if (uMsg == WM_RBUTTONUP)
						e.button = e.B_RIGHT;
					e.x = GET_X_LPARAM(lParam);
					e.y = GET_Y_LPARAM(lParam);
					win->OnMouseUp(e);
					return 0;
				}
				case WM_MOUSELEAVE:
				{
					WIN_PRIV->isMouseExit_ = true;
					win->OnMouseExit();
					WIN_PRIV->tracker_.Reset(hwnd);
					return 0;
				}
				//case WM_MOUSEHOVER:
				//    win->OnMouseEnter();
				//   // m_mouseTrack.Reset(M_HWND);
				//    return 0;
				case WM_MOUSEMOVE:
				{
					if (WIN_PRIV->isMouseExit_)
					{
						win->OnMouseEnter();
						WIN_PRIV->isMouseExit_ = false;
						WIN_PRIV->tracker_.Reset(hwnd);
						return 0;
					}
					WIN_PRIV->tracker_.OnMouseMove(hwnd);
					ak::MouseEvent e;
					e.extraButton = (int)wParam;
					e.button = e.UNKNOWN;
					e.x = GET_X_LPARAM(lParam);
					e.y = GET_Y_LPARAM(lParam);
					win->OnMouseMove(e);
					return 0;
				}
				case WM_CREATE:
				{
					WIN_PRIV->isCreated_ = true;
					WIN_PRIV->hdc_ = ::GetDC(WIN_HWND);
					win->OnCreate();
					return 0;
				}
				case WM_MOUSEWHEEL:
				{
					ak::MouseEvent e;
					if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
						e.delta = ak::MouseEvent::MOUSE_UP;
					if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
						e.delta = ak::MouseEvent::MOUSE_DOWN;
					e.x = GET_X_LPARAM(lParam);
					e.y = GET_Y_LPARAM(lParam);
					win->OnMouseWheel(e);
					return 0;
				}
				case WM_SIZE:
				{
					ak::SizeEvent event;
					event.flag = (int)wParam;
					event.width = LOWORD(lParam);
					event.height = HIWORD(lParam);
					win->OnSize(event);
					return 0;
				}
				case WM_PAINT:
				{
					PAINTSTRUCT ps;
					HDC hdc = BeginPaint(hwnd, &ps);

					//// All painting occurs here, between BeginPaint and EndPaint.

					//FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 2));

					EndPaint(hwnd, &ps);
					PaintEvent e;
					e.dirtyRect.SetLTRB((float)ps.rcPaint.left,(float)ps.rcPaint.top, (float)ps.rcPaint.right, (float)ps.rcPaint.bottom);
					win->OnPaint(e);
					//::ValidateRect(hwnd, NULL);
					//e.dirtyRect.Print();
					return 0;
				}
				case WM_ERASEBKGND:
					return TRUE;
				case WM_ACTIVATE:
				{
					if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE)
					{
						win->OnActivate();
					}
					else if (wParam == WA_INACTIVE)
					{
						win->OnDeactivate();
					}
					return 0;
				}
				case WM_SHOWWINDOW:
				{
					if (wParam)
						win->OnVisible();
					else
						win->OnHide();
					return 0;
				}
				case WM_ENABLE:
				{
					if (wParam)
						win->OnEnable();
					else
						win->OnDisable();
					return 0;
				}
				case WM_DESTROY:
				{
					win->OnDestroy();
					return 0;
				}
				}
			}
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	};
	void NativeWindow::CreateWin(InitInfo info)
	{
		if (privateInfo_ == nullptr)
			privateInfo_ = new PrivateInfo;

		if (this->privateInfo_->isCreated_)
			return;

		

		static const wchar_t* classname = L"Win32Window";
		//register
		{

			static WNDCLASS wc = { 0 };
			//only once
			if (wc.lpszClassName != classname)
			{
				wc.lpfnWndProc = _NativeWindowHelper::WindowProc;
				wc.hInstance = ::GetModuleHandle(0);
				wc.lpszClassName = classname;
				wc.style = CS_DBLCLKS| CS_OWNDC;
				::RegisterClass(&wc);
			}
			//create
			HWND hwnd = ::CreateWindowEx(NULL, classname, info.name_,
				WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, info.width_, info.height_,
				NULL,
				NULL, ::GetModuleHandle(0), this);

			//error
			if (hwnd == NULL)
			{
				std::cout << "windows doesn't created\n";
				exit(5555);
			}
		}
	}
	NativeWindow::NativeWindow(InitInfo info)
	{
		initInfo_ = info;
	}
	

	NativeWindow::~NativeWindow()
	{
		this->Destroy();
	}
	void NativeWindow::SetName(const wchar_t* name)
	{
		::SetWindowText(M_HWND, name);
	}

	void NativeWindow::Hide()
	{
		ShowWindow(M_HWND, SW_HIDE);
	}

	void NativeWindow::Show()
	{
		this->CreateWin(initInfo_);
		ShowWindow(M_HWND, SW_SHOW);
	}

	int NativeWindow::GetWidth()
	{
		RECT rect;
		GetClientRect(M_HWND, &rect);
		return rect.right;
	}

	int NativeWindow::GetHeight()
	{
		RECT rect;
		GetClientRect(M_HWND, &rect);
		return rect.bottom;
	}

	bool NativeWindow::IsMouseDown()
	{
		return privateInfo_->isMouseDown_;
	}
	void NativeWindow::CaptureMouse()
	{
		if (M_HWND)
			::SetCapture(M_HWND);
	}

	void NativeWindow::ReleaseMouseCapture()
	{
		::ReleaseCapture();
	}
	void NativeWindow::Repaint()
	{
		::InvalidateRect(M_HWND, NULL, 0);
	}

	void NativeWindow::Destroy()
	{
		if (M_HWND)
		{
			::DestroyWindow(M_HWND);
			ReleaseDC(M_HWND, privateInfo_->hdc_);
			delete privateInfo_;
		}
	}

	void* NativeWindow::GetDC()
	{
		return privateInfo_->hdc_;
	}

	void NativeWindow::CaptureKey()
	{
		::SetFocus(M_HWND);
	}

	void NativeWindow::ReleaseKeyCapture()
	{
	}

	void NativeWindow::Enable()
	{
		EnableWindow(M_HWND, TRUE);
	}

	void NativeWindow::Disable()
	{
		EnableWindow(M_HWND, FALSE);
	}

	void NativeWindow::Maximized()
	{
		ShowWindow(M_HWND, SW_MAXIMIZE);
	}

	void NativeWindow::Minimized()
	{
		ShowWindow(M_HWND, SW_MINIMIZE);
	}

	bool NativeWindow::IsEnable()
	{
		return IsWindowEnabled(M_HWND);
	}

	bool NativeWindow::IsVisible()
	{
		return IsWindowVisible(M_HWND);
	}

	bool NativeWindow::IsCreated()
	{
		return privateInfo_->isCreated_ ;
	}


	void NativeWindow::EventLoop()
	{
		MSG msg = { };
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	void* NativeWindow::GetHandle()
	{
		return privateInfo_->winHWND_;
	}

	void NativeWindow::OnCreate()
	{
		
	}

	void NativeWindow::OnSize(SizeEvent& e)
	{
		
	}

	void NativeWindow::OnPaint(PaintEvent& e)
	{
		
		

	}

	void NativeWindow::OnDestroy()
	{
	}

	void NativeWindow::OnEnable()
	{
	}

	void NativeWindow::OnDisable()
	{
	}

	void NativeWindow::OnVisible()
	{
	}

	void NativeWindow::OnHide()
	{
	}

	void NativeWindow::OnActivate()
	{
	}

	void NativeWindow::OnDeactivate()
	{
	}

	void NativeWindow::OnMouseMove(MouseEvent& e)
	{
	}

	void NativeWindow::OnMouseEnter()
	{
	}

	void NativeWindow::OnMouseExit()
	{
	}

	void NativeWindow::OnMouseUp(MouseEvent& e)
	{
	}

	void NativeWindow::OnMouseDown(MouseEvent& e)
	{
	}

	void NativeWindow::OnMouseWheel(MouseEvent& e)
	{
	}

	void NativeWindow::OnMouseCapture()
	{
	}

	void NativeWindow::OnMouseReleaseCapture()
	{
	}

	void NativeWindow::OnKeyDown(KeyEvent& e)
	{
	}

	void NativeWindow::OnKeyUp(KeyEvent& e)
	{
	}

	void NativeWindow::OnKeyCapture()
	{
	}

	void NativeWindow::OnKeyReleaseCapture()
	{
	}

}

