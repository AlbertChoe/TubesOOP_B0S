#include "../../header/Consumable.hpp"
#include "../../header/Item.hpp"
#include "../../header/Config.hpp"
using namespace std;

Consumable::Consumable(): Item(){
    origin = "";
    addedWeight = 0;
}

Consumable::Consumable(int id, string code, string name, string type, int price, string origin, int addedWeight)
    : Item::Item(id, code, name, type, price), origin(origin), addedWeight(addedWeight) {}

Consumable::~Consumable() {}

Consumable::Consumable(const Consumable& consumable): Item(consumable), origin(consumable.origin), addedWeight(consumable.addedWeight) {}

string Consumable::getOrigin(){
    return origin;
}

int Consumable::getAddedWeight(){
    return addedWeight;
}

void Consumable::setOrigin(string origin){
    this->origin = origin;
}

void Consumable::setAddedWeight(int addedWeight){
    this->addedWeight = addedWeight;
}

ItemType Consumable::getItemType() {
    return ItemType::Consumable;
}