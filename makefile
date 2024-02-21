# Executable name
BIN=Parallel

# Directories
OBJ_DIR=obj
BIN_DIR=bin

# All object files to create (derived from all files in /src)
# Awesome! Now I'll never have to look at this file again when I make new definition files.
objs := $(patsubst src/%.cpp,%.o,$(wildcard src/*.cpp))

# Linker, version, and misc additions
CC=cc
VERSION=-std=c++11
RTL=-lrt
LPTHREAD=-lpthread

# All call
all: directories program

# Make all of these directories if they don't exist
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# General obj compilation rule
%.o: src/%.cpp
	$(CC) $(VERSION) -c src/$*.cpp -o $(OBJ_DIR)/$*.o

# Primary source compilation
src_comp: src/*.cpp
	make -s $(objs)

# Program binary executable compilation
program: src_comp
	g++ $(OBJ_DIR)/*.o -o $(BIN_DIR)/$(BIN) $(RTL) $(LPTHREAD)

# Clean does a recursive removal of the generated bin and obj directories.
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
