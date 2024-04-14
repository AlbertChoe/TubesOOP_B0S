#include "../../header/Herbivore.hpp"
#include "../../header/Exception.hpp"
using namespace std;

Herbivore::Herbivore() : Livestock::Livestock(){}

Herbivore::Herbivore(int id, string code, string name, string type, int price, int currentWeight, int harvestWeight)
    : Livestock::Livestock(id, code, name, type, price, currentWeight, harvestWeight) {}

Herbivore::~Herbivore() {}

Herbivore::Herbivore(const Herbivore& herbivore): Livestock::Livestock(herbivore) {}

void Herbivore::eat(Consumable food){
    if(food.getType() == "PRODUCT_FRUIT_PLANT"){
        addCurrentWeight(food.getAddedWeight());
    }
    else if (food.getType() == "PRODUCT_MATERIAL_PLANT"){
        throw EatMaterialException();
    }
    else{
        throw HerbivoresEatMeatException();
    }
}
