CC=					clang
LD=					clang

TARGET=				libdsa.a
TEST_TARGET=		run_tests
SRC_DIR=			src
INCLUDE_DIR=		include
BUILD_DIR=			build
TEST_DIR=			test

SRCS= 				$(wildcard $(SRC_DIR)/*.c)
TEST_SRCS=			$(wildcard $(TEST_DIR)/*.c)	
OBJS= 				$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

DBFLAGS= 			-g3 -O0
CCFLAGS= 			-std=c99 -Wextra -Werror -Wpedantic -Wall $(DBFLAGS) -I. -I$(INCLUDE_DIR)
LDFLAGS=

all: $(TARGET)

$(BUILD_DIR):
	@echo "build dir"
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo ".c.o"
	$(CC) $(CCFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	@echo "target"
	ar rsc $@ $^

clean:
	@echo "clean"
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET) *.core

commit:
	echo "commit"
	git add .
	git commit -m "AUTO COMMIT: `date +'%Y-%m-%d %H:%M:%S'`"
	git push origin main

install:
	rm -rf /usr/local/lib/$(TARGET)
	cp $(TARGET) /usr/local/lib

$(TEST_TARGET): $(TEST_SRCS) $(TARGET)
	@echo "test target"
	$(CC) $(CCFLAGS) $(TEST_SRCS) -L. -ldsa -o $(TEST_TARGET)

test: $(TEST_TARGET)
	@echo "test"	
	./$(TEST_TARGET)

debug: $(TEST_TARGET)
	@echo "debug"
	lldb -o "process handle SIGTRAP -n true -s true -p true" -o "run" -- $(TEST_TARGET)

.PHONY: clean commit install all test debug

