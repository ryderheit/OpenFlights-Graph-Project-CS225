# Generated files
CLEAN_RM =

EXE = a.out
TEST = test

BUILD_DIR ?= build
SRC_DIRS ?= src

EXE_OBJ = $(SRC_DIRS)/main.o

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%.cpp=%.o)
OBJS_BUILD := $(addprefix $(BUILD_DIR)/, $(OBJS))

LDFLAGS := -std=c++14 -stdlib=libc++ -lc++abi
CXXFLAGS := -std=c++14 -stdlib=libc++ -O0 -MMD -MP -g -c

CXX = clang++
LD = clang++

# Rule for `all` (first/default rule):
all: $(EXE)

$(EXE): $(OBJS_BUILD)
	$(LD) $(OBJS_BUILD) $(LDFLAGS) -o $@

# Ensure BUILD_DIR exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/src
	@mkdir -p $(BUILD_DIR)/tests
	@mkdir -p $(BUILD_DIR)/catch

# Rules for compiling source code.
# - Every object file is required by $(EXE)
# - Generates the rule requiring the .cpp file of the same name
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Rules for compiling test suite.
# - Grab every .cpp file in tests/, compile them to .o files
# - Build the test program w/ catchmain.cpp
OBJS_TEST += $(filter-out $(EXE_OBJ), $(OBJS))
CPP_TEST = $(wildcard tests/*.cpp)
CPP_TEST += catch/catchmain.cpp
OBJS_TEST += $(CPP_TEST:.cpp=.o)

$(TEST): $(patsubst %.o, $(BUILD_DIR)/%.o, $(OBJS_TEST))
	$(LD) $(patsubst %.o, $(BUILD_DIR)/%.o, $(OBJS_TEST)) $(LDFLAGS) -o $@

-include $(BUILD_DIR)/src/*.d
-include $(BUILD_DIR)/tests/*.d
-include $(BUILD_DIR)/catch/*.d

.PHONY: all clean

clean:
	rm -rf $(EXE) $(TEST) $(BUILD_DIR) $(CLEAN_RM) *.o *.d
