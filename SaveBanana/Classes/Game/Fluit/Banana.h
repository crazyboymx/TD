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
    static PassRefPtr<Banana> create() {
        return adoptRef(new Banana());
    }
    inline virtual ~Banana();
    
    void die();
protected:
    Banana();
private:
};

#endif /* defined(__SaveBanana__Banana__) */
