#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "Crop.hpp"
#include "Livestock.hpp"
#include "Consumable.hpp"
#include "Building.hpp"
#include "Herbivore.hpp"
#include "Carnivore.hpp"
#include "Omnivore.hpp"
#include <iostream> 
#include <map>
using namespace std;

class GameConfig {
private:
    int guldenToWin;
    int weightToWin;
    int inventoryRow;
    int inventoryCol;
    int fieldRow;
    int fieldCol;
    int barnRow;
    int barnCol;

public:
    GameConfig();
    int getGuldenToWin();
    int getWieghtToWin();
    int getInventoryRow();
    int getInventoryCol();
    int getFieldRow();
    int getFieldCol();
    int getBarnRow();
    int getBarnCol();
    void setGameConfig(int _guldenToWin, int _weightToWin, int _inventoryRow, int _inventoryCol, int _fieldRow, int _fieldCol, int _barnRow, int _barnCol);
};

class CropConfig {
private:
    map<string, Crop> config;
public:
    CropConfig();
    void addConfig(string code, Crop config);
    Crop getConfig(string code);
};

class LivestockConfig {
private:
    map<string, Livestock> config;
public:
    LivestockConfig();
    ~LivestockConfig();
    void addOmnivoreConfig(string code, Omnivore config);
    void addCarnivoreConfig(string code, Carnivore config);
    void addHerbivoreConfig(string code, Herbivore config);
    Livestock getConfig(string code);
};

class ConsumableConfig {
private:
    map<string, Consumable> config;
public:
    ConsumableConfig();
    ~ConsumableConfig();
    void addConfig(string code, Consumable config);
    Consumable getConfig(string code);
};

class BuildingConfig {
private:
    map<string, Building> config;
public:
    BuildingConfig();
    ~BuildingConfig();
    void addConfig(string code, Building config);
    Building getConfig(string code);
};


#endif