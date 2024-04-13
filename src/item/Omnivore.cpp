#include "header/Omnivore.hpp"
#include "header/Exception.hpp"
using namespace std;

Omnivore::Omnivore() : Livestock::Livestock(){}

Omnivore::Omnivore(int id, string code, string name, string type, int price, int currentWeight, int harvestWeight)
    : Livestock::Livestock(id, code, name, type, price, currentWeight, harvestWeight) {}

Omnivore::~Omnivore() {}

Omnivore::Omnivore(const Omnivore& omnivore): Livestock::Livestock(omnivore) {}

void Omnivore::eat(Consumable food){
    if(food.getType() == "PRODUCT_ANIMAL" || food.getType() == "PRODUCT_FRUIT_PLANT"){
        Livestock::eat(food.getAddedWeight());
    }
    else if (food.getType() == "PRODUCT_MATERIAL_PLANT"){
        throw EatMaterialException();
    }
}

vector<Consumable> Omnivore::harvest(ConsumableConfig configConsumable){
    if(!isReadyToHarvest()){
        throw HarvestNotReadyException();
    }
    else{
        int harvestID1, harvestPrice1, harvestAddedWeight1;
        string harvestCode1, harvestName1, harvestType1, harvestOrigin1;

        int harvestID2, harvestPrice2, harvestAddedWeight2;
        string harvestCode2, harvestName2, harvestType2, harvestOrigin2;

        if (this->getCode() == "CHK"){
            harvestID1 = this->getHarvestResult().size() + 1;
            harvestCode1 = "CHM";
            Consumable consumable1 = configConsumable.getConfig(harvestCode1);
            harvestName1 = "CHICKEN_MEAT";
            harvestType1 = "PRODUCT_ANIMAL";
            harvestPrice1 = consumable1.getPrice();
            harvestOrigin1 = consumable1.getOrigin();
            harvestAddedWeight1 = consumable1.getAddedWeight();

            harvestID2 = this->getHarvestResult().size() + 1;
            harvestCode2 = "CHE";
            Consumable consumable2 = configConsumable.getConfig(harvestCode2);
            harvestName2 = "CHICKEN_EGG";
            harvestType2 = "PRODUCT_ANIMAL";
            harvestPrice2 = consumable2.getPrice();
            harvestOrigin2 = consumable2.getOrigin();
            harvestAddedWeight2 = consumable2.getAddedWeight();
        }
        else if (this->getCode() == "DCK"){
            harvestID1 = this->getHarvestResult().size() + 1;
            harvestCode1 = "DCM";
            Consumable consumable1 = configConsumable.getConfig(harvestCode1);
            harvestName1 = "DUCK_MEAT";
            harvestType1 = "PRODUCT_ANIMAL";
            harvestPrice1 = consumable1.getPrice();
            harvestOrigin1 = consumable1.getOrigin();
            harvestAddedWeight1 = consumable1.getAddedWeight();

            harvestID2 = this->getHarvestResult().size() + 1;
            harvestCode2 = "DCE";
            Consumable consumable2 = configConsumable.getConfig(harvestCode2);
            harvestName2 = "DUCK_EGG";
            harvestType2 = "PRODUCT_ANIMAL";
            harvestPrice2 = consumable2.getPrice();
            harvestOrigin2 = consumable2.getOrigin();
            harvestAddedWeight2 = consumable2.getAddedWeight();
        }

        Consumable newHarvest1 = Consumable(harvestID1, harvestCode1, harvestName1, harvestType1, harvestPrice1, harvestOrigin1, configConsumable);
        Consumable newHarvest2 = Consumable(harvestID2, harvestCode2, harvestName2, harvestType2, harvestPrice2, harvestOrigin2, configConsumable);
        vector<Consumable> temp = Livestock::harvest(newHarvest1);
        temp.push_back(newHarvest2);
        setHarvestResult(temp);
        return temp;
    }
}