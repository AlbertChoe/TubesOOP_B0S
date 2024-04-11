CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SRC = $(wildcard src/*.cpp) \
      $(wildcard src/game/*.cpp) \
      $(wildcard src/grid/*.cpp) \
      $(wildcard src/item/*.cpp) \
      $(wildcard src/pcolor/*.c) \
      $(wildcard src/player/*.cpp) \
      $(wildcard src/utils/*.cpp)

OBJ = $(SRC:.cpp=.o)
OBJ := $(OBJ:.c=.o)

EXEC = game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$(EXEC)
