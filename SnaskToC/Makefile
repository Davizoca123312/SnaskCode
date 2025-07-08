# Makefile para o projeto SnaskToC

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC_DIR = src
BUILD_DIR = build

# Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Arquivos gerados por Flex e Bison
GENERATED_SRCS = $(BUILD_DIR)/lex.yy.c $(BUILD_DIR)/snask_parser.tab.c
GENERATED_HDRS = $(BUILD_DIR)/snask_parser.tab.h

# Todos os arquivos fonte (incluindo os gerados)
ALL_SRCS = $(SRCS) $(GENERATED_SRCS)

# Arquivos objeto
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS)) \
       $(patsubst $(BUILD_DIR)/%.c,$(BUILD_DIR)/%.o,$(GENERATED_SRCS))

# Adicionar os novos arquivos .c aqui
OBJS += $(BUILD_DIR)/environment.o $(BUILD_DIR)/interpreter.o

TARGET = snask_interpreter_c

.PHONY: all clean run

all: $(BUILD_DIR) $(GENERATED_SRCS) $(GENERATED_HDRS) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/snask_parser.tab.c $(BUILD_DIR)/snask_parser.tab.h: $(SRC_DIR)/snask_parser.y
	bison -d -o $(BUILD_DIR)/snask_parser.tab.c $< -v

$(BUILD_DIR)/lex.yy.c: $(SRC_DIR)/snask_lexer.l $(BUILD_DIR)/snask_parser.tab.h
	flex -o $@ $<

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(GENERATED_SRCS) $(GENERATED_HDRS)

run:
	./$(TARGET)
