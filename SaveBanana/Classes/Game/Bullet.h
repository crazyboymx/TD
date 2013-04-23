//
//  Bullet.h
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-21.
//
//

#ifndef __SaveBanana__Bullet__
#define __SaveBanana__Bullet__

#include <iostream>
#include "RefCounted.h"
#include "RefPtr.h"

class Bio;


class Bullet : public RefCounted<Bullet> {
public:
    inline virtual ~Bullet() {};
    
    Bio* shooter() const { return mShooter.get(); }
protected:
    Bullet(PassRefPtr<Bio> shooter, PassRefPtr<Bio> target);
private:
    RefPtr<Bio> mShooter;
    float mSpeed;   // speed per second.
    float mAngle;   // Angle in degree
    float mPosition;
};

#endif /* defined(__SaveBanana__Bullet__) */
