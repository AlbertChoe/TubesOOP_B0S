CXX = g++
CXXFLAGS = -std=c++14 -Wall -g

BIN_DIR = bin
EXEC = game

# Manually listing each source file
SRC = src/pcolor/pcolor.cpp \
      src/item/Item.cpp \
      src/item/Crop.cpp \
      src/item/Livestock.cpp \
      src/item/Consumable.cpp \
      src/item/Building.cpp \
      src/item/Carnivore.cpp \
      src/item/Herbivore.cpp \
      src/item/Omnivore.cpp \
      src/grid/Field.cpp \
      src/grid/Inventory.cpp \
      src/grid/Barn.cpp \
      src/player/Player.cpp \
      src/player/Breeder.cpp \
      src/player/Farmer.cpp \
      src/player/Mayor.cpp \
      src/utils/Utils.cpp \
      src/game/Config.cpp \
      src/game/Store.cpp \
      src/game/Game.cpp \
      src/main.cpp

# Object files corresponding to each source
OBJ = $(SRC:%.cpp=$(BIN_DIR)/%.o)
OBJ := $(OBJ:%.c=$(BIN_DIR)/%.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$(EXEC)