# Executable name
BIN=Parallel

# Directories
OBJ_DIR=obj
OBJ_DIR_LECT_HELLO=$(OBJ_DIR)/from-lecture/hello
OBJ_DIR_LECT_NUM_INTEG=$(OBJ_DIR)/from-lecture/num-integ
OBJ_DIR_LECT_NUM_THREADS_DEF=$(OBJ_DIR)/from-lecture/num-threads-defined
OBJ_DIR_LECT_PI=$(OBJ_DIR)/from-lecture/pi-program
OBJ_DIR_LECT_SYNCHRONIZATION=$(OBJ_DIR)/from-lecture/synchronization
BIN_DIR=bin
BIN_LECT_DIR=$(BIN_DIR)/lecture

# All object files to create (derived from all files in /src)
# Awesome! Now I'll never have to look at this file again when I make new definition files.
objs := $(patsubst src/%.cpp,%.o,$(wildcard src/*.cpp))
objs_lecture_hellosample := $(patsubst src/from-lecture/hello/%.cpp,%.o,$(wildcard src/from-lecture/hello/*.cpp))
objs_lecture_numinteg := $(patsubst src/from-lecture/num-integ/%.cpp,%.o,$(wildcard src/from-lecture/num-integ/*.cpp))
objs_lecture_numthreadsdefined := $(patsubst src/from-lecture/num-threads-defined/%.cpp,%.o,$(wildcard src/from-lecture/num-threads-defined/*.cpp))
objs_lecture_piprogram := $(patsubst src/from-lecture/pi-program/%.cpp,%.o,$(wildcard src/from-lecture/pi-program/*.cpp))
objs_lecture_synchronization := $(patsubst src/from-lecture/synchronization/%.cpp,%.o,$(wildcard src/from-lecture/synchronization/*.cpp))

# Linker, version, and misc additions
CC=cc
VERSION=-std=c++11
OPENMP=-fopenmp

# All call
all: directories program

# Make all of these directories if they don't exist
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR_LECT_HELLO)
	@mkdir -p $(OBJ_DIR_LECT_NUM_INTEG)
	@mkdir -p $(OBJ_DIR_LECT_NUM_THREADS_DEF)
	@mkdir -p $(OBJ_DIR_LECT_PI)
	@mkdir -p $(OBJ_DIR_LECT_SYNCHRONIZATION)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BIN_LECT_DIR)

# General obj compilation rule
src-objs: %.o
	$(CC) $(VERSION) -c src/$*.cpp -o $(OBJ_DIR)/$*.o $(OPENMP)
# Lecure obj comps
from-lect-hello-%.o: src/from-lecture/hello/%.cpp
	$(CC) $(VERSION) -c src/from-lecture/hello/$*.cpp -o $(OBJ_DIR_LECT_HELLO)/$*.o $(OPENMP)
from-lect-numinteg-%.o: src/from-lecture/num-integ/%.cpp
	$(CC) $(VERSION) -c src/from-lecture/num-integ/$*.cpp -o $(OBJ_DIR_LECT_NUM_INTEG)/$*.o $(OPENMP)
from-lect-numthreadsdefined-%.o: src/from-lecture/num-threads-defined/%.cpp
	$(CC) $(VERSION) -c src/from-lecture/num-threads-defined/$*.cpp -o $(OBJ_DIR_LECT_NUM_THREADS_DEF)/$*.o $(OPENMP)
from-lect-piprogram-%.o: src/from-lecture/pi-program/%.cpp
	$(CC) $(VERSION) -c src/from-lecture/pi-program/$*.cpp -o $(OBJ_DIR_LECT_PI)/$*.o $(OPENMP)
from-lect-synchronization-%.o: src/from-lecture/synchronization/%.cpp
	$(CC) $(VERSION) -c src/from-lecture/synchronization/$*.cpp -o $(OBJ_DIR_LECT_SYNCHRONIZATION)/$*.o $(OPENMP)

# Lecture program objects
lect_comp: 
	make -s from-lect-hello-$(objs_lecture_hellosample)
	make -s from-lect-numinteg-$(objs_lecture_numinteg)
	make -s from-lect-numinteg-$(objs_lecture_numinteg)
	make -s from-lect-numthreadsdefined-$(objs_lecture_numthreadsdefined)
	make -s from-lect-piprogram-$(objs_lecture_piprogram)
	make -s from-lect-synchronization-$(objs_lecture_synchronization)

# Lecture program executables
lect_programs: lect_comp
	g++ $(OBJ_DIR_LECT_HELLO)/*.o -o $(BIN_LECT_DIR)/hello $(OPENMP)
	g++ $(OBJ_DIR_LECT_NUM_INTEG)/*.o -o $(BIN_LECT_DIR)/numinteg $(OPENMP)
	g++ $(OBJ_DIR_LECT_NUM_THREADS_DEF)/*.o -o $(BIN_LECT_DIR)/ntd $(OPENMP)
	g++ $(OBJ_DIR_LECT_PI)/*.o -o $(BIN_LECT_DIR)/parapi $(OPENMP)
	g++ $(OBJ_DIR_LECT_SYNCHRONIZATION)/*.o -o $(BIN_LECT_DIR)/synchro $(OPENMP)

# Primary source compilation
src_comp:
	make -s src-objs $(objs)

# Program binary executable compilation
program: src_comp
	g++ $(OBJ_DIR)/*.o -o $(BIN_DIR)/$(BIN) $(OPENMP)

# Clean does a recursive removal of the generated bin and obj directories.
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
