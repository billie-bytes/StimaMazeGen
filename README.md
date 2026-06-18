# StimaMazeGen

## Dependancies
Make: To execute the build rules defined in the Makefile.
Clang & LLVM: The compiler toolchain capable of targeting WebAssembly (wasm32).
LLD (LLVM Linker): Required by Clang to link WebAssembly binaries (wasm-ld).
Python 3: Used to spin up a quick local HTTP server for testing.

## Installing the dependancies
```bash
sudo apt update && sudo apt upgrade -y
sudo apt install build-essential python3 -y
sudo apt install clang lld -y
```

## Compile and run
 ```bash
make
make serve
 ```