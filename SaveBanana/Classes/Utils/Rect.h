//
//  Rect.h
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-24.
//
//

#ifndef __SaveBanana__Rect__
#define __SaveBanana__Rect__

#include "Point.h"

class Rect {
public:
    Rect() { }
    Rect(const Point& location, const Size& size)
        : m_location(location), m_size(size) { }
    Rect(float x, float y, float width, float height)
        : m_location(Point(x, y)), m_size(Size(width, height)) { }

    static Rect narrowPrecision(double x, double y, double width, double height);

    Point location() const { return m_location; }
    Size size() const { return m_size; }

    void setLocation(const Point& location) { m_location = location; }
    void setSize(const Size& size) { m_size = size; }

    float x() const { return m_location.x(); }
    float y() const { return m_location.y(); }
    float maxX() const { return x() + width(); }
    float maxY() const { return y() + height(); }
    float width() const { return m_size.width(); }
    float height() const { return m_size.height(); }

    void setX(float x) { m_location.setX(x); }
    void setY(float y) { m_location.setY(y); }
    void setWidth(float width) { m_size.setWidth(width); }
    void setHeight(float height) { m_size.setHeight(height); }

    bool isEmpty() const { return m_size.isEmpty(); }

    Point center() const { return Point(x() + width() / 2, y() + height() / 2); }

    void move(const Size& delta) { m_location += delta; } 
    void move(float dx, float dy) { m_location.move(dx, dy); } 

    bool intersects(const Rect&) const;
    bool contains(const Rect&) const;

    void intersect(const Rect&);
    void unite(const Rect&);
    void uniteIfNonZero(const Rect&);

    bool contains(float px, float py) const
        { return px >= x() && px <= maxX() && py >= y() && py <= maxY(); }
    bool contains(const Point& point) const { return contains(point.x(), point.y()); }

    void inflateX(float dx) {
        m_location.setX(m_location.x() - dx);
        m_size.setWidth(m_size.width() + dx + dx);
    }
    void inflateY(float dy) {
        m_location.setY(m_location.y() - dy);
        m_size.setHeight(m_size.height() + dy + dy);
    }
    void inflate(float d) { inflateX(d); inflateY(d); }
    void scale(float s) { scale(s, s); }
    void scale(float sx, float sy);

    // Re-initializes this rectangle to fit the sets of passed points.
    void fitToPoints(const Point& p0, const Point& p1);
    void fitToPoints(const Point& p0, const Point& p1, const Point& p2);
    void fitToPoints(const Point& p0, const Point& p1, const Point& p2, const Point& p3);

private:
    Point m_location;
    Size m_size;

    void setLocationAndSizeFromEdges(float left, float top, float right, float bottom)
    {
        m_location.set(left, top);
        m_size.setWidth(right - left);
        m_size.setHeight(bottom - top);
    }
};

inline Rect intersection(const Rect& a, const Rect& b)
{
    Rect c = a;
    c.intersect(b);
    return c;
}

inline Rect unionRect(const Rect& a, const Rect& b)
{
    Rect c = a;
    c.unite(b);
    return c;
}


inline bool operator==(const Rect& a, const Rect& b)
{
    return a.location() == b.location() && a.size() == b.size();
}

inline bool operator!=(const Rect& a, const Rect& b)
{
    return a.location() != b.location() || a.size() != b.size();
}

// Map rect r from srcRect to an equivalent rect in destRect.
Rect mapRect(const Rect& r, const Rect& srcRect, const Rect& destRect);

#endif /* defined(__SaveBanana__Rect__) */
