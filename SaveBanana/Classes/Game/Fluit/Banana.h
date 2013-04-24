//
//  Banana.h
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-21.
//
//

#ifndef __SaveBanana__Banana__
#define __SaveBanana__Banana__

#include <iostream>
#include "PassRefPtr.h"
#include "RefPtr.h"
#include "Fluit.h"

class Banana : public Fluit {
public:
    static PassRefPtr<Banana> create(const Point& position, const Size& size,
        float life, float speed = 0.0f, float angle = 0.0f) {
        return adoptRef(new Banana(position, size, life, speed, angle));
    }
    inline virtual ~Banana();

    virtual void die() {}
protected:
    Banana(const Point& position, const Size& size, float life, float speed = 0.0f, float angle = 0.0f);
private:
};

#endif /* defined(__SaveBanana__Banana__) */
