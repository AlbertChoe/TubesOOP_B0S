#include "../../header/Crop.hpp"
#include "../../header/Config.hpp"
#include "../../header/Exception.hpp"
#include "../../header/Consumable.hpp"

using namespace std;


Crop::Crop() : Item::Item(){
    currentDuration = 0;
    harvestDuration = 0;
}

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

int Crop::getHarvestDuration(){
    return harvestDuration;
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

ostream& operator<<(ostream& os, const Crop& crop) {
    if (crop.currentDuration < crop.harvestDuration) {
        string str = crop.code;
        for(int i = 0; i < (int) str.length(); i++){
            print_red(str[i]);
        }
    } else {
        string str = crop.code;
        for(int i = 0; i < (int) str.length(); i++){
            print_green(str[i]);
        }
    }
    return os;
}
    
bool Crop::isReadyToHarvest(){
    return this->currentDuration >= this->harvestDuration;
}

ItemType Crop::getItemType() {
    return ItemType::Crop;
}