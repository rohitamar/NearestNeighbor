#include <iostream>
#include <functional>
#include <vector>
#include <array>
#include <fstream>
#include <thread>
#include <mutex>
#include <string>

#include "bruteforce.h"
#include "KDtree.h"
#include "util.h"

const size_t S = 100;
const std::string typ = "med";

std::vector<std::array<int, S>> coordinates;

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

    KDTree<S> kdtree(coordinates);

    file.open("./data/" + typ + "-q", std::ifstream::in);

    std::array<int, S> query;
    while(file >> query) {
        // auto start = std::chrono::high_resolution_clock::now();
        int coordInd = bruteForce<int, S>(coordinates, query);

        std::cout << coordinates[coordInd] << "\n";
        
        std::array<int, S> ans = kdtree.nearestNeighbor(query);
        std::cout << ans << "\n";
        // auto end = std::chrono::high_resolution_clock::now();
        // std::chrono::duration<double> duration = end - start;
        // std::cout << "Time taken: " << duration.count() << "\n";



        // start = std::chrono::high_resolution_clock::now();
        // std::cout << bruteForce_threaded(query) << "\n";
        // end = std::chrono::high_resolution_clock::now();
        // duration = end - start;
        // std::cout << "Time taken: " << duration.count() << "\n";
    }
}