CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -Iinclude
LDFLAGS =
DEBUG_FLAGS = -g

TARGET = bin/sudoku_solver
SRCS = src/main.cpp src/sudoku_solver.cpp src/board.cpp src/graph.cpp src/node.cpp
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRCS))

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files in the build directory
build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the build directory exists
build:
	mkdir -p build

# Clean target to remove compiled files
clean:
	rm -f $(TARGET) $(OBJS)
	rm -rf build/

run: $(TARGET)
	./$(TARGET)

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean all