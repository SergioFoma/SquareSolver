CXX = g++

# -I flag

BUILD_DIR = Build
FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align \
	-Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations\
	-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain\
	-Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy\
	-Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
EXE_NAME = $(BUILD_DIR)/result.exe

SOURCES = square.cpp solver.cpp test.cpp flagSearch.cpp myAssert.cpp mathComparison.cpp
OBJECTS= $(SOURCES:.cpp=.obj) # square.obj

OBJECTS_IN_SOURCE = $(addprefix src/, $(OBJECTS))

.PHONY: all clean

all: $(EXE_NAME)

# Source/square.obj

$(EXE_NAME): makeBuild $(OBJECTS_IN_SOURCE)
	$(CXX) $(FLAGS) $(addprefix ./$(BUILD_DIR)/, $(OBJECTS_IN_SOURCE)) -o $(EXE_NAME)

$(OBJECTS_IN_SOURCE): %.obj: %.cpp # $^ = Source/square.cpp, $@ = Source/square.obj
	$(CXX) $(FLAGS) -I ./include -c ./$^ -o ./$(BUILD_DIR)/$@ 

makeBuild:
	mkdir -p ./$(BUILD_DIR)/src
clean:
	rm -rf ./$(BUILD_DIR)

