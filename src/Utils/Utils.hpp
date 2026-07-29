/*
<Copyright Adam Kurbiel 2026>

Contains utility functions.
*/


#ifndef UTILS_HPP
#define UTILS_HPP

namespace utils {
    template <typename T>
    constexpr inline T lerp(T a, T b, T t) noexcept {
        return (static_cast<T>(1) - t) * a + t * b;
    }
}

#endif