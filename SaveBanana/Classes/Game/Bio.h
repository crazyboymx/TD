//
//  Bio.h
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-21.
//
//

#ifndef __SaveBanana__Bio__
#define __SaveBanana__Bio__

#include <iostream>
#include "RefCounted.h"
#include "Damage.h"

class Bio : public RefCounted<Bio> {
public:
    inline virtual ~Bio() {}
    
    float life() const { return mLife; }
    virtual void die() = 0;
    virtual bool takenDamage(Bio* source, Damage::DamageType type, Damage::DamageEffect effect) = 0;
    virtual void didDamageToTarget(const Bio* target, Damage::DamageType type, Damage::DamageEffect effect) {};
    
    bool isDead() const { return mLife <= 0; }
    bool isAlive() const { return !isDead(); }

protected:
    Bio() {}
    
    void appendDamage(Damage::DamageEffect effect) { mEffects.push_back(effect); }
private:
    // attributes
    float mLife;
    DamageEffectList mEffects;
};

#endif /* defined(__SaveBanana__Bio__) */
