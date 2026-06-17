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

int* generateTopologicalGrid(unsigned int n, unsigned int m, unsigned int seed) {
    simple_srand(seed);

    unsigned int totalSize = n * m;
    int* grid = (int*)simple_malloc(totalSize * sizeof(int));

    for (unsigned int i = 0; i < totalSize; ++i) {
        grid[i] = (simple_rand() % 100) + 1; 
    }

    return grid;
}
