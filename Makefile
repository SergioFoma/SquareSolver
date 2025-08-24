CXX = g++

BUILD_DIR = Build
FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
EXE_NAME = result.exe

SOURCES = square.cpp solver.cpp test.cpp flagSearch.cpp
OBJECTS_WITHOUT_PREFIX = $(SOURCES:.cpp=.obj)
OBJECTS = $(addprefix $(BUILD_DIR)/, $(OBJECTS_WITHOUT_PREFIX))


# TODO store .obj and .exe into build folder
.PHONY: all clean

all: $(EXE_NAME)

$(EXE_NAME): $(OBJECTS)
	$(CXX) $(FLAGS) $^ -o $@

$(OBJECTS): $(BUILD_DIR)/%.obj: %.cpp
	$(CXX) $(FLAGS) -c $^ -o $@

clean:
	rm -f $(OBJECTS) $(EXE_NAME)
