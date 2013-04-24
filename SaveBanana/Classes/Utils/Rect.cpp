//
//  Rect.cpp
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-24.
//
//

#include "Rect.h"
#include <algorithm>
#include <math.h>

using std::max;
using std::min;

Rect Rect::narrowPrecision(double x, double y, double width, double height)
{
    return Rect(narrowPrecisionToFloat(x), narrowPrecisionToFloat(y), narrowPrecisionToFloat(width), narrowPrecisionToFloat(height));
}

bool Rect::intersects(const Rect& other) const
{
    // Checking emptiness handles negative widths as well as zero.
    return !isEmpty() && !other.isEmpty()
        && x() < other.maxX() && other.x() < maxX()
        && y() < other.maxY() && other.y() < maxY();
}

bool Rect::contains(const Rect& other) const
{
    return x() <= other.x() && maxX() >= other.maxX()
        && y() <= other.y() && maxY() >= other.maxY();
}

void Rect::intersect(const Rect& other)
{
    float l = max(x(), other.x());
    float t = max(y(), other.y());
    float r = min(maxX(), other.maxX());
    float b = min(maxY(), other.maxY());

    // Return a clean empty rectangle for non-intersecting cases.
    if (l >= r || t >= b) {
        l = 0;
        t = 0;
        r = 0;
        b = 0;
    }

    setLocationAndSizeFromEdges(l, t, r, b);
}

void Rect::unite(const Rect& other)
{
    // Handle empty special cases first.
    if (other.isEmpty())
        return;
    if (isEmpty()) {
        *this = other;
        return;
    }

    float l = min(x(), other.x());
    float t = min(y(), other.y());
    float r = max(maxX(), other.maxX());
    float b = max(maxY(), other.maxY());

    setLocationAndSizeFromEdges(l, t, r, b);
}

void Rect::uniteIfNonZero(const Rect& other)
{
    // Handle empty special cases first.
    if (!other.width() && !other.height())
        return;
    if (!width() && !height()) {
        *this = other;
        return;
    }

    float left = min(x(), other.x());
    float top = min(y(), other.y());
    float right = max(maxX(), other.maxX());
    float bottom = max(maxY(), other.maxY());

    setLocationAndSizeFromEdges(left, top, right, bottom);
}

void Rect::scale(float sx, float sy)
{
    m_location.setX(x() * sx);
    m_location.setY(y() * sy);
    m_size.setWidth(width() * sx);
    m_size.setHeight(height() * sy);
}

void Rect::fitToPoints(const FloatPoint& p0, const FloatPoint& p1)
{
    float left = min(p0.x(), p1.x());
    float top = min(p0.y(), p1.y());
    float right = max(p0.x(), p1.x());
    float bottom = max(p0.y(), p1.y());

    setLocationAndSizeFromEdges(left, top, right, bottom);
}

template <typename T>
T min3(const T& v1, const T& v2, const T& v3)
{
    return min(min(v1, v2), v3);
}

template <typename T>
T max3(const T& v1, const T& v2, const T& v3)
{
    return max(max(v1, v2), v3);
}

template <typename T>
T min4(const T& v1, const T& v2, const T& v3, const T& v4)
{
    return min(min(v1, v2), min(v3, v4));
}

template <typename T>
T max4(const T& v1, const T& v2, const T& v3, const T& v4)
{
    return max(max(v1, v2), max(v3, v4));
}

void Rect::fitToPoints(const FloatPoint& p0, const FloatPoint& p1, const FloatPoint& p2)
{
    float left = min3(p0.x(), p1.x(), p2.x());
    float top = min3(p0.y(), p1.y(), p2.y());
    float right = max3(p0.x(), p1.x(), p2.x());
    float bottom = max3(p0.y(), p1.y(), p2.y());

    setLocationAndSizeFromEdges(left, top, right, bottom);
}

void Rect::fitToPoints(const FloatPoint& p0, const FloatPoint& p1, const FloatPoint& p2, const FloatPoint& p3)
{
    float left = min4(p0.x(), p1.x(), p2.x(), p3.x());
    float top = min4(p0.y(), p1.y(), p2.y(), p3.y());
    float right = max4(p0.x(), p1.x(), p2.x(), p3.x());
    float bottom = max4(p0.y(), p1.y(), p2.y(), p3.y());

    setLocationAndSizeFromEdges(left, top, right, bottom);
}

Rect mapRect(const Rect& r, const Rect& srcRect, const Rect& destRect)
{
    if (srcRect.width() == 0 || srcRect.height() == 0)
        return Rect();

    float widthScale = destRect.width() / srcRect.width();
    float heightScale = destRect.height() / srcRect.height();
    return Rect(destRect.x() + (r.x() - srcRect.x()) * widthScale,
                     destRect.y() + (r.y() - srcRect.y()) * heightScale,
                     r.width() * widthScale, r.height() * heightScale);
}
