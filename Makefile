CC = g++
CFLAGS = -std=c++20 -O3 -Wall -Wextra
LDFLAGS = -L/usr/local/bin
OBJ = xxnacci-benchmark.o
ASM = xxnacci-benchmark.s
SRC = xxnacci-benchmark.cpp
PROGRAM = xxnacci-benchmark

all: $(PROGRAM)
	./$(PROGRAM)

$(PROGRAM): $(ASM)
	$(CC) $(ASM) -o $(PROGRAM)

$(ASM): $(SRC)
	$(CC) $(CFLAGS) -S -g $(SRC)

clean:; rm -f *.o *.s $(PROGRAM)
