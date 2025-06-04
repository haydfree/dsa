CC=					clang
LD=					clang

TARGET=				libdsa.a
SRC_DIR=			src
INCLUDE_DIR=		include
BUILD_DIR=			build

SRCS= 				$(wildcard $(SRC_DIR)/*.c)
OBJS= 				$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

DBFLAGS= 			-g3 -O0
CCFLAGS= 			-ansi -Wextra -Werror -Wpedantic -Wall $(DBFLAGS) -I. -I$(INCLUDE_DIR)
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
	rm -rf $(BUILD_DIR) $(TARGET) *.core

commit:
	echo "commit"
	git add .
	git commit -m "AUTO COMMIT: `date +'%Y-%m-%d %H:%M:%S'`"
	git push origin main

install:
	rm -rf /usr/local/lib/$(TARGET)
	cp $(TARGET) /usr/local/lib

.PHONY: clean commit install all

