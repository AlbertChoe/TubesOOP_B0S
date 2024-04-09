#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "Crop.hpp"
#include "Livestock.hpp"
#include "Consumable.hpp"
#include "Building.hpp"
#include "Herbivore.hpp"
#include "Carnivore.hpp"
#include "Omnivore.hpp"
#include <memory>
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
    int getWeightToWin();
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
    void addCropConfig(string code, Crop config);
    map<string, Crop>& getRefConfigMap();
    Crop getConfig(string code);
};

class LivestockConfig {
private:
    map<string, shared_ptr<Livestock>> config;
public:
    LivestockConfig();
    ~LivestockConfig();
    void addOmnivoreConfig(string code, shared_ptr<Omnivore> config);
    void addCarnivoreConfig(string code, shared_ptr<Carnivore> config);
    void addHerbivoreConfig(string code, shared_ptr<Herbivore> config);
    map<string, shared_ptr<Livestock>>& getRefConfigMap();
    shared_ptr<Livestock> getConfig(string code);
};

class ConsumableConfig {
private:
    map<string, Consumable> config;
public:
    ConsumableConfig();
    ~ConsumableConfig();
    void addConsumableConfig(string code, Consumable config);
    map<string, Consumable>& getRefConfigMap();
    Consumable getConfig(string code);
};

class BuildingConfig {
private:
    map<string, Building> config;
public:
    BuildingConfig();
    ~BuildingConfig();
    void addBuildingConfig(string code, Building config);
    Building getConfig(string code);
};


#endif