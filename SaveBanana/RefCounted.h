//
//  RefCounted.h
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-21.
//
//

#ifndef SaveBanana_RefCounted_h
#define SaveBanana_RefCounted_h

#include "Noncopyable.h"

class RefCountedBase {
public:
    void ref()
    {
        ++m_refCount;
    }
    
    bool hasOneRef() const
    {
        return m_refCount == 1;
    }
    
    int refCount() const
    {
        return m_refCount;
    }
    
    void relaxAdoptionRequirement()
    {
#ifndef NDEBUG
        m_adoptionIsRequired = false;
#endif
    }
    
    // Helper for generating JIT code. Please do not use for non-JIT purposes.
    const int* addressOfCount() const
    {
        return &m_refCount;
    }
    
protected:
    RefCountedBase()
    : m_refCount(1)
#ifndef NDEBUG
    , m_deletionHasBegun(false)
    , m_adoptionIsRequired(true)
#endif
    {
    }
    
    ~RefCountedBase()
    {
    }
    
    // Returns whether the pointer should be freed or not.
    bool derefBase()
    {
        if (m_refCount == 1) {
#ifndef NDEBUG
            m_deletionHasBegun = true;
#endif
            return true;
        }
        
        --m_refCount;
        return false;
    }
    
#ifndef NDEBUG
    bool deletionHasBegun() const
    {
        return m_deletionHasBegun;
    }
#endif
    
private:
    template<typename T> friend class CrossThreadRefCounted;
    
#ifndef NDEBUG
    friend void adopted(RefCountedBase*);
#endif
    
    int m_refCount;
#ifndef NDEBUG
    bool m_deletionHasBegun;
    bool m_adoptionIsRequired;
#endif
};

#ifndef NDEBUG

inline void adopted(RefCountedBase* object)
{
    if (!object)
        return;
    object->m_adoptionIsRequired = false;
}

#endif

template<typename T> class RefCounted : public RefCountedBase {
    MAKE_NONCOPYABLE(RefCounted);
public:
    void deref()
    {
        if (derefBase())
            delete static_cast<T*>(this);
    }
    
protected:
    RefCounted() { }
    ~RefCounted()
    {
    }
};

#endif /* defined(SaveBanana_RefCounted_h) */
