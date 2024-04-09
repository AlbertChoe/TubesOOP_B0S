#include "../../header/Config.hpp"

// GameConfig
GameConfig::GameConfig() {
    this->guldenToWin = 0;
    this->weightToWin = 0;
    this->inventoryRow = 0;
    this->inventoryCol = 0;
    this->fieldRow = 0;
    this->fieldCol = 0;
    this->barnRow = 0;
    this->barnCol = 0;
}
int GameConfig::getGuldenToWin() { return this->guldenToWin; }
int GameConfig::getWeightToWin() { return this->weightToWin; }
int GameConfig::getInventoryRow() { return this->inventoryRow; }
int GameConfig::getInventoryCol() { return this->inventoryCol;}
int GameConfig::getFieldRow() { return this->fieldRow; }
int GameConfig::getFieldCol() { return this->fieldCol; }
int GameConfig::getBarnRow() { return this->barnRow; }
int GameConfig::getBarnCol() { return this->barnCol; }
void GameConfig::setGameConfig(int _guldenToWin, int _weightToWin, int _inventoryRow, int _inventoryCol, int _fieldRow, int _fieldCol, int _barnRow, int _barnCol) {
    this->guldenToWin = _guldenToWin;
    this->weightToWin = _weightToWin;
    this->inventoryRow = _inventoryRow;
    this->inventoryCol = _inventoryCol;
    this->fieldRow = _fieldRow;
    this->fieldCol = _fieldCol;
    this->barnRow = _barnRow;
    this->barnCol = _barnCol;
}


// CropConfig
CropConfig::CropConfig() {}
CropConfig::~CropConfig() {}
void CropConfig::addCropConfig(string code, Crop config) {
    this->config.insert(make_pair(code, config));
}
map<string, Crop>& CropConfig::getRefConfigMap() {
    return this->config;
}
Crop CropConfig::getConfig(string code) {
    return this->config.at(code);
}


// LivestockConfig
LivestockConfig::LivestockConfig() {}
LivestockConfig::~LivestockConfig() {}
void LivestockConfig::addOmnivoreConfig(string code, shared_ptr<Omnivore> config) {
    this->config.insert(make_pair(code, config));
}
void LivestockConfig::addCarnivoreConfig(string code, shared_ptr<Carnivore> config) {
    this->config.insert(make_pair(code, config));
}
void LivestockConfig::addHerbivoreConfig(string code, shared_ptr<Herbivore> config) {
    this->config.insert(make_pair(code, config));
}
map<string, shared_ptr<Livestock>>& LivestockConfig::getRefConfigMap() {
    return this->config;
}
shared_ptr<Livestock> LivestockConfig::getConfig(string code) {
    return this->config.at(code);
}


// ConsumableConfig
ConsumableConfig::ConsumableConfig() {}
ConsumableConfig::~ConsumableConfig() {}
void ConsumableConfig::addConsumableConfig(string code, Consumable config) {
    this->config.insert(make_pair(code, config));
}
map<string, Consumable>& ConsumableConfig::getRefConfigMap() {
    return this->config;
};
Consumable ConsumableConfig::getConfig(string code) {
    return this->config.at(code);
}


// BuildingConfig
BuildingConfig::BuildingConfig() {}
BuildingConfig::~BuildingConfig() {}
void BuildingConfig::addBuildingConfig(string code, Building config) {
    this->config.insert(make_pair(code, config));
}
Building BuildingConfig::getConfig(string code) {
    return this->config.at(code);
}
