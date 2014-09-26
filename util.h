#ifndef UTIL_H_
#define UTIL_H_

#include <sstream>

template<typename T>
inline std::string to_string(const T& val) {
    std::stringstream ss;
    if (ss << val)
        return ss.str();
    return "";
}

#endif  // UTIL_H_