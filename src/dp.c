#define MIN(a, b) ((a) < (b) ? (a) : (b))

extern void* simple_malloc(unsigned int size);

void* memset(void* dest, int val, unsigned int len) {
    unsigned char* ptr = (unsigned char*)dest;
    while (len-- > 0) *ptr++ = val;
    return dest;
}

int* carveOptimalPath(int* topologicalGrid, unsigned int n, unsigned int m) {
    unsigned int totalSize = n * m;
    
    int* costMatrix = (int*)simple_malloc(totalSize * sizeof(int));
    int* pathGrid = (int*)simple_malloc(totalSize * sizeof(int));

    for(unsigned int i = 0; i < totalSize; ++i) {
        pathGrid[i] = 0;
    }

    costMatrix[0] = topologicalGrid[0];

    for (unsigned int x = 1; x < n; ++x) {
        costMatrix[x] = costMatrix[x - 1] + topologicalGrid[x];
    }

    for (unsigned int y = 1; y < m; ++y) {
        costMatrix[y * n] = costMatrix[(y - 1) * n] + topologicalGrid[y * n];
    }

    for (unsigned int y = 1; y < m; ++y) {
        for (unsigned int x = 1; x < n; ++x) {
            int costFromLeft = costMatrix[y * n + (x - 1)];
            int costFromTop = costMatrix[(y - 1) * n + x];
            
            costMatrix[y * n + x] = topologicalGrid[y * n + x] + MIN(costFromLeft, costFromTop);
        }
    }

    int currentX = n - 1;
    int currentY = m - 1;

    pathGrid[currentY * n + currentX] = 1;

    while (currentX > 0 || currentY > 0) {
        if (currentX == 0) {
            currentY--;
        } else if (currentY == 0) {
            currentX--;
        } else {
            int costLeft = costMatrix[currentY * n + (currentX - 1)];
            int costTop = costMatrix[(currentY - 1) * n + currentX];

            if (costLeft < costTop) {
                currentX--;
            } else {
                currentY--;
            }
        }
        pathGrid[currentY * n + currentX] = 1;
    }

    return pathGrid;
}