#pragma once
namespace ak {
	struct LayoutParams
	{
		const static int MATCH_PARENT = -21;
		const static int WRAP_CONTENT = -12;

		int width, height;
		LayoutParams(int w,int h):width(w),height(h){}
	};
}