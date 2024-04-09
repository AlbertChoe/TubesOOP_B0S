# Define compiler
CC = g++

# Define flags
CFLAGS = -Wall -std=c++11

# Define the source files
SRC = src/main.cpp src/game/Game.cpp src/game/Config.cpp

# Define the object files
OBJ = $(SRC:.cpp=.o)

# Define the executable name
EXE = game.exe

# Default target
all: $(EXE)

# Compile and link the program
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	del /f /q $(OBJ) $(EXE)

# Run the program
run: $(EXE)
	$(EXE)

# Phony targets
.PHONY: all clean run