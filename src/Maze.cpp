#include <cstdlib>

extern "C" {
    int* generateTopologicalGrid(unsigned int n, unsigned int m, unsigned int seed) {
        std::srand(seed);

        unsigned int totalSize = n * m;
        
        int* grid = new int[totalSize];

        for (unsigned int i = 0; i < totalSize; ++i) {
            grid[i] = (std::rand() % 100) + 1; 
        }

        return grid;
    }

    void freeGrid(int* grid) {
        delete[] grid;
    }
}
