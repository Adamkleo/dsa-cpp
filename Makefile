




CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17 -I. -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lgtest -lgtest_main -pthread

MAIN_TARGET = main
MAIN_SRC = main.cpp

TEST_TARGET = linked_list_test
TEST_SRC = tests/linked_list_test.cpp

all: $(MAIN_TARGET) $(TEST_TARGET)

$(MAIN_TARGET): $(MAIN_SRC) linkedlist/linked_list.h linkedlist/linked_list.tpp
	$(CXX) $(CXXFLAGS) $(MAIN_SRC) -o $(MAIN_TARGET)

$(TEST_TARGET): $(TEST_SRC) linkedlist/linked_list.h linkedlist/linked_list.tpp
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST_TARGET) $(LDFLAGS)

clean:
	rm -f $(MAIN_TARGET) $(TEST_TARGET)
