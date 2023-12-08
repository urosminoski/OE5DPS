# Makefile for testing of fixedPointBlockFir

# Compiler and flags
CC 		= gcc
CFLAGS 	= -Wall -Wextra -std=c99

# Source files
SRC = main.c fixedPointBlockFir.c

# Header files
HEADERS = fixedPointBlockFir.h firCoef.h tistdtypes.h 

# Object files
OBJ = $(SRC: .c = .o)

# Executable name
EXECUTABLE = test 

# Rule to build object files
%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build executable
$(EXECUTABLE) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE)

# Clean rule
clean:
	rm -f $(OBJ) $(EXECUTABLE)

.PONY:clean