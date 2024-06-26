# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -pthread

# Linker flags
LDFLAGS = -lm

# Executable name
EXEC = MyPrimeCounter

# Source files
SRC = main.c MyPrimeCounter.c

# Object files
OBJ = $(SRC:.c=.o)

# Header files
DEPS = MyPrimeCounter.h

# Default target
all: $(EXEC)

# Linking the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compiling the source files
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(EXEC)

# Phony targets
.PHONY: all clean

