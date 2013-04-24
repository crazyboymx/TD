//
//  Size.h
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-24.
//
//

#ifndef __SaveBanana__Size__
#define __SaveBanana__Size__

class Size {
public:
    Size() : m_width(0), m_height(0) { }
    Size(float width, float height) : m_width(width), m_height(height) { }

    static Size narrowPrecision(double width, double height);

    float width() const { return m_width; }
    float height() const { return m_height; }

    void setWidth(float width) { m_width = width; }
    void setHeight(float height) { m_height = height; }

    bool isEmpty() const { return m_width <= 0 || m_height <= 0; }

    float aspectRatio() const { return m_width / m_height; }

    void scale(float scale)
    {
        m_width *= scale;
        m_height *= scale;
    }

    Size expandedTo(const Size& other) const
    {
        return Size(m_width > other.m_width ? m_width : other.m_width,
            m_height > other.m_height ? m_height : other.m_height);
    }

    Size shrunkTo(const Size& other) const
    {
       return Size(m_width < other.m_width ? m_width : other.m_width,
           m_height < other.m_height ? m_height : other.m_height);
    }

    float diagonalLength() const;
    float diagonalLengthSquared() const
    {
        return m_width * m_width + m_height * m_height;
    }

private:
    float m_width, m_height;
};

inline Size& operator+=(Size& a, const Size& b)
{
    a.setWidth(a.width() + b.width());
    a.setHeight(a.height() + b.height());
    return a;
}

inline Size& operator-=(Size& a, const Size& b)
{
    a.setWidth(a.width() - b.width());
    a.setHeight(a.height() - b.height());
    return a;
}

inline Size operator+(const Size& a, const Size& b)
{
    return Size(a.width() + b.width(), a.height() + b.height());
}

inline Size operator-(const Size& a, const Size& b)
{
    return Size(a.width() - b.width(), a.height() - b.height());
}

inline Size operator-(const Size& size)
{
    return Size(-size.width(), -size.height());
}

inline bool operator==(const Size& a, const Size& b)
{
    return a.width() == b.width() && a.height() == b.height();
}

inline bool operator!=(const Size& a, const Size& b)
{
    return a.width() != b.width() || a.height() != b.height();
}

inline float narrowPrecisionToFloat(double number)
{
    return static_cast<float>(number);
}

#endif /* defined(__SaveBanana__Size__) */
