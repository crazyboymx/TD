//
//  Bio.h
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-21.
//
//

#ifndef __SaveBanana__Bio__
#define __SaveBanana__Bio__

#include "RefCounted.h"
#include "Point.h"
#include "Damage.h"

class Bio : public RefCounted<Bio> {
public:
    inline virtual ~Bio() {}

    float life() const { return mLife; }
    Position position() const { return mPosition; }
    Size size() const { return size; }
    float angle() const { return mAngle; }
    float speed() const { return mSpeed; }
    bool canMove() const { return false; }

    virtual void die() = 0;
    virtual bool takenDamage(Bio* source, Damage::DamageType type, Damage::DamageEffect effect) = 0;
    virtual void didDamageToTarget(const Bio* target, Damage::DamageType type, Damage::DamageEffect effect) {};

    bool isDead() const { return mLife <= 0; }
    bool isAlive() const { return !isDead(); }

protected:
    Bio(const Point& position, const Size& size, float life, float speed, float angle = 0.0f)
        : mPosition(position), mSize(size), mLife(life), mSpeed(speed), mAngle(angle) {}

    void appendDamage(Damage::DamageEffect effect) { mEffects.push_back(effect); }
private:
    // attributes
    Point mPosition;
    Size mSize;
    float mLife;
    float mSpeed;
    float mAngle // in Degree, clockwise, east for 0 degree.
    DamageEffectList mEffects;
};

#endif /* defined(__SaveBanana__Bio__) */
