document.getElementById('generate-btn').addEventListener('click', () => {
    const n = parseInt(document.getElementById('input-n').value);
    const m = parseInt(document.getElementById('input-m').value);
    
    // Generate a random seed for the C++ RNG
    const seed = Math.floor(Math.random() * 1000000);

    try {
        const topoPtr = Module._generateTopologicalGrid(n, m, seed);

        const pathPtr = Module._carveOptimalPath(topoPtr, n, m);

        // Because C++ 'int' is 32-bit, we use Int32Array. We divide the pointer by 4 to get the correct memory offset.
        const totalCells = n * m;
        const pathData = new Int32Array(Module.HEAP32.buffer, pathPtr, totalCells);

        renderMaze(pathData, n, m);

        Module._freeGrid(topoPtr);
        Module._freeGrid(pathPtr);
        
    } catch (error) {
        console.error("Wasm execution failed. Ensure the Module is loaded.", error);
    }
});

function renderMaze(pathData, n, m) {
    const container = document.getElementById('maze-container');
    
    container.innerHTML = '';

    container.style.gridTemplateColumns = `repeat(${n}, 1fr)`;
    container.style.gridTemplateRows = `repeat(${m}, 1fr)`;

    for (let i = 0; i < pathData.length; i++) {
        const cell = document.createElement('div');
        cell.classList.add('cell');
        
        if (pathData[i] === 1) {
            cell.classList.add('path');
        } else {
            cell.classList.add('empty');
        }
        
        container.appendChild(cell);
    }
}