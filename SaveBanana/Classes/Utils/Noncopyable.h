//
//  Noncopyable.h
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-21.
//
//

#ifndef SaveBanana_Noncopyable_h
#define SaveBanana_Noncopyable_h

#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if __has_feature(cxx_deleted_functions)
    #define MAKE_NONCOPYABLE(ClassName) \
        _Pragma("clang diagnostic push") \
        _Pragma("clang diagnostic ignored \"-Wunknown-pragmas\"") \
        _Pragma("clang diagnostic ignored \"-Wc++0x-extensions\"") \
        private: \
            ClassName(const ClassName&) = delete; \
            ClassName& operator=(const ClassName&) = delete; \
        _Pragma("clang diagnostic pop")
#else
    #define MAKE_NONCOPYABLE(ClassName) \
        private: \
            ClassName(const ClassName&); \
            ClassName& operator=(const ClassName&)
#endif

#endif /* defined(SaveBanana_Noncopyable_h) */
