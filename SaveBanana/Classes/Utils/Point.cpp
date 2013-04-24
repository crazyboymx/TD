//
//  Point.cpp
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-24.
//
//

#include "Point.h"
#include <limits>
#include <math.h>

Point::Point(const IntPoint& p) : m_x(p.x()), m_y(p.y())
{
}

void Point::normalize()
{
    float tempLength = length();

    if (tempLength) {
        m_x /= tempLength;
        m_y /= tempLength;
    }
}

float Point::length() const
{
    return sqrtf(lengthSquared());
}

Point Point::narrowPrecision(double x, double y)
{
    return Point(narrowPrecisionToFloat(x), narrowPrecisionToFloat(y));
}

float findSlope(const Point& p1, const Point& p2, float& c)
{
    if (p2.x() == p1.x())
        return std::numeric_limits<float>::infinity();

    // y = mx + c
    float slope = (p2.y() - p1.y()) / (p2.x() - p1.x());
    c = p1.y() - slope * p1.x();
    return slope;
}

bool findIntersection(const Point& p1, const Point& p2, const Point& d1, const Point& d2, Point& intersection) 
{
    float pOffset = 0;
    float pSlope = findSlope(p1, p2, pOffset);

    float dOffset = 0;
    float dSlope = findSlope(d1, d2, dOffset);

    if (dSlope == pSlope)
        return false;

    if (pSlope == std::numeric_limits<float>::infinity()) {
        intersection.setX(p1.x());
        intersection.setY(dSlope * intersection.x() + dOffset);
        return true;
    }
    if (dSlope == std::numeric_limits<float>::infinity()) {
        intersection.setX(d1.x());
        intersection.setY(pSlope * intersection.x() + pOffset);
        return true;
    }

    // Find x at intersection, where ys overlap; x = (c' - c) / (m - m')
    intersection.setX((dOffset - pOffset) / (pSlope - dSlope));
    intersection.setY(pSlope * intersection.x() + pOffset);
    return true;
}
