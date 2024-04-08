#include "header/Livestock.hpp"
#include "header/Item.hpp"
#include "header/Config.hpp"
#include "pcolor/pcolor.h"
using namespace std;

Livestock::Livestock() : Item::Item(){
    currentWeight = 0;
    harvestWeight = 0;
    harvestResult = {};
}

Livestock::Livestock(int id, string code, string name, string type, int price, int currentWeight, LivestockConfig livestockConfig) 
    : Item::Item(id, code, name, type, price), harvestWeight(getHarvestWeightFromConfig(code, livestockConfig)), currentWeight(0) {}

Livestock::~Livestock() {}

Livestock::Livestock(const Livestock& other): Item(other), currentWeight(other.currentWeight), harvestWeight(other.harvestWeight) {
    for (const Consumable& c : other.harvestResult) {
        harvestResult.push_back(c);
    }
}

int Livestock::getCurrentWeight(){
    return currentWeight;
}

int Livestock::getHarvestWeight(){
    return harvestWeight;
}

int Livestock::getHarvestWeightFromConfig(string code, LivestockConfig configLivestock){
    return configLivestock.getConfig(code).harvestWeight;
}

vector<Consumable> Livestock::getHarvestResult(){
    return harvestResult;
}

void Livestock::setCurrentWeight(int currentWeight){
    this->currentWeight = currentWeight;
}

void Livestock::setHarvestWeight(int harvestWeight){
    this->harvestWeight = harvestWeight;
}

void Livestock::setHarvestResult(vector<Consumable>& harvestResult) {
    this->harvestResult = harvestResult;
}

void Livestock::eat(Consumable food){
    this->setCurrentWeight(this->getCurrentWeight() + food.getAddedWeight());
}

vector<Consumable> Livestock::harvest(Consumable newHarvestResult){
    vector<Consumable> temp = this->getHarvestResult();
    temp.push_back(newHarvestResult);
    setHarvestResult(temp);
    return harvestResult;
}

ostream& operator<<(ostream& os, const Livestock& livestock) {
    if (livestock.currentWeight < livestock.harvestWeight) {
        string str = livestock.code;
        for(int i = 0; i < str.length(); i++){
            print_red(str[i]);
        }
    } else {
        string str = livestock.code;
        for(int i = 0; i < str.length(); i++){
            print_green(str[i]);
        }
    }
    return os;
}