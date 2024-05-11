#include <iostream>
#include <chrono>

#include "KDtree.h"
#include "bruteforce.h"
#include "util.h"

const size_t D = 3;
const size_t K = 3;

const std::string typ = "med";

std::vector<std::array<int, D>> coordinates;

int main() {
    std::ifstream file("./data/" + typ);
    if(!file.is_open()) {
        std::cerr << "Error: file not found\n";
        return EXIT_FAILURE;
    }

    std::array<int, D> a;
    while(file >> a) {
        coordinates.push_back(a);
    }

    file.close();
    KDTree<D> kdtree(coordinates);
    file.open("./data/" + typ + "-q", std::ifstream::in);

    std::array<int, D> query;

    int sumQuery = 0, total = 0;
    double avgTimeBruteForce = 0.0;
    double avgTimeKDTree = 0.0;

    while(file >> query) {
        total++;

        // auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> knearest = bruteForce<int, D>(coordinates, query, K);
        for(int a : knearest) {
            std::cout << coordinates[a] << "\n";
        }
        // auto end = std::chrono::high_resolution_clock::now();
        // std::chrono::duration<double> duration = end - start;
        // avgTimeBruteForce += duration.count();
        std::cout << "\n";
        std::vector<int> knearest_bf = bruteForce_threaded<int, D>(coordinates, query, K);
        for(int a : knearest_bf) {
            std::cout << coordinates[a] << "\n";
        }

        // start = std::chrono::high_resolution_clock::now();
        std::vector<std::array<int, D>> kdTreeAns = kdtree.nearestNeighbor(query, K);
        std::cout << "\n";
        for(std::array<int, D> a : kdTreeAns) {
            std::cout << a << "\n";
        }
        std::cout << "\n";
        // end = std::chrono::high_resolution_clock::now();
        // duration = end - start;
        // avgTimeKDTree += duration.count();

        // if(kdTreeAns == coordinates[bfInd]) {
        //     sumQuery++;
        // }

        // auto end = std::chrono::high_resolution_clock::now();
        // std::chrono::duration<double> duration = end - start;
        // std::cout << "Time taken: " << duration.count() << "\n";
        // start = std::chrono::high_resolution_clock::now();
        // std::cout << bruteForce_threaded(query) << "\n";
        // end = std::chrono::high_resolution_clock::now();
        // duration = end - start;
        // std::cout << "Time taken: " << duration.count() << "\n";
    }

    // std::cout << "Accuracy: " << sumQuery << " / " << total << "\n"; 
    // std::cout << "Benchmarks:\n";
    // std::cout << "Average Time Brute Force: " << avgTimeBruteForce / total << "\n";
    // std::cout << "Average Time KDTree: " << avgTimeKDTree / total << "\n"; 
}