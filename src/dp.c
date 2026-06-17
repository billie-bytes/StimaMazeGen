#define MIN(a, b) ((a) < (b) ? (a) : (b))

extern void* simple_malloc(unsigned int size);
extern int simple_rand(void);

void addRandomBranch(int* pathGrid, unsigned int n, unsigned int m);

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
    
    int number_of_branch = ((simple_rand()%10)+1);
    for(int i = 0; i<number_of_branch; ++i){
        addRandomBranch(pathGrid, n, m);
    }

    return pathGrid;
}


// Helper for Manhattan distance
static int simple_abs(int x) {
    return x < 0 ? -x : x;
}

void addRandomBranch(int* pathGrid, unsigned int n, unsigned int m) {
    unsigned int totalSize = n * m;
    int emptyCount = 0;
    
    // Check if there are any empty spaces to start a branch
    for (unsigned int i = 0; i < totalSize; i++) {
        if (pathGrid[i] == 0) emptyCount++;
    }
    
    if (emptyCount == 0) return;

    unsigned int startX, startY;
    do {
        unsigned int idx = (unsigned int)simple_rand() % totalSize;
        startX = idx % n;
        startY = idx / n;
    } while (pathGrid[startY * n + startX] != 0);

    int minDistance = totalSize + 1; 
    unsigned int targetX = startX, targetY = startY;

    for (unsigned int y = 0; y < m; y++) {
        for (unsigned int x = 0; x < n; x++) {
            if (pathGrid[y * n + x] == 1) { 
                int dist = simple_abs((int)startX - (int)x) + simple_abs((int)startY - (int)y);
                if (dist < minDistance) {
                    minDistance = dist;
                    targetX = x;
                    targetY = y;
                }
            }
        }
    }

    int currX = startX;
    int currY = startY;
    
    while (currX != (int)targetX || currY != (int)targetY) {
        pathGrid[currY * n + currX] = 1; 

        if (simple_abs(currX - (int)targetX) > simple_abs(currY - (int)targetY)) {
            currX += (currX < (int)targetX) ? 1 : -1;
        } else {
            currY += (currY < (int)targetY) ? 1 : -1;
        }
    }
}