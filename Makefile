# Makefile

CXX = g++
CXXFLAGS = -std=c++11 -I./inc
SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_DIR = obj
BIN_DIR = bin
TARGETS = clean build program

all: $(TARGETS)

# rule to compile .cpp files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# rule to build cube
program: $(OBJ_DIR)/program.o
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $(BIN_DIR)/$@


# rule for debug
debug: CXXFLAGS += -DDEBUG -g
debug: all

# rule for release
release: CXXFLAGS += -O2
release: all

build:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean