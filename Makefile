CC = gcc
CXX = g++
RM = rm -rf
CPPFLAGS = -g -std=c++17 -I.
LDFLAGS = -g
LDLIBS = -lstdc++fs
SRCDIR = src
BINDIR = bin
SOURCES = $(shell ls $(SRCDIR)/*)
CLANG_TIDY := clang-tidy

all: $(BINDIR)/interference

$(BINDIR)/interference: clean
	mkdir -p $(BINDIR)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(SOURCES) -o $(BINDIR)/interference $(LDLIBS)

clean:
	$(RM) $(BINDIR)

.PHONY: all clean
