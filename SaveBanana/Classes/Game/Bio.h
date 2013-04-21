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

class Bio : public RefCounted<Bio> {
public:
    inline virtual ~Bio() {}
    
    virtual void die() = 0;

protected:
    Bio() {}
private:
};

#endif /* defined(__SaveBanana__Bio__) */
