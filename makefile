# 编译器和编译选项
CC = emcc
CFLAGS = -O2 -I C:\Users\30668\gitstore\simulator\src\header
LDFLAGS = -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']"

# 源文件和目标文件
SRCS = src/main.c src/cpu/core.c src/cpu/isa.c src/code/program.c
OBJS = $(SRCS:.c=.o)

# 目标文件
TARGET = myprogram.js

# 默认目标：编译为 WebAssembly
all: $(TARGET)

# 生成 WebAssembly 可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -s WASM=1 -o $(TARGET)

# 生成目标文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)
