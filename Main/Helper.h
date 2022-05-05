#pragma once
#define repeat_for(t) for(unsigned int i=0;i<t;i++)
#include<functional>
#include<string>

namespace ak
{
    static std::string W_S(std::wstring wstr)
    {
        std::string str;
        for (auto& c : wstr)
        {
            str += (char)c;
        }
        return str;
    }
    class Math
    {
    public:
        static float PI;
        static float Sin(float rad);
        static float Cos(float rad);
        static float Tan(float rad);

        static float ASin(float ratio);
        static float ACos(float ratio);
        static float ATan(float ratio);

        static int Abs(int v);
        static float Abs(float v);
        static double Abs(double v);
        static long Abs(long v);
        /*ret small int >=x*/
        static int Ceil(float v);
        /*ret great int <=x*/
        static int Floor(float v);
        /*base e*/
        static float Log(float v);
        /*base 10*/
        static float Log10(float v);
        /*ret remainder*/
        static int Fmod(float divident, float divisor);
        static float Sqroot(float v);
        static float Square(float v);
        static float Power(float base, float exponent);
        /*ret frac part and set intpart*/
        static float ModF(float v, int& intPart);
        /*ret e^exponent*/
        static float Exp(float exponent);

        static int Max(int a, int b);
        static int Min(int a, int b);

        static float Max(float a, float b);
        static float Min(float a, float b);

        static float Normalize(float v, float maxValue);
        //triangle
        static float SqDist(float x, float y);
        static float Distance(float x, float y);


        //interpolate
        static float Clamp(float x, float lowerlimit, float upperlimit);
        static float Smoothstep(float edge0, float edge1, float x);

    };
    class Size
    {
    public:
        Size();

        Size(const Size& size);

        Size(float width,
            float height);

        Size operator+(const Size& sz) const
        {
            return Size(width + sz.width,
                height + sz.height);
        }

        Size operator-(const Size& sz) const
        {
            return Size(width - sz.width,
                height - sz.height);
        }

        bool Equals(const Size& sz) const;

        bool Empty() const;

    public:

        float width;
        float height;
    };
    class Point
    {
    public:
        Point();

        Point(const Point& point);

        Point(const Size& size);

        Point(float x,
            float y);
        void Set(float x, float y);

        Point operator+(const Point& point) const
        {
            return Point(x + point.x,
                y + point.y);
        }

        Point operator-(const Point& point) const
        {
            return Point(x - point.x,
                y - point.y);
        }

        bool Equals(const Point& point);

    public:

        float x = 0;
        float y = 0;
    };
    class Rect
    {
    public:

        Rect();
        Rect(float x,
            float y,
            float width,
            float height);

        Rect(const Point& location,
            const Size& size);

        Rect* Clone() const;
        void SetXYWH(float x, float y, float w, float h);
        void SetLTRB(float l, float t, float r, float b);
        void GetLocation(Point* point) const;

        void GetSize(Size* size) const;

        void GetBounds(Rect* rect) const;

        float GetLeft() const;

        float GetTop() const;

        float GetRight() const;

        float GetBottom() const;

        bool IsEmptyArea() const;

        bool Equals(const Rect& rect) const;

        bool Contains(float x,
            float y) const;

        bool Contains(const Point& pt) const;

        bool Contains(Rect& rect) const;

        void Inflate(float dx,
            float dy);

        void Inflate(const Point& point);

        bool Intersect(const Rect& rect);

        static bool Intersect(Rect& c,
            const Rect& a,
            const Rect& b);


        bool IntersectsWith(const Rect& rect) const;

        static bool Union(Rect& c,
            const Rect& a,
            const Rect& b);

        void Offset(const Point& point);

        void Offset(float dx,
            float dy);
        void Print(const char* msg);
        void PrintLTRB(const char* msg);

    public:

        float x = 0, y = 0, width = 0, height = 0;
    };

    class Random
    {
    public:
        static int RangeInt(int a, int b);
        static float RangeFloat(float a, float b);
    private:
        static void Init();
        static bool m_isSeeded;
    };

    class AccurateTime
    {
    public:
        static float Millisecond();
        static  float Second();
        static  long  GetTick();
        static  long  GetFrequency();
        static float MesureTime(std::function<void()> fun);
    private:
        static  void Init();
    };
}

