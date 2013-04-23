//
//  PassRefPtr.h
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-21.
//
//

#ifndef SaveBanana_PassRefPtr_h
#define SaveBanana_PassRefPtr_h

#include "NullPtr.h"

template<typename T> class RefPtr;
template<typename T> class PassRefPtr;
template<typename T> PassRefPtr<T> adoptRef(T*);

inline void adopted(const void*) { }

template<typename T> void refIfNotNull(T* ptr)
{
    if (ptr != 0)
        ptr->ref();
}

template<typename T> void derefIfNotNull(T* ptr)
{
    if (ptr != 0)
        ptr->deref();
}


template<typename T> class PassRefPtr {
public:
    PassRefPtr() : m_ptr(0) { }
    PassRefPtr(T* ptr) : m_ptr(ptr) { refIfNotNull(ptr); }
    // It somewhat breaks the type system to allow transfer of ownership out of
    // a const PassRefPtr. However, it makes it much easier to work with PassRefPtr
    // temporaries, and we don't have a need to use real const PassRefPtrs anyway.
    PassRefPtr(const PassRefPtr& o) : m_ptr(o.leakRef()) { }
    template<typename U> PassRefPtr(const PassRefPtr<U>& o) : m_ptr(o.leakRef()) { }
    
    inline ~PassRefPtr() { derefIfNotNull(m_ptr); }
    
    template<typename U> PassRefPtr(const RefPtr<U>&);
    
    T* get() const { return m_ptr; }
    
    void clear();
    T* leakRef() const;
    
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    
    bool operator!() const { return !m_ptr; }
    
    // This conversion operator allows implicit conversion to bool but not to other integer types.
    typedef T* (PassRefPtr::*UnspecifiedBoolType);
    operator UnspecifiedBoolType() const { return m_ptr ? &PassRefPtr::m_ptr : 0; }
    
    PassRefPtr& operator=(T*);
    PassRefPtr& operator=(const PassRefPtr&);
    PassRefPtr& operator=(std::nullptr_t) { clear(); return *this; }
    template<typename U> PassRefPtr& operator=(const PassRefPtr<U>&);
    template<typename U> PassRefPtr& operator=(const RefPtr<U>&);
    
    friend PassRefPtr adoptRef<T>(T*);
    
    // FIXME: Remove releaseRef once we change all callers to call leakRef instead.
    T* releaseRef() const { return leakRef(); }
    
private:
    // adopting constructor
    PassRefPtr(T* ptr, bool) : m_ptr(ptr) { }
    
    mutable T* m_ptr;
};

template<typename T> template<typename U> inline PassRefPtr<T>::PassRefPtr(const RefPtr<U>& o)
: m_ptr(o.get())
{
    T* ptr = m_ptr;
    refIfNotNull(ptr);
}

template<typename T> inline void PassRefPtr<T>::clear()
{
    T* ptr = m_ptr;
    m_ptr = 0;
    derefIfNotNull(ptr);
}

template<typename T> inline T* PassRefPtr<T>::leakRef() const
{
    T* ptr = m_ptr;
    m_ptr = 0;
    return ptr;
}

template<typename T> template<typename U> inline PassRefPtr<T>& PassRefPtr<T>::operator=(const RefPtr<U>& o)
{
    T* optr = o.get();
    refIfNotNull(optr);
    T* ptr = m_ptr;
    m_ptr = optr;
    derefIfNotNull(ptr);
    return *this;
}

template<typename T> inline PassRefPtr<T>& PassRefPtr<T>::operator=(T* optr)
{
    refIfNotNull(optr);
    T* ptr = m_ptr;
    m_ptr = optr;
    derefIfNotNull(ptr);
    return *this;
}

template<typename T> inline PassRefPtr<T>& PassRefPtr<T>::operator=(const PassRefPtr<T>& ref)
{
    T* ptr = m_ptr;
    m_ptr = ref.leakRef();
    derefIfNotNull(ptr);
    return *this;
}

template<typename T> template<typename U> inline PassRefPtr<T>& PassRefPtr<T>::operator=(const PassRefPtr<U>& ref)
{
    T* ptr = m_ptr;
    m_ptr = ref.leakRef();
    derefIfNotNull(ptr);
    return *this;
}

template<typename T, typename U> inline bool operator==(const PassRefPtr<T>& a, const PassRefPtr<U>& b)
{
    return a.get() == b.get();
}

template<typename T, typename U> inline bool operator==(const PassRefPtr<T>& a, const RefPtr<U>& b)
{
    return a.get() == b.get();
}

template<typename T, typename U> inline bool operator==(const RefPtr<T>& a, const PassRefPtr<U>& b)
{
    return a.get() == b.get();
}

template<typename T, typename U> inline bool operator==(const PassRefPtr<T>& a, U* b)
{
    return a.get() == b;
}

template<typename T, typename U> inline bool operator==(T* a, const PassRefPtr<U>& b)
{
    return a == b.get();
}

template<typename T, typename U> inline bool operator!=(const PassRefPtr<T>& a, const PassRefPtr<U>& b)
{
    return a.get() != b.get();
}

template<typename T, typename U> inline bool operator!=(const PassRefPtr<T>& a, const RefPtr<U>& b)
{
    return a.get() != b.get();
}

template<typename T, typename U> inline bool operator!=(const RefPtr<T>& a, const PassRefPtr<U>& b)
{
    return a.get() != b.get();
}

template<typename T, typename U> inline bool operator!=(const PassRefPtr<T>& a, U* b)
{
    return a.get() != b;
}

template<typename T, typename U> inline bool operator!=(T* a, const PassRefPtr<U>& b)
{
    return a != b.get();
}

template<typename T> inline PassRefPtr<T> adoptRef(T* p)
{
    adopted(p);
    return PassRefPtr<T>(p, true);
}

template<typename T, typename U> inline PassRefPtr<T> static_pointer_cast(const PassRefPtr<U>& p)
{
    return adoptRef(static_cast<T*>(p.leakRef()));
}

template<typename T, typename U> inline PassRefPtr<T> const_pointer_cast(const PassRefPtr<U>& p)
{
    return adoptRef(const_cast<T*>(p.leakRef()));
}

template<typename T> inline T* getPtr(const PassRefPtr<T>& p)
{
    return p.get();
}

#endif /* defined(SaveBanana_PassRefPtr_h) */
