CXX=g++-12
CXXFLAGS=-g -Wall -pedantic -std=c++2b
CONFIG=debug
SRC=src
OBJ=obj
BIN=vmrss
SRCS=$(wildcard $(SRC)/*.cpp)
OBJS_DEBUG=$(patsubst $(SRC)/%.cpp, $(OBJ)/debug/%.o, $(SRCS))
OBJS_DEBUG_NO_MAIN = $(filter-out $(OBJ)/debug/main.o, $(OBJS_DEBUG))
OBJS_RELEASE=$(patsubst $(SRC)/%.cpp, $(OBJ)/release/%.o, $(SRCS))

TEST=tests
TESTS=$(wildcard $(TEST)/*.cpp)
TESTBINS=$(patsubst $(TEST)/%.cpp, $(TEST)/bin/%, $(TESTS))

.PHONY: debug all clean cleanall clean_test test

all: debug

debug: bin/debug/$(BIN)

release: CXXFLAGS=-g -Wall -pedantic -std=c++23 -O3 -DNDEBUG -flto -fPIE
release: CONFIG=release
release: bin/release/$(BIN)

ifeq ($(MAKECMDGOALS),release)
bin/release/$(BIN): bin/release obj/release $(OBJS_RELEASE)
	$(CXX) $(CXXFLAGS) $(OBJS_RELEASE) -o $@
	strip -s $@

obj/release/%.o: $(SRC)/%.cpp $(SRC)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/release:
	mkdir -p $@

obj/release:
	mkdir -p $@
else
bin/debug/$(BIN): bin/debug obj/debug $(OBJS_DEBUG)
	$(CXX) $(CXXFLAGS) $(OBJS_DEBUG) -o $@

obj/debug/%.o: $(SRC)/%.cpp $(SRC)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/debug:
	mkdir -p $@

obj/debug:
	mkdir -p $@
endif

$(TEST)/bin/%: $(TEST)/%.cpp
	$(CXX) $(CXXFLAGS) $< $(OBJS_DEBUG_NO_MAIN) -o $@ -lcriterion

$(TEST)/bin:
	mkdir -p $@

test: clean_tests $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

clean:
	$(RM) -r bin obj

clean_tests:
	$(RM) -r $(TEST)/bin

cleanall: clean clean_tests
