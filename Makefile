CXX = g++
CXXFLAGS = -std=c++20
SRC_DIR = src
BIN_DIR = bin

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
TARGETS := $(addprefix $(BIN_DIR)/,$(notdir $(basename $(SOURCES))))

all: $(TARGETS)

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: all clean
clean:
	rm -f $(BIN_DIR)/*

