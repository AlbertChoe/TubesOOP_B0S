#ifndef MAYOR_HPP
#define MAYOR_HPP

#include "Player.hpp"
#include "Breeder.hpp"
#include "Farmer.hpp"
#include "Utils.hpp"
#include "Config.hpp"
#include "Exception.hpp"
#include <vector>
using namespace std;

class Mayor : public Player {
public:
    Mayor( string name, int InventoryRow, int InventoryCol): Player(name,InventoryRow,InventoryCol) {}
    Mayor( string name, int weight, int gulden, int InventoryRow, int InventoryCol): Player(name,gulden,weight,InventoryRow,InventoryCol) {}
    void addNewPlayer(vector<shared_ptr<Player>>& players, GameConfig gameConfig);
    void collectTax(vector<shared_ptr<Player>>& players);
    void buildBuilding(const BuildingConfig& recipe);
    int getTaxable();
    PlayerType getType();
};

#endif