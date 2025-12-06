# Copyright PCLP Team, 2025

# Compiler setup
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I. -ulimit=1024 -g

# Define targets
TARGETS = battleships
SRC = battleships_meu.c  nava.c matrice.c tabla.c joc.c
# Default target: build all
build: $(TARGETS)

# Run target: execute battleships
run: battleships
	./battleships

# Build battleships executable
battleships: $(SRC)
	$(CC)  $(SRC) $(CFLAGS) -o battleships -lm

# Pack the solution into a zip file
pack:
	zip -FSr 3XX_aaaaaa_Tema2.zip README Makefile *.c *.h

# Clean build artifacts
clean:
	rm -f $(TARGETS)

.PHONY: build run pack clean
