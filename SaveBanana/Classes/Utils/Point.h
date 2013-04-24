//
//  Point.h
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-24.
//
//

#ifndef __SaveBanana__Point__
#define __SaveBanana__Point__

#include "Size.h"

class Point {
public:
    Point() : m_x(0), m_y(0) { }
    Point(float x, float y) : m_x(x), m_y(y) { }
    Point(const IntPoint&);


    static Point zero() { return Point(); }

    static Point narrowPrecision(double x, double y);

    float x() const { return m_x; }
    float y() const { return m_y; }

    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }
    void set(float x, float y)
    {
        m_x = x;
        m_y = y;
    }
    void move(float dx, float dy)
    {
        m_x += dx;
        m_y += dy;
    }
    void scale(float sx, float sy)
    {
        m_x *= sx;
        m_y *= sy;
    }

    void normalize();

    float dot(const Point& a) const
    {
        return m_x * a.x() + m_y * a.y();
    }

    float length() const;
    float lengthSquared() const
    {
        return m_x * m_x + m_y * m_y;
    }

private:
    float m_x, m_y;
};


inline Point& operator+=(Point& a, const Size& b)
{
    a.move(b.width(), b.height());
    return a;
}

inline Point& operator+=(Point& a, const Point& b)
{
    a.move(b.x(), b.y());
    return a;
}

inline Point& operator-=(Point& a, const Size& b)
{
    a.move(-b.width(), -b.height());
    return a;
}

inline Point operator+(const Point& a, const Size& b)
{
    return Point(a.x() + b.width(), a.y() + b.height());
}

inline Point operator+(const Point& a, const Point& b)
{
    return Point(a.x() + b.x(), a.y() + b.y());
}

inline Size operator-(const Point& a, const Point& b)
{
    return Size(a.x() - b.x(), a.y() - b.y());
}

inline Point operator-(const Point& a, const Size& b)
{
    return Point(a.x() - b.width(), a.y() - b.height());
}

inline bool operator==(const Point& a, const Point& b)
{
    return a.x() == b.x() && a.y() == b.y();
}

inline bool operator!=(const Point& a, const Point& b)
{
    return a.x() != b.x() || a.y() != b.y();
}

inline float operator*(const Point& a, const Point& b)
{
    // dot product
    return a.dot(b);
}

float findSlope(const Point& p1, const Point& p2, float& c);

// Find point where lines through the two pairs of points intersect. Returns false if the lines don't intersect.
bool findIntersection(const Point& p1, const Point& p2, const Point& d1, const Point& d2, Point& intersection);

}

#endif /* defined(__SaveBanana__Point__) */
