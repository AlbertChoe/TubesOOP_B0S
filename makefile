CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SRC = $(wildcard src/pcolor/*.c) \
      $(wildcard src/item/*.cpp) \
      $(wildcard src/grid/*.cpp) \
      $(wildcard src/player/*.cpp) \
      $(wildcard src/utils/*.cpp) \
      $(wildcard src/*.cpp) \
      $(wildcard src/game/*.cpp) \
      

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
