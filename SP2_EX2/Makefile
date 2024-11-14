# Id: 211696521 Mail: galh2011@icloud.com
CXX=g++
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Graph.cpp Algorithms.cpp 
OBJECTS=$(subst .cpp,.o,$(SOURCES))

.PHONY: all clean run test demo valgrind tidy

all: demo test

run: demo
	./$<
	
check: test
	./$<

demo: Demo.o $(filter-out TestCounter.o Test.o,$(OBJECTS))
	$(CXX) $(CXXFLAGS) $^ -o $@

test: TestCounter.o Test.o $(filter-out Demo.o,$(OBJECTS))
	$(CXX) $(CXXFLAGS) $^ -o $@

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test