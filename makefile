CC = gcc

CFLAGS = -Wall -Wextra -g -std=c11 -Iinclude -g
LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

# 自动查找所有 C 文件
SRC = $(wildcard src/*.c)

# 把 src/xxx.c 转换为 build/xxx.o
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

TARGET = build/main.exe

all: $(TARGET)

# 链接所有目标文件
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# 单独编译每个 C 文件
build/%.o: src/%.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# 自动包含头文件依赖
-include $(OBJ:.o=.d)

# 创建 build 文件夹
$(OBJ): | build

build:
	mkdir build

run: all
	./$(TARGET)

clean:
	$(RM) $(OBJ) $(OBJ:.o=.d) $(TARGET)

.PHONY: all run clean