CXXFLAGS=-std=c++17 -g -Wall -Wextra -Werror

SRCS=$(wildcard *.cc)
OBJS=$(SRCS:.cc=.o)
CXX ?= clang++
all: solver

solver: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o solver

.PHONY: clean