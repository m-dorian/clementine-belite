# Copyright PCLP Team, 2025

# Compiler setup.
CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -I. -g

# Define targets, e.g., ninel, codeinvim, vectsecv, nomogram.
TARGETS=runic

# Manually define all targets.
build: $(TARGETS)

runic: runic.c lege.c main.c comenzi.c
	$(CC) $(CFLAGS) runic.c lege.c main.c comenzi.c -o runic


# Pack the solution into a zip file.
pack:
	zip -FSr aaaaaaaaa.zip README Makefile *.c *.h

# Clean the solution.
clean:
	rm -f $(TARGETS)

.PHONY: pack clean
