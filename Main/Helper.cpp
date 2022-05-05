#include "Helper.h"
#include<cmath>
#include <time.h>
#include <stdlib.h>
#include<Windows.h>
#include <cstdint>
#include<iostream>
namespace ak
{
	float Math::PI = 3.14159265f;
	float Math::Sin(float rad)
	{
		return std::sin(rad);
	}
	float Math::Cos(float rad)
	{
		return ::cosf(rad);

	}
	float Math::Tan(float rad)
	{
		return ::tanf(rad);
	}
	float Math::ASin(float ratio)
	{
		return ::asinf(ratio);
	}
	float Math::ACos(float ratio)
	{
		return ::acosf(ratio);
	}
	float Math::ATan(float ratio)
	{
		return ::atanf(ratio);
	}
	int Math::Abs(int v)
	{
		return std::abs(v);
	}
	float Math::Abs(float v)
	{
		return std::abs(v);
	}
	double Math::Abs(double v)
	{
		return std::abs(v);
	}
	long Math::Abs(long v)
	{
		return std::abs(v);
	}
	int Math::Ceil(float v)
	{
		return (int)std::ceil(v);
	}
	int Math::Floor(float v)
	{
		return (int)std::floor(v);

	}
	float Math::Log(float v)
	{
		return std::log(v);

	}
	float Math::Log10(float v)
	{
		return std::log10(v);

	}
	int Math::Fmod(float divident, float divisor)
	{
		return (int)std::fmod(divident, divisor);
	}
	float Math::Sqroot(float v)
	{
		return std::sqrt(v);
	}
	float Math::Square(float v)
	{
		return v * v;
	}
	float Math::Power(float base, float exponent)
	{
		return std::pow(base, exponent);
	}
	float Math::ModF(float v, int& intPart)
	{
		return (float)std::modf(v, (double*)&intPart);
	}
	float Math::Exp(float exponent)
	{
		return std::exp(exponent);
	}
	int Math::Max(int a, int b)
	{
		return a > b ? a : b;
	}
	int Math::Min(int a, int b)
	{
		return a < b ? a : b;
	}
	float Math::Max(float a, float b)
	{
		return a > b ? a : b;
	}
	float Math::Min(float a, float b)
	{
		return a < b ? a : b;
	}
	float Math::Normalize(float v, float maxValue)
	{
		return v / maxValue;
	}
	float Math::SqDist(float x, float y)
	{
		return x * x + y * y;
	}
	float Math::Distance(float x, float y)
	{
		return Sqroot(SqDist(x, y));
	}

	//interpolate

	float Math::Clamp(float x, float lowerlimit, float upperlimit) {
		if (x < lowerlimit)
			x = lowerlimit;
		if (x > upperlimit)
			x = upperlimit;
		return x;
	}
	float Math::Smoothstep(float edge0, float edge1, float x) {
		// Scale, bias and saturate x to 0..1 range
		x = Clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
		// Evaluate polynomial
		return x * x * (3 - 2 * x);
	}

	Size::Size()
	{

		this->width = height = 0;
	}
	Size::Size(const Size& size)
	{
		this->width = size.width;
		this->height = size.height;
	}
	Size::Size(float width, float height)
	{
		this->width = width;
		this->height = height;
	}
	bool Size::Equals(const Size& sz) const
	{
		return (width == sz.width) && (height == sz.height);
	}
	bool Size::Empty() const
	{
		return (width == 0 && height == 0);
	}
	Point::Point()
	{
		this->x = y = 0;
	}
	Point::Point(const Point& point)
	{
		this->x = point.x;
		this->y = point.y;
	}
	Point::Point(const Size& size)
	{
		this->x = size.width;
		this->y = size.height;
	}
	Point::Point(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void Point::Set(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	bool Point::Equals(const Point& point)
	{
		return (x == point.x) && (y == point.y);
	}
	Rect::Rect()
	{
		x = y = width = height = 0;
	}
	Rect::Rect(float x, float y, float width, float height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	Rect::Rect(const Point& location, const Size& size)
	{
		this->x = location.x;
		this->y = location.y;
		this->width = size.width;
		this->height = size.height;
	}
	Rect* Rect::Clone() const
	{
		return new Rect(x, y, width, height);
	}
	void Rect::SetXYWH(float x, float y, float w, float h)
	{
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
	}
	void Rect::SetLTRB(float l, float t, float r, float b)
	{
		SetXYWH(l, t, r - l, b - t);
	}
	void Rect::GetLocation(Point* point) const
	{
		point->x = x;
		point->y = y;
	}
	void Rect::GetSize(Size* size) const
	{
		size->width = width;
		size->height = height;
	}
	void Rect::GetBounds(Rect* rect) const
	{
		rect->x = x;
		rect->y = y;
		rect->width = width;
		rect->height = height;
	}
	float Rect::GetLeft() const
	{
		return x;
	}
	float Rect::GetTop() const
	{
		return y;
	}
	float Rect::GetRight() const
	{
		return x + width;
	}
	float Rect::GetBottom() const
	{
		return y + height;
	}
	bool Rect::IsEmptyArea() const
	{
		return (width <= 0) || (height <= 0);
	}
	bool Rect::Equals(const Rect& rect) const
	{
		return x == rect.x &&
			this->y == rect.y &&
			this->width == rect.width &&
			this->height == rect.height;
	}
	bool Rect::Contains(float x, float y) const
	{
		return x >= this->x && x < this->x + width &&
			y >= this->y && y < this->y + height;
	}
	bool Rect::Contains(const Point& pt) const
	{
		return Contains(pt.x, pt.y);
	}
	bool Rect::Contains(Rect& rect) const
	{
		return (x <= rect.x) && (rect.GetRight() <= GetRight()) &&
			(y <= rect.y) && (rect.GetBottom() <= GetBottom());
	}
	void Rect::Inflate(float dx, float dy)
	{
		this->x -= dx;
		this->y -= dy;
		this->width += 2 * dx;
		this->height += 2 * dy;
	}
	void Rect::Inflate(const Point& point)
	{
		Inflate(point.x, point.y);
	}
	bool Rect::Intersect(const Rect& rect)
	{
		return Intersect(*this, *this, rect);
	}
	bool Rect::Intersect(Rect& c, const Rect& a, const Rect& b)
	{
		float right = Math::Min(a.GetRight(), b.GetRight());
		float bottom = Math::Min(a.GetBottom(), b.GetBottom());
		float left = Math::Max(a.GetLeft(), b.GetLeft());
		float top = Math::Max(a.GetTop(), b.GetTop());


		c.x = left;
		c.y = top;
		c.width = right - left;
		c.height = bottom - top;
		if (c.width < 0)
			c.width = 0;
		if (c.height < 0)
			c.height = 0;
		return !c.IsEmptyArea();
	}
	bool Rect::IntersectsWith(const Rect& rect) const
	{
		return (GetLeft() < rect.GetRight() &&
			GetTop() < rect.GetBottom() &&
			GetRight() > rect.GetLeft() &&
			GetBottom() > rect.GetTop());
	}
	bool Rect::Union(Rect& c, const Rect& a, const Rect& b)
	{
		float right = Math::Max(a.GetRight(), b.GetRight());
		float bottom = Math::Max(a.GetBottom(), b.GetBottom());
		float left = Math::Min(a.GetLeft(), b.GetLeft());
		float top = Math::Min(a.GetTop(), b.GetTop());

		c.x = left;
		c.y = top;
		c.width = right - left;
		c.height = bottom - top;
		return !c.IsEmptyArea();
	}
	void Rect::Offset(const Point& point)
	{
		Offset(point.x, point.y);
	}
	void Rect::Offset(float dx, float dy)
	{
		this->x += dx;
		this->y += dy;
	}

	void Rect::Print(const char* msg)
	{
		std::cout <<msg<< " x::" << x << " y:" << y << " w:" << width << " h:" << height << "\n";
	}

	void Rect::PrintLTRB(const char* msg)
	{
		std::cout << msg << " L::" << GetLeft() << " T:" << GetTop() << " R:" << GetRight() << " B:" << GetBottom() << "\n";
	}

	bool Random::m_isSeeded = false;
	int Random::RangeInt(int a, int b)
	{
		Init();
		return  int(a + (float(::rand()) / float(RAND_MAX)) * (b - a));
	}

	float Random::RangeFloat(float a, float b)
	{
		Init();
		return  a + (float(::rand()) / float(RAND_MAX)) * (b - a);
	}

	void Random::Init()
	{
		if (!m_isSeeded)
		{
			m_isSeeded = true;
			::srand((unsigned int)time(0));
		}
	}

	static long ___g_frequency = 0;
	static bool isInited = false;
	long AccurateTime::GetTick()
	{
		Init();
		LARGE_INTEGER ticks;
		if (!QueryPerformanceCounter(&ticks))
		{
			std::cout << "some error in GetTicks\n";
		}
		return ticks.QuadPart;
	}

	long  AccurateTime::GetFrequency()
	{
		Init();
		return ___g_frequency;
	}

	float AccurateTime::MesureTime(std::function<void()> fun)
	{
		auto a = Millisecond();
		fun();
		auto b = Millisecond();
		return b-a;
	}

	float AccurateTime::Millisecond()
	{

		return GetTick() * (1000.0 / ___g_frequency);
	}

	float AccurateTime::Second()
	{
		return GetTick() * (1.0 / ___g_frequency);
	}

	void AccurateTime::Init()
	{
		if (!isInited)
		{
			if (!QueryPerformanceFrequency((LARGE_INTEGER*)&___g_frequency))
			{
				std::cout << "erro  InitTimer\n";
			}
		}
		else
			isInited = true;
	}

}