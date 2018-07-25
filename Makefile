CC := gcc
CXX := g++
RM := rm -rf
MKDIR_P := mkdir -p
CLANG_TIDY := clang-tidy

TARGET_EXECUTABLE := interference

SOURCE_DIR := ./src
BUILD_DIR := ./build
INCLUDE_DIR := ./include

CPPFLAGS := -g -std=c++17 -I$(INCLUDE_DIR) -MMD -MP
LDFLAGS := -lstdc++ -lstdc++fs

SOURCES := $(shell find $(SOURCE_DIR) -name *.cpp)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
DEPENDS := $(patsubst %.o,%.d,$(OBJECTS))

$(BUILD_DIR)/$(TARGET_EXECUTABLE): $(BUILD_DIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	$(MKDIR_P) $(BUILD_DIR)
	$(MKDIR_P) $(BUILD_DIR)/analysis
	$(MKDIR_P) $(BUILD_DIR)/instruction
	$(MKDIR_P) $(BUILD_DIR)/state
	$(MKDIR_P) $(BUILD_DIR)/scope
	$(MKDIR_P) $(BUILD_DIR)/interpreter

clean:
	$(RM) $(BUILD_DIR)

compilation_database: clean
	intercept-build make

analyze:
	$(CLANG_TIDY) -p . src/*.cpp

.PHONY: clean

-include $(DEPENDS)
