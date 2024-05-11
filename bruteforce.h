#include <iostream>
#include <functional>
#include <vector>
#include <array>
#include <fstream>
#include <thread>
#include <mutex>
#include <string>
#include <queue>

template<typename T, size_t N>
std::vector<T> bruteForce(const std::vector<std::array<T, N>>& coordinates, const std::array<T, N> &query, int K) {
    size_t sz = coordinates.size();
    int mn = INT_MAX, argmin = -1;
    std::priority_queue<std::pair<int, int>> q;
    for(size_t i = 0; i < sz; i++) {
        T dist = distance(coordinates[i], query);
        q.emplace(dist, i);
        if(q.size() > K) q.pop();
        if(dist < mn) {
            mn = dist, argmin = i;
        }
    }
    std::vector<T> ret;
    while(!q.empty()) {
        auto [_, ind] = q.top(); 
        q.pop();
        ret.push_back(ind);
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

template<typename T, size_t N>
void each_thread(const std::vector<std::array<T, N>>& coordinates, const std::array<T, N> &query, size_t j, size_t num_threads, std::mutex &mtx, std::priority_queue<std::pair<int, int>>& q, int K) {
    size_t sz = coordinates.size();
    int mn = INT_MAX, argmin = -1;
    for(size_t i = j; i < sz; i += num_threads) {
        T dist = distance(coordinates[i], query);
        std::lock_guard<std::mutex> lock(mtx);
        q.emplace(dist, i);
        if(q.size() > K) q.pop();
    }
}

template<typename T, size_t N>
std::vector<int> bruteForce_threaded(std::vector<std::array<T, N>> coordinates, const std::array<T, N> &query, int K) {
    size_t num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::priority_queue<std::pair<int, int>> q;
    std::mutex mtx;
    for(size_t i = 0; i < num_threads; i++) {
        threads.push_back(std::thread(each_thread<T, N>, coordinates, query, i, num_threads, std::ref(mtx), std::ref(q), K));
    }
    for(size_t i = 0; i < num_threads; i++) {
        threads[i].join();
    }
    std::vector<int> indices;
    while(!q.empty()) {
        auto [_, ind] = q.top();
        q.pop();
        indices.push_back(ind);
    }
    reverse(indices.begin(), indices.end());
    return indices;
}