//
//  Damage.cpp
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-21.
//
//

#include "Damage.h"
#include "Bio.h"

Damage::Damage(PassRefPtr<Bio> source, PassRefPtr<Bio> target, DamageType type, DamageEffect effect)
: mSource(source)
, mTarget(target)
, mType(type)
, mEffect(effect) {

}

Damage::~Damage() {
    mSource = NULL;
    mTarget = NULL;
}

bool Damage::doDamage() {
    if (mTarget == NULL || mTarget->isDead())
        return false;
    
    bool ret = mTarget->takenDamage(mSource.get(), mType, mEffect);
    if (mSource)
        mSource->didDamageToTarget(mTarget.get(), mType, mEffect);
    return ret;
}

PhysicalDamage::PhysicalDamage(PassRefPtr<Bio> source, PassRefPtr<Bio> target,
                               float damage, float splashPercent, float splashRadius)
:Damage(source, target, PHYSICAL) {
    mEffect.mType = DamageEffect::SPLASH;
    mEffect.mFirstDamage = damage;
    mEffect.mSplashPercent = splashPercent;
    mEffect.mSplashRadius = splashRadius;
}