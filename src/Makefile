# Operating system
OS = POSIX

# Compiler
CXX = g++

# Flags passed to the preprocessor.
CPPFLAGS =

# Flags passed to the C++ compiler.
CXXFLAGS = -g -Wall -Wextra --pedantic

# Time
TIME_OBJ = clock.o timer.o
TIME_SRC = src/time
TIME_CPPFLAGS =

clock.o : $(TIME_SRC)/clock.cc
	$(CXX) $(TIME_CPPFLAGS) $(CXXFLAGS) -D$(OS) -c -o $@ $<

timer.o : $(TIME_SRC)/timer.cc
	$(CXX) $(TIME_CPPFLAGS) $(CXXFLAGS) -D$(OS) -c -o $@ $<

# Demo
DEMO_SRC = src/demo
DEMO_CPPFLAGS = -lrt -I$(TIME_SRC)

cli_demo : $(DEMO_SRC)/cli_demo.cc clock.o timer.o
	$(CXX) $(DEMO_CPPFLAGS) $(CXXFLAGS) -D$(OS) -o $@ $^

# Tests

GTEST_DIR = deps/gtest-1.6.0
TEST_DIR = test
CPPFLAGS = -lrt -lpthread -I$(GTEST_DIR)/include -I$(TIME_SRC)

TESTS = timer_unittest

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
        $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
        $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Unit tests

TEST_OBJ = timer_unittest.o

timer_unittest.o : $(TEST_DIR)/timer_unittest.cc \
                   $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

timer_unittest : timer.o clock.o timer_unittest.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

# Clean
clean :
	rm $(TESTS) $(TEST_OBJ) $(TIME_OBJ) cli_demo
