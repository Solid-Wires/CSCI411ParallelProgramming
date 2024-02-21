# Executable name
BIN=Parallel
BIN_LECT=Sample # Lecture program sample

# Directories
OBJ_DIR=obj
OBJ_DIR_LECT=obj/from-lecture
BIN_DIR=bin

# All object files to create (derived from all files in /src)
# Awesome! Now I'll never have to look at this file again when I make new definition files.
objs := $(patsubst src/%.cpp,%.o,$(wildcard src/*.cpp))
objs_lecture := $(patsubst src/from-lecture/%.cpp,%.o,$(wildcard src/from-lecture/*.cpp))

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
	@mkdir -p $(OBJ_DIR_LECT)
	@mkdir -p $(BIN_DIR)

# General obj compilation rule
src=%.o: src/%.cpp
	$(CC) $(VERSION) -c src/$*.cpp -o $(OBJ_DIR)/$*.o
# General obj compilation rule
from-lect=%.o: src/from-lecture/%.cpp
	$(CC) $(VERSION) -c src/$*.cpp -o $(OBJ_DIR_LECT)/$*.o

# Primary source compilation
src_comp: src/*.cpp
	make -s src=$(objs)
	make -s from-lect=$(objs_lecture)

# Program binary executable compilation
program: src_comp
	g++ $(OBJ_DIR)/*.o -o $(BIN_DIR)/$(BIN) $(RTL) $(LPTHREAD)
	g++ $(OBJ_DIR_LECT)/*.o -o $(BIN_DIR)/$(BIN_LECT) $(RTL) $(LPTHREAD)

# Clean does a recursive removal of the generated bin and obj directories.
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
