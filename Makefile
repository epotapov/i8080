CXX = g++
CXXFLAGS = -std=c++17 -g
TARGET = I8080
SPACETARGET = space-invaders
BUILD = build/

TEST_OBJS = $(BUILD)I8080.o $(BUILD)run_test.o
SPACE_OBJS = $(BUILD)I8080.o $(BUILD)space-invaders.o

all: test

test: $(BUILD)$(TARGET)

space: $(BUILD)$(SPACETARGET)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)$(TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJS)

$(BUILD)$(SPACETARGET): $(SPACE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(SPACE_OBJS)

$(BUILD)%.o: %.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)space-invaders.o: space-invaders/space-invaders.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)

.PHONY: all test space clean