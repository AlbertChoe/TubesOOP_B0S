#include "header/Herbivore.hpp"
#include "header/Exception.hpp"
using namespace std;

Herbivore::Herbivore() : Livestock::Livestock(){}

Herbivore::Herbivore(int id, string code, string name, string type, int price, int currentWeight, LivestockConfig livestockConfig)
    : Livestock::Livestock(id, code, name, type, price, currentWeight, livestockConfig) {}

Herbivore::~Herbivore() {}

Herbivore::Herbivore(const Herbivore& herbivore): Livestock::Livestock(herbivore) {}

void Herbivore::eat(Consumable food){
    if(food.getType() == "PRODUCT_FRUIT_PLANT"){
        Livestock::eat(food);
    }
    else if (food.getType() == "PRODUCT_MATERIAL_PLANT"){
        throw EatMaterialException();
    }
    else{
        throw HerbivoresEatMeatException();
    }
}

vector<Consumable> Herbivore::harvest(ConsumableConfig configConsumable){
    if(this->getCurrentWeight() < this->getHarvestWeight()){
        throw HarvestNotReadyException();
    }
    else{
        int harvestID, harvestPrice, harvestAddedWeight;
        string harvestCode, harvestName, harvestType, harvestOrigin;

        if (this->getCode() == "COW"){
            harvestID = this->getHarvestResult().size() + 1;
            harvestCode = "COM";
            Consumable consumable = configConsumable.getConfig(harvestCode);
            harvestName = "COW_MEAT";
            harvestType = "PRODUCT_ANIMAL";
            harvestPrice = consumable.getPrice();
            harvestOrigin = consumable.getOrigin();
            harvestAddedWeight = consumable.getAddedWeight();
        }
        else if (this->getCode() == "SHP"){
            harvestID = this->getHarvestResult().size() + 1;
            harvestCode = "SHM";
            Consumable consumable = configConsumable.getConfig(harvestCode);
            harvestName = "SHEEP_MEAT";
            harvestType = "PRODUCT_ANIMAL";
            harvestPrice = consumable.getPrice();
            harvestOrigin = consumable.getOrigin();
            harvestAddedWeight = consumable.getAddedWeight();
        }
        else if (this->getCode() == "HRS"){
            harvestID = this->getHarvestResult().size() + 1;
            harvestCode = "HRM";
            Consumable consumable = configConsumable.getConfig(harvestCode);
            harvestName = "HORSE_MEAT";
            harvestType = "PRODUCT_ANIMAL";
            harvestPrice = consumable.getPrice();
            harvestOrigin = consumable.getOrigin();
            harvestAddedWeight = consumable.getAddedWeight();
        }
        else if (this->getCode() == "RBT"){
            harvestID = this->getHarvestResult().size() + 1;
            harvestCode = "RBM";
            Consumable consumable = configConsumable.getConfig(harvestCode);
            harvestName = "RABBIT_MEAT";
            harvestType = "PRODUCT_ANIMAL";
            harvestPrice = consumable.getPrice();
            harvestOrigin = consumable.getOrigin();
            harvestAddedWeight = consumable.getAddedWeight();
        }
        Consumable newHarvest = Consumable(harvestID, harvestCode, harvestName, harvestType, harvestPrice, harvestOrigin, configConsumable);
        return Livestock::harvest(newHarvest);
    }
}