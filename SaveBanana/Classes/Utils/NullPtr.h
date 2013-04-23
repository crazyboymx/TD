//
//  NullPtr.h
//  SaveBanana
//
//  Created by 朱 晓 on 13-4-23.
//
//

#ifndef __SaveBanana__NullPtr__
#define __SaveBanana__NullPtr__

#ifndef __has_feature
#define __has_feature(feature) 0
#endif

#if __has_feature(cxx_nullptr) || (defined(_MSC_VER) && _MSC_VER >= 1600)

#define HAVE_NULLPTR 1

#else

namespace std {
    class nullptr_t { };
}

extern std::nullptr_t nullptr;

#endif

#endif /* defined(__SaveBanana__NullPtr__) */
