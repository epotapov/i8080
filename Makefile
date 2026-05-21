CXX = g++
CXXFLAGS = -std=c++17 -g

TARGET = I8080
SPACETARGET = space-invaders
BASICTARGET = basic

BUILD = build/

RAYLIB_LIBS = -lraylib

TEST_OBJS = $(BUILD)I8080.o $(BUILD)run_test.o
SPACE_OBJS = $(BUILD)I8080.o $(BUILD)space-invaders.o
BASIC_OBJS = $(BUILD)I8080.o $(BUILD)basic.o

all: test

test: $(BUILD)$(TARGET)

space: $(BUILD)$(SPACETARGET)

basic: $(BUILD)$(BASICTARGET)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)$(TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJS)

$(BUILD)$(SPACETARGET): $(SPACE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(SPACE_OBJS) $(RAYLIB_LIBS)

$(BUILD)$(BASICTARGET): $(BASIC_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(BASIC_OBJS)

$(BUILD)%.o: %.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)space-invaders.o: space-invaders/space-invaders.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)basic.o: basic/basic.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)

.PHONY: all test space basic clean