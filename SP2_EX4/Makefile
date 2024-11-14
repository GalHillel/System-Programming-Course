CXX = g++
CXXFLAGS = -std=c++17 -Iinclude
SRCS = src/complex.hpp src/node.hpp src/tree.hpp main.cpp
TEST_SRCS = test.cpp
OBJS = $(SRCS:src/%.cpp=obj/%.o)
DEPS = $(wildcard src/*.hpp)
EXECUTABLE = obj/tree_demo
TEST_EXECUTABLE = obj/test

all: tree_demo test

tree: tree_demo
	./obj/tree_demo

tree_demo: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $^

obj/%.o: src/%.cpp $(DEPS) | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj:
	mkdir -p obj

valgrind: $(EXECUTABLE)
	valgrind --leak-check=full ./$(EXECUTABLE)

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(TEST_SRCS) $(SRCS) | obj
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_SRCS)

clean:
	rm -f $(EXECUTABLE) $(TEST_EXECUTABLE) obj/*.o

.PHONY: all clean tree valgrind test
