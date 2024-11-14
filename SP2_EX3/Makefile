# Id: 211696521 Mail: galh2011@icloud.com
CXX=g++
CXXFLAGS=-std=c++17 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=main.cpp catan.cpp player.cpp board.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

# Test sources and objects
TEST_SOURCES=Test.cpp catan.cpp player.cpp board.cpp
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)

# Main program and test targets
TEST_EXECUTABLE=test

.PHONY: all clean run main valgrind tidy

all: main

catan: main
	./$<
	
main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

check: test
	./test

test: $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: main
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./main 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o main test
