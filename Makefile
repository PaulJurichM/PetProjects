


Создадим `Makefile`, который:
- соберёт все `.c` файлы в объектные
- слинкует их в один исполняемый файл `graph`
- положит его в директорию `build`

Пример Makefile (который я предложу) будет включать:

```make
CC = gcc
CFLAGS = -Wall -Wextra -Werror
BUILD_DIR = build
TARGET = $(BUILD_DIR)/graph

SRC = \
	src/main.c \
	src/lexer.c \
	src/s21_rpn.c \
	src/evaluate_rpn.c \
	src/draw_graph.c \
	src/s21_stack.c \
	src/s21_string.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJ) -lm -o $(TARGET)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) src/*.o
