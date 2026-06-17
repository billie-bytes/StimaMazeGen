static unsigned int next_seed = 1;

void simple_srand(unsigned int seed) {
    next_seed = seed;
}

int simple_rand(void) {
    next_seed = next_seed * 1103515245 + 12345;
    return (unsigned int)(next_seed / 65536) % 32768;
}

int memory_pool[100000];
int memory_index = 0;

void resetMemory() {
    memory_index = 0;
}

void* simple_malloc(unsigned int size) {
    unsigned int alloc_size = (size + 3) / 4;
    void* ptr = &memory_pool[memory_index];
    memory_index += alloc_size;
    return ptr;
}

/* Struct to track intermediate subgoals */
typedef struct {
    unsigned int x;
    unsigned int y;
} Subgoal;

/* Generates ordered, scattered subgoals guaranteed to be reachable moving only down/right */
void generateSubgoals(unsigned int n, unsigned int m, Subgoal* subgoals, unsigned int num_subgoals) {
    for (unsigned int i = 0; i < num_subgoals; ++i) {
        unsigned int prev_x = (i == 0) ? 0 : subgoals[i - 1].x;
        unsigned int prev_y = (i == 0) ? 0 : subgoals[i - 1].y;
        
        // Calculate a progressive window bounding box to ensure non-decreasing order
        unsigned int next_x = ((i + 2) * (n - 1)) / (num_subgoals + 1);
        unsigned int next_y = ((i + 2) * (m - 1)) / (num_subgoals + 1);
        if (i == num_subgoals - 1) {
            next_x = n - 1;
            next_y = m - 1;
        }
        
        unsigned int range_x = next_x - prev_x + 1;
        unsigned int range_y = next_y - prev_y + 1;
        
        subgoals[i].x = prev_x + (simple_rand() % range_x);
        subgoals[i].y = prev_y + (simple_rand() % range_y);
        
        // Safeguards
        if (subgoals[i].x >= n) subgoals[i].x = n - 1;
        if (subgoals[i].y >= m) subgoals[i].y = m - 1;
    }
}

int* generateTopologicalGrid(unsigned int n, unsigned int m, unsigned int seed) {
    simple_srand(seed);

    unsigned int totalSize = n * m;
    int* grid = (int*)simple_malloc(totalSize * sizeof(int));

    for (unsigned int i = 0; i < totalSize; ++i) {
        grid[i] = (simple_rand() % 100) + 1; 
    }

    return grid;
}