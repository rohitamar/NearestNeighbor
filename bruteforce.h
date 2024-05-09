#include <iostream>
#include <functional>
#include <vector>
#include <array>
#include <fstream>
#include <thread>
#include <mutex>
#include <string>

template<typename T, size_t N>
int bruteForce(const std::vector<std::array<T, N>>& coordinates, const std::array<T, N> &query) {
    size_t sz = coordinates.size();
    int mn = INT_MAX, argmin = -1;
    for(size_t i = 0; i < sz; i++) {
        int dist = 0;
        for(size_t k = 0; k < N; k++) {
            dist += (coordinates[i][k] - query[k]) * (coordinates[i][k] - query[k]);
        }
        if(dist < mn) {
            mn = dist, argmin = i;
        }
    }
    return argmin;
}

template<typename T, size_t N>
void each_thread(const std::vector<std::array<T, N>>& coordinates, const std::array<T, N> &query, size_t j, size_t num_threads, std::mutex &mtx, int &g_mn, int &g_argmin) {
    size_t sz = coordinates.size();
    int mn = INT_MAX, argmin = -1;
    for(size_t i = j; i < sz; i += num_threads) {
        int dist = 0;
        for(size_t k = 0; k < N; k++) {
            dist += (coordinates[i][k] - query[k]) * (coordinates[i][k] - query[k]);
        }
        if(dist < mn) {
            mn = dist, argmin = i;
        }
    }
    std::lock_guard<std::mutex> lock(mtx);
    if(mn < g_mn) {
        g_mn = mn, g_argmin = argmin;
    }
}

template<typename T, size_t N>
int bruteForce_threaded(std::vector<std::array<T, N>> coordinates, const std::array<T, N> &query) {
    size_t num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    int g_mn = INT_MAX, g_argmin = -1;
    std::mutex mtx;
    for(size_t i = 0; i < num_threads; i++) {
        threads.push_back(std::thread(each_thread<T, N>, coordinates, query, i, num_threads, std::ref(mtx), std::ref(g_mn), std::ref(g_argmin)));
    }
    for(size_t i = 0; i < num_threads; i++) {
        threads[i].join();
    }
    return g_argmin;
}