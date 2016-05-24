SRC_DIR = src
OBJ_DIR = .obj
LIB_DIR = lib
INC_DIR = include

CC = afl-gcc
CXX = afl-g++
CFLAGS = -I$(INC_DIR) -L$(LIB_DIR) -Wl,-rpath -Wl,$(LIB_DIR)
CPPFLAGS = -I$(INC_DIR) -L$(LIB_DIR) -Wl,-rpath -Wl,$(LIB_DIR)
LIBS =

_DEPS = aflize.h
DEPS = $(patsubst %, $(INC_DIR)/%, $(_DEPS))

SRC = $(wildcard $(SRC_DIR)/*.cpp)
ARGV_SRC = $(filter-out src/stdinalize.cpp, $(SRC))
STDIN_SRC = $(filter-out src/argvalize.cpp, $(SRC))
ARGV_OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(ARGV_SRC))
STDIN_OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(STDIN_SRC))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	@mkdir -p $(@D)
	$(CXX) -c -o $@ $< $(CPPFLAGS)

argv: $(ARGV_OBJ)
	$(CXX) -o aflized $^ $(CPPFLAGS) $(LIBS)

stdin: $(STDIN_OBJ)
	$(CXX) -o aflized $^ $(CPPFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR)/ core aflized

# Echo out a make variable when running make print-VAR
print-%: ; @echo $* = $($*)
