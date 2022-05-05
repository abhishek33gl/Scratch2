#pragma once
#include"Helper.h"
namespace ak
{
	struct Key {
		enum {
			LEFT, RIGHT, UP, DOWN, HOME, END,
			INSERT, F2, BACKSPACE, ENTER, SHIFT,
			CTRL, PRINT, DEL,ESC,TAB
		};

		

	};
	struct MouseEvent
	{
		enum {
			B_LEFT, B_RIGHT, UNKNOWN, MOUSE_UP, MOUSE_DOWN
		};
		int x, y;
		int button;
		int extraButton;/*MK_CONTROL L|M|RBUTTON SHIFT*/
		int delta = 0;
	};
	struct SizeEvent
	{
		int width, height;
		int flag;
	};
	struct KeyEvent
	{
		unsigned char key = 0;
	};

	struct PaintEvent
	{
		Rect dirtyRect;
	};


}