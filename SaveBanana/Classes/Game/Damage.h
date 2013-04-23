//
//  Damage.h
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-21.
//
//

#ifndef __SaveBanana__Damage__
#define __SaveBanana__Damage__

#include <vector>
#include <iostream>
#include "RefCounted.h"
#include "PassRefPtr.h"
#include "RefPtr.h"

#define DEFAULT_SPLASH_PERCENT  0.3f    // 30% splash damage
#define DEFAULT_SPLASH_RADIUS   100
#define DEFAULT_STUN_DURATION   3       // 3 seconds
#define DEFAULT_DOT_DAMAGE      100
#define DEFAULT_SLOW_DOWN       0.3f    // slow down 30% speed

class Bio;

class Damage : public RefCounted<Damage> {
public:
    enum DamageType {
        UNKNOWN     = 0X0000,
        FIRE        = 0X0001,
        ICE         = 0X0002,
        LIGHT       = 0X0004,
        POISON      = 0X0008,
        PHYSICAL    = 0X0010,
        ARCANE      = 0X0020,
    };

    struct DamageEffect {
        enum EffectType {
            NONE        = 0X0000,
            STUN        = 0X0001,
            SLOWDOWN    = 0X0002,
            POISON      = 0X0004,
            FIRE        = 0X0008,
            SPLASH      = 0x0010,
        } mType;
        
        float mFirstDamage;
        float mDuration;
        long mBeginTime;
        
        // For SLOWDOWN
        float mSlowPercent;
        // For POSION and FIRE
        float mDotDamage;
        // For SPLASH
        float mSplashPercent;
        float mSplashRadius;
        
        DamageEffect() {
            mType = NONE;
            mFirstDamage = 0;
            mDuration = 0;
            mBeginTime = 0;
            mSlowPercent = 0;
            mDotDamage = 0;
            mSplashPercent = 0;
            mSplashRadius = 0;
        }
        
        static DamageEffect noEffect() {
            return DamageEffect();
        }
    };

    inline virtual ~Damage();
    
    virtual bool doDamage();
    
protected:
    Damage(PassRefPtr<Bio> source, PassRefPtr<Bio> target,
           DamageType type = UNKNOWN, DamageEffect effect = DamageEffect::noEffect());
    
protected:
    DamageType mType;
    DamageEffect mEffect;
    
    RefPtr<Bio> mSource;
    RefPtr<Bio> mTarget;
};

typedef std::vector<Damage::DamageEffect> DamageEffectList;

class PhysicalDamage : public Damage {
public:
    static PassRefPtr<PhysicalDamage> create(PassRefPtr<Bio> source, PassRefPtr<Bio> target,
                                             float damage = 0, float splashPercent = DEFAULT_SPLASH_PERCENT,
                                             float splashRadius = DEFAULT_SPLASH_RADIUS) {
        return adoptRef(new PhysicalDamage(source, target, damage, splashPercent, splashRadius));
    }
    
    virtual ~PhysicalDamage() {}
    
protected:
    PhysicalDamage(PassRefPtr<Bio> source, PassRefPtr<Bio> target, float damage, float splashPercent, float splashRadius);
};

#endif /* defined(__SaveBanana__Damage__) */
