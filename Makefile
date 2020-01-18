CC=gcc
CXX=g++

LDFLAGS += -pthread -ldl -lm
DISABLED_WARNS = -Wno-missing-field-initializers -Wno-unused-value -Wno-unused-function -Wno-missing-braces
CFLAGS += -g -std=gnu11 -Icode -Wall -Wextra -Werror $(DISABLED_WARNS)
CXXFLAGS += -g -std=c++11 -Icode -Wall -Wextra -Werror $(DISABLED_WARNS)

EXAMPLES_SRCS += $(wildcard examples/*.c)
EXAMPLES_SRCS += $(wildcard examples/*.cc)

EXAMPLES += $(patsubst %.c,%,$(EXAMPLES_SRCS))
EXAMPLES += $(patsubst %.cc,%,$(EXAMPLES_SRCS))

.PHONY: all clean examples test

all: clean examples test

test: clean tests/tester
	@echo '> Building unit tests'
	build/tester

examples: $(EXAMPLES)
	@echo '> Building examples'

clean:
	@echo '> Cleaning up files'
	#@rm build/$(EXAMPLES) build/tester

% : %.c
	@mkdir -p build
	@echo '=> Building $@'
	$(CC) -g $(CFLAGS) $^ $(LDFLAGS) -o build/$(@F)

% : %.cc
	@mkdir -p build
	@echo '=> Building $@'
	$(CXX) -g $(CXXFLAGS) $^ $(LDFLAGS) -o build/$(@F)

