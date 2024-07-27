# Compiler options
CXX = g++
CXXFLAGS = -std=c++20 -Wall

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Find all source files recursively in SRC_DIR and INCLUDE_DIR
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
INCLUDES := $(shell find $(INCLUDE_DIR) -name '*.h')

# Object files derived from source files
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Target executable
TARGET = chess

# Default target
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# Rule to compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDES)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean target
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Phony targets
.PHONY: all clean
