#==========================
#|       VARIABLES        |
#==========================
TARGET=jvm

CC=gcc

CFLAGS=-W
CFLAGS+=-Wall
CFLAGS+=-ansi
CFLAGS+=-pedantic
CFLAGS+=-O3
CFLAGS+=-std=c99

SRC_DIR=src
OBJ_DIR=obj

SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

LIB_SRCS = $(shell find $(SRC_DIR)/lib -name '*.c')
LIB_OBJS=$(LIB_SRCS:.c=.o)

TEST_SRCS=$(wildcard test/**/*.c)
TEST_SRCS+=$(wildcard test/*.c)
TEST_OBJS=$(TEST_SRCS:.c=.o)

#==========================
#           MAIN          |
#==========================
all: $(TARGET)

#==========================
#        BUILDING         |
#==========================
$(TARGET): $(OBJS)
	@echo "...Building JVM project..."
	$(CC) -o $@ $^ $(CFLAGS)
	@echo "...Successfully Compiled..."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $<

#==========================
#|        RUN JVM         |
#==========================
run:
	./$(TARGET)

#==========================
#|       UNIT TESTS       |
#==========================

test_target: $(TEST_SRCS) $(LIB_SRCS)
	@echo "------------------------"
	@echo "< Testing JVM Project  >"
	@echo "------------------------"
	@$(CC) -o $@ $^ $(CFLAGS) -Isrc
	@./$@
	@rm $@

test: test_target

#==========================
#      CLEAN PROJECT      |
#==========================
clean:
	@rm -rf $(TARGET) $(OBJS)
mrproper: clean
	@rm -rf $(EXEC)
