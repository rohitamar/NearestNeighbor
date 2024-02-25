#include <functional>
#include <chrono>

template<class R, class... Args>
struct TimeDec<R(Args ...)> {
public:
    TimeDec(std::function<R(Args...)> func): f_(func) { }

    R operator ()(Args ...args) {
        auto start = std::chrono::high_resolution_clock::now();
        R res = f_(args);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << duration.count() << std::endl;
        return res;
    }
private:
    std::function<R(Args ...)> f_;
};
