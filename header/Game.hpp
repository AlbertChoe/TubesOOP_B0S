#ifndef GAME_HPP
#define GAME_HPP

#include "Config.hpp"
#include "Player.hpp"
#include "Store.hpp"
#include "Mayor.hpp"
#include "Farmer.hpp"
#include "Breeder.hpp"
#include <iostream>
#include <vector>
using namespace std;

class Game {
private:
    static GameConfig gameConfig;
    static CropConfig cropConfig;
    static LivestockConfig livestockConfig;
    static ConsumableConfig consumableConfig;
    static BuildingConfig buildingConfig;
    Store store;
    vector<Player> players;
    int currentIndex;
public:
    Game();
    ~Game();
    void loadGameConfig();
    void loadCropConfig();
    void loadLiveStockConfig();
    void loadComsumableConfig();
    void load();
    void newGame();
    void save();
    void handleInput();
    void run();
};

#endif