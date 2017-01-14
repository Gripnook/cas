CXX := clang++
CXXFLAGS := -std=c++14 -stdlib=libc++ -Wall -Wextra -pedantic -g
LIBFLAGS := -lreadline

TARGET := cas
BUILD_DIR := ./build
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(BUILD_DIR) $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBFLAGS)

-include $(DEPS)

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/$(TARGET) $(OBJS) $(DEPS)
