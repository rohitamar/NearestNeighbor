#include <iostream>
#include <functional>
#include <vector>
#include <array>
#include <fstream>
#include <thread>
#include <mutex>
#include <string>

const size_t S = 250;
const std::string typ = "large";

std::vector<std::array<int, S>> coordinates;

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

template<typename T, size_t N>
int bruteForce(const std::array<T, N> &query) {
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
void each_thread(const std::array<T, N> &query, size_t j, size_t num_threads, std::mutex &mtx, int &g_mn, int &g_argmin) {
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
int bruteForce_threaded(const std::array<T, N> &query) {
    size_t num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    int g_mn = INT_MAX, g_argmin = -1;
    std::mutex mtx;
    for(size_t i = 0; i < num_threads; i++) {
        threads.push_back(std::thread(each_thread<T, N>, query, i, num_threads, std::ref(mtx), std::ref(g_mn), std::ref(g_argmin)));
    }
    for(size_t i = 0; i < num_threads; i++) {
        threads[i].join();
    }
    return g_argmin;
}

int main() {
    std::ifstream file("./data/" + typ);
    if(!file.is_open()) {
        std::cerr << "Error: file not found\n";
        return EXIT_FAILURE;
    }

    std::array<int, S> a;
    while(file >> a) {
        coordinates.push_back(a);
    }

    file.close();
    file.open("./data/" + typ + "-q", std::ifstream::in);

    std::array<int, S> query;
    while(file >> query) {
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << bruteForce(query) << "\n";
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time taken: " << duration.count() << "\n";

        start = std::chrono::high_resolution_clock::now();
        std::cout << bruteForce_threaded(query) << "\n";
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "Time taken: " << duration.count() << "\n";
    }
}