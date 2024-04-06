#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "Crop.hpp"
#include "Livestock.hpp"
#include "Consumable.hpp"
#include "Building.hpp"
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
    GameConfig(int guldenToWin, int weighToWin, int inventoryRow, int inventoryCol, int fieldRow, int fieldCol, int barnRow, int barnCol);
    void getGuldenToWin();
    void getWieghToWin();
    void getInventoryRow();
    void getInvetoryCol();
    void getFieldRow();
    void getFieldCol();
    void getBarnRow();
    void getBarnCol();
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
    void addConfig(string code, Livestock config);
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
    map<string, Building> recipe;
public:
    BuildingConfig();
    ~BuildingConfig();
    void addConfig(string code, Building config);
    Building getConfig(string code);

};


#endif