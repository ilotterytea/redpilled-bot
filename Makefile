CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -lixwebsocket

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

SRC_SUBDIRS := $(shell find $(SRC_DIR) -type d)
SRC_FILES := $(wildcard $(addsuffix /*.cpp,$(SRC_SUBDIRS)))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

TARGET = $(BIN_DIR)/redpilled_bot

all: $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
