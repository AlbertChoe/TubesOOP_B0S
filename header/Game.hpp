#ifndef GAME_HPP
#define GAME_HPP

#include "Config.hpp"
#include "Player.hpp"
#include "Store.hpp"
#include "Mayor.hpp"
#include "Farmer.hpp"
#include "Breeder.hpp"
#include "Exception.hpp"
#include "Utils.hpp"
#include "Mine.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <memory>
#include <iostream>
#include <vector>
using namespace std;

namespace fs = filesystem;

class Game {
private:
    GameConfig gameConfig;
    CropConfig cropConfig;
    LivestockConfig livestockConfig;
    ConsumableConfig consumableConfig;
    BuildingConfig buildingConfig;
    Store store;
    Mine mine;
    vector<shared_ptr<Player>> players;
    int currentPlayer;
public:
    Game();
    ~Game();
    void nextPlayer();
    bool isWinCondition();
    void loadGameConfig();
    void loadCropConfig();
    void loadLivestockConfig();
    void loadConsumableConfig();
    void loadBuildingConfig();
    void loadHarvestConfig();
    void loadConfig();
    void loadGameState(string fileLocation);
    void saveGameState();
    void newGame();
    void handleInput();
    void start();
    void run();
    void debugPrint();
    void printPlayers();
};

#endif