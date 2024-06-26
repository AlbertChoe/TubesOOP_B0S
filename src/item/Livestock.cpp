#include "../../header/Livestock.hpp"
#include "../../header/Item.hpp"
#include "../../header/Config.hpp"

using namespace std;

Livestock::Livestock() : Item::Item(){
    currentWeight = 0;
    harvestWeight = 0;
}

Livestock::Livestock(int id, string code, string name, string type, int price, int currentWeight, int harvestWeight) 
    : Item::Item(id, code, name, type, price),  currentWeight(0), harvestWeight(harvestWeight) {}

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

void Livestock::addHarvestResult(Consumable result) {
    this->harvestResult.push_back(result);
}

// void Livestock::eat(int weight){
//     this->setCurrentWeight(this->getCurrentWeight() + weight);
// }

ostream& operator<<(ostream& os, const Livestock& livestock) {
    if (livestock.currentWeight < livestock.harvestWeight) {
        string str = livestock.code;
        for(int i = 0; i < (int) str.length(); i++){
            print_red(str[i]);
        }
    } else {
        string str = livestock.code;
        for(int i = 0; i < (int) str.length(); i++){
            print_green(str[i]);
        }
    }
    return os;
}

bool Livestock::isReadyToHarvest(){
    return this->currentWeight >= this->harvestWeight;
}

ItemType Livestock::getItemType() {
    return ItemType::Livestock;
}