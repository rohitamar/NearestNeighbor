#include <iostream>
#include <array>
#include <functional>
#include <chrono>

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

// template<class R, class... Args>
// struct TimeDec<R(Args ...)> {
// public:
//     TimeDec(std::function<R(Args...)> func): f_(func) { }

//     R operator ()(Args ...args) {
//         auto start = std::chrono::high_resolution_clock::now();
//         R res = f_(args);
//         auto end = std::chrono::high_resolution_clock::now();
//         std::chrono::duration<double> duration = end - start;
//         std::cout << duration.count() << std::endl;
//         return res;
//     }
// private:
//     std::function<R(Args ...)> f_;
// };
