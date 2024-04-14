#include "../../header/Carnivore.hpp"
#include "../../header/Exception.hpp"
using namespace std;

Carnivore::Carnivore() : Livestock::Livestock(){}

Carnivore::Carnivore(int id, string code, string name, string type, int price, int currentWeight, int harvestWeight)
    : Livestock::Livestock(id, code, name, type, price, currentWeight, harvestWeight) {}

Carnivore::~Carnivore() {}

Carnivore::Carnivore(const Carnivore& carnivore): Livestock::Livestock(carnivore) {}

void Carnivore::eat(Consumable food){
    if(food.getType() == "PRODUCT_ANIMAL"){
        addCurrentWeight(food.getAddedWeight());
    }
    else if (food.getType() == "PRODUCT_MATERIAL_PLANT"){
        throw EatMaterialException();
    }
    else{
        throw CarnivoresEatPlantsException();
    }
}
