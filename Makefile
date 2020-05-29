CC=gcc
CXX=g++
STDC=-std=gnu11

ifeq ($(OS),Windows_NT)
	CFLAGS += -DWIN32
else
	OSDEF := $(shell uname -s)
	ifeq ($(OSDEF),Linux)
		LDFLAGS += -pthread -ldl -lm
	endif
	ifeq ($(OSDEF),OpenBSD)
		STDC=-std=c11
		CC=clang
		CXX=clang++
		LDFLAGS += -pthread -lm
	endif
	ifeq ($(OSDEF),FreeBSD)
		STDC=-std=c11
		CC=clang
		CXX=clang++
		LDFLAGS+=-pthread -lm
	endif
endif

WARNS = -Wall -Wextra -Werror -Wno-missing-field-initializers -Wno-unused-value -Wno-unused-function -Wno-missing-braces
CFLAGS += -g $(STDC) -Icode $(WARNS)
CXXFLAGS += -g -std=c++11 -Icode $(WARNS)

EXAMPLES += $(patsubst %.c,%,$(wildcard code/apps/examples/*.c))
EXAMPLES += $(patsubst %.cc,%,$(wildcard code/apps/examples/*.cc))

BUILD_FILES = $(wildcard build/*)

.PHONY: all clean examples test

all: clean examples test

test: clean code/tests/tester
	@echo '> Building unit tests'
	build/tester

examples: $(EXAMPLES)
	@echo '> Building examples'

clean:
ifneq ($(BUILD_FILES),)
	@echo '> Cleaning up files'
	@rm -r $(BUILD_FILES)
endif

% : %.c
	@mkdir -p build
	@echo '=> Building $(@F)'
	$(CC) -g $(CFLAGS) $^ $(LDFLAGS) -o build/$(@F)

% : %.cc
	@mkdir -p build
	@echo '=> Building $(@F)'
	$(CXX) -g $(CXXFLAGS) $^ $(LDFLAGS) -o build/$(@F)
