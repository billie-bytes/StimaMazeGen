# --- Configuration ---
CC = clang

# Compiler Flags:
# --target=wasm32: Target WebAssembly
# -nostdlib: No std libraries
# -Wl,--no-entry: No main() function required
# -Wl,--export=...: Explicitly export the functions JS needs
# -Wl,--allow-undefined: Allow symbols to be unresolved
CFLAGS = --target=wasm32 -O3 -nostdlib \
     -Wl,--no-entry \
     -Wl,--export=generateTopologicalGrid \
     -Wl,--export=carveOptimalPath \
     -Wl,--export=resetMemory \
     -Wl,--export=memory \
     -Wl,--allow-undefined \
     -Wall -Wextra \
     -Wl,--initial-memory=1048576 \
     -I src

# --- Paths ---
SOURCE_DIR = src
OUTPUT_DIR = public
TARGET = $(OUTPUT_DIR)/map_generator.wasm

# List of all C source files
SRC = $(SOURCE_DIR)/maze.c \
      $(SOURCE_DIR)/dp.c

# --- Rules ---
all: $(TARGET)

$(TARGET): $(SRC)
	@echo "Creating output directory..."
	mkdir -p $(OUTPUT_DIR)
	@echo "Compiling Map Generator..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
	@echo "Build successful! Binary placed in $(OUTPUT_DIR)/"

clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)

serve:
	@echo "Starting server at http://localhost:8000"
	@echo "Serving content from ./public"
	python3 -m http.server 8000 --directory $(OUTPUT_DIR)

.PHONY: all clean serve
