#include "../../header/Omnivore.hpp"
#include "../../header/Exception.hpp"
using namespace std;

Omnivore::Omnivore() : Livestock::Livestock(){}

Omnivore::Omnivore(int id, string code, string name, string type, int price, int currentWeight, int harvestWeight)
    : Livestock::Livestock(id, code, name, type, price, currentWeight, harvestWeight) {}

Omnivore::~Omnivore() {}

Omnivore::Omnivore(const Omnivore& omnivore): Livestock::Livestock(omnivore) {}

void Omnivore::eat(Consumable food){
    if(food.getType() == "PRODUCT_ANIMAL" || food.getType() == "PRODUCT_FRUIT_PLANT"){
        addCurrentWeight(food.getAddedWeight());
    }
    else if (food.getType() == "PRODUCT_MATERIAL_PLANT"){
        throw EatMaterialException();
    }
}
