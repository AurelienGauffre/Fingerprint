CXX      = clang++
#CXXFLAGS = -std=c++11 -lm -Weverything -Wno-compat -Wno-padded -Wno-conversion -Wno-global-constructors -Wno-exit-time-destructors
CXXFLAGS =  -Wall -Wextra -O0 -g -std=c++11 `pkg-config --cflags opencv`
EXEC     = fingerprint
#LIB      = -lsfml-window -lsfml-graphics -lsfml-system
SRC      = $(shell find src -type f -name '*.cpp')
OBJ      = $(patsubst src/%.cpp, obj/%.o, $(SRC))
DEP      = $(OBJ:.o=.d)
all: print_compilation $(EXEC) open

-include $(DEP)

print_compilation:
	@printf '\n→ compilation...\n'

$(EXEC): $(OBJ)
	$(CXX)  $^ -o $(EXEC)

obj/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS)  -c $< `pkg-config --libs opencv` -o $@

open:
	@printf '\n→ launch $(EXEC)...\n'
		

clean:
	@printf '\n→ clean...\n'
	rm -f $(OBJ)
	rm -f $(DEP)
	rm -f $(EXEC)

cm: clean all


.PHONY: all print_compilation open clean cm
