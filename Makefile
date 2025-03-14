
# 				Compiler and flags

CC = gcc
# Specifies the compiler
CFLAGS = -g -c
# Adds debugging info (-g) and compiles .c files into .o files (-c).
LDFLAGS = -g
# Adds debugging info during the linking phase
INCLUDES = -I./
# Ensures the compiler looks for header files in the current directory



# 				Define object files
OBJECTS = build/compiler.o build/cprocess.o build/helpers/buffer.o build/helpers/vector.o

# 				Target executable
TARGET = main.exe

# 				Ensure build directory exists
.PHONY: all clean build
all: build $(OBJECTS)
	$(CC) main.c $(INCLUDES) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

# 				Create necessary build directories (Windows-compatible)
build:
	if not exist build mkdir build
	if not exist build\helpers mkdir build\helpers

# 				Compile source files into object files
build/compiler.o: compiler.c
	$(CC) $(CFLAGS) $(INCLUDES) -o build/compiler.o compiler.c

build/cprocess.o: cprocess.c
	$(CC) $(CFLAGS) $(INCLUDES) -o build/cprocess.o cprocess.c

build/helpers/buffer.o: helpers/buffer.c
	$(CC) $(CFLAGS) $(INCLUDES) -o build/helpers/buffer.o helpers/buffer.c

build/helpers/vector.o: helpers/vector.c
	$(CC) $(CFLAGS) $(INCLUDES) -o build/helpers/vector.o helpers/vector.c

# 				Clean build files (Windows-compatible)
clean:
	if exist main.exe del /Q main.exe
	if exist build\compiler.o del /Q build\compiler.o
	if exist build\cprocess.o del /Q build\cprocess.o
	if exist build\helpers\buffer.o del /Q build\helpers\buffer.o
	if exist build\helpers\vector.o del /Q build\helpers\vector.o
	if exist build rmdir /S /Q build
