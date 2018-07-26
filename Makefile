CC := gcc-8
CXX := g++-8
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
SOURCE_SUBDIRS := $(shell find $(SOURCE_DIR) -mindepth 1 -type d)
BUILD_SUBDIRS := $(patsubst $(SOURCE_DIR)/%,$(BUILD_DIR)/%,$(SOURCE_SUBDIRS))

$(BUILD_DIR)/$(TARGET_EXECUTABLE): build_dirs $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build_dirs:
	$(MKDIR_P) $(BUILD_DIR) $(BUILD_SUBDIRS)

clean:
	$(RM) $(BUILD_SUBDIRS) $(BUILD_DIR)

compilation_database: clean
	intercept-build make

analyze:
	$(CLANG_TIDY) -p . src/*.cpp

.PHONY: clean build_dirs analyze compilation_database

-include $(DEPENDS)
