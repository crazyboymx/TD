//
//  Fluit.h
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-21.
//
//

#ifndef __SaveBanana__Fluit__
#define __SaveBanana__Fluit__

#include <iostream>
#include "Bio.h"

class Fluit : public Bio {
public:
    inline virtual ~Fluit(){}
protected:
    Fluit(const Point& position, const Size& size, float life, float speed = 0.0f, float angle = 0.0f)
        : Bio(position, size, life, speed, angle) {}
};

#endif /* defined(__SaveBanana__Fluit__) */
