TARGET_EXEC ?= a.out
TEST = test

BUILD_DIR ?= build
SRC_DIRS ?= src

EXE_OBJ = $(BUILD_DIR)/$(SRC_DIRS)/main.o

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(patsubst %.cpp, %.o, $(addprefix $(BUILD_DIR)/, $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -march=native -g -std=c++14 -O2
CXX = clang++
LD = clang++

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)


# c++ source
$(BUILD_DIR)/%.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Rules for compiling test suite.
# - Grab every .cpp file in tests/, compile them to .o files
# - Build the test program w/ catchmain.cpp
OBJS_TEST += $(filter-out $(EXE_OBJ), $(OBJS))
CPP_TEST = $(wildcard tests/*.cpp)
CPP_TEST += catch/catchmain.cpp
OBJS_TEST += $(CPP_TEST:.cpp=.o)

$(TEST): output_msg $(OBJS_TEST)
	$(LD) $(filter-out $<, $^) $(LDFLAGS) -o $@

output_msg: ; $(CLANG_VERSION_MSG)

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR) tests/tests.o test

-include $(DEPS)

MKDIR_P ?= mkdir -p


