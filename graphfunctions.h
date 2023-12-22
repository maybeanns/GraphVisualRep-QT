#ifndef GRAPHFUNCTIONS_H
#define GRAPHFUNCTIONS_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

                                    // Function to generate an adjacency matrix
std::vector<std::vector<int>> generateAdjacencyMatrix(int numNodes, double density) {
    // Seed the random number generator
    std::srand(std::time(0));

    // Initialize the adjacency matrix with zeros
    std::vector<std::vector<int>> adjacencyMatrix(numNodes, std::vector<int>(numNodes, 0));

    // Populate the adjacency matrix based on density
    for (int i = 0; i < numNodes; ++i) {
        for (int j = i + 1; j < numNodes; ++j) {
            if ((std::rand() % 100) < density * 100) {
                // If the random value is less than density, connect nodes i and j
                adjacencyMatrix[i][j] = 1;
                adjacencyMatrix[j][i] = 1;
            }
        }
    }

    return adjacencyMatrix;
}

                                    // Function to print the adjacency matrix
void printAdjacencyMatrix(const std::vector<std::vector<int>>& adjacencyMatrix) {
    for (const auto& row : adjacencyMatrix) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}



#endif
