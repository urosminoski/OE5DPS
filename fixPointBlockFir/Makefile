# Makefile for testing of fixedPointBlockFir.c

vpath %.c src
vpath %.h inc

CC = g++

PY_NAME = plotResults.py
EXE = main.exe
SRC = main.c fixedPointBlockFir.c
OBJ = main.o fixedPointBlockFir.o 
HEADER = fixedPointBlockFir.h firCoef.h tistdtypes.h 

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ)

$(OBJ): $(SRC) $(HEADER)
	$(CC) -c $?

run_c: $(EXE)
	cd .\src\ && ..\$(EXE) 		# exe must be ran from src directory because of relative paths inside the main.c

run_py: $(EXE)
	cd .\python\ && python3 $(PY_NAME)

clean:
	del *.o *.exe inc\*.gch

.PHONY: all run_c run_py clean

