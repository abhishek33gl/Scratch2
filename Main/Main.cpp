#include<iostream>
#include"gui/GUIWindow.h"
#include"gui/ViewWindow.h"
#include<string>

using namespace ak;

class MyGUIWindow :public GUIWindow
{
protected:
	virtual void OnCreate() override
	{
		GUIWindow::OnCreate();
		repeat_for(10) {
			AddChild(new ViewWindow());
		}
	}
};
int main()
{
	Log::Enable(false);
	auto win = new MyGUIWindow();
	win->Show();

	NativeWindow::EventLoop();
	return 0;
}