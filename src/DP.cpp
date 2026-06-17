#include <algorithm>

extern "C" {
    int* carveOptimalPath(int* topologicalGrid, unsigned int n, unsigned int m) {
        unsigned int totalSize = n * m;
        
        int* costMatrix = new int[totalSize];

        auto getIndex = [n](unsigned int x, unsigned int y) {
            return (y * n) + x;
        };

        
        costMatrix[0] = topologicalGrid[0];

        for (unsigned int x = 1; x < n; ++x) {
            costMatrix[getIndex(x, 0)] = costMatrix[getIndex(x - 1, 0)] + topologicalGrid[getIndex(x, 0)];
        }

        for (unsigned int y = 1; y < m; ++y) {
            costMatrix[getIndex(0, y)] = costMatrix[getIndex(0, y - 1)] + topologicalGrid[getIndex(0, y)];
        }

        for (unsigned int y = 1; y < m; ++y) {
            for (unsigned int x = 1; x < n; ++x) {
                int costFromLeft = costMatrix[getIndex(x - 1, y)];
                int costFromTop = costMatrix[getIndex(x, y - 1)];
                
                costMatrix[getIndex(x, y)] = topologicalGrid[getIndex(x, y)] + std::min(costFromLeft, costFromTop);
            }
        }

        
        int currentX = n - 1;
        int currentY = m - 1;

        pathGrid[getIndex(currentX, currentY)] = 1;

        while (currentX > 0 || currentY > 0) {
            if (currentX == 0) {
                currentY--;
            } else if (currentY == 0) {
                currentX--;
            } else {
                int costLeft = costMatrix[getIndex(currentX - 1, currentY)];
                int costTop = costMatrix[getIndex(currentX, currentY - 1)];

                if (costLeft < costTop) {
                } else {
                }
            }
            pathGrid[getIndex(currentX, currentY)] = 1;
        }

        delete[] costMatrix;

        return pathGrid;
    }
}
