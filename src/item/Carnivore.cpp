#include "../../header/Carnivore.hpp"
#include "../../header/Exception.hpp"
using namespace std;

Carnivore::Carnivore() : Livestock::Livestock(){}

Carnivore::Carnivore(int id, string code, string name, string type, int price, int currentWeight, LivestockConfig livestockConfig)
    : Livestock::Livestock(id, code, name, type, price, currentWeight, livestockConfig) {}

Carnivore::Carnivore(int id, string code, string name, string type, int price, int currentWeight, int harvestWeight)
    : Livestock::Livestock(id, code, name, type, price, currentWeight, harvestWeight) {}

Carnivore::~Carnivore() {}

Carnivore::Carnivore(const Carnivore& carnivore): Livestock::Livestock(carnivore) {}

void Carnivore::eat(Consumable food){
    if(food.getType() == "PRODUCT_ANIMAL"){
        Livestock::eat(food.getAddedWeight());
    }
    else if (food.getType() == "PRODUCT_MATERIAL_PLANT"){
        throw EatMaterialException();
    }
    else{
        throw CarnivoresEatPlantsException();
    }
}

vector<Consumable> Carnivore::harvest(ConsumableConfig configConsumable){
    if(!isReadyToHarvest()){
        throw HarvestNotReadyException();
    }
    else{
        int harvestID, harvestPrice, harvestAddedWeight;
        string harvestCode, harvestName, harvestType, harvestOrigin;

        if (this->getCode() == "SNK"){
            harvestID = this->getHarvestResult().size() + 1;
            harvestCode = "SNM";
            Consumable consumable = configConsumable.getConfig(harvestCode);
            harvestName = "SNAKE_MEAT";
            harvestType = "PRODUCT_ANIMAL";
            harvestPrice = consumable.getPrice();
            harvestOrigin = consumable.getOrigin();
            harvestAddedWeight = consumable.getAddedWeight();
        }

        Consumable newHarvest = Consumable(harvestID, harvestCode, harvestName, harvestType, harvestPrice, harvestOrigin, configConsumable);
        return Livestock::harvest(newHarvest);
    }
}