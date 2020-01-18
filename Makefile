CC=gcc
CXX=g++

ifeq ($(OS),Windows_NT)
	CFLAGS += -DWIN32
else
	OSDEF := $(shell uname -s)
	ifeq ($(OSDEF),Linux)
		LDFLAGS += -pthread -ldl -lm
	endif
endif

WARNS = -Wal -Wextra -Werror -Wno-missing-field-initializers -Wno-unused-value -Wno-unused-function -Wno-missing-braces
CFLAGS += -g -std=gnu11 -Icode $(WARNS)
CXXFLAGS += -g -std=c++11 -Icode $(WARNS)

EXAMPLES_SRCS += $(wildcard code/apps/examples/*.c)
EXAMPLES_SRCS += $(wildcard code/apps/examples/*.cc)

EXAMPLES += $(patsubst %.c,%,$(EXAMPLES_SRCS))
EXAMPLES += $(patsubst %.cc,%,$(EXAMPLES_SRCS))

BUILD_FILES = $(wildcard build/*)

.PHONY: all clean examples test

all: clean examples test

test: clean code/apps/tests/tester
	@echo '> Building unit tests'
	build/tester

examples: $(EXAMPLES)
	@echo '> Building examples'

clean:
ifneq ($(BUILD_FILES),)
	@echo '> Cleaning up files'
	@rm $(BUILD_FILES)
endif

% : %.c
	@mkdir -p build
	@echo '=> Building $(@F)'
	$(CC) -g $(CFLAGS) $^ $(LDFLAGS) -o build/$(@F)

% : %.cc
	@mkdir -p build
	@echo '=> Building $(@F)'
	$(CXX) -g $(CXXFLAGS) $^ $(LDFLAGS) -o build/$(@F)

