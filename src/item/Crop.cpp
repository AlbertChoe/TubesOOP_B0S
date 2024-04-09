#include "../../header/Crop.hpp"
#include "../../header/Config.hpp"
#include "../pcolor/pcolor.h"
#include "../../header/Exception.hpp"
#include "../../header/Consumable.hpp"

using namespace std;

Crop::Crop() : Item::Item(){
    currentDuration = 0;
    harvestDuration = 0;
}

Crop::Crop(int id, string code, string name, string type, int price, int currentDuration, CropConfig cropConfig) 
    : Item::Item(id, code, name, type, price), currentDuration(0), harvestDuration(getHarvestDuration(code, cropConfig)) {}

Crop::Crop(int id, string code, string name, string type, int price, int currentDuration, int harvestDuration) 
    : Item::Item(id, code, name, type, price), currentDuration(0), harvestDuration(harvestDuration) {}

Crop::~Crop() {}

Crop::Crop(const Crop& other) : Item(other), currentDuration(other.currentDuration), harvestDuration(other.harvestDuration) {
    for (const Consumable& c : other.harvestResult) {
        harvestResult.push_back(c);
    }
}

int Crop::getCurrentDuration(){
    return currentDuration;
}

int Crop::getHarvestDuration(string code, CropConfig configCrop){
    Crop crop = configCrop.getConfig(code);
    return crop.harvestDuration;
}

vector<Consumable> Crop::getHarvestResult(){
    return harvestResult;
}

void Crop::setCurrentDuration(int currentDuration){
    this->currentDuration = currentDuration;
}

void Crop::setHarvestDuration(int harvestDuration){
    this->harvestDuration = harvestDuration;
}

void Crop::setHarvestResult(vector<Consumable>& harvestResult) {
    this->harvestResult = harvestResult;
}

void Crop::addHarvestResult(Consumable result) {
    this->harvestResult.push_back(result);
}

void Crop::incrementDuration(){
    this->currentDuration += 1;
}

vector<Consumable> Crop::harvest(ConsumableConfig configConsumable){
    if(!isReadyToHarvest()){
        throw HarvestNotReadyException();
    }
    else{
        int harvestID, harvestPrice, harvestAddedWeight;
        string harvestCode, harvestName, harvestType, harvestOrigin;

        if (this->getCode() == "TEK"){
            harvestID = this->getHarvestResult().size() + 1;
            harvestCode = "TAW";
            Consumable consumable = configConsumable.getConfig(harvestCode);
            harvestName = "TEAK_WOOD";
            harvestType = "PRODUCT_MATERIAL_PLANT";
            harvestPrice = consumable.getPrice();
            harvestOrigin = consumable.getOrigin();
            harvestAddedWeight = consumable.getAddedWeight();
        }
        else if (this->getCode() == "SDT"){
            harvestID = this->getHarvestResult().size() + 1;
            harvestCode = "SAW";
            Consumable consumable = configConsumable.getConfig(harvestCode);
            harvestName = "SANDALWOOD_WOOD";
            harvestType = "PRODUCT_MATERIAL_PLANT";
            harvestPrice = consumable.getPrice();
            harvestOrigin = consumable.getOrigin();
            harvestAddedWeight = consumable.getAddedWeight();
        }
        else if (this->getCode() == "ALT"){
            harvestID = this->getHarvestResult().size() + 1;
            harvestCode = "ALW";
            Consumable consumable = configConsumable.getConfig(harvestCode);
            harvestName = "ALOE_WOOD";
            harvestType = "PRODUCT_MATERIAL_PLANT";
            harvestPrice = consumable.getPrice();
            harvestOrigin = consumable.getOrigin();
            harvestAddedWeight = consumable.getAddedWeight();
        }
        else if (this->getCode() == "IRN"){
            harvestID = this->getHarvestResult().size() + 1;
            harvestCode = "IRW";
            Consumable consumable = configConsumable.getConfig(harvestCode);
            harvestName = "IRONWOOD_WOOD";
            harvestType = "PRODUCT_MATERIAL_PLANT";
            harvestPrice = consumable.getPrice();
            harvestOrigin = consumable.getOrigin();
            harvestAddedWeight = consumable.getAddedWeight();
        }
        else if (this->getCode() == "APL"){
            harvestID = this->getHarvestResult().size() + 1;
            harvestCode = "APP";
            Consumable consumable = configConsumable.getConfig(harvestCode);
            harvestName = "APPLE";
            harvestType = "PRODUCT_FRUIT_PLANT";
            harvestPrice = consumable.getPrice();
            harvestOrigin = consumable.getOrigin();
            harvestAddedWeight = consumable.getAddedWeight();
        }
        else if (this->getCode() == "ORG"){
            harvestID = this->getHarvestResult().size() + 1;
            harvestCode = "ORG";
            Consumable consumable = configConsumable.getConfig(harvestCode);
            harvestName = "ORANGE";
            harvestType = "PRODUCT_FRUIT_PLANT";
            harvestPrice = consumable.getPrice();
            harvestOrigin = consumable.getOrigin();
            harvestAddedWeight = consumable.getAddedWeight();
        }
        else if (this->getCode() == "BNT"){
            harvestID = this->getHarvestResult().size() + 1;
            harvestCode = "BNP";
            Consumable consumable = configConsumable.getConfig(harvestCode);
            harvestName = "BANANA";
            harvestType = "PRODUCT_FRUIT_PLANT";
            harvestPrice = consumable.getPrice();
            harvestOrigin = consumable.getOrigin();
            harvestAddedWeight = consumable.getAddedWeight();
        }
        else if (this->getCode() == "GAV"){
            harvestID = this->getHarvestResult().size() + 1;
            harvestCode = "GAP";
            Consumable consumable = configConsumable.getConfig(harvestCode);
            harvestName = "GUAVA";
            harvestType = "PRODUCT_FRUIT_PLANT";
            harvestPrice = consumable.getPrice();
            harvestOrigin = consumable.getOrigin();
            harvestAddedWeight = consumable.getAddedWeight();
        }
        Consumable newHarvest = Consumable(harvestID, harvestCode, harvestName, harvestType, harvestPrice, harvestOrigin, configConsumable);
        vector<Consumable> temp = this->getHarvestResult();
        temp.push_back(newHarvest);
        setHarvestResult(temp);
        return temp;
    }
}

ostream& operator<<(ostream& os, const Crop& crop) {
    if (crop.currentDuration < crop.harvestDuration) {
        string str = crop.code;
        for(int i = 0; i < str.length(); i++){
            print_red(str[i]);
        }
    } else {
        string str = crop.code;
        for(int i = 0; i < str.length(); i++){
            print_green(str[i]);
        }
    }
    return os;
}
    
bool Crop::isReadyToHarvest(){
    return this->currentDuration >= this->harvestDuration;
}