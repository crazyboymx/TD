//
//  Size.cpp
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-24.
//
//

#include "Size.h"
#include <math.h>

float Size::diagonalLength() const
{
    return sqrtf(diagonalLengthSquared());
}

Size Size::narrowPrecision(double width, double height)
{
    return Size(narrowPrecisionToFloat(width), narrowPrecisionToFloat(height));
}
