#include <iostream>
#include <array>

template<typename T, size_t N>
std::istream& operator>>(std::istream& is, std::array<T, N>& arr) {
    for (size_t i = 0; i < N; ++i) {
        is >> arr[i];
    }
    return is;
}

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& is, std::array<T, N>& arr) {
    for (size_t i = 0; i < N; ++i) {
        is << arr[i] << " ";
    }
    return is;
}

